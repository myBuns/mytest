#ifndef ADDNUM_H
#define ADDNUM_H

#include <QObject>
#include <QRunnable>
#include <QVector>
#include <QMutex>

class AddNum:public QRunnable
{
private:
    virtual void run() override;
    QMutex mutex;
};

#endif // ADDNUM_H
