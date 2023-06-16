#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>

class myLabel:public QLabel
{
    Q_OBJECT
public:
    myLabel(QWidget *parent = nullptr);
public slots:
    void setStrNum(const QString &str);
};

#endif // MYLABEL_H
