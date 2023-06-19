#ifndef SEACHERFORM_H
#define SEACHERFORM_H

#include <QWidget>
#include <QString>

namespace Ui {
class SeacherForm;
}

class SeacherForm : public QWidget
{
    Q_OBJECT

public:
    explicit SeacherForm(QWidget *parent = nullptr);
    ~SeacherForm();

    void setLineText(const QString &str);

private:
    virtual void closeEvent(QCloseEvent *event);

private:
    Ui::SeacherForm *ui;
};

#endif // SEACHERFORM_H
