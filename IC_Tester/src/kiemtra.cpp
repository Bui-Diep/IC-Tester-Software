#include "kiemtra.h"
#include <QSerialPortInfo>

KiemTra::KiemTra()
{
    QGridLayout *lopKiemTraTong = new QGridLayout(this);
    QGroupBox *boxCauHinhKetNoi = new QGroupBox("Thiết lập kết nối tới phần cứng");
    boxCauHinhKetNoi->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    boxCauHinhKetNoi->setFixedSize(410, 120);
    QGroupBox *boxKiemTraIC = new QGroupBox("Kiểm tra IC");
    boxKiemTraIC->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    boxKiemTraIC->setDisabled(true);
    QGroupBox *boxChonIC = new QGroupBox("Chọn IC kiểm tra");
    boxChonIC->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    boxChonIC->setFixedWidth(410);

    //    thiết lập cấu hình truyền thông

    lopKiemTraTong->addWidget(boxCauHinhKetNoi, 0, 0);
    lopKiemTraTong->addWidget(boxChonIC, 1, 0);
    lopKiemTraTong->addWidget(boxKiemTraIC, 0, 1, 2, 1);

    QComboBox *danhSachCongCOM = new QComboBox;
    danhSachCongCOM->setStyleSheet("font-size: 14px; color : #CC0000");
    danhSachCongCOM->setFixedWidth(200);
    danhSachCongCOM->setPlaceholderText("Không tìm thấy thiết bị");
    QComboBox *danhSachBaud = new QComboBox;
    danhSachBaud->setFixedWidth(100);
    danhSachBaud->setStyleSheet("font-weight: 500;font-size: 14px; color: black");
    QPushButton *nutNhanKetNoi = new QPushButton;
    nutNhanKetNoi->setFixedWidth(80);
    nutNhanKetNoi->setText("Ngắt\nkết nối");
    nutNhanKetNoi->setStyleSheet("QPushButton {"
                                 "background-color: #CC0000;"
                                 "color: white;"
                                 "font-weight: bold;"
                                 "font-size: 16px;"
                                 "}"
                                 "QPushButton:hover {"
                                 "background-color: #007500;"
                                 "}");

    QGridLayout *lopCauHinhKetNoi = new QGridLayout(boxCauHinhKetNoi);

    lopCauHinhKetNoi
        ->addWidget(new QLabel(
                        "<html><body><p style=\"font-size:15px; "
                        "font-weight:550; color: normal;\">Tìm thiết bị: </p></body></html>"),
                    0,
                    0);
    lopCauHinhKetNoi->addWidget(danhSachCongCOM, 0, 1);
    lopCauHinhKetNoi->addWidget(nutNhanKetNoi, 0, 2);
    lopCauHinhKetNoi
        ->addWidget(new QLabel("<html><body><p style=\"font-size:15px; "
                               "font-weight:550; color: normal;\">Tốc độ Baud: </p></body></html>"),
                    1,
                    0);
    lopCauHinhKetNoi->addWidget(danhSachBaud, 1, 1);
    danhSachBaud->addItem("9600bps");
    danhSachBaud->addItem("19200bps");
    serialPort = new QSerialPort(this);
    QSerialPortInfo *portInfo = new QSerialPortInfo;
    // Tạo một QTimer để thực hiện kiểm tra định kỳ
    QTimer *timer = new QTimer;
    timer->setInterval(1000);
    //    int *soLuongCOM = new int(0);
    connect(timer, &QTimer::timeout, this, [=]() {
        //     Liệt kê các cổng COM và thêm vào QComboBox
        QList<QSerialPortInfo> availablePorts = QSerialPortInfo::availablePorts();

        if (availablePorts.size() != danhSachCongCOM->count()) {
            if (availablePorts.isEmpty()) {
                danhSachCongCOM->clear();
                danhSachCongCOM->setPlaceholderText("Không tìm thấy thiết bị");
                danhSachCongCOM->setStyleSheet("font-size: 14px; color : #CC0000");
                boxKiemTraIC->setDisabled(true);
                danhSachCongCOM->setDisabled(true); // Vô hiệu hóa QComboBox
                nutNhanKetNoi->setText("Ngắt\nkết nối");
                nutNhanKetNoi->setStyleSheet("QPushButton {"
                                             "background-color: #CC0000;"
                                             "color: white;"
                                             "font-weight: bold;"
                                             "font-size: 16px;"
                                             "}"
                                             "QPushButton:hover {"
                                             "background-color: #007500;"
                                             "}");
                QMessageBox::warning(this,
                                     "Thông tin kết nối",
                                     "Ngắt kết nối với thiết bị phần cứng");
            } else {
                danhSachCongCOM->setDisabled(false);

                danhSachCongCOM->clear();
                danhSachCongCOM->setPlaceholderText(
                    "Tìm thấy " + QString::number(availablePorts.size()) + " thiết bị");
                danhSachCongCOM->setStyleSheet("font-size: 14px; color : green");
                nutNhanKetNoi->setText("Kết nối");
                nutNhanKetNoi->setStyleSheet("QPushButton {"
                                             "background-color: #009900;"
                                             "color: white;"
                                             "font-weight: bold;"
                                             "font-size: 16px;"
                                             "}"
                                             "QPushButton:hover {"
                                             "background-color: #007500;"
                                             "}");
                foreach (*portInfo, availablePorts) {
                    danhSachCongCOM->addItem(portInfo->portName());
                }
            }
        }
    });

    // Khởi động QTimer để bắt đầu kiểm tra
    timer->start();

    connect(nutNhanKetNoi, &QPushButton::clicked, this, [=]() {

        // Cài đặt thông số kết nối UART (ví dụ: tốc độ baud 9600)
        if (danhSachBaud->currentText() == "9600bps") {
            serialPort->setPortName(danhSachCongCOM->currentText());
            serialPort->setBaudRate(QSerialPort::Baud9600);
            serialPort->setDataBits(QSerialPort::Data8);
            serialPort->setParity(QSerialPort::NoParity);
            serialPort->setStopBits(QSerialPort::OneStop);
            serialPort->setFlowControl(QSerialPort::NoFlowControl);

        } else if (danhSachBaud->currentText() == "19200bps") {
            serialPort->setPortName(danhSachCongCOM->currentText());
            serialPort->setBaudRate(QSerialPort::Baud19200);
            serialPort->setDataBits(QSerialPort::Data8);
            serialPort->setParity(QSerialPort::NoParity);
            serialPort->setStopBits(QSerialPort::OneStop);
            serialPort->setFlowControl(QSerialPort::NoFlowControl);
        }

        // Mở cổng UART để kiểm tra kết nối
        if (serialPort->open(QIODevice::ReadWrite)) {
            nutNhanKetNoi->setText("Đã\nkết nối");
            QMessageBox::information(this,
                                     "Thông tin kết nối",
                                     "Đã kết nối tới " + portInfo->portName() + "\nTốc độ Baud "
                                         + danhSachBaud->currentText());
            qDebug() << "Connected to serial port:" << portInfo->portName();
            boxKiemTraIC->setDisabled(false);
            // Ở đây, bạn có thể thực hiện các thao tác truyền dữ liệu hoặc xử lý dữ liệu từ cổng UART
            qDebug() << "kết nối thành công";
            // Đóng cổng UART khi kết thúc

            serialPort->close();
        } else {
            if (danhSachCongCOM->currentText() == "" && danhSachCongCOM->count() != 0) {
                QMessageBox::warning(this, "Thông tin kết nối", "Hãy chọn 1 thiết bị");
            } else {
                QMessageBox::warning(this, "Thông tin kết nối", "Hãy kết nối cable với máy tính!");
            }
        }
    });

    QVBoxLayout *lopChonIC = new QVBoxLayout(boxChonIC);
    QListView *khungNhinThuVien = new QListView;
    khungNhinThuVien->setStyleSheet("font-weight: 400;font-size: 15px; color: black");
    QFileSystemModel *moHinhThuVien = new QFileSystemModel;
    QLineEdit *timKiemIC = new QLineEdit;
    timKiemIC->setPlaceholderText("Nhập từ khóa tìm kiếm...");
    timKiemIC->setStyleSheet("font-weight: 400;font-size: 14px; color: normal");
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
            filePath = moHinhThuVien->filePath(index);

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
    QSplitter *splitKiemTra = new QSplitter;
    splitKiemTra->setStyleSheet("QSplitter::handle { background-color: white; }");
    QProgressBar *thanhTienTrinh = new QProgressBar;
    lopKiemTraIC->addWidget(splitKiemTra);
    lopKiemTraIC->addWidget(thanhTienTrinh, Qt::AlignBottom);
    QWidget *widHienThiKetqua = new QWidget(splitKiemTra);
    QGridLayout *lopSymHienThiKetQua = new QGridLayout(widHienThiKetqua);
    lopSymHienThiKetQua->addWidget(
        new QLabel("<html><body><p style=\"font-size:15px; "
                   "font-weight:550; color: normal;\">Chọn tốc độ kiểm tra: </p></body></html>"),
        0,
        0);
    QComboBox *tocDoKiemTra = new QComboBox;
    tocDoKiemTra->setStyleSheet("font-weight: 500;font-size: 15px; color: black");
    tocDoKiemTra->addItem("Chậm");
    tocDoKiemTra->addItem("Bình Thường");
    tocDoKiemTra->addItem("Nhanh");
    lopSymHienThiKetQua->addWidget(tocDoKiemTra, 0, 1);
    lopSymHienThiKetQua->addWidget(new QLabel(" "), 0, 2);
    lopSymHienThiKetQua->addWidget(new QLabel(" "), 0, 3);
    QPushButton *nutRun = new QPushButton("Chạy");
    nutRun->setStyleSheet("QPushButton {"
                          "background-color: #009900;"
                          "color: white;"
                          "font-weight: bold;"
                          "font-size: 16px;"
                          "}"
                          "QPushButton:hover {"
                          "background-color: #007500;"
                          "}");
    lopSymHienThiKetQua->addWidget(nutRun, 0, 4);

    lopSymHienThiKetQua->addWidget(new QLabel(" Hiển thị kết quả ở đây"), 1, 0, 1, 5);
    QWidget *widkhungSymIC = new QWidget(splitKiemTra);
    QVBoxLayout *lopkhungSymIC = new QVBoxLayout(widkhungSymIC);
    lopkhungSymIC->setAlignment(Qt::AlignCenter);
    QFrame *khungSymIC = new QFrame;
    lopkhungSymIC->addWidget(khungSymIC);
    //    lopkhungSymIC->addWidget(new QLabel(""));
    khungSymIC->setFixedSize(160, 440); // Đặt kích thước hình chữ nhật
    khungSymIC->setStyleSheet("QFrame {"
                              "   background-color: #A8D9D0;"
                              "   border: 2px solid black;"
                              "   border-radius: 10px;"
                              "}");
    //    biểu tượng các chân IC
    lopChanIC = new QGridLayout(khungSymIC);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            pin[i][j] = new QPushButton;
            pin[i][j]->setFixedSize(40, 25);
            pin[i][j]->setEnabled(0);
            pin[i][j]->setStyleSheet("background-color: grey;"
                                     " border-radius: 8px;"
                                     " border: 1px solid blue;");
            lopChanIC->addWidget(pin[i][j], i, j);
        }
    }
    QLabel *gap = new QLabel("   ");
    gap->setStyleSheet("border: normal;");
    lopChanIC->addWidget(gap, 0, 1);

    splitKiemTra->setStretchFactor(0, 1);
    splitKiemTra->setStretchFactor(1, 1);
    thanhTienTrinh->setValue(35);
    thanhTienTrinh->setRange(0, 100);
    thanhTienTrinh->setToolTip("Thanh tiến trình kiểm tra");

    //LẬP TRÌNH TRUYỀN NHẬN DỮ LIỆU TỚI PHẦN CỨNG TỪ FILE TRONG THƯ VIỆN
    /*    connect(nutRun, SIGNAL(clicked(bool)), this, SLOT(sendData(filePath, serialPort)))*/;
    QObject::connect(nutRun, &QPushButton::clicked, this, [=]() {
        sendSerial->sendData(filePath, serialPort);
    });
    QObject::connect(serialPort, &QSerialPort::readyRead, this, [=]() {
        receiveByte = (receiveSerial->receiveData(serialPort, receiveByte));
        if (receiveByte.size() == 10) {
            qDebug() << "du 10";
            emit nhanDu10Byte();
        };
    });
    connect(this, SIGNAL(nhanDu10Byte()), this, SLOT(indicateLed()));
}

