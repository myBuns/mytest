#include "seacherform.h"
#include "ui_seacherform.h"

SeacherForm::SeacherForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SeacherForm)
{
    ui->setupUi(this);
}

SeacherForm::~SeacherForm()
{
    delete ui;
}

void SeacherForm::setLineText(const QString &str)
{
    ui->lineEdit->setText(str);
}
