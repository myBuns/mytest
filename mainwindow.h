#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThreadPool>
#include <QUdpSocket>
#include <QVector>
#include "mytextedit.h"
#include <QIcon>
#include <QFontDialog>
#include <QString>
#include <QFont>
#include <QTextCodec>

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
    bool isAvail(int index);     //看当前tab是否可用,包含返回true
    void ConnectSignal(myTextEdit *edit);   //循环链接pushbtn
    void SaveDataToFile(const QString &filePath);
private slots:
    void onNewFile();
    void onCloseTab();
    void onOpenFile();
    void onSave();
    void SetFontLabelStatus(const QFont font, const QString &string);//设置状态栏字体状态
    void ShowFontDialog();  //显示字体窗口
    void onSavethis();      //保存
    QString ReturnFilePath(QString fileName);

private:
    Ui::MainWindow *ui;
    int num = 0;
    int StrNum = 0;
    QVector<myTextEdit*> m_vec;
    const QString TableStr = "tab";
    QVector<QString> filepathList;
    //QTextCodec TextCodec;
};
#endif // MAINWINDOW_H
