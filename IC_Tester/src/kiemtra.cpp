#include "kiemtra.h"
#include <QSerialPortInfo>
#include <QtSerialPort>

KiemTra::KiemTra()
{
    QGridLayout *lopKiemTraTong = new QGridLayout(this);
    QGroupBox *boxCauHinhKetNoi = new QGroupBox("Thiết lập kết nối phần cứng");
    boxCauHinhKetNoi->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");
    boxCauHinhKetNoi->setFixedHeight(150);
    QGroupBox *boxKiemTraIC = new QGroupBox("Kiểm tra IC");
    boxKiemTraIC->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");
    boxKiemTraIC->setDisabled(true);
    QGroupBox *boxChonIC = new QGroupBox("Chọn IC kiểm tra");
    boxChonIC->setStyleSheet(" font-weight: bold;font-size: 16px; color: #0000FF");

    //    thiết lập cấu hình truyền thông

    lopKiemTraTong->addWidget(boxCauHinhKetNoi, 0, 0);
    lopKiemTraTong->addWidget(boxChonIC, 1, 0);
    lopKiemTraTong->addWidget(boxKiemTraIC, 0, 1, 2, 1);

    QComboBox *danhSachCongCOM = new QComboBox;
    danhSachCongCOM->setStyleSheet("font-weight: 500;font-size: 15px; color: black");
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
            boxKiemTraIC->setDisabled(true);
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

        serialPort->setPortName(danhSachCongCOM->currentText());

        // Cài đặt thông số kết nối UART (ví dụ: tốc độ baud 9600)
        serialPort->setBaudRate(QSerialPort::Baud9600);

        // Mở cổng UART để kiểm tra kết nối
        if (serialPort->open(QIODevice::ReadWrite)) {
            QMessageBox::information(this,
                                     "Thông tin kết nối",
                                     "Đã kết nối tới " + portInfo->portName());
            qDebug() << "Connected to serial port:" << portInfo->portName();
            boxKiemTraIC->setDisabled(false);

            // Ở đây, bạn có thể thực hiện các thao tác truyền dữ liệu hoặc xử lý dữ liệu từ cổng UART.

            // Đóng cổng UART khi kết thúc
            serialPort->close();
        } else {
            QMessageBox::warning(this, "Thông tin kết nối", "Kết nối thất bại!");
        }
    });

    QVBoxLayout *lopChonIC = new QVBoxLayout(boxChonIC);
    QListView *khungNhinThuVien = new QListView;
    khungNhinThuVien->setStyleSheet("font-weight: 400;font-size: 15px; color: black");
    QFileSystemModel *moHinhThuVien = new QFileSystemModel;
    QLineEdit *timKiemIC = new QLineEdit;
    timKiemIC->setStyleSheet("font-weight: 400;font-size: 14px; color: black");
    timKiemIC->setPlaceholderText("Nhập từ khóa tìm kiếm...");
    QLabel *bangHienThiThuocTinhIC = new QLabel("Khu vực hiển thị thông tin IC....");
    bangHienThiThuocTinhIC->setAlignment(Qt::AlignTop);
    bangHienThiThuocTinhIC->setStyleSheet("font-weight: 400;font-size: 15px; color: black");
    bangHienThiThuocTinhIC->setWordWrap(true); // Thiết lập tự động xuống dòng

    lopChonIC->addWidget(timKiemIC);
    lopChonIC->addWidget(khungNhinThuVien);
    lopChonIC->addWidget(bangHienThiThuocTinhIC);

    moHinhThuVien->setRootPath(QDir::currentPath());

    khungNhinThuVien->setModel(moHinhThuVien);

    khungNhinThuVien->setRootIndex(moHinhThuVien->index(QDir::currentPath() + "/library"));

    // Khi một mục được chọn HIỂN THỊ THÔNG TIN LÊN QLABLE
    connect(khungNhinThuVien, &QListView::clicked, this, [=](const QModelIndex &index) {
        if (index.isValid()) {
            // Lấy dữ liệu của chỉ mục hiện tại
            QVariant itemData = khungNhinThuVien->model()->data(index, Qt::DisplayRole);
            // Chuyển đổi dữ liệu thành chuỗi và lấy tên của mục
            QString itemName = itemData.toString();

            // Loại bỏ 4 ký tự cuối của tên
            itemName = itemName.left(itemName.length() - 4);

            boxKiemTraIC->setTitle("Kiểm tra IC " + itemName);
            // Lấy đường dẫn đầy đủ của tệp được chọn
            QString filePath = moHinhThuVien->filePath(index);

            // Đọc nội dung của tệp
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly)) {
                char firstByte;
                QDataStream stream(&file);
                stream >> firstByte;
                firstByte &= (0b00011111);
                int viTriByteThuocTinh = static_cast<int>(firstByte);
                // Di chuyển đến byte chứa thông tin IC
                file.seek((viTriByteThuocTinh * 10 + 10) + 1);

                // Đọc nội dung từ byte thứ 5 đến hết
                QByteArray fileContent = file.readAll();
                file.close();

                // Hiển thị nội dung trên QTextEdit
                bangHienThiThuocTinhIC->setText(QString(fileContent));
            }
        }
    });

    QVBoxLayout *lopKiemTraIC = new QVBoxLayout(boxKiemTraIC);

    lopKiemTraIC->addWidget(new QListView);
    lopKiemTraIC->addWidget(new QPushButton("Kiểm tra"));
}
void KiemTra::backHome()
{
    qDebug() << "ok";
}
KiemTra::~KiemTra() {}
