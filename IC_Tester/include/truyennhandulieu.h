#ifndef TRUYENNHANDULIEU_H
#define TRUYENNHANDULIEU_H

#include <QSerialPort>
#include <QThread>
#include <QtWidgets>

class TruyenDuLieu : public QThread
{
public:
    TruyenDuLieu(QObject *parent = nullptr);
    ~TruyenDuLieu();

    void sendData(QString filePath, QSerialPort *serialPort);
};
class NhanDuLieu : public QThread
{
public:
    NhanDuLieu(QObject *parent = nullptr);
    ~NhanDuLieu();

    void sendData(QString filePath, QSerialPort *serialPort);
    QVector<char> receiveData(QSerialPort *serialPort, QVector<char> receiveByte);
};
#endif // TRUYENNHANDULIEU_H
