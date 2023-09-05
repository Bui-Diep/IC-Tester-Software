#include "taothuvien.h"

TaoThuVien::TaoThuVien()
{
    //    QFont tieuDeBox("Sans Serif", 10, QFont::Bold);
    khongGianTaoThuVien = new QStackedWidget;

    //    =============================================================================================
    trangCauHinhChan = new QWidget;
    lopCauHinhChan = new QVBoxLayout;
    QHBoxLayout *lopCauHinhChanTong = new QHBoxLayout;
    lopCauHinhChanTong->addLayout(lopCauHinhChan);
    trangCauHinhChan->setLayout(lopCauHinhChanTong);

    //    nhom thuoc tinh
    QGroupBox *boxThuocTinh = new QGroupBox("Thuộc tính IC");
    boxThuocTinh->setStyleSheet("font-size: 15px;");
    QHBoxLayout *lopThuocTinhChung = new QHBoxLayout;
    QFormLayout *lopThuocTinh = new QFormLayout;
    QPushButton *nutHienSym = new QPushButton("Xong");
    QVBoxLayout *lopNutHienSym = new QVBoxLayout;
    nutHienSym->setStyleSheet(
        "background-color: #009900;font-size: 16px;font-weight: bold; color: white");
    lopNutHienSym->addWidget(nutHienSym);
    lopNutHienSym->addWidget(new QLabel("   "));
    lopNutHienSym->addWidget(new QLabel("   "));
    lopNutHienSym->addWidget(new QLabel("   "));
    tenIC = new QLineEdit;
    tenIC->setFixedSize(150, 25);
    lopThuocTinh->addRow("Tên IC:", tenIC);
    tenIC->setPlaceholderText("Nhập tên IC");
    QComboBox *soChanIC = new QComboBox;
    soChanIC->setFixedSize(150, 25);
    soChanIC->addItem(" 12 Chân");
    soChanIC->addItem(" 14 Chân");
    soChanIC->addItem(" 16 Chân");
    soChanIC->addItem(" 20 Chân");
    lopThuocTinh->addRow("Số chân IC:", soChanIC);
    QComboBox *congNgheBanDan = new QComboBox;
    congNgheBanDan->setFixedSize(150, 25);
    congNgheBanDan->addItem("CMOS (3.3V)");
    congNgheBanDan->addItem("TTL (5V)");
    lopThuocTinh->addRow("Công nghệ:", congNgheBanDan);
    lopThuocTinhChung->addLayout(lopThuocTinh);
    lopThuocTinhChung->addLayout(lopNutHienSym);
    boxThuocTinh->setLayout(lopThuocTinhChung);
    lopCauHinhChan->addWidget(boxThuocTinh);
    moTaIC = new QTextEdit;
    lopThuocTinh->addRow("Mô tả:", moTaIC);
    moTaIC->setPlaceholderText("Mô tả IC tại đây ...");
    connect(nutHienSym, &QPushButton::clicked, [soChanIC, this]() {
        if (!tenIC->text().isEmpty()) {
            if (soChanIC->currentIndex() == 1) {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC14);
                boxCauHinhChan->setFixedHeight(400);
            } else if (soChanIC->currentText() == " 16 Chân") {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC16);
                boxCauHinhChan->setFixedHeight(420);
            } else if (soChanIC->currentText() == " 20 Chân") {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC20);
                boxCauHinhChan->setFixedHeight(450);
            } else {
                QMessageBox::warning(this,
                                     "Cảnh báo",
                                     "IC" + soChanIC->currentText()
                                         + " chưa được hỗ trợ\nVui lòng chọn loại khác");
                khongGianHienSymIC->setCurrentWidget(trangHienSymDefault);
            }
        } else {
            QMessageBox::warning(this, "Cảnh báo", "Vui lòng nhập tên IC");
        }
    });

    //  nhom cau hinh chan
    boxCauHinhChan = new QGroupBox("Cấu hình chân IC");
    boxCauHinhChan->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    khongGianHienSymIC = new QStackedWidget;
    khongGianHienSymIC->setStyleSheet("font-weight: 550;font-size: 15px; color: nomal");
    trangHienSymDefault = new QWidget;
    trangHienSymIC14 = new QWidget;
    trangHienSymIC16 = new QWidget;
    trangHienSymIC20 = new QWidget;
    khongGianHienSymIC->addWidget(trangHienSymDefault);
    khongGianHienSymIC->addWidget(trangHienSymIC14);
    khongGianHienSymIC->addWidget(trangHienSymIC16);
    khongGianHienSymIC->addWidget(trangHienSymIC20);
    QVBoxLayout *lopKhonGianHienSymIC = new QVBoxLayout;
    lopKhonGianHienSymIC->addWidget(khongGianHienSymIC);
    boxCauHinhChan->setFixedHeight(400);
    boxCauHinhChan->setLayout(lopKhonGianHienSymIC);
    lopGanChan14 = new QGridLayout;
    lopGanChan16 = new QGridLayout;
    lopGanChan20 = new QGridLayout;
    //    chan 1
    QMenu *pinType1 = new QMenu;
    pinType1->addAction(new QAction("VCC"));
    pinType1->addAction(new QAction("GND"));
    pinType1->addAction(new QAction("CLK"));
    pinType1->addAction(new QAction("DATA_IN"));
    pinType1->addAction(new QAction("DATA_OUT"));
    pinType1->addAction(new QAction("NC"));
    QPushButton *pin1_14 = new QPushButton("Pin 1");
    QPushButton *pin1_16 = new QPushButton("Pin 1");
    QPushButton *pin1_20 = new QPushButton("Pin 1");
    pin1_14->setMenu(pinType1);
    pin1_16->setMenu(pinType1);
    pin1_20->setMenu(pinType1);
    lopGanChan14->addWidget(pin1_14, 0, 0);
    lopGanChan16->addWidget(pin1_16, 0, 0);
    lopGanChan20->addWidget(pin1_20, 0, 0);
    //    chan 2
    QMenu *pinType2 = new QMenu;
    pinType2->addAction(new QAction("VCC"));
    pinType2->addAction(new QAction("GND"));
    pinType2->addAction(new QAction("CLK"));
    pinType2->addAction(new QAction("DATA_IN"));
    pinType2->addAction(new QAction("DATA_OUT"));
    pinType2->addAction(new QAction("NC"));
    QPushButton *pin2_14 = new QPushButton("Pin 2");
    QPushButton *pin2_16 = new QPushButton("Pin 2");
    QPushButton *pin2_20 = new QPushButton("Pin 2");
    pin2_14->setMenu(pinType2);
    pin2_16->setMenu(pinType2);
    pin2_20->setMenu(pinType2);
    lopGanChan14->addWidget(pin2_14, 1, 0);
    lopGanChan16->addWidget(pin2_16, 1, 0);
    lopGanChan20->addWidget(pin2_20, 1, 0);
    //    chan 3
    QMenu *pinType3 = new QMenu;
    pinType3->addAction(new QAction("VCC"));
    pinType3->addAction(new QAction("GND"));
    pinType3->addAction(new QAction("CLK"));
    pinType3->addAction(new QAction("DATA_IN"));
    pinType3->addAction(new QAction("DATA_OUT"));
    pinType3->addAction(new QAction("NC"));
    QPushButton *pin3_14 = new QPushButton("Pin 3");
    QPushButton *pin3_16 = new QPushButton("Pin 3");
    QPushButton *pin3_20 = new QPushButton("Pin 3");
    pin3_14->setMenu(pinType3);
    pin3_16->setMenu(pinType3);
    pin3_20->setMenu(pinType3);
    lopGanChan14->addWidget(pin3_14, 2, 0);
    lopGanChan16->addWidget(pin3_16, 2, 0);
    lopGanChan20->addWidget(pin3_20, 2, 0);
    //    chan 4
    QMenu *pinType4 = new QMenu;
    pinType4->addAction(new QAction("VCC"));
    pinType4->addAction(new QAction("GND"));
    pinType4->addAction(new QAction("CLK"));
    pinType4->addAction(new QAction("DATA_IN"));
    pinType4->addAction(new QAction("DATA_OUT"));
    pinType4->addAction(new QAction("NC"));
    QPushButton *pin4_14 = new QPushButton("Pin 4");
    QPushButton *pin4_16 = new QPushButton("Pin 4");
    QPushButton *pin4_20 = new QPushButton("Pin 4");
    pin4_14->setMenu(pinType4);
    pin4_16->setMenu(pinType4);
    pin4_20->setMenu(pinType4);
    lopGanChan14->addWidget(pin4_14, 3, 0);
    lopGanChan16->addWidget(pin4_16, 3, 0);
    lopGanChan20->addWidget(pin4_20, 3, 0);
    //    chan 5
    QMenu *pinType5 = new QMenu;
    pinType5->addAction(new QAction("VCC"));
    pinType5->addAction(new QAction("GND"));
    pinType5->addAction(new QAction("CLK"));
    pinType5->addAction(new QAction("DATA_IN"));
    pinType5->addAction(new QAction("DATA_OUT"));
    pinType5->addAction(new QAction("NC"));
    QPushButton *pin5_14 = new QPushButton("Pin 5");
    QPushButton *pin5_16 = new QPushButton("Pin 5");
    QPushButton *pin5_20 = new QPushButton("Pin 5");
    pin5_14->setMenu(pinType5);
    pin5_16->setMenu(pinType5);
    pin5_20->setMenu(pinType5);
    lopGanChan14->addWidget(pin5_14, 4, 0);
    lopGanChan16->addWidget(pin5_16, 4, 0);
    lopGanChan20->addWidget(pin5_20, 4, 0);
    //    chan 6
    QMenu *pinType = new QMenu;
    pinType->setCursor(Qt::PointingHandCursor);
    //    pinType->setStyleSheet("background-color: #9AC7BF; color: red;");
    pinType->addAction(new QAction("VCC"));
    pinType->addAction(new QAction("GND"));
    pinType->addAction(new QAction("CLK"));
    pinType->addAction(new QAction("DATA_IN"));
    pinType->addAction(new QAction("DATA_OUT"));
    pinType->addAction(new QAction("NC"));
    QPushButton *pin6_14 = new QPushButton("Pin 6");
    QPushButton *pin6_16 = new QPushButton("Pin 6");
    QPushButton *pin6_20 = new QPushButton("Pin 6");
    pin6_14->setMenu(pinType);
    pin6_16->setMenu(pinType);
    pin6_20->setMenu(pinType);
    lopGanChan14->addWidget(pin6_14, 5, 0);
    lopGanChan16->addWidget(pin6_16, 5, 0);
    lopGanChan20->addWidget(pin6_20, 5, 0);
    //    chan 7
    QPushButton *pin7_14 = new QPushButton("Pin 7");
    QPushButton *pin7_16 = new QPushButton("Pin 7");
    QPushButton *pin7_20 = new QPushButton("Pin 7");
    pin7_14->setMenu(pinType);
    pin7_16->setMenu(pinType);
    pin7_20->setMenu(pinType);
    lopGanChan14->addWidget(pin7_14, 6, 0);
    lopGanChan16->addWidget(pin7_16, 6, 0);
    lopGanChan20->addWidget(pin7_20, 6, 0);
    //    chan 8
    QPushButton *pin8_14 = new QPushButton("Pin 8");
    QPushButton *pin8_16 = new QPushButton("Pin 8");
    QPushButton *pin8_20 = new QPushButton("Pin 8");
    pin8_14->setMenu(pinType);
    pin8_16->setMenu(pinType);
    pin8_20->setMenu(pinType);
    lopGanChan14->addWidget(pin8_14, 6, 2);
    lopGanChan16->addWidget(pin8_16, 7, 0);
    lopGanChan20->addWidget(pin8_20, 7, 0);
    //    Chan 9
    QPushButton *pin9_14 = new QPushButton("Pin 9");
    QPushButton *pin9_16 = new QPushButton("Pin 9");
    QPushButton *pin9_20 = new QPushButton("Pin 9");
    pin9_14->setMenu(pinType);
    pin9_16->setMenu(pinType);
    pin9_20->setMenu(pinType);
    lopGanChan14->addWidget(pin9_14, 5, 2);
    lopGanChan16->addWidget(pin9_16, 7, 2);
    lopGanChan20->addWidget(pin9_20, 8, 0);
    //    Chan 10
    QPushButton *pin10_14 = new QPushButton("Pin 10");
    QPushButton *pin10_16 = new QPushButton("Pin 10");
    QPushButton *pin10_20 = new QPushButton("Pin 10");
    pin10_14->setMenu(pinType);
    pin10_16->setMenu(pinType);
    pin10_20->setMenu(pinType);
    lopGanChan14->addWidget(pin10_14, 4, 2);
    lopGanChan16->addWidget(pin10_16, 6, 2);
    lopGanChan20->addWidget(pin10_20, 9, 0);
    //    Chan 11
    QPushButton *pin11_14 = new QPushButton("Pin 11");
    QPushButton *pin11_16 = new QPushButton("Pin 11");
    QPushButton *pin11_20 = new QPushButton("Pin 11");
    pin11_14->setMenu(pinType);
    pin11_16->setMenu(pinType);
    pin11_20->setMenu(pinType);
    lopGanChan14->addWidget(pin11_14, 3, 2);
    lopGanChan16->addWidget(pin11_16, 5, 2);
    lopGanChan20->addWidget(pin11_20, 9, 2);
    //    Chan 12
    QPushButton *pin12_14 = new QPushButton("Pin 12");
    QPushButton *pin12_16 = new QPushButton("Pin 12");
    QPushButton *pin12_20 = new QPushButton("Pin 12");
    pin12_14->setMenu(pinType);
    pin12_16->setMenu(pinType);
    pin12_20->setMenu(pinType);
    lopGanChan14->addWidget(pin12_14, 2, 2);
    lopGanChan16->addWidget(pin12_16, 4, 2);
    lopGanChan20->addWidget(pin12_20, 8, 2);
    //    Chan 13
    QPushButton *pin13_14 = new QPushButton("Pin13");
    QPushButton *pin13_16 = new QPushButton("Pin13");
    QPushButton *pin13_20 = new QPushButton("Pin13");
    pin13_14->setMenu(pinType);
    pin13_16->setMenu(pinType);
    pin13_20->setMenu(pinType);
    lopGanChan14->addWidget(pin13_14, 1, 2);
    lopGanChan16->addWidget(pin13_16, 3, 2);
    lopGanChan20->addWidget(pin13_20, 7, 2);
    //    Chan 14
    QPushButton *pin14_14 = new QPushButton("Pin 14");
    QPushButton *pin14_16 = new QPushButton("Pin 14");
    QPushButton *pin14_20 = new QPushButton("Pin 14");
    pin14_14->setMenu(pinType);
    pin14_16->setMenu(pinType);
    pin14_20->setMenu(pinType);
    lopGanChan14->addWidget(pin14_14, 0, 2);
    lopGanChan16->addWidget(pin14_16, 2, 2);
    lopGanChan20->addWidget(pin14_20, 6, 2);
    //    Chan 15
    QPushButton *pin15_16 = new QPushButton("Pin 15");
    QPushButton *pin15_20 = new QPushButton("Pin 15");
    pin15_16->setMenu(pinType);
    pin15_20->setMenu(pinType);
    lopGanChan16->addWidget(pin15_16, 1, 2);
    lopGanChan20->addWidget(pin15_20, 5, 2);
    //    Chan 16
    QPushButton *pin16_16 = new QPushButton("Pin 16");
    QPushButton *pin16_20 = new QPushButton("Pin 16");
    pin16_16->setMenu(pinType);
    pin16_20->setMenu(pinType);
    lopGanChan16->addWidget(pin16_16, 0, 2);
    lopGanChan20->addWidget(pin16_20, 4, 2);
    //    Chan 17
    QPushButton *pin17 = new QPushButton("Pin 17");
    pin17->setMenu(pinType);
    lopGanChan20->addWidget(pin17, 3, 2);
    //    Chan 18
    QPushButton *pin18 = new QPushButton("Pin 18");
    pin18->setMenu(pinType);
    lopGanChan20->addWidget(pin18, 2, 2);
    //    Chan 19
    QPushButton *pin19 = new QPushButton("Pin 19");
    pin19->setMenu(pinType);
    lopGanChan20->addWidget(pin19, 1, 2);
    //    Chan 20
    QPushButton *pin20 = new QPushButton("Pin 20");
    pin20->setMenu(pinType);
    lopGanChan20->addWidget(pin20, 0, 2);

    //    chen anh SymIC
    QLabel *imageLabelIC14 = new QLabel;
    QLabel *imageLabelIC16 = new QLabel;
    QLabel *imageLabelIC20 = new QLabel;
    QPixmap pixmap14("://resources/IC14.png"); // Đường dẫn đến tệp hình ảnh IC14
    QPixmap pixmap16("://resources/IC16.png"); // Đường dẫn đến tệp hình ảnh IC16
    QPixmap pixmap20("://resources/IC20.png"); // Đường dẫn đến tệp hình ảnh IC20
    QPixmap scaledPixmap14 = pixmap14.scaled(QSize(220, 340));
    QPixmap scaledPixmap16 = pixmap16.scaled(QSize(220, 370));
    QPixmap scaledPixmap20 = pixmap20.scaled(QSize(220, 400));

    QVBoxLayout *lopTrangHienSymDefault = new QVBoxLayout;
    QLabel *nhanTrangHienSymDefault = new QLabel(
        "Cấu hình chân cho IC kiểm tra tại đây\nHãy tham khảo Datasheet");
    nhanTrangHienSymDefault->setStyleSheet(
        "font-size: 18px;font-weight: bold; color: #0000FF; font-style: italic;");
    nhanTrangHienSymDefault->setAlignment(Qt::AlignCenter);

    QLabel *icontrangHienSymDefault = new QLabel;
    QPixmap pixmapIcon("://resources/SoftwareIcon.png"); // Đường dẫn đến tệp hình ảnh
    QPixmap scaledPixmapIcon = pixmapIcon.scaled(QSize(200, 200));
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(0); // Điều chỉnh độ mờ ở đây;
    icontrangHienSymDefault->setAlignment(Qt::AlignCenter);

    icontrangHienSymDefault->setGraphicsEffect(blurEffect);
    icontrangHienSymDefault->setPixmap(scaledPixmapIcon);

    lopTrangHienSymDefault->addWidget(new QLabel("  "));
    lopTrangHienSymDefault->addWidget(icontrangHienSymDefault);
    lopTrangHienSymDefault->addWidget(nhanTrangHienSymDefault);

    trangHienSymDefault->setLayout(lopTrangHienSymDefault);
    imageLabelIC14->setPixmap(scaledPixmap14);
    imageLabelIC14->setAlignment(Qt::AlignCenter);
    lopGanChan14->addWidget(imageLabelIC14, 0, 1, 7, 1);
    trangHienSymIC14->setLayout(lopGanChan14);
    imageLabelIC16->setPixmap(scaledPixmap16);
    imageLabelIC16->setAlignment(Qt::AlignCenter);
    lopGanChan16->addWidget(imageLabelIC16, 0, 1, 8, 1);
    trangHienSymIC16->setLayout(lopGanChan16);
    imageLabelIC20->setPixmap(scaledPixmap20);
    imageLabelIC20->setAlignment(Qt::AlignCenter);
    lopGanChan20->addWidget(imageLabelIC20, 0, 1, 10, 1);
    trangHienSymIC20->setLayout(lopGanChan20);

    lopCauHinhChan->addWidget(boxCauHinhChan);

    //    nhom hien thi
    QGroupBox *boxHienThi = new QGroupBox("Hiển thị thông tin IC");
    boxHienThi->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    QVBoxLayout *lopHienThi = new QVBoxLayout;
    QListView *danhSachThuocTinh = new QListView;
    danhSachThuocTinh->setStyleSheet("font-weight: nomal");
    danhSachThuocTinh->setFixedHeight(150);
    QTableView *bangGanChan = new QTableView;

    lopHienThi->addWidget(danhSachThuocTinh);
    lopHienThi->addWidget(bangGanChan);

    boxHienThi->setLayout(lopHienThi);

    //    Nut nhan
    QHBoxLayout *lopNext = new QHBoxLayout;
    QPushButton *next = new QPushButton("Tiếp Theo");
    next->setStyleSheet(
        "background-color: #009900;font-size: 16px;font-weight: bold; color: white");
    next->setFixedSize(200, 30);
    connect(next, SIGNAL(clicked(bool)), this, SLOT(opTrangCauHinhDuLieu()));
    QPushButton *datLai = new QPushButton("Đặt lại");
    datLai->setStyleSheet(
        "background-color: #009900;font-size: 16px;font-weight: bold; color: white");
    datLai->setFixedSize(200, 30);
    connect(datLai, SIGNAL(clicked(bool)), this, SLOT(opTrangCauHinhChan()));
    lopNext->addWidget(datLai);
    lopNext->addWidget(next);
    lopHienThi->addLayout(lopNext);

    lopCauHinhChanTong->addWidget(boxHienThi);

    //=============================================================================================
    trangCauHinhDuLieu = new QWidget;
    QPushButton *finish = new QPushButton("Finish");
    QPushButton *back = new QPushButton("Quay lại");
    QVBoxLayout *lopCauHinhDuLieu = new QVBoxLayout;
    lopCauHinhDuLieu->addWidget(finish);
    lopCauHinhDuLieu->addWidget(back);
    trangCauHinhDuLieu->setLayout(lopCauHinhDuLieu);

    connect(finish, SIGNAL(clicked(bool)), this, SLOT(opComplete()));
    connect(finish, SIGNAL(clicked(bool)), this, SLOT(opTrangCauHinhChan()));
    connect(back, &QPushButton::clicked, this, [this]() {
        khongGianTaoThuVien->setCurrentWidget(trangCauHinhChan);
    });

    khongGianTaoThuVien->addWidget(trangCauHinhChan);
    khongGianTaoThuVien->addWidget(trangCauHinhDuLieu);
    khongGianTaoThuVien->setCurrentWidget(trangCauHinhChan);

    QVBoxLayout *lopTaoThuVien = new QVBoxLayout;
    lopTaoThuVien->addWidget(khongGianTaoThuVien);
    QLabel *a = new QLabel("Tạo Thư Viện");
    lopTaoThuVien->addWidget(a);
    this->setLayout(lopTaoThuVien);
}
void TaoThuVien::opTrangCauHinhDuLieu()
{
    khongGianTaoThuVien->setCurrentWidget(trangCauHinhDuLieu);
}
void TaoThuVien::opTrangCauHinhChan()
{
    khongGianTaoThuVien->setCurrentWidget(trangCauHinhChan);
    khongGianHienSymIC->setCurrentWidget(trangHienSymDefault);
    boxCauHinhChan->setFixedHeight(400);
    tenIC->clear();
    moTaIC->clear();
}

void TaoThuVien::opComplete()
{
    QMessageBox::information(this, "Thông báo", "Tạo thư viện hoàn tất");
}
