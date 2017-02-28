#ifndef STATUSRECEIVER_H
#define STATUSRECEIVER_H

#include <QThread>

class StatusReceiver : public QThread
{
    Q_OBJECT
public:
    explicit StatusReceiver(QObject *parent = 0);

public Q_SLOTS:

};

#endif // STATUSRECEIVER_H
