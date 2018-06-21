#include <QtGui>
#include <QtNetwork>
#include <QtScript>
#include "BTCCAgent.hpp"

BTCCAgent::BTCCAgent(const char* pUrl, const char* prop, const char* msg) :
  url(pUrl),
  changeProperty(prop),
  networkTimeout(3000),
  actualChangeMsg(msg) {
}

void BTCCAgent::setTimeout(int timeout) {
    this->networkTimeout = timeout;
}

void BTCCAgent::retrieveChange() {
    QNetworkAccessManager manager;

    QUrl url(this->url);
    QNetworkRequest request;
    request.setUrl(url);

    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop loop;

    QNetworkReply* currentReply = manager.get(request);
    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(currentReply, SIGNAL(finished()), &loop, SLOT(quit()));

    timer.start(this->networkTimeout);
    loop.exec();

    if(timer.isActive()) {
        timer.stop();
        if(currentReply->error() > 0) {
            emit changeMessage(QString("Network Error!"));
        }
        else {
          int v = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

          if (v >= 200 && v < 300) {
              QByteArray data = currentReply->readAll();
              qDebug() << "Received data:" << data;

              QJsonParseError jsonError;
              QJsonDocument jsonResponse = QJsonDocument::fromJson(data, &jsonError);

              if (jsonError.error != QJsonParseError::NoError) {
                  qDebug() << jsonError.errorString();
                  emit changeMessage(QString("Response Error!"));
              }

              QMap<QString, QVariant> map = jsonResponse.toVariant().toMap();

              if (map[this->changeProperty].isNull()) {
                  qDebug() << "Error: document property not found!";
                  emit changeMessage(QString("Response Error!"));
                  return;
              }

              emit changeMessage(QString(actualChangeMsg).arg(QTime().currentTime().toString()));
              emit changeRetrieved(map[this->changeProperty].toDouble());
          }
        }
    } else {
        qDebug() << "Timeout!";
        emit changeMessage(QString("Network Error!"));
        disconnect(currentReply, SIGNAL(finished()), &loop, SLOT(quit()));

        currentReply->abort();
    }
}
