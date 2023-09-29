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
    serialPort = new QSerialPort;
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

        serialPort->setPortName(danhSachCongCOM->currentText());

        // Cài đặt thông số kết nối UART (ví dụ: tốc độ baud 9600)
        if (danhSachBaud->currentText() == "9600bps") {
            serialPort->setBaudRate(QSerialPort::Baud9600);
        } else if (danhSachBaud->currentText() == "19200bps") {
            serialPort->setBaudRate(QSerialPort::Baud19200);
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

            // Ở đây, bạn có thể thực hiện các thao tác truyền dữ liệu hoặc xử lý dữ liệu từ cổng UART.

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
    QWidget *widSymIC = new QWidget(splitKiemTra);
    QVBoxLayout *lopSymIC = new QVBoxLayout(widSymIC);
    lopSymIC->setAlignment(Qt::AlignCenter);
    QFrame *symIC = new QFrame;
    lopSymIC->addWidget(symIC);
    //    lopSymIC->addWidget(new QLabel(""));
    symIC->setFixedSize(160, 440); // Đặt kích thước hình chữ nhật
    symIC->setStyleSheet("QFrame {"
                         "   background-color: #A8D9D0;"
                         "   border: 2px solid black;"
                         "   border-radius: 10px;"
                         "}");
    //    biểu tượng các chân IC
    QGridLayout *lopChanIC = new QGridLayout(symIC);
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            pin[i][j] = new QPushButton;
            pin[i][j]->setFixedSize(32, 32);
            pin[i][j]->setEnabled(0);
            pin[i][j]->setStyleSheet("background-color: grey;"
                                     " border-radius: 16px;"
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

    //    LẬP TRÌNH TRUYỀN NHẬN DỮ LIỆU TỚI PHẦN CỨNG TỪ FILE TRONG THƯ VIỆN
    connect(nutRun, &QPushButton::clicked, this, [=]() {
        QFile binFile(filePath); // filePath duong dan toi file duoc chon
        if (!binFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Khong the mo tep .bin";
            return;
        }

        // Di chuyển con trỏ đọc tệp đến byte thứ hai
        binFile.seek(1);

        char *byteMaHoaDuLieu = new char[10]; // Mảng char có 10 phần tử

        // Đọc 10 byte từ tệp .bin và lưu vào mảng char
        qint64 bytesRead = binFile.read(byteMaHoaDuLieu, 10);

        qDebug() << "Du lieu 10 byte: ";
        for (int n = 0; n < 10; ++n) {
            unsigned char unsignedChar = static_cast<unsigned char>(byteMaHoaDuLieu[n]);
            QString binaryString = QString("%1").arg(unsignedChar, 8, 2, QChar('0'));
            qDebug() << "Byte " << n + 1 << binaryString;
        }

        if (bytesRead != 10) {
            qDebug() << "Khong doc du 10 byte tu tep .bin";
            binFile.close();
            return;
        }
        binFile.close();
        //        tạo mảng hai chiều chứa thông tin dữ liêu từ hai chân nhận được
        char duLieuGanChanIC[10][3];
        //        HIEN THI THONG TIN TU DU LIEU NHAN DUOC LEN SYMIC
        for (int i = 0; i < 10; ++i) {
            // 4 bit trọng số cao mang thông tin hàng chân bên trái
            duLieuGanChanIC[i][0] = byteMaHoaDuLieu[i] & (0b00110000);
        }
        for (int i = 0; i < 10; ++i) {
            // 4 bit trọng số thấp mang thông tin hàng chân bên phải
            duLieuGanChanIC[i][2] = byteMaHoaDuLieu[i] & (0b00000011);
        }

        //    thêm cấu chân IC từ file dữ liệu nhận về
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; j += 2) {
                //Nếu chân dữ liệu không kết nối
                if (duLieuGanChanIC[i][j] == (0b00110000) // NC
                    || duLieuGanChanIC[i][j] == (0b00000011)) {
                    pin[i][j]->setStyleSheet("background-color: grey;"
                                             " border-radius: 16px;"
                                             " border: 1px solid blue;");
                    lopChanIC->addWidget(pin[i][j], i, j);

                    //nếu chân dữ liệu kết nối với nguồn VCC hoặc mang mức logic 1
                } else if (duLieuGanChanIC[i][j] == (0b00010000) // LOGIC 1
                           || duLieuGanChanIC[i][j] == (0b00000001)) {
                    pin[i][j]->setStyleSheet("background-color: green;"
                                             " border-radius: 16px;"
                                             " border: 1px solid blue;");
                    lopChanIC->addWidget(pin[i][j], i, j);
                    //nếu chân dữ liệu kết nối với đất hoặc mang mức logic 0
                } else if (duLieuGanChanIC[i][j] == (0b00100000) //LOGIC 0
                           || duLieuGanChanIC[i][j] == (0b00000010)) {
                    pin[i][j]->setStyleSheet("background-color: red;"
                                             " border-radius: 16px;"
                                             " border: 1px solid blue;");
                    lopChanIC->addWidget(pin[i][j], i, j);
                } else /* if (duLieuGanChanIC[i][j] == (0b00000000) //Không xác định
                           || duLieuGanChanIC[i][j] == (0b00000000))*/
                {
                    pin[i][j]->setStyleSheet("background-color: white;"
                                             " border-radius: 16px;"
                                             " border: 1px solid blue;");
                    lopChanIC->addWidget(pin[i][j], i, j);
                }
            }
        }
    });
}
void KiemTra::backHome()
{
    qDebug() << "ok";
}
KiemTra::~KiemTra() {}
