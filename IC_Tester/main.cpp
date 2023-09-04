#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //        w.resize(550, 400);
    //    w.setStyleSheet("background-color: #F5F5F5;");

    w.show();
    return a.exec();
}
