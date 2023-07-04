#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QObject>
#include <QTextEdit>
#include <QWheelEvent>
#include <QPoint>
#include <QDebug>
#include "seacherform.h"
#include <QMenu>
#include <QAction>

class myTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit myTextEdit(QWidget *parent = nullptr);
    ~myTextEdit();

public slots:
    void newSeacherForm();
    void onBold();
    void onItalic();
    void onUnderline();
signals:
    void fontFarmt(QFont font);
private:
    virtual void wheelEvent(QWheelEvent *event);
    virtual void contextMenuEvent(QContextMenuEvent *event);


    bool isAvailable = false;
    SeacherForm *widget;
    QMenu *contextMenu;
    QAction *find;
};

#endif // MYTEXTEDIT_H
