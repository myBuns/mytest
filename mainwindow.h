#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <QUdpSocket>
#include <QVector>
#include "mytextedit.h"
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void strNum(const QString &str);

private:
    void InitUI();
    void CalaStrNum();
    bool isAvail(int index);     //看当前tab是否可用
    void ConnectSignal(myTextEdit *edit);
private slots:
    void onNewFile();
    void onCloseTab();
    void onOpenFile();
    void onSave();

private:
    Ui::MainWindow *ui;
    int num = 0;
    int StrNum = 0;
    QVector<myTextEdit*> m_vec;
};
#endif // MAINWINDOW_H
