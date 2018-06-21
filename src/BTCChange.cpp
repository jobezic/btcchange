#include <QtGui>
#include "BTCChange.hpp"

void BTCChange::setChange(double change) {
    if (mChange != change) {
        mChange = change;

        emit changeUpdated(change);
    }
}
