#include "mylabel.h"

myLabel::myLabel(QWidget *parent):QLabel(parent)
{
    this->setText("character number:" + QString::number( 0 ));
}

void myLabel::setStrNum(const QString &str)
{
    this->setText("character number:" + str);
}
