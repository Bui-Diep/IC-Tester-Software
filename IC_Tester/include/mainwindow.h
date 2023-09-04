#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "kiemtra.h"
#include "taothuvien.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void opHome();
    void opKiemTra();
    void opTaoThuVien();

private:
    QStackedWidget *khongGianLamViec;
    QWidget *trangHome;
    KiemTra *trangKiemTra;
    TaoThuVien *trangTaoThuVien;
};
#endif // MAINWINDOW_H