void KiemTra::indicateLed()
{
    //    qDebug() << "Da nhan 10 byte";
    //    char *receiveData = new char[10]{0};
    char duLieuGanChanIC[10][3];
    //        HIEN THI THONG TIN TU DU LIEU NHAN DUOC LEN khungSymIC
    for (int i = 0; i < 10; ++i) {
        // 4 bit trọng số cao mang thông tin hàng chân bên trái
        duLieuGanChanIC[i][0] = receiveByte[i] & (0b00110000);
    }
    for (int i = 0; i < 10; ++i) {
        // 4 bit trọng số thấp mang thông tin hàng chân bên phải
        duLieuGanChanIC[i][2] = receiveByte[i] & (0b00000011);
    }

    //    thêm cấu chân IC từ file dữ liệu nhận về
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            //Nếu chân dữ liệu không kết nối
            if (duLieuGanChanIC[i][j] == (0b00110000) // NC
                || duLieuGanChanIC[i][j] == (0b00000011)) {
                pin[i][j]->setStyleSheet("background-color: grey;"
                                         " border-radius: 8px;"
                                         " border: 1px solid blue;");
                lopChanIC->addWidget(pin[i][j], i, j);

                //nếu chân dữ liệu kết nối với nguồn VCC hoặc mang mức logic 1
            } else if (duLieuGanChanIC[i][j] == (0b00010000) // LOGIC 1
                       || duLieuGanChanIC[i][j] == (0b00000001)) {
                pin[i][j]->setStyleSheet("background-color: green;"
                                         " border-radius: 8px;"
                                         " border: 1px solid blue;");
                lopChanIC->addWidget(pin[i][j], i, j);
                //nếu chân dữ liệu kết nối với đất hoặc mang mức logic 0
            } else if (duLieuGanChanIC[i][j] == (0b00100000) //LOGIC 0
                       || duLieuGanChanIC[i][j] == (0b00000010)) {
                pin[i][j]->setStyleSheet("background-color: red;"
                                         " border-radius: 8px;"
                                         " border: 1px solid blue;");
                lopChanIC->addWidget(pin[i][j], i, j);
            } else /* if (duLieuGanChanIC[i][j] == (0b00000000) //Không xác định
                                       || duLieuGanChanIC[i][j] == (0b00000000))*/
            {
                pin[i][j]->setStyleSheet("background-color: white;"
                                         " border-radius: 8px;"
                                         " border: 1px solid blue;");
                lopChanIC->addWidget(pin[i][j], i, j);
            }
        }
    }
    //thực hiện giải phóng bộ nhớ
    receiveByte.clear();
    std::memset(duLieuGanChanIC, 0, sizeof(duLieuGanChanIC));
}
//void KiemTra::sendData(QString &filePath, QSerialPort &serialPort)
//{
//    dataSerial->sendData(filePath, serialPort);
//}
KiemTra::~KiemTra()
{
    serialPort->close();
    receiveByte.clear();
}
