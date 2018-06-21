#include <QtWidgets/QtWidgets>
#include <QtNetwork>
#include "BTCChange.hpp"
#include "BTCCAgent.hpp"

int main( int argc, char **argv )
{
    QApplication app(argc, argv);

    QLCDNumber *lcd = new QLCDNumber;
    lcd->setDigitCount(10);

    QPushButton *exitButton = new QPushButton("&Exit");
    QLabel *label = new QLabel();

    BTCChange btcchange;
    BTCCAgent btccagent("https://www.bitstamp.net/api/v2/ticker/btceur/",
                        "last",
                        "The current BTC/EUR change at %1 is:");

    // Connect the btc change model (BTCChange) to the view (lcd display)
    QObject::connect(&btcchange, SIGNAL(changeUpdated(double)), lcd, SLOT(display(double)));

    // Connect the agent that retrieve the change value to the btc change model
    QObject::connect(&btccagent, SIGNAL(changeRetrieved(double)), &btcchange, SLOT(setChange(double)));

    // Connect the agent to the ui label to display info message or errors
    QObject::connect(&btccagent, SIGNAL(changeMessage(QString)), label, SLOT(setText(QString)));

    // Connect the exit button to the app quit slot
    QObject::connect(exitButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    // Retrieve the change from the api
    btccagent.retrieveChange();

    // Set the timer to update the change each 10 secs
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &btccagent, SLOT(retrieveChange()));
    timer->start(10000);

    // UI Stuff..
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(lcd);
    layout->addWidget(exitButton);

    QWidget window;
    window.setLayout(layout);
    window.resize(500, 200);

    window.show();

    return app.exec();
}
