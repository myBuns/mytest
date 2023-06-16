#include "addnum.h"
#include <QThread>
#include <QDebug>

extern int i;
extern QVector<int> vec;

void AddNum::run()
{
    QThread::msleep(1);
    mutex.lock();
    vec[i] = i;
    qDebug() << vec.at(i++) << QThread::currentThreadId();
    mutex.unlock();
}
