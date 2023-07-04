#include "mytextedit.h"
#include <QMenu>
#include <QAction>
#include <QKeySequence>
#include <QLineEdit>
#include "seacherform.h"
#include <QShortcut>

myTextEdit::myTextEdit(QWidget *parent)
    : QTextEdit(parent)
{

    // 创建上下文菜单
    this->contextMenu = new QMenu(this);

    // 添加默认的右键菜单操作
    this->contextMenu->addActions(QTextEdit::createStandardContextMenu()->actions());

    // 添加额外的操作
    this->find = new QAction(this);
    this->find->setEnabled(false);
    this->find->setText("搜索");
    this->find->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F));
    this->contextMenu->addAction(find);
    //设置快捷方式
    QKeySequence sequeue = find->shortcut();
    QShortcut *Shortcut = new QShortcut(sequeue,this);

    connect(this->find,&QAction::triggered,this,&myTextEdit::newSeacherForm);
    connect(this,&myTextEdit::copyAvailable,this,[this](bool yes){
        this->isAvailable = yes;
        this->find->setEnabled(yes);
    });
    connect(Shortcut,&QShortcut::activated,this,&myTextEdit::newSeacherForm);
}

myTextEdit::~myTextEdit()
{

}

void myTextEdit::newSeacherForm()
{
    this->widget = new SeacherForm;
    this->widget->setLineText(this->textCursor().selectedText());
    this->widget->showNormal();
}

void myTextEdit::onBold()
{
    if(!this->textCursor().hasSelection())
    {
        return;
    }

    QTextCursor cursor = this->textCursor();
    QTextCharFormat format = cursor.charFormat();

    // 检查当前是否已经应用了加粗样式
    if (format.fontWeight() == QFont::Bold) {
        format.setFontWeight(QFont::Normal); // 取消加粗样式
    } else {
        format.setFontWeight(QFont::Bold); // 应用加粗样式
    }

    cursor.mergeCharFormat(format);
    this->mergeCurrentCharFormat(format);
}

void myTextEdit::onItalic()
{
    if(!this->textCursor().hasSelection())
    {
        return;
    }

    QTextCursor Cursor = this->textCursor();
    QTextCharFormat Format = Cursor.charFormat();

    if(Format.fontItalic())
    {
        Format.setFontItalic(false);
    }
    else
    {
        Format.setFontItalic(true);
    }

    Cursor.mergeCharFormat(Format);
    this->mergeCurrentCharFormat(Format);
}

void myTextEdit::onUnderline()
{
    if(!this->textCursor().hasSelection())
    {
        return;
    }

    QTextCursor Cursor = this->textCursor();
    QTextCharFormat Format = Cursor.charFormat();

    if(Format.fontUnderline())
    {
        Format.setFontUnderline(false);
    }
    else
    {
        Format.setFontUnderline(true);
    }

    Cursor.mergeCharFormat(Format);
    this->mergeCurrentCharFormat(Format);
}

void myTextEdit::wheelEvent(QWheelEvent *event)
{
    // 判断Ctrl键是否按下
    if (event->modifiers() & Qt::ControlModifier)
    {
        QPoint numDegrees = event->angleDelta();
        if(numDegrees.y() > 0)
        {
            this->zoomIn();
        }
        else
        {
            this->zoomOut();
        }
        event->accept(); // 接受滚轮事件
    }
    else
    {
        // 在没有按下Ctrl键的情况下，执行正常的滚动功能
        QTextEdit::wheelEvent(event);
    }
}

void myTextEdit::contextMenuEvent(QContextMenuEvent *event)
{
    // 显示上下文菜单
    this->contextMenu->exec(event->globalPos());
}


