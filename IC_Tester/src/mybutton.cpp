#include "mybutton.h"

MyButton::MyButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setText(text);
}

void MyButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    //    qDebug() << "vào";
}

void MyButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    //    qDebug() << "rời";
}
