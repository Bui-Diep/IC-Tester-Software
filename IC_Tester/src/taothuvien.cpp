#include "taothuvien.h"

TaoThuVien::TaoThuVien()
{
    khongGianTaoThuVien = new QStackedWidget;

    //    =============================================================================================
    trangCauHinhChan = new QWidget;
    lopCauHinhChan = new QVBoxLayout;
    QSplitter *splitCauHinhChanTong = new QSplitter(Qt::Horizontal);
    QWidget *widCauHinhChanTong = new QWidget(splitCauHinhChanTong);
    widCauHinhChanTong->setLayout(lopCauHinhChan);
    QHBoxLayout *lopTempTrangCauHinhChan = new QHBoxLayout(trangCauHinhChan);
    lopTempTrangCauHinhChan->addWidget(splitCauHinhChanTong);

    //    nhom thuoc tinh
    QGroupBox *boxThuocTinh = new QGroupBox();
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
    connect(nutHienSym, &QPushButton::clicked, [congNgheBanDan, soChanIC, this]() {
        if (!tenIC->text().isEmpty()) {
            QString textMoTaIC;
            if (!moTaIC->toPlainText().isEmpty()) {
                textMoTaIC = "<br><b>Ghi chú:</b> " + moTaIC->toPlainText();
            }
            auto placeholder = soChanIC->currentText();
            bangHienThiThuocTinhIC->setText(
                "<b>Tên IC:</b> " + tenIC->text() + "<br><b>Số chân IC:</b> " + placeholder
                + "<br><b>Công nghệ:</b> " + congNgheBanDan->currentText() + textMoTaIC);

            if (soChanIC->currentIndex() == 1) {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC14);
                boxCauHinhChan->setFixedHeight(400);
            } else if (soChanIC->currentText() == " 16 Chân") {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC16);
                boxCauHinhChan->setFixedHeight(420);
            } else if (soChanIC->currentText() == " 20 Chân") {
                khongGianHienSymIC->setCurrentWidget(trangHienSymIC20);
                boxCauHinhChan->setFixedHeight(455);
            } else {
                QMessageBox::information(this,
                                         "Thông báo",
                                         "IC" + soChanIC->currentText()
                                             + " chưa được hỗ trợ\nVui lòng chọn loại khác");
                khongGianHienSymIC->setCurrentWidget(trangHienSymDefault);
            };
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
    lopKhonGianHienSymIC->setAlignment(khongGianHienSymIC, Qt::AlignCenter);
    khongGianHienSymIC->setFixedWidth(500);
    lopGanChan14 = new QGridLayout;
    lopGanChan16 = new QGridLayout;
    lopGanChan20 = new QGridLayout;

    //    chan 1
    QMenu *pinType1 = new QMenu;
    pinType1->addAction(new QAction("VCC"));
    pinType1->addAction(new QAction("GND"));
    pinType1->addAction(new QAction("CLK"));
    pinType1->addAction(new QAction("DIN"));
    pinType1->addAction(new QAction("DOUT"));
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
    pinType2->addAction(new QAction("DIN"));
    pinType2->addAction(new QAction("DOUT"));
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
    pinType3->addAction(new QAction("DIN"));
    pinType3->addAction(new QAction("DOUT"));
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
    pinType4->addAction(new QAction("DIN"));
    pinType4->addAction(new QAction("DOUT"));
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
    pinType5->addAction(new QAction("DIN"));
    pinType5->addAction(new QAction("DOUT"));
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
    QMenu *pinType6 = new QMenu;
    pinType6->addAction(new QAction("VCC"));
    pinType6->addAction(new QAction("GND"));
    pinType6->addAction(new QAction("CLK"));
    pinType6->addAction(new QAction("DIN"));
    pinType6->addAction(new QAction("DOUT"));
    pinType6->addAction(new QAction("NC"));
    QPushButton *pin6_14 = new QPushButton("Pin 6");
    QPushButton *pin6_16 = new QPushButton("Pin 6");
    QPushButton *pin6_20 = new QPushButton("Pin 6");
    pin6_14->setMenu(pinType6);
    pin6_16->setMenu(pinType6);
    pin6_20->setMenu(pinType6);
    lopGanChan14->addWidget(pin6_14, 5, 0);
    lopGanChan16->addWidget(pin6_16, 5, 0);
    lopGanChan20->addWidget(pin6_20, 5, 0);
    //    chan 7
    QMenu *pinType7 = new QMenu;
    pinType7->addAction(new QAction("VCC"));
    pinType7->addAction(new QAction("GND"));
    pinType7->addAction(new QAction("CLK"));
    pinType7->addAction(new QAction("DIN"));
    pinType7->addAction(new QAction("DOUT"));
    pinType7->addAction(new QAction("NC"));
    QPushButton *pin7_14 = new QPushButton("Pin 7");
    QPushButton *pin7_16 = new QPushButton("Pin 7");
    QPushButton *pin7_20 = new QPushButton("Pin 7");
    pin7_14->setMenu(pinType7);
    pin7_16->setMenu(pinType7);
    pin7_20->setMenu(pinType7);
    lopGanChan14->addWidget(pin7_14, 6, 0);
    lopGanChan16->addWidget(pin7_16, 6, 0);
    lopGanChan20->addWidget(pin7_20, 6, 0);
    //    chan 8
    QMenu *pinType8 = new QMenu;
    pinType8->addAction(new QAction("VCC"));
    pinType8->addAction(new QAction("GND"));
    pinType8->addAction(new QAction("CLK"));
    pinType8->addAction(new QAction("DIN"));
    pinType8->addAction(new QAction("DOUT"));
    pinType8->addAction(new QAction("NC"));
    QPushButton *pin8_14 = new QPushButton("Pin 8");
    QPushButton *pin8_16 = new QPushButton("Pin 8");
    QPushButton *pin8_20 = new QPushButton("Pin 8");
    pin8_14->setMenu(pinType8);
    pin8_16->setMenu(pinType8);
    pin8_20->setMenu(pinType8);
    lopGanChan14->addWidget(pin8_14, 6, 2);
    lopGanChan16->addWidget(pin8_16, 7, 0);
    lopGanChan20->addWidget(pin8_20, 7, 0);
    //    Chan 9
    QMenu *pinType9 = new QMenu;
    pinType9->addAction(new QAction("VCC"));
    pinType9->addAction(new QAction("GND"));
    pinType9->addAction(new QAction("CLK"));
    pinType9->addAction(new QAction("DIN"));
    pinType9->addAction(new QAction("DOUT"));
    pinType9->addAction(new QAction("NC"));
    QPushButton *pin9_14 = new QPushButton("Pin 9");
    QPushButton *pin9_16 = new QPushButton("Pin 9");
    QPushButton *pin9_20 = new QPushButton("Pin 9");
    pin9_14->setMenu(pinType9);
    pin9_16->setMenu(pinType9);
    pin9_20->setMenu(pinType9);
    lopGanChan14->addWidget(pin9_14, 5, 2);
    lopGanChan16->addWidget(pin9_16, 7, 2);
    lopGanChan20->addWidget(pin9_20, 8, 0);
    //    Chan 10
    QMenu *pinType10 = new QMenu;
    pinType10->addAction(new QAction("VCC"));
    pinType10->addAction(new QAction("GND"));
    pinType10->addAction(new QAction("CLK"));
    pinType10->addAction(new QAction("DIN"));
    pinType10->addAction(new QAction("DOUT"));
    pinType10->addAction(new QAction("NC"));
    QPushButton *pin10_14 = new QPushButton("Pin 10");
    QPushButton *pin10_16 = new QPushButton("Pin 10");
    QPushButton *pin10_20 = new QPushButton("Pin 10");
    pin10_14->setMenu(pinType10);
    pin10_16->setMenu(pinType10);
    pin10_20->setMenu(pinType10);
    lopGanChan14->addWidget(pin10_14, 4, 2);
    lopGanChan16->addWidget(pin10_16, 6, 2);
    lopGanChan20->addWidget(pin10_20, 9, 0);
    //    Chan 11
    QMenu *pinType11 = new QMenu;
    pinType11->addAction(new QAction("VCC"));
    pinType11->addAction(new QAction("GND"));
    pinType11->addAction(new QAction("CLK"));
    pinType11->addAction(new QAction("DIN"));
    pinType11->addAction(new QAction("DOUT"));
    pinType11->addAction(new QAction("NC"));
    QPushButton *pin11_14 = new QPushButton("Pin 11");
    QPushButton *pin11_16 = new QPushButton("Pin 11");
    QPushButton *pin11_20 = new QPushButton("Pin 11");
    pin11_14->setMenu(pinType11);
    pin11_16->setMenu(pinType11);
    pin11_20->setMenu(pinType11);
    lopGanChan14->addWidget(pin11_14, 3, 2);
    lopGanChan16->addWidget(pin11_16, 5, 2);
    lopGanChan20->addWidget(pin11_20, 9, 2);
    //    Chan 12
    QMenu *pinType12 = new QMenu;
    pinType12->addAction(new QAction("VCC"));
    pinType12->addAction(new QAction("GND"));
    pinType12->addAction(new QAction("CLK"));
    pinType12->addAction(new QAction("DIN"));
    pinType12->addAction(new QAction("DOUT"));
    pinType12->addAction(new QAction("NC"));
    QPushButton *pin12_14 = new QPushButton("Pin 12");
    QPushButton *pin12_16 = new QPushButton("Pin 12");
    QPushButton *pin12_20 = new QPushButton("Pin 12");
    pin12_14->setMenu(pinType12);
    pin12_16->setMenu(pinType12);
    pin12_20->setMenu(pinType12);
    lopGanChan14->addWidget(pin12_14, 2, 2);
    lopGanChan16->addWidget(pin12_16, 4, 2);
    lopGanChan20->addWidget(pin12_20, 8, 2);
    //    Chan 13
    QMenu *pinType13 = new QMenu;
    pinType13->addAction(new QAction("VCC"));
    pinType13->addAction(new QAction("GND"));
    pinType13->addAction(new QAction("CLK"));
    pinType13->addAction(new QAction("DIN"));
    pinType13->addAction(new QAction("DOUT"));
    pinType13->addAction(new QAction("NC"));
    QPushButton *pin13_14 = new QPushButton("Pin 13");
    QPushButton *pin13_16 = new QPushButton("Pin 13");
    QPushButton *pin13_20 = new QPushButton("Pin 13");
    pin13_14->setMenu(pinType13);
    pin13_16->setMenu(pinType13);
    pin13_20->setMenu(pinType13);
    lopGanChan14->addWidget(pin13_14, 1, 2);
    lopGanChan16->addWidget(pin13_16, 3, 2);
    lopGanChan20->addWidget(pin13_20, 7, 2);
    //    Chan 14
    QMenu *pinType14 = new QMenu;
    pinType14->addAction(new QAction("VCC"));
    pinType14->addAction(new QAction("GND"));
    pinType14->addAction(new QAction("CLK"));
    pinType14->addAction(new QAction("DIN"));
    pinType14->addAction(new QAction("DOUT"));
    pinType14->addAction(new QAction("NC"));
    QPushButton *pin14_14 = new QPushButton("Pin 14");
    QPushButton *pin14_16 = new QPushButton("Pin 14");
    QPushButton *pin14_20 = new QPushButton("Pin 14");
    pin14_14->setMenu(pinType14);
    pin14_16->setMenu(pinType14);
    pin14_20->setMenu(pinType14);
    lopGanChan14->addWidget(pin14_14, 0, 2);
    lopGanChan16->addWidget(pin14_16, 2, 2);
    lopGanChan20->addWidget(pin14_20, 6, 2);
    //    Chan 15
    QMenu *pinType15 = new QMenu;
    pinType15->addAction(new QAction("VCC"));
    pinType15->addAction(new QAction("GND"));
    pinType15->addAction(new QAction("CLK"));
    pinType15->addAction(new QAction("DIN"));
    pinType15->addAction(new QAction("DOUT"));
    pinType15->addAction(new QAction("NC"));
    QPushButton *pin15_16 = new QPushButton("Pin 15");
    QPushButton *pin15_20 = new QPushButton("Pin 15");
    pin15_16->setMenu(pinType15);
    pin15_20->setMenu(pinType15);
    lopGanChan16->addWidget(pin15_16, 1, 2);
    lopGanChan20->addWidget(pin15_20, 5, 2);
    //    Chan 16
    QMenu *pinType16 = new QMenu;
    pinType16->addAction(new QAction("VCC"));
    pinType16->addAction(new QAction("GND"));
    pinType16->addAction(new QAction("CLK"));
    pinType16->addAction(new QAction("DIN"));
    pinType16->addAction(new QAction("DOUT"));
    pinType16->addAction(new QAction("NC"));
    QPushButton *pin16_16 = new QPushButton("Pin 16");
    QPushButton *pin16_20 = new QPushButton("Pin 16");
    pin16_16->setMenu(pinType16);
    pin16_20->setMenu(pinType16);
    lopGanChan16->addWidget(pin16_16, 0, 2);
    lopGanChan20->addWidget(pin16_20, 4, 2);
    //    Chan 17
    QMenu *pinType17 = new QMenu;
    pinType17->addAction(new QAction("VCC"));
    pinType17->addAction(new QAction("GND"));
    pinType17->addAction(new QAction("CLK"));
    pinType17->addAction(new QAction("DIN"));
    pinType17->addAction(new QAction("DOUT"));
    pinType17->addAction(new QAction("NC"));
    QPushButton *pin17 = new QPushButton("Pin 17");
    pin17->setMenu(pinType17);
    lopGanChan20->addWidget(pin17, 3, 2);
    //    Chan 18
    QMenu *pinType18 = new QMenu;
    pinType18->addAction(new QAction("VCC"));
    pinType18->addAction(new QAction("GND"));
    pinType18->addAction(new QAction("CLK"));
    pinType18->addAction(new QAction("DIN"));
    pinType18->addAction(new QAction("DOUT"));
    pinType18->addAction(new QAction("NC"));
    QPushButton *pin18 = new QPushButton("Pin 18");
    pin18->setMenu(pinType18);
    lopGanChan20->addWidget(pin18, 2, 2);
    //    Chan 19
    QMenu *pinType19 = new QMenu;
    pinType19->addAction(new QAction("VCC"));
    pinType19->addAction(new QAction("GND"));
    pinType19->addAction(new QAction("CLK"));
    pinType19->addAction(new QAction("DIN"));
    pinType19->addAction(new QAction("DOUT"));
    pinType19->addAction(new QAction("NC"));
    QPushButton *pin19 = new QPushButton("Pin 19");
    pin19->setMenu(pinType19);
    lopGanChan20->addWidget(pin19, 1, 2);
    //    Chan 20
    QMenu *pinType20 = new QMenu;
    pinType20->addAction(new QAction("VCC"));
    pinType20->addAction(new QAction("GND"));
    pinType20->addAction(new QAction("CLK"));
    pinType20->addAction(new QAction("DIN"));
    pinType20->addAction(new QAction("DOUT"));
    pinType20->addAction(new QAction("NC"));
    QPushButton *pin20 = new QPushButton("Pin 20");
    pin20->setMenu(pinType20);
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
        "font-size: 18px;font-weight: 550; color: #0000FF; font-style: italic;");
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
    QGroupBox *boxHienThi = new QGroupBox("Hiển thị thông tin");
    boxHienThi->setStyleSheet("font-weight: bold;font-size: 16px; color: #0000FF");
    lopHienThiThuocTinhIC = new QGridLayout;

    bangHienThiThuocTinhIC = new QLabel;
    bangHienThiThuocTinhIC->setStyleSheet("font-weight: 400;font-size: 15px; color: black");
    bangHienThiThuocTinhIC->setWordWrap(true);

    //hien thi Icon socket
    QFrame *khungSocket20 = new QFrame;
    khungSocket20->setObjectName("khungSocket20"); // Đặt tên cho việc trang trí CSS sau này
    khungSocket20->setFixedHeight(370);            // Đặt kích thước hình chữ nhật
    khungSocket20->setStyleSheet("QFrame#khungSocket20 {"
                                 "   background-color: red;"
                                 "   border: 2px solid black;"
                                 "   border-radius: 10px;"
                                 "}");
    QLabel *chanSocketIC[10][3];
    QGridLayout *lopKhungChan = new QGridLayout(khungSocket20);
    QLabel *space = new QLabel("    ");

    space->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    lopKhungChan->addWidget(space, 1, 1);
    // Vòng lặp để tạo và đặt tên cho 20 hình tròn và lưu vào mảng hai chiều
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanSocketIC[i][j] = new QLabel("NC");
            chanSocketIC[i][j]->setAlignment(Qt::AlignCenter);
            chanSocketIC[i][j]->setFixedSize(30, 30);
            chanSocketIC[i][j]->setStyleSheet(
                "background-color: white; border-radius: 15px; font-size: 10px;");

            // Đặt tên cho con trỏ dựa trên số đếm i và j
            QString tenChanSocketIC = QString("chanSocKet_%1%2").arg(i).arg(j);
            chanSocketIC[i][j]->setObjectName(tenChanSocketIC);

            lopKhungChan->addWidget(chanSocketIC[i][j], i, j);
        }
    }

    QList<QAction *> acPin1 = pinType1->actions();
    QList<QAction *> acPin2 = pinType2->actions();
    QList<QAction *> acPin3 = pinType3->actions();
    QList<QAction *> acPin4 = pinType4->actions();
    QList<QAction *> acPin5 = pinType5->actions();
    QList<QAction *> acPin6 = pinType6->actions();
    QList<QAction *> acPin7 = pinType7->actions();
    QList<QAction *> acPin8 = pinType8->actions();
    QList<QAction *> acPin9 = pinType9->actions();
    QList<QAction *> acPin10 = pinType10->actions();
    QList<QAction *> acPin11 = pinType11->actions();
    QList<QAction *> acPin12 = pinType12->actions();
    QList<QAction *> acPin13 = pinType13->actions();
    QList<QAction *> acPin14 = pinType14->actions();
    QList<QAction *> acPin15 = pinType15->actions();
    QList<QAction *> acPin16 = pinType16->actions();
    QList<QAction *> acPin17 = pinType17->actions();
    QList<QAction *> acPin18 = pinType18->actions();
    QList<QAction *> acPin19 = pinType19->actions();
    QList<QAction *> acPin20 = pinType20->actions();

    for (int i = 0; i < 6; ++i) {
        QAction *acTick1 = acPin1.at(i);
        connect(acTick1, &QAction::triggered, [chanSocketIC, acTick1]() {
            chanSocketIC[0][0]->setText(acTick1->text());
        });
        QAction *acTick2 = acPin2.at(i);
        connect(acTick2, &QAction::triggered, [chanSocketIC, acTick2]() {
            chanSocketIC[1][0]->setText(acTick2->text());
        });
        QAction *acTick3 = acPin3.at(i);
        connect(acTick3, &QAction::triggered, [chanSocketIC, acTick3]() {
            chanSocketIC[2][0]->setText(acTick3->text());
        });
        QAction *acTick4 = acPin4.at(i);
        connect(acTick4, &QAction::triggered, [chanSocketIC, acTick4]() {
            chanSocketIC[3][0]->setText(acTick4->text());
        });
        QAction *acTick5 = acPin5.at(i);
        connect(acTick5, &QAction::triggered, [chanSocketIC, acTick5]() {
            chanSocketIC[4][0]->setText(acTick5->text());
        });
        QAction *acTick6 = acPin6.at(i);
        connect(acTick6, &QAction::triggered, [chanSocketIC, acTick6]() {
            chanSocketIC[5][0]->setText(acTick6->text());
        });
        QAction *acTick7 = acPin7.at(i);
        connect(acTick7, &QAction::triggered, [chanSocketIC, acTick7]() {
            chanSocketIC[6][0]->setText(acTick7->text());
        });
        QAction *acTick8 = acPin8.at(i);
        connect(acTick8, &QAction::triggered, [chanSocketIC, acTick8, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[6][2]->setText(acTick8->text());
            } else {
                chanSocketIC[7][0]->setText(acTick8->text());
            }
        });
        QAction *acTick9 = acPin9.at(i);
        connect(acTick9, &QAction::triggered, [chanSocketIC, acTick9, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[5][2]->setText(acTick9->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[7][2]->setText(acTick9->text());
            } else {
                chanSocketIC[8][0]->setText(acTick9->text());
            }
        });
        QAction *acTick10 = acPin10.at(i);
        connect(acTick10, &QAction::triggered, [chanSocketIC, acTick10, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[4][2]->setText(acTick10->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[6][2]->setText(acTick10->text());
            } else {
                chanSocketIC[9][0]->setText(acTick10->text());
            }
        });
        QAction *acTick11 = acPin11.at(i);
        connect(acTick11, &QAction::triggered, [chanSocketIC, acTick11, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[3][2]->setText(acTick11->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[5][2]->setText(acTick11->text());
            } else {
                chanSocketIC[9][2]->setText(acTick11->text());
            }
        });
        QAction *acTick12 = acPin12.at(i);
        connect(acTick12, &QAction::triggered, [chanSocketIC, acTick12, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[2][2]->setText(acTick12->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[4][2]->setText(acTick12->text());
            } else {
                chanSocketIC[8][2]->setText(acTick12->text());
            }
        });
        QAction *acTick13 = acPin13.at(i);
        connect(acTick13, &QAction::triggered, [chanSocketIC, acTick13, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[1][2]->setText(acTick13->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[3][2]->setText(acTick13->text());
            } else {
                chanSocketIC[7][2]->setText(acTick13->text());
            }
        });
        QAction *acTick14 = acPin14.at(i);
        connect(acTick14, &QAction::triggered, [chanSocketIC, acTick14, soChanIC]() {
            if (soChanIC->currentText() == " 14 Chân") {
                chanSocketIC[0][2]->setText(acTick14->text());
            } else if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[2][2]->setText(acTick14->text());
            } else {
                chanSocketIC[6][2]->setText(acTick14->text());
            }
        });
        QAction *acTick15 = acPin15.at(i);
        connect(acTick15, &QAction::triggered, [chanSocketIC, acTick15, soChanIC]() {
            if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[1][2]->setText(acTick15->text());
            } else {
                chanSocketIC[5][2]->setText(acTick15->text());
            }
        });
        QAction *acTick16 = acPin16.at(i);
        connect(acTick16, &QAction::triggered, [chanSocketIC, acTick16, soChanIC]() {
            if (soChanIC->currentText() == " 16 Chân") {
                chanSocketIC[0][2]->setText(acTick16->text());
            } else {
                chanSocketIC[4][2]->setText(acTick16->text());
            }
        });
        QAction *acTick17 = acPin17.at(i);
        connect(acTick17, &QAction::triggered, [chanSocketIC, acTick17]() {
            chanSocketIC[3][2]->setText(acTick17->text());
        });
        QAction *acTick18 = acPin18.at(i);
        connect(acTick18, &QAction::triggered, [chanSocketIC, acTick18]() {
            chanSocketIC[2][2]->setText(acTick18->text());
        });
        QAction *acTick19 = acPin19.at(i);
        connect(acTick19, &QAction::triggered, [chanSocketIC, acTick19]() {
            chanSocketIC[1][2]->setText(acTick19->text());
        });
        QAction *acTick20 = acPin20.at(i);
        connect(acTick20, &QAction::triggered, [chanSocketIC, acTick20]() {
            chanSocketIC[0][2]->setText(acTick20->text());
        });
    }
    lopHienThiThuocTinhIC->addWidget(new QLabel(""), 1, 0);
    lopHienThiThuocTinhIC->addWidget(khungSocket20, 2, 1);
    lopHienThiThuocTinhIC->addWidget(new QLabel(""), 3, 2);
    lopHienThiThuocTinhIC->setAlignment(khungSocket20, Qt::AlignCenter);

    boxHienThi->setLayout(lopHienThiThuocTinhIC);

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
    connect(datLai, &QPushButton::clicked, [chanSocketIC]() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; j += 2) {
                chanSocketIC[i][j]->setText("NC");
            }
        }
    });
    lopNext->addWidget(datLai);
    //    lopNext->addWidget(new QLabel("                                           "));
    lopNext->addWidget(next);
    lopHienThiThuocTinhIC->addWidget(bangHienThiThuocTinhIC, 0, 0, 1, 3);
    lopHienThiThuocTinhIC->addLayout(lopNext, 4, 0, 1, 3);

    splitCauHinhChanTong->addWidget(boxHienThi);

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
    bangHienThiThuocTinhIC->clear();
    tenIC->clear();
    moTaIC->clear();
}

void TaoThuVien::opComplete()
{
    QMessageBox::information(this, "Thông báo", "Tạo thư viện hoàn tất");
}
