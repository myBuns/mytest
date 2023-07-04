#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QPushButton>
#include <QVector>
#include <QByteArray>
#include <QTextEdit>
#include "mylabel.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QToolBar>
#include <QHBoxLayout>
#include <QPixmap>
#include <QKeySequence>
#include <QShortcut>
#include <QThread>
#include <QComboBox>

QVector<int> vec(50,0);
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    this->InitUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitUI()
{
    //设置title
    this->setWindowTitle(QString("Text Editor"));
    this->setWindowIcon(QIcon("qrc:/buns.jpg"));

    //初始化ToolBar
    QToolBar* toolbar = new QToolBar(this);
    toolbar->setObjectName("toolbar");
    QPushButton *bold = new QPushButton("Bold", toolbar);
    QPushButton *italic = new QPushButton("Italic", toolbar);
    QPushButton *underline = new QPushButton("Underline", toolbar);

    toolbar->addWidget(bold);
    toolbar->addWidget(italic);
    toolbar->addWidget(underline);

    this->addToolBar(toolbar);

    //初始化tab
    myTextEdit *textEdit = new myTextEdit(this);
    connect(textEdit,&myTextEdit::textChanged,this,&MainWindow::CalaStrNum);
    ui->tabWidget->addTab(textEdit,QString("tab%1").arg(++this->num));
    this->ConnectSignal(textEdit);

    //初始化状态栏
    myLabel *label = new myLabel(ui->statusbar);
    connect(this,&MainWindow::strNum,label,&myLabel::setStrNum);
    QPushButton *FontLabel = new QPushButton(ui->statusbar);
    FontLabel->setFlat(true);
    this->SetFontLabelStatus(this->font(),this->fontInfo().family());
    QComboBox *comboBox = new QComboBox(ui->statusbar);

    comboBox->addItem("UTF-8");
    comboBox->addItem("ASCII");
    comboBox->addItem("ISO-8859-1");


    //链接字体dialog
    connect(FontLabel,&QPushButton::clicked,this,&MainWindow::ShowFontDialog);

    ui->statusbar->addWidget(label);
    ui->statusbar->addWidget(FontLabel);
    ui->statusbar->addWidget(comboBox);

    QKeySequence sequeue = ui->savethis->shortcut();
    QShortcut *shortcut = new QShortcut(sequeue, this);

    //action信号槽
    connect(ui->newfile,&QAction::triggered,this,&MainWindow::onNewFile);
    connect(ui->closeTab,&QAction::triggered,this,&MainWindow::onCloseTab);
    connect(ui->open,&QAction::triggered,this,&MainWindow::onOpenFile);
    connect(ui->save,&QAction::triggered,this,&MainWindow::onSave);
    // 连接快捷方式的activated()信号到相应的槽函数
    connect(shortcut, &QShortcut::activated, this,&MainWindow::onSavethis);

    //切换tab时统计字数
    connect(ui->tabWidget,&QTabWidget::currentChanged,this,&MainWindow::CalaStrNum);
}

void MainWindow::CalaStrNum()
{
    qDebug() << ui->tabWidget->currentIndex();
    myTextEdit *edit = qobject_cast<myTextEdit*>(ui->tabWidget->currentWidget());
    emit strNum(QString::number(edit->toPlainText().size()));
}

bool MainWindow::isAvail(int index)
{
    return ui->tabWidget->tabText(index).contains(this->TableStr);
}

void MainWindow::ConnectSignal(myTextEdit *edit)
{
    QToolBar *foundToolbar = this->findChild<QToolBar*>("toolbar");
    if(foundToolbar) {
        QObjectList btnList = foundToolbar->children();
        foreach (auto btnVar, btnList) {
            //qDebug() << btnVar->metaObject()->className();
            if(btnVar->metaObject()->className() == QString("QPushButton").toStdString())
            {
                QPushButton* btn = qobject_cast<QPushButton*>(btnVar);
                if(btn->text() == "Bold") {
                    connect(btn,&QPushButton::clicked,edit,&myTextEdit::onBold);
                }

                if(btn->text() == "Underline")
                {
                    connect(btn,&QPushButton::clicked,edit,&myTextEdit::onUnderline);
                }

                if(btn->text() == "Italic")
                {
                    connect(btn,&QPushButton::clicked,edit,&myTextEdit::onItalic);
                }
            }
        }
    }
}

