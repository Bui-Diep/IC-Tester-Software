#ifndef KIEMTRA_H
#define KIEMTRA_H
#include <QtSerialPort>
#include <QtWidgets>

class KiemTra : public QWidget
{
    Q_OBJECT;

public:
    KiemTra();
    ~KiemTra();

public slots:
    void backHome();

private:
    QSerialPort *serialPort;
    QPushButton *pin[10][3];
    QString filePath;
};

#endif // KIEMTRA_H
