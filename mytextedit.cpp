#include "mytextedit.h"
#include <QMenu>
#include <QAction>
#include <QKeySequence>

myTextEdit::myTextEdit(QWidget *parent)
    : QTextEdit(parent)
{
    //this->setFont();
    this->setMouseTracking(true);
    this->setFocusPolicy(Qt::StrongFocus);
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
    // 创建上下文菜单
    QMenu contextMenu(this);

    // 添加默认的右键菜单操作
    contextMenu.addActions(QTextEdit::createStandardContextMenu()->actions());

    // 添加额外的操作
    QAction *find = new QAction(this);
    find->setText("搜索");
    find->setShortcut(QKeySequence(QKeySequence::Find));
    contextMenu.addAction(find);

    connect(find,&QAction::changed,this,[](){
        qDebug() << "dadada";
    });


    // 显示上下文菜单
    contextMenu.exec(event->globalPos());
}


