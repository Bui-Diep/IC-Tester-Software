#ifndef TAOTHUVIEN_H
#define TAOTHUVIEN_H
#include <QtWidgets>

class TaoThuVien : public QWidget
{
    Q_OBJECT
public:
    TaoThuVien();
public slots:
    void opTrangCauHinhDuLieu();
    void opTrangCauHinhChan();
    void opComplete();

private:
    QStackedWidget *khongGianTaoThuVien;
    QVBoxLayout *lopCauHinhChan;
    QGroupBox *boxCauHinhChan;
    QStackedWidget *khongGianHienSymIC;
    QWidget *trangHienSymDefault;
    QWidget *trangHienSymIC14;
    QWidget *trangHienSymIC16;
    QWidget *trangHienSymIC20;
    QGridLayout *lopGanChan14;
    QGridLayout *lopGanChan16;
    QGridLayout *lopGanChan20;
    QWidget *layoutWidget;
    QWidget *trangCauHinhChan;
    QWidget *trangCauHinhDuLieu;
    QComboBox *soChanIC;
    QLineEdit *tenIC;
    QTextEdit *moTaIC;
};

#endif // TAOTHUVIEN_H
