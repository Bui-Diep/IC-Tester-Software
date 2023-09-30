#include "truyennhandulieu.h"
#include "qdebug.h"

void TruyenDuLieu::sendData(QString filePath, QSerialPort *serialPort)
{
    serialPort->open(QIODevice::ReadWrite);
    QFile binFile(filePath); // filePath duong dan toi file duoc chon
    binFile.open(QIODevice::ReadOnly);
    // Di chuyển con trỏ đọc tệp đến byte thứ hai
    binFile.seek(1);
    char *sendData = new char[10]; // Mảng char để lưu dữ liệu gửi đi

    binFile.read(sendData, 10);
    //    binFile.close(); // Đóng file .bin sau khi đọc xong
    //Gửi dữ liệu từ sendData qua UART
    serialPort->write(sendData, 10);
    //    qDebug() << "Da gui du lieu";

    binFile.close(); // Đóng file .bin sau khi đọc xong
}
TruyenDuLieu::~TruyenDuLieu(){};
QVector<char> NhanDuLieu::receiveData(QSerialPort *serialPort, QVector<char> receiveByte)
{
    //    QVector<char> data;
    char *byte = new char;
    serialPort->read(byte, 1);
    receiveByte.append(*byte); // Thêm một phần tử char vào mảng
                               //    qDebug() << receiveByte.size();
    return receiveByte;
}
NhanDuLieu::~NhanDuLieu(){};
