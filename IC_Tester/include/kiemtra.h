#ifndef KIEMTRA_H
#define KIEMTRA_H
#include <QtSerialPort>
#include <QtWidgets>
#include "truyennhandulieu.h"

class KiemTra : public QWidget
{
    Q_OBJECT;

public:
    KiemTra();
    ~KiemTra();

public slots:
    //    void sendData(QString &filePath, QSerialPort &serialPort); //Gửi dữ liệu qua UART
    //    void receiveData(QSerialPort &serialPort);                 //Nhận dữ liệu từ UART
    void indicateLed(); //LED Chỉ thị
signals:
    void nhanDu10Byte();

private:
    QPushButton *nutAutoRun;
    QPushButton *nutStop;
    int viTriByteThuocTinh;
    TruyenDuLieu *sendSerial;
    NhanDuLieu *receiveSerial;
    QGridLayout *lopChanIC;
    QSerialPort *serialPort;
    QPushButton *pin[10][3];
    QString filePath;
    QVector<char> receiveByte; // Khởi tạo một QVector<char> rỗng-  Mảng char để lưu dữ liệu nhận về
    int *chiSoBaiKiemTra;
};

#endif // KIEMTRA_H
