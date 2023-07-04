#include "seacherform.h"
#include "ui_seacherform.h"
#include <QCloseEvent>
#include <QDebug>

//using myint8 = uchar; C++11新特性
//typedef uchar myint8;
SeacherForm::SeacherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeacherForm)
{
    ui->setupUi(this);


    connect(ui->seacher,&QPushButton::clicked,this,&SeacherForm::onSeacher);
}

SeacherForm::~SeacherForm()
{
    delete ui;
}

void SeacherForm::setLineText(const QString &str)
{
    ui->lineEdit->setText(str);
}

void SeacherForm::onSeacher()
{
    QString str = ui->lineEdit->text();
}

void SeacherForm::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    deleteLater(); // 释放内存
}
