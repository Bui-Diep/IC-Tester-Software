#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QObject>
#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT

public:
    MyButton(const QString &text, QWidget *parent = nullptr);

    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // MYBUTTON_H
