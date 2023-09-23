#include "kiemtra.h"
#include <QSerialPortInfo>
#include <QtSerialPort>

KiemTra::KiemTra()
{
    QGridLayout *lopKiemTraTong = new QGridLayout(this);
    QGroupBox *boxCauHinhKetNoi = new QGroupBox("Thiết lập kết nối phần cứng");
    boxCauHinhKetNoi->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");
    QGroupBox *boxKiemTra = new QGroupBox("Kiểm tra IC");
    boxKiemTra->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");
    QGroupBox *boxChonIC = new QGroupBox("Chọn IC kiểm tra");
    boxChonIC->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");
    QStatusBar *statusBar = new QStatusBar;
    statusBar->setFixedSize(400, 20);

    QPropertyAnimation *animation = new QPropertyAnimation(statusBar, "windowOpacity");
    animation->setDuration(2000); // Thời gian hiển thị (ms)
    animation->setStartValue(0.0);
    animation->setEndValue(100);

    lopKiemTraTong->addWidget(boxCauHinhKetNoi, 0, 0);
    lopKiemTraTong->addWidget(statusBar, 1, 0);
    lopKiemTraTong->addWidget(boxChonIC, 2, 0);
    lopKiemTraTong->addWidget(boxKiemTra, 0, 1, 3, 1);

    //    thiết lập cấu hình truyền thông

    QComboBox *danhSachCongCOM = new QComboBox;
    QPushButton *nutNhanKetNoi = new QPushButton("Kết nối");
    nutNhanKetNoi->setStyleSheet("QPushButton {"
                                 "background-color: #009900;"
                                 "color: white;"
                                 "font-weight: bold;"
                                 "font-size: 16px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #007500;"
                                 "}");
    nutNhanKetNoi->setFixedWidth(80);
    QGridLayout *lopCauHinhKetNoi = new QGridLayout(boxCauHinhKetNoi);
    lopCauHinhKetNoi->addWidget(danhSachCongCOM, 0, 0);
    lopCauHinhKetNoi->addWidget(nutNhanKetNoi, 0, 1);

    QSerialPortInfo *portInfo = new QSerialPortInfo;
    // Tạo một QTimer để thực hiện kiểm tra định kỳ
    QTimer *timer = new QTimer;
    timer->setInterval(10);
    connect(timer, &QTimer::timeout, this, [=]() {
        //     Liệt kê các cổng COM và thêm vào QComboBox
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();
        if (availablePorts.isEmpty()) {
            danhSachCongCOM->clear();
            danhSachCongCOM->addItem("Không phát hiện thiết bị");
            danhSachCongCOM->setDisabled(true); // Vô hiệu hóa QComboBox
        } else {
            danhSachCongCOM->setDisabled(false);
            if (danhSachCongCOM->itemText(0) == ("Không phát hiện thiết bị")) {
                danhSachCongCOM->clear();
            } else if (danhSachCongCOM->count() == 0) {
                foreach (*portInfo, availablePorts) {
                    danhSachCongCOM->addItem(portInfo->portName());
                }
            }
        }
    });

    // Khởi động QTimer để bắt đầu kiểm tra
    timer->start();

    connect(nutNhanKetNoi, &QPushButton::clicked, this, [=]() {
        QSerialPort *serialPort = new QSerialPort;

        serialPort->setPortName(portInfo->portName());
        statusBar->showMessage("Đã kết nối tới " + portInfo->portName(), 2000);
        // Áp dụng hiệu ứng xuất hiện
        animation->start();

        // Cài đặt thông số kết nối UART (ví dụ: tốc độ baud 9600)
        serialPort->setBaudRate(QSerialPort::Baud9600);

        // Mở cổng UART để kiểm tra kết nối
        if (serialPort->open(QIODevice::ReadWrite)) {
            qDebug() << "Connected to serial port:" << portInfo->portName();

            // Ở đây, bạn có thể thực hiện các thao tác truyền dữ liệu hoặc xử lý dữ liệu từ cổng UART.

            // Đóng cổng UART khi kết thúc
            serialPort->close();
        }
    });
}
void KiemTra::backHome()
{
    qDebug() << "ok";
}
KiemTra::~KiemTra() {}
