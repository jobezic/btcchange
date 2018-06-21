/*!
  \class BTTChange
  \brief The BTTChange class represents a model of a currency change.
 */

#include <QtGui>

class BTCChange : public QObject
{
    Q_OBJECT

    public:
        BTCChange() {
            mChange = 0;
        }

        double last() const {
            return mChange;
        }

    public slots:
        void setChange(double);

    signals:
        void changeUpdated(double);

    private:
        int mChange;
};
