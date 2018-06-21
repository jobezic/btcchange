#include <QtTest>
#include "../src/BTCCAgent.hpp"

class BTCCAgentTest : public QObject
{
    Q_OBJECT

    public slots:
        void testResponse(double change) {
          QVERIFY(change > 0);
    }

    private slots:
        void test() {
            BTCCAgent agent("https://www.bitstamp.net/api/v2/ticker/btceur/",
                            "last",
                            "The current BTC/EUR change at %1 is:");

            QObject::connect(&agent, SIGNAL(changeRetrieved(double)), this, SLOT(testResponse(double)));

            agent.retrieveChange();
        }
};
