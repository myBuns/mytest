#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QWheelEvent>
#include <QPoint>
#include <QDebug>

class myTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit myTextEdit(QWidget *parent = nullptr);

signals:

private:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);


    bool isOK = false;
};

#endif // MYTEXTEDIT_H
