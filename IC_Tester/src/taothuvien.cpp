#include "taothuvien.h"

MyButton::MyButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent)
{
    setText(text);
}

void MyButton::enterEvent(QEnterEvent *event)
{
    QPushButton::enterEvent(event);
    emit entered();
}

void MyButton::leaveEvent(QEvent *event)
{
    QPushButton::leaveEvent(event);
    emit left();
}

TaoThuVien::TaoThuVien()
{
    //=============================================================
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
    congNgheBanDan->addItem(" CMOS (3.3V)");
    congNgheBanDan->addItem(" TTL (5V)");
    lopThuocTinh->addRow("Công nghệ:", congNgheBanDan);
    lopThuocTinhChung->addLayout(lopThuocTinh);
    lopThuocTinhChung->addLayout(lopNutHienSym);
    boxThuocTinh->setLayout(lopThuocTinhChung);
    lopCauHinhChan->addWidget(boxThuocTinh);
    moTaIC = new QTextEdit;
    lopThuocTinh->addRow("Mô tả:", moTaIC);
    moTaIC->setPlaceholderText("Mô tả IC tại đây ...");
    connect(nutHienSym, &QPushButton::clicked, [congNgheBanDan, soChanIC, this]() {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 3; j += 2) {
                chanSocketIC[i][j]->setText("NC");
            }
        }
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

    //    Tạo và kết nối tín hiệu từ box cấu hình chân IC với Sym trên box hiển thị thông tin
    QMenu *pinType14[14];
    MyButton *pin14L[7];
    for (int i = 0; i < 7; ++i) {
        pinType14[i] = new QMenu;
        pinType14[i]->addAction(new QAction("VCC"));
        pinType14[i]->addAction(new QAction("GND"));
        pinType14[i]->addAction(new QAction("CLK"));
        pinType14[i]->addAction(new QAction("DIN"));
        pinType14[i]->addAction(new QAction("DOUT"));
        pinType14[i]->addAction(new QAction("NC"));
        QString pL = QString::number(i + 1);
        pin14L[i] = new MyButton("Pin " + pL);
        pin14L[i]->setMenu(pinType14[i]);
        lopGanChan14->addWidget(pin14L[i], i, 0);
    }

    MyButton *pin14R[7];
    for (int i = 0; i < 7; ++i) {
        pinType14[i + 7] = new QMenu;
        pinType14[i + 7]->addAction(new QAction("VCC"));
        pinType14[i + 7]->addAction(new QAction("GND"));
        pinType14[i + 7]->addAction(new QAction("CLK"));
        pinType14[i + 7]->addAction(new QAction("DIN"));
        pinType14[i + 7]->addAction(new QAction("DOUT"));
        pinType14[i + 7]->addAction(new QAction("NC"));
        QString pR = QString::number(14 - i);
        pin14R[i] = new MyButton("Pin " + pR);
        pin14R[i]->setMenu(pinType14[i + 7]);
        lopGanChan14->addWidget(pin14R[i], i, 2);
    }

    QList<QAction *> acPin14[14];
    for (int i = 0; i < 14; ++i) {
        acPin14[i] = pinType14[i]->actions();
    }

    QAction *acTick14[14];
    for (int n = 0; n < 7; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick14[n] = acPin14[n].at(i);
            connect(acTick14[n], &QAction::hovered, [this, acTick14, n]() {
                chanSocketIC[n][0]->setText(acTick14[n]->text());
            });
        }
    }
    for (int n = 0; n < 7; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick14[n + 7] = acPin14[n + 7].at(i);
            connect(acTick14[n + 7], &QAction::hovered, [this, acTick14, n]() {
                chanSocketIC[n][2]->setText(acTick14[n + 7]->text());
            });
        }
    }

    for (int i = 0; i < 7; ++i) {
        pin14L[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin14L[i]->setStyleSheet("QPushButton:hover { background-color: yellow;}");
        connect(pinType14[i], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType14[i], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin14L[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin14L[i], &MyButton::left, [i, this, pinType14]() {
            if (!pinType14[i]->isVisible()) {
                chanSocketIC[i][0]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
        pin14R[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin14R[i]->setStyleSheet("QPushButton:hover { background-color: yellow; }");
        connect(pinType14[i + 7], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType14[i + 7], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin14R[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin14R[i], &MyButton::left, [i, this, pinType14]() {
            if (!pinType14[i + 7]->isVisible()) {
                chanSocketIC[i][2]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
    }

    QMenu *pinType16[16];
    MyButton *pin16L[8];
    for (int i = 0; i < 8; ++i) {
        pinType16[i] = new QMenu;
        pinType16[i]->addAction(new QAction("VCC"));
        pinType16[i]->addAction(new QAction("GND"));
        pinType16[i]->addAction(new QAction("CLK"));
        pinType16[i]->addAction(new QAction("DIN"));
        pinType16[i]->addAction(new QAction("DOUT"));
        pinType16[i]->addAction(new QAction("NC"));
        QString pL = QString::number(i + 1);
        pin16L[i] = new MyButton("Pin " + pL);
        pin16L[i]->setMenu(pinType16[i]);
        lopGanChan16->addWidget(pin16L[i], i, 0);
    }

    MyButton *pin16R[8];
    for (int i = 0; i < 8; ++i) {
        pinType16[i + 8] = new QMenu;
        pinType16[i + 8]->addAction(new QAction("VCC"));
        pinType16[i + 8]->addAction(new QAction("GND"));
        pinType16[i + 8]->addAction(new QAction("CLK"));
        pinType16[i + 8]->addAction(new QAction("DIN"));
        pinType16[i + 8]->addAction(new QAction("DOUT"));
        pinType16[i + 8]->addAction(new QAction("NC"));
        QString pR = QString::number(16 - i);
        pin16R[i] = new MyButton("Pin " + pR);
        pin16R[i]->setMenu(pinType16[i + 8]);
        lopGanChan16->addWidget(pin16R[i], i, 2);
    }

    QList<QAction *> acPin16[16];
    for (int i = 0; i < 16; ++i) {
        acPin16[i] = pinType16[i]->actions();
    }

    QAction *acTick16[16];
    for (int n = 0; n < 8; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick16[n] = acPin16[n].at(i);
            connect(acTick16[n], &QAction::hovered, [this, acTick16, n]() {
                chanSocketIC[n][0]->setText(acTick16[n]->text());
            });
        }
    }
    for (int n = 0; n < 8; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick16[n + 8] = acPin16[n + 8].at(i);
            connect(acTick16[n + 8], &QAction::hovered, [this, acTick16, n]() {
                chanSocketIC[n][2]->setText(acTick16[n + 8]->text());
            });
        }
    }

    for (int i = 0; i < 8; ++i) {
        pin16L[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin16L[i]->setStyleSheet("QPushButton:hover { background-color: yellow;}");
        connect(pinType16[i], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType16[i], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin16L[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin16L[i], &MyButton::left, [i, this, pinType16]() {
            if (!pinType16[i]->isVisible()) {
                chanSocketIC[i][0]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
        pin16R[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin16R[i]->setStyleSheet("QPushButton:hover { background-color: yellow; }");
        connect(pinType16[i + 8], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType16[i + 8], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin16R[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin16R[i], &MyButton::left, [i, this, pinType16]() {
            if (!pinType16[i + 8]->isVisible()) {
                chanSocketIC[i][2]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
    }

    QMenu *pinType20[20];
    MyButton *pin20L[10];
    for (int i = 0; i < 10; ++i) {
        pinType20[i] = new QMenu;
        pinType20[i]->addAction(new QAction("VCC"));
        pinType20[i]->addAction(new QAction("GND"));
        pinType20[i]->addAction(new QAction("CLK"));
        pinType20[i]->addAction(new QAction("DIN"));
        pinType20[i]->addAction(new QAction("DOUT"));
        pinType20[i]->addAction(new QAction("NC"));
        QString pL = QString::number(i + 1);
        pin20L[i] = new MyButton("Pin " + pL);
        pin20L[i]->setMenu(pinType20[i]);
        lopGanChan20->addWidget(pin20L[i], i, 0);
    }

    MyButton *pin20R[10];
    for (int i = 0; i < 10; ++i) {
        pinType20[i + 10] = new QMenu;
        pinType20[i + 10]->addAction(new QAction("VCC"));
        pinType20[i + 10]->addAction(new QAction("GND"));
        pinType20[i + 10]->addAction(new QAction("CLK"));
        pinType20[i + 10]->addAction(new QAction("DIN"));
        pinType20[i + 10]->addAction(new QAction("DOUT"));
        pinType20[i + 10]->addAction(new QAction("NC"));
        QString pR = QString::number(20 - i);
        pin20R[i] = new MyButton("Pin " + pR);
        pin20R[i]->setMenu(pinType20[i + 10]);
        lopGanChan20->addWidget(pin20R[i], i, 2);
    }

    QList<QAction *> acPin20[20];
    for (int i = 0; i < 20; ++i) {
        acPin20[i] = pinType20[i]->actions();
    }

    QAction *acTick20[20];
    for (int n = 0; n < 10; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick20[n] = acPin20[n].at(i);
            connect(acTick20[n], &QAction::hovered, [this, acTick20, n]() {
                chanSocketIC[n][0]->setText(acTick20[n]->text());
            });
        }
    }
    for (int n = 0; n < 10; ++n) {
        for (int i = 0; i < 6; ++i) {
            acTick20[n + 10] = acPin20[n + 10].at(i);
            connect(acTick20[n + 10], &QAction::hovered, [this, acTick20, n]() {
                chanSocketIC[n][2]->setText(acTick20[n + 10]->text());
            });
        }
    }
    for (int i = 0; i < 10; ++i) {
        pin20L[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin20L[i]->setStyleSheet("QPushButton:hover { background-color: yellow;}");
        connect(pinType20[i], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType20[i], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin20L[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][0]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin20L[i], &MyButton::left, [i, this, pinType20]() {
            if (!pinType20[i]->isVisible()) {
                chanSocketIC[i][0]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
        pin20R[i]->setCursor(QCursor(Qt::PointingHandCursor));
        pin20R[i]->setStyleSheet("QPushButton:hover { background-color: yellow; }");
        connect(pinType20[i + 10], &QMenu::aboutToShow, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pinType20[i + 10], &QMenu::aboutToHide, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: white;border-radius: 12px; font-size: 12px;");
        });
        connect(pin20R[i], &MyButton::entered, [i, this]() {
            chanSocketIC[i][2]->setStyleSheet(
                "background-color: yellow; border-radius: 12px; font-size: 12px;");
        });
        connect(pin20R[i], &MyButton::left, [i, this, pinType20]() {
            if (!pinType20[i + 10]->isVisible()) {
                chanSocketIC[i][2]->setStyleSheet(
                    "background-color: white; border-radius: 12px; font-size: 12px;");
            }
        });
    }

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
    bangHienThiThuocTinhIC->setFixedHeight(140);
    bangHienThiThuocTinhIC->setAlignment(Qt::AlignTop);

    //hien thi Icon socket
    QFrame *khungSocket20 = new QFrame;
    khungSocket20->setObjectName("khungSocket20"); // Đặt tên cho việc trang trí CSS sau này
    khungSocket20->setFixedHeight(400);            // Đặt kích thước hình chữ nhật
    khungSocket20->setStyleSheet("QFrame#khungSocket20 {"
                                 "   background-color: #999999;"
                                 "   border: 2px solid black;"
                                 "   border-radius: 10px;"
                                 "}");
    QGridLayout *lopKhungChan = new QGridLayout(khungSocket20);
    QLabel *space = new QLabel("Socket IC\n 20 Chân");

    space->setStyleSheet("background-color: rgba(0, 0, 0, 0); color: white");

    lopKhungChan->addWidget(space, 4, 1, 2, 1, Qt::AlignCenter);
    // Vòng lặp để tạo và đặt tên cho 20 hình tròn và lưu vào mảng hai chiều
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanSocketIC[i][j] = new QLabel("NC");
            chanSocketIC[i][j]->setAlignment(Qt::AlignCenter);
            chanSocketIC[i][j]->setFixedSize(40, 28);
            chanSocketIC[i][j]->setStyleSheet(
                "background-color: white; border-radius: 12px; font-size: 12px;");

            // Đặt tên cho con trỏ dựa trên số đếm i và j
            QString tenChanSocketIC = QString("chanSocKet_%1%2").arg(i).arg(j);
            chanSocketIC[i][j]->setObjectName(tenChanSocketIC);

            lopKhungChan->addWidget(chanSocketIC[i][j], i, j);
        }
    }

    lopHienThiThuocTinhIC->addWidget(new QLabel(""), 1, 0);
    lopHienThiThuocTinhIC->addWidget(khungSocket20, 2, 1);
    lopHienThiThuocTinhIC->addWidget(new QLabel(""), 3, 2);
    lopHienThiThuocTinhIC->setAlignment(khungSocket20, Qt::AlignCenter);

    boxHienThi->setLayout(lopHienThiThuocTinhIC);

    //    Nut nhan
    QHBoxLayout *lopNutNhanCauHinhChanIC = new QHBoxLayout;
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
    lopNutNhanCauHinhChanIC->addWidget(datLai);
    lopNutNhanCauHinhChanIC->addWidget(next);
    lopHienThiThuocTinhIC->addWidget(bangHienThiThuocTinhIC, 0, 0, 1, 3);
    lopHienThiThuocTinhIC->addLayout(lopNutNhanCauHinhChanIC, 4, 0, 1, 3);

    splitCauHinhChanTong->addWidget(boxHienThi);

    //=============================================================
    trangCauHinhDuLieu = new QWidget;
    QSplitter *splitCauHinhDuLieu = new QSplitter(Qt::Horizontal);

    //    tạo bảng cấu hình dữ liệu 20 chân
    QFrame *khungCauHinhDuLieu20 = new QFrame;
    QFrame *khungSymIC20 = new QFrame;
    khungCauHinhDuLieu20->setObjectName(
        "khungCauHinhDuLieu20");          // Đặt tên cho việc trang trí CSS sau này
    khungSymIC20->setFixedSize(250, 485); // Đặt kích thước hình chữ nhật
    khungSymIC20->setStyleSheet(
        "font-size: 20px; color: blue; font-weight: bold; background-color: rgba(0, 0, 0, 0);");
    khungCauHinhDuLieu20->setStyleSheet("QFrame#khungCauHinhDuLieu20 {"
                                        "   background-color: #A8D9D0;"
                                        "   border: 2px solid black;"
                                        "   border-radius: 10px;"
                                        "}");

    QGridLayout *lopKhungCauHinhDuLieu20 = new QGridLayout(khungCauHinhDuLieu20);
    QGridLayout *lopChuaKhungCauHinhDuLieu20 = new QGridLayout(khungSymIC20);
    lopChuaKhungCauHinhDuLieu20->addWidget(khungCauHinhDuLieu20, 0, 1, 10, 1);

    for (int i = 0; i < 10; ++i) {
        QString pL = QString::number(i + 1);
        QString pR = QString::number(i + 11);
        lopKhungCauHinhDuLieu20->addWidget(new QLabel(pL), i, 0, Qt::AlignCenter);
        lopKhungCauHinhDuLieu20->addWidget(new QLabel(pR), 9 - i, 2, Qt::AlignCenter);
    }
    //    QLabel *space2 = new QLabel("               ");

    //    space2->setStyleSheet("background-color: rgba(0, 0, 0, 0);");
    lopKhungCauHinhDuLieu20->addWidget(new QLabel("               "), 1, 1);

    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanDuLieuIC20[i][j] = new QPushButton("X");
            chanDuLieuIC20[i][j]->setFixedSize(32, 32);
            chanDuLieuIC20[i][j]->setStyleSheet("background-color: white;"
                                                " border-radius: 16px; "
                                                " font-size: 16px;"
                                                " font-weight: bold;"
                                                " color: blue;"
                                                " border: 1px solid blue;");

            // Đặt tên cho con trỏ dựa trên số đếm i và j
            QString tenchanDuLieuIC20 = QString("chanDuLieu_%1%2").arg(i).arg(j);
            chanDuLieuIC20[i][j]->setObjectName(tenchanDuLieuIC20);

            lopChuaKhungCauHinhDuLieu20->addWidget(chanDuLieuIC20[i][j], i, j, Qt::AlignCenter);
        }
    }
    int *state20[20]; // 20 biến trạng thái cho 20 nút
    // Thiết lập toàn bộ mảng state20 bằng 0
    for (int i = 0; i < 20; ++i) {
        state20[i] = new int(0);
    }

    for (int i = 0; i < 10; ++i) {
        connect(chanDuLieuIC20[i][0], &QPushButton::clicked, [i, this, state20]() {
            // Thiết lập trạng thái ban đầu
            if (*state20[i] == 0) {
                chanDuLieuIC20[i][0]->setText("0");
                //            ->setEnabled(false); // Tắt chức năng nút
                chanDuLieuIC20[i][0]->setStyleSheet(
                    "background-color: red; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state20[i] == 1) {
                chanDuLieuIC20[i][0]->setText("1");
                chanDuLieuIC20[i][0]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state20[i] == 2) {
                chanDuLieuIC20[i][0]->setText("Z");
                chanDuLieuIC20[i][0]->setStyleSheet(
                    "background-color: grey; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state20[i] = (*state20[i] + 1) % 3;
        });
    }
    for (int i = 0; i < 10; ++i) {
        connect(chanDuLieuIC20[i][2], &QPushButton::clicked, [i, this, state20]() {
            // Thiết lập trạng thái ban đầu
            if (*state20[i + 10] == 0) {
                chanDuLieuIC20[i][2]->setText("0");
                //            ->setEnabled(false); // Tắt chức năng nút
                chanDuLieuIC20[i][2]->setStyleSheet(
                    "background-color: red; border-radius: 16px; border: 1px solid blue;"
                    "font-size: 16px; color: white; font-weight: bold;");
            } else if (*state20[i + 10] == 1) {
                chanDuLieuIC20[i][2]->setText("1");
                chanDuLieuIC20[i][2]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state20[i + 10] == 2) {
                chanDuLieuIC20[i][2]->setText("Z");
                chanDuLieuIC20[i][2]->setStyleSheet(
                    "background-color: grey; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state20[i + 10] = (*state20[i + 10] + 1) % 3;
        });
    }

    //    tạo bảng cấu hình dữ liệu 16 chân
    QFrame *khungCauHinhDuLieu16 = new QFrame;
    QFrame *khungSymIC16 = new QFrame;
    khungCauHinhDuLieu16->setObjectName(
        "khungCauHinhDuLieu16");          // Đặt tên cho việc trang trí CSS sau này
    khungSymIC16->setFixedSize(250, 445); // Đặt kích thước hình chữ nhật
    khungSymIC16->setStyleSheet(
        "font-size: 20px; color: blue; font-weight: bold; background-color: rgba(0, 0, 0, 0);");
    khungCauHinhDuLieu16->setStyleSheet("QFrame#khungCauHinhDuLieu16 {"
                                        "   background-color: #A8D9D0;"
                                        "   border: 2px solid black;"
                                        "   border-radius: 10px;"
                                        "}");
    QGridLayout *lopKhungCauHinhDuLieu16 = new QGridLayout(khungCauHinhDuLieu16);
    QGridLayout *lopChuaKhungCauHinhDuLieu16 = new QGridLayout(khungSymIC16);
    lopChuaKhungCauHinhDuLieu16->addWidget(khungCauHinhDuLieu16, 0, 1, 8, 1);
    for (int i = 0; i < 8; ++i) {
        QString pL = QString::number(i + 1);
        QString pR = QString::number(i + 9);
        lopKhungCauHinhDuLieu16->addWidget(new QLabel(pL), i, 0, Qt::AlignCenter);
        lopKhungCauHinhDuLieu16->addWidget(new QLabel(pR), 7 - i, 2, Qt::AlignCenter);
    }
    lopKhungCauHinhDuLieu16->addWidget(new QLabel("               "), 1, 1);

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanDuLieuIC16[i][j] = new QPushButton("X");
            chanDuLieuIC16[i][j]->setFixedSize(32, 32);
            chanDuLieuIC16[i][j]->setStyleSheet("background-color: white;"
                                                " border-radius: 16px; "
                                                " font-size: 16px;"
                                                " font-weight: bold;"
                                                " color: blue;"
                                                " border: 1px solid blue;");

            // Đặt tên cho con trỏ dựa trên số đếm i và j
            QString tenChanDuLieuIC16 = QString("chanDuLieu_%1%2").arg(i).arg(j);
            chanDuLieuIC16[i][j]->setObjectName(tenChanDuLieuIC16);

            lopChuaKhungCauHinhDuLieu16->addWidget(chanDuLieuIC16[i][j], i, j, Qt::AlignCenter);
        }
    }
    int *state16[16]; // 16 biến trạng thái cho 16 nút
    // Thiết lập toàn bộ mảng state16 bằng 0
    for (int i = 0; i < 16; ++i) {
        state16[i] = new int(0);
    }

    for (int i = 0; i < 8; ++i) {
        connect(chanDuLieuIC16[i][0], &QPushButton::clicked, [i, this, state16]() {
            // Thiết lập trạng thái ban đầu
            if (*state16[i] == 0) {
                chanDuLieuIC16[i][0]->setText("0");
                //            ->setEnabled(false); // Tắt chức năng nút
                chanDuLieuIC16[i][0]->setStyleSheet(
                    "background-color: red; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state16[i] == 1) {
                chanDuLieuIC16[i][0]->setText("1");
                chanDuLieuIC16[i][0]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state16[i] == 2) {
                chanDuLieuIC16[i][0]->setText("Z");
                chanDuLieuIC16[i][0]->setStyleSheet(
                    "background-color: grey; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state16[i] = (*state16[i] + 1) % 3;
        });
    }
    for (int i = 0; i < 8; ++i) {
        connect(chanDuLieuIC16[i][2], &QPushButton::clicked, [i, this, state16]() {
            // Thiết lập trạng thái ban đầu
            if (*state16[i + 8] == 0) {
                chanDuLieuIC16[i][2]->setText("0");
                //            ->setEnabled(false); // Tắt chức năng nút
                chanDuLieuIC16[i][2]->setStyleSheet(
                    "background-color: red; border-radius: 16px; border: 1px solid blue;"
                    "font-size: 16px; color: white; font-weight: bold;");
            } else if (*state16[i + 8] == 1) {
                chanDuLieuIC16[i][2]->setText("1");
                chanDuLieuIC16[i][2]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state16[i + 8] == 2) {
                chanDuLieuIC16[i][2]->setText("Z");
                chanDuLieuIC16[i][2]->setStyleSheet(
                    "background-color: grey; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state16[i + 8] = (*state16[i + 8] + 1) % 3;
        });
    }

    //    tạo bảng cấu hình dữ liệu 14 chân
    QFrame *khungCauHinhDuLieu14 = new QFrame;
    QFrame *khungSymIC14 = new QFrame;
    khungCauHinhDuLieu14->setObjectName(
        "khungCauHinhDuLieu14");          // Đặt tên cho việc trang trí CSS sau này
    khungSymIC14->setFixedSize(250, 415); // Đặt kích thước hình chữ nhật
    khungSymIC14->setStyleSheet(
        "font-size: 20px; color: blue; font-weight: bold; background-color: rgba(0, 0, 0, 0);");
    khungCauHinhDuLieu14->setStyleSheet("QFrame#khungCauHinhDuLieu14 {"
                                        "   background-color: #A8D9D0;"
                                        "   border: 2px solid black;"
                                        "   border-radius: 10px;"
                                        "}");
    QGridLayout *lopkhungCauHinhDuLieu14 = new QGridLayout(khungCauHinhDuLieu14);
    QGridLayout *lopChuakhungCauHinhDuLieu14 = new QGridLayout(khungSymIC14);
    lopChuakhungCauHinhDuLieu14->addWidget(khungCauHinhDuLieu14, 0, 1, 7, 1);
    for (int i = 0; i < 7; ++i) {
        QString pL = QString::number(i + 1);
        QString pR = QString::number(i + 8);
        lopkhungCauHinhDuLieu14->addWidget(new QLabel(pL), i, 0, Qt::AlignCenter);
        lopkhungCauHinhDuLieu14->addWidget(new QLabel(pR), 6 - i, 2, Qt::AlignCenter);
    }
    lopkhungCauHinhDuLieu14->addWidget(new QLabel("               "), 1, 1);

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanDuLieuIC14[i][j] = new QPushButton("X");
            chanDuLieuIC14[i][j]->setFixedSize(32, 32);
            chanDuLieuIC14[i][j]->setStyleSheet("background-color: white;"
                                                " border-radius: 16px; "
                                                " font-size: 16px;"
                                                " font-weight: bold;"
                                                " color: blue;"
                                                " border: 1px solid blue;");

            // Đặt tên cho con trỏ dựa trên số đếm i và j
            QString tenchanDuLieuIC14 = QString("chanDuLieu_%1%2").arg(i).arg(j);
            chanDuLieuIC14[i][j]->setObjectName(tenchanDuLieuIC14);

            lopChuakhungCauHinhDuLieu14->addWidget(chanDuLieuIC14[i][j], i, j, Qt::AlignCenter);
        }
    }
    int *state14[14]; // 14 biến trạng thái cho 14 nút
    // Thiết lập toàn bộ mảng state14 bằng 0
    for (int i = 0; i < 14; ++i) {
        state14[i] = new int(0);
    }

    for (int i = 0; i < 7; ++i) {
        connect(chanDuLieuIC14[i][0], &QPushButton::clicked, [i, this, state14]() {
            // Thiết lập trạng thái ban đầu
            if (*state14[i] == 0) {
                chanDuLieuIC14[i][0]->setText("0");
                chanDuLieuIC14[i][0]->setStyleSheet(
                    "background-color: red; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state14[i] == 1) {
                chanDuLieuIC14[i][0]->setText("1");
                chanDuLieuIC14[i][0]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state14[i] == 2) {
                chanDuLieuIC14[i][0]->setText("Z");
                chanDuLieuIC14[i][0]->setStyleSheet(
                    "background-color: grey; border-radius: 16px;"
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state14[i] = (*state14[i] + 1) % 3;
        });
    }
    for (int i = 0; i < 7; ++i) {
        connect(chanDuLieuIC14[i][2], &QPushButton::clicked, [i, this, state14]() {
            // Thiết lập trạng thái ban đầu
            if (*state14[i + 7] == 0) {
                chanDuLieuIC14[i][2]->setText("0");
                //            ->setEnabled(false); // Tắt chức năng nút
                chanDuLieuIC14[i][2]->setStyleSheet(
                    "background-color: red; border-radius: 16px; border: 1px solid blue;"
                    "font-size: 16px; color: white; font-weight: bold;");
            } else if (*state14[i + 7] == 1) {
                chanDuLieuIC14[i][2]->setText("1");
                chanDuLieuIC14[i][2]->setStyleSheet(
                    "background-color: #009900; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            } else if (*state14[i + 7] == 2) {
                chanDuLieuIC14[i][2]->setText("Z");
                chanDuLieuIC14[i][2]->setStyleSheet(
                    "background-color: grey; border-radius: 16px; "
                    "font-size: 16px; color: white; font-weight: bold; border: 1px solid "
                    "blue;");
            }
            *state14[i + 7] = (*state14[i + 7] + 1) % 3;
        });
    }

    for (int i = 0; i < 7; ++i) {
        for (int j = 0; j < 3; j += 2) {
            connect(next, &QPushButton::clicked, [this, i, j, soChanIC]() {
                if (soChanIC->currentText() == " 14 Chân") {
                    if (chanSocketIC[i][j]->text() == "NC") {
                        chanDuLieuIC14[i][j]->setText("NC");
                        chanDuLieuIC14[i][j]->setEnabled(0);
                        chanDuLieuIC14[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC14[i][j]->setStyleSheet(
                            "background-color: grey; border-radius: 8px; "
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "VCC") {
                        chanDuLieuIC14[i][j]->setText("VCC");
                        chanDuLieuIC14[i][j]->setEnabled(0);
                        chanDuLieuIC14[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC14[i][j]->setStyleSheet(
                            "background-color: #009900; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "GND") {
                        chanDuLieuIC14[i][j]->setText("GND");
                        chanDuLieuIC14[i][j]->setEnabled(0);
                        chanDuLieuIC14[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC14[i][j]->setStyleSheet(
                            "background-color: red; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else {
                        chanDuLieuIC14[i][j]->setText("X");
                        chanDuLieuIC14[i][j]->setEnabled(1);
                        chanDuLieuIC14[i][j]->setFixedSize(32, 32);
                        chanDuLieuIC14[i][j]->setStyleSheet("background-color: white;"
                                                            " border-radius: 16px; "
                                                            " font-size: 16px;"
                                                            " font-weight: bold;"
                                                            " color: blue;"
                                                            " border: 1px solid blue;");
                    }
                }
            });
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 3; j += 2) {
            connect(next, &QPushButton::clicked, [this, i, j, soChanIC]() {
                if (soChanIC->currentText() == " 16 Chân") {
                    if (chanSocketIC[i][j]->text() == "NC") {
                        chanDuLieuIC16[i][j]->setText("NC");
                        chanDuLieuIC16[i][j]->setEnabled(0);
                        chanDuLieuIC16[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC16[i][j]->setStyleSheet(
                            "background-color: grey; border-radius: 8px; "
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "VCC") {
                        chanDuLieuIC16[i][j]->setText("VCC");
                        chanDuLieuIC16[i][j]->setEnabled(0);
                        chanDuLieuIC16[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC16[i][j]->setStyleSheet(
                            "background-color: #009900; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "GND") {
                        chanDuLieuIC16[i][j]->setText("GND");
                        chanDuLieuIC16[i][j]->setEnabled(0);
                        chanDuLieuIC16[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC16[i][j]->setStyleSheet(
                            "background-color: red; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else {
                        chanDuLieuIC16[i][j]->setText("X");
                        chanDuLieuIC16[i][j]->setEnabled(1);
                        chanDuLieuIC16[i][j]->setFixedSize(32, 32);
                        chanDuLieuIC16[i][j]->setStyleSheet("background-color: white;"
                                                            " border-radius: 16px; "
                                                            " font-size: 16px;"
                                                            " font-weight: bold;"
                                                            " color: blue;"
                                                            " border: 1px solid blue;");
                    }
                }
            });
        }
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            connect(next, &QPushButton::clicked, [this, i, j, soChanIC]() {
                if (soChanIC->currentText() == " 20 Chân") {
                    if (chanSocketIC[i][j]->text() == "NC") {
                        chanDuLieuIC20[i][j]->setText("NC");
                        chanDuLieuIC20[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC20[i][j]->setEnabled(0);
                        chanDuLieuIC20[i][j]->setStyleSheet(
                            "background-color: grey; border-radius: 8px; "
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "VCC") {
                        chanDuLieuIC20[i][j]->setText("VCC");
                        chanDuLieuIC20[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC20[i][j]->setEnabled(0);
                        chanDuLieuIC20[i][j]->setStyleSheet(
                            "background-color: #009900; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else if (chanSocketIC[i][j]->text() == "GND") {
                        chanDuLieuIC20[i][j]->setText("GND");
                        chanDuLieuIC20[i][j]->setFixedSize(38, 30);
                        chanDuLieuIC20[i][j]->setEnabled(0);
                        chanDuLieuIC20[i][j]->setStyleSheet(
                            "background-color: red; border-radius: 8px;"
                            "font-size: 14px; color: white; font-weight: bold; border: 1px "
                            "solid "
                            "blue;");
                    } else {
                        chanDuLieuIC20[i][j]->setText("X");
                        chanDuLieuIC20[i][j]->setEnabled(1);
                        chanDuLieuIC20[i][j]->setFixedSize(32, 32);
                        chanDuLieuIC20[i][j]->setStyleSheet("background-color: white;"
                                                            " border-radius: 16px; "
                                                            " font-size: 16px;"
                                                            " font-weight: bold;"
                                                            " color: blue;"
                                                            " border: 1px solid blue;");
                    }
                }
            });
        }
    }

    QPushButton *finish = new QPushButton("Hoàn thành");
    finish->setStyleSheet(
        "background-color: #009900;font-size: 16px;font-weight: bold; color: white");
    QPushButton *back = new QPushButton("Quay lại");
    back->setStyleSheet(
        "background-color: #009900;font-size: 16px;font-weight: bold; color: white");
    QHBoxLayout *lopCauHinhDuLieu = new QHBoxLayout;
    QHBoxLayout *lopNutNhanCauHinhDuLieu = new QHBoxLayout;

    lopNutNhanCauHinhDuLieu->addWidget(finish);
    lopNutNhanCauHinhDuLieu->addWidget(back);
    lopCauHinhDuLieu->addWidget(splitCauHinhDuLieu);

    khongGianCauHinhDuLieu = new QStackedWidget(splitCauHinhDuLieu);

    khongGianCauHinhDuLieu->addWidget(khungSymIC14);
    khongGianCauHinhDuLieu->addWidget(khungSymIC16);
    khongGianCauHinhDuLieu->addWidget(khungSymIC20);

    connect(next,
            &QPushButton::clicked,
            [soChanIC, this, khungSymIC20, khungSymIC16, khungSymIC14]() {
                if (soChanIC->currentText() == " 14 Chân") {
                    khongGianCauHinhDuLieu->setCurrentWidget(khungSymIC14);
                } else if (soChanIC->currentText() == " 16 Chân") {
                    khongGianCauHinhDuLieu->setCurrentWidget(khungSymIC16);
                } else if (soChanIC->currentText() == " 20 Chân") {
                    khongGianCauHinhDuLieu->setCurrentWidget(khungSymIC20);
                }
            });

    lopCauHinhDuLieu->addLayout(lopNutNhanCauHinhDuLieu);
    trangCauHinhDuLieu->setLayout(lopCauHinhDuLieu);

    connect(finish, SIGNAL(clicked(bool)), this, SLOT(opComplete()));
    connect(finish, SIGNAL(clicked(bool)), this, SLOT(opTrangCauHinhChan()));
    connect(back, &QPushButton::clicked, this, [this]() {
        khongGianTaoThuVien->setCurrentWidget(trangCauHinhChan);
    });

    //    ======================================================================
    khongGianTaoThuVien = new QStackedWidget;
    khongGianTaoThuVien->addWidget(trangCauHinhChan);
    khongGianTaoThuVien->addWidget(trangCauHinhDuLieu);
    khongGianTaoThuVien->setCurrentWidget(trangCauHinhChan);

    QVBoxLayout *lopTaoThuVien = new QVBoxLayout;
    lopTaoThuVien->addWidget(khongGianTaoThuVien);
    lopTaoThuVien->addWidget(new QLabel("Tạo Thư Viện"));
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
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 3; j += 2) {
            chanSocketIC[i][j]->setText("NC");
        }
    }
}
void TaoThuVien::opComplete()
{
    QMessageBox::information(this, "Thông báo", "Tạo thư viện hoàn tất");
}
