/*!
  \class BTCCAgent
  \brief The BTCCAgent class represents an agent for retrieving the currency
  change from a json api.
 */

#include <QtGui>
#include <QtNetwork>

class BTCCAgent : public QObject
{
    Q_OBJECT

    public:
        BTCCAgent(const char*, const char*, const char*);
        void setTimeout(int);

    public slots:
        void retrieveChange();

    signals:
        void changeRetrieved(double);
        void changeMessage(QString);

    private:
        QString url;
        QString changeProperty;
        int networkTimeout;
        QString actualChangeMsg;
};