void MainWindow::SaveDataToFile(const QString &filePath)
{
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            out.setCodec(codec);
            QString fileContent = qobject_cast<myTextEdit*>(ui->tabWidget->currentWidget())->toPlainText();
            out << fileContent;
            file.close();
            QMessageBox::information(nullptr, "Success", "File saved successfully.");
        } else {
            QMessageBox::warning(nullptr, "Error", "Failed to save file: " + file.errorString());
        }
    }
    else {
        QMessageBox::warning(nullptr, "Error", "file is no exit: ");
    }
}

void MainWindow::onCloseTab()
{
    if(ui->tabWidget->count() == 1)
    {
        QMessageBox::warning(nullptr, "Error", "至少保留一个tab!");
        return;
    }
    ui->tabWidget->removeTab(ui->tabWidget->currentIndex());
}

void MainWindow::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(nullptr, "Open File", "C:\\Users\\worker\\Desktop", "TXT Files (*.txt)");
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        QFileInfo info(file);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            QTextStream in(&file);
            in.setCodec(codec);
            QString fileContent = in.readAll();
            file.close();

            // 在这里可以使用 fileContent 进行操作
            // 例如，将文件内容显示在 myTextEdit 中

            if( this->isAvail(ui->tabWidget->currentIndex()) )
            {
                ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),info.fileName());
                myTextEdit *edit = qobject_cast<myTextEdit*>(ui->tabWidget->currentWidget());
                edit->setText(fileContent);
            }
            else {
                onNewFile();
                int index = ui->tabWidget->currentIndex() + 1;
                ui->tabWidget->setTabText(index,info.fileName());
                myTextEdit *edit = qobject_cast<myTextEdit*>(ui->tabWidget->widget(index));
                edit->setText(fileContent);
            }
        } else {
            QMessageBox::warning(nullptr, "Error", "Failed to open file: " + file.errorString());
        }
    }
    this->filepathList.push_back(std::move(filePath));
}

void MainWindow::onSave()
{
    QString filePath = QFileDialog::getSaveFileName(nullptr, "Save File", "", "Text Files (*.txt)");
    if(filePath != "")
    {
        this->SaveDataToFile(filePath);
    }
}

void MainWindow::SetFontLabelStatus(const QFont font, const QString &string)
{
    QObjectList list = this->statusBar()->children();

    foreach (auto var, list) {
        if(var->metaObject()->className() == QString("QPushButton").toStdString())
        {
            QPushButton *label = qobject_cast<QPushButton*>(var);
            label->setFont(font);
            label->setText(string);
        }
    }
}

void MainWindow::ShowFontDialog()
{
    bool ret;
    QFont font = QFontDialog::getFont(&ret);
    if(ret)
        ui->tabWidget->setFont(font);
}

void MainWindow::onSavethis()
{
    if(this->isAvail(ui->tabWidget->currentIndex()))
    {
        this->onSave();
    }
    else
    {
        QString filepath = this->ReturnFilePath(ui->tabWidget->tabText(ui->tabWidget->currentIndex()));
        this->SaveDataToFile(filepath);
    }
}

QString MainWindow::ReturnFilePath(QString fileName)
{
    foreach (QString var, this->filepathList) {
        if( var.split("/").back() == fileName )
        {
            return var;
        }
    }
    return QString("");
}

void MainWindow::onNewFile()
{
    myTextEdit *textEdit = new myTextEdit(this);
    ui->tabWidget->addTab(textEdit,QString("tab%1").arg(++this->num));
    connect(textEdit,&myTextEdit::textChanged,this,&MainWindow::CalaStrNum);
    this->ConnectSignal(textEdit);
}
