#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //    tuy chinh giao diện Home
    setWindowTitle("IC Tester Development Version");
    setWindowIcon(QIcon("://resources/SoftwareIcon.png"));

    QGridLayout *lopHome = new QGridLayout;
    QHBoxLayout *lopWellcome = new QHBoxLayout;
    QVBoxLayout *lopNutNhan = new QVBoxLayout;

    QLabel *space = new QLabel("        ");
    QLabel *wellcomeText = new QLabel("Welcome to IC Tester Development Version");
    wellcomeText->setAlignment(Qt::AlignLeft);
    wellcomeText->setStyleSheet("color: #0000FF; font-size: 36px;font-weight: bold;");
    QLabel *wellcomeIcon = new QLabel;
    QLabel *homeIcon = new QLabel;
    QPixmap pixmap("://resources/SoftwareIcon.png"); // Đường dẫn đến tệp hình ảnh
    //    QPixmap scaledPixmap = pixmap.scaled(QSize(55, 55));
    QPixmap scaledPixmapBigIcon = pixmap.scaled(QSize(400, 400));
    QGraphicsBlurEffect *blurEffect = new QGraphicsBlurEffect();
    blurEffect->setBlurRadius(0); // Điều chỉnh độ mờ ở đây;
                                  //    wellcomeIcon->setPixmap(scaledPixmap);
    wellcomeIcon->setAlignment(Qt::AlignLeft);
    homeIcon->setGraphicsEffect(blurEffect);
    homeIcon->setPixmap(scaledPixmapBigIcon);
    homeIcon->setAlignment(Qt::AlignCenter);
    lopWellcome->addWidget(wellcomeIcon);
    lopWellcome->addWidget(wellcomeText);
    //    lopHome->addWidget(space, 0, 0);

    lopHome->addWidget(space, 0, 2);
    lopHome->addWidget(space, 0, 4);
    lopHome->addLayout(lopWellcome, 0, 3);
    lopHome->addWidget(homeIcon, 3, 3, 11, 1);
    lopHome->addWidget(space, 1, 1);
    QSize iconSize(30, 30);
    QPushButton *nutKiemTra = new QPushButton("  Kiểm Tra IC");
    nutKiemTra->setFixedSize(300, 55);
    nutKiemTra->setStyleSheet("font-size: 20px;background-color: #A9C4EB;font-weight: 600;");
    nutKiemTra->setIcon(QIcon("://resources/KiemTra.png"));
    nutKiemTra->setIconSize(iconSize);
    QPushButton *nutTaoThuVien = new QPushButton("  Tạo Thư Viện");
    nutTaoThuVien->setFixedSize(300, 55);
    nutTaoThuVien->setStyleSheet("font-size: 20px;background-color: #A9C4EB; font-weight: 600");
    nutTaoThuVien->setIcon(QIcon("://resources/TaoThuVien.png"));
    nutTaoThuVien->setIconSize(iconSize);
    QPushButton *nutXemThuVien = new QPushButton("  Xem Thư Viện");
    nutXemThuVien->setFixedSize(300, 55);
    nutXemThuVien->setStyleSheet("font-size: 20px;background-color: #A9C4EB; font-weight: 600");
    nutXemThuVien->setIcon(QIcon("://resources/XemThuVien.png"));
    nutXemThuVien->setIconSize(iconSize);
    QPushButton *nutXemLichSu = new QPushButton("  Xem Lịch Sử");
    nutXemLichSu->setFixedSize(300, 55);
    nutXemLichSu->setStyleSheet("font-size: 20px;background-color: #A9C4EB; font-weight: 600");
    nutXemLichSu->setIcon(QIcon("://resources/XemLichSu.png"));
    nutXemLichSu->setIconSize(iconSize);

    QLabel *nhanThongTin = new QLabel("                 Thông Tin?");
    nhanThongTin->setStyleSheet("font-size: 20px;font-weight: bold;");
    QPushButton *nutHuongDan = new QPushButton("  Hướng Dẫn");
    nutHuongDan->setFixedSize(300, 55);
    nutHuongDan->setStyleSheet(
        "font-size: 20px;background-color: #009900;  color: white; font-weight: 600");
    nutHuongDan->setIcon(QIcon("://resources/HuongDan.png"));
    nutHuongDan->setIconSize(iconSize);
    QPushButton *nutLienHe = new QPushButton("  Liên Hệ");
    nutLienHe->setFixedSize(300, 55);
    nutLienHe->setStyleSheet(
        "font-size: 20px;background-color: #009900;  color: white; font-weight: 600");
    nutLienHe->setIcon(QIcon("://resources/LienHe.png"));
    nutLienHe->setIconSize(iconSize);
    QMenu *menuLienHe = new QMenu;
    QAction *fB = new QAction("FaceBook");
    fB->setIcon(QIcon("://resources/Face.png"));
    menuLienHe->addAction(fB);
    QAction *tG = new QAction("Telegram");
    tG->setIcon(QIcon("://resources/Tele.png"));
    menuLienHe->addAction(tG);
    QAction *gH = new QAction("GitHub");
    gH->setIcon(QIcon("://resources/Git.png"));
    menuLienHe->addAction(gH);
    nutLienHe->setMenu(menuLienHe);
    QObject::connect(fB, &QAction::triggered, [&]() {
        QDesktopServices::openUrl(QUrl("https://www.facebook.com/buidiep01/"));
    });
    QObject::connect(gH, &QAction::triggered, [&]() {
        QDesktopServices::openUrl(QUrl("https://github.com/Bui-Diep"));
    });
    lopNutNhan->addWidget(nutKiemTra);
    //    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(nutTaoThuVien);
    //    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(nutXemThuVien);
    //    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(nutXemLichSu);
    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(nhanThongTin);
    nhanThongTin->setAlignment(Qt::AlignBottom);
    lopNutNhan->addWidget(nutHuongDan);
    //    lopNutNhan->addWidget(space);
    lopNutNhan->addWidget(nutLienHe);
    //    lopNutNhan->addWidget(space);
    //    lopNutNhan->addWidget(space);
    QGroupBox *boxNutNhan = new QGroupBox;
    boxNutNhan->setLayout(lopNutNhan);
    lopHome->addWidget(boxNutNhan, 2, 1, 14, 1);
    QLabel *auThor = new QLabel("The software is designed and created by BuiDiep");
    lopHome->addWidget(auThor, 14, 3);
    auThor->setAlignment(Qt::AlignCenter);
    auThor->setStyleSheet("color: #0000FF; font-size: 22px;font-weight: bold; font-style: italic;");

    //    cau hinh thanh menu
    QMenu *tep = menuBar()->addMenu("&Tệp");
    QMenu *timKiem = menuBar()->addMenu("Tìm &Kiếm");
    QMenu *chinhSua = menuBar()->addMenu("&Chỉnh sửa");
    QMenu *congcu = menuBar()->addMenu("&Công Cụ");
    QMenu *huongDan = menuBar()->addMenu("&Hướng dẫn");
    QMenu *thongTin = menuBar()->addMenu("&Thông tin");

    //    cau hinh thanh cong cu
    QToolBar *thanhCongCu = new QToolBar;
    QToolBar *thanhLienHe = new QToolBar;
    thanhCongCu->setMovable(0);
    thanhCongCu->setAllowedAreas(Qt::RightToolBarArea);
    addToolBar(thanhCongCu);
    QPushButton *nutBackHome = new QPushButton(" Home");
    nutBackHome->setStyleSheet("background-color: #A8D9D0;font-weight: bold;");
    nutBackHome->setIcon(QIcon("://resources/home.png"));
    nutBackHome->setIconSize(QSize(20, 20));
    nutBackHome->setToolTip("Trở về trang chủ");
    thanhCongCu->addWidget(nutBackHome);

    QAction *acKiemTra = new QAction("Chuyển tới trang kiểm tra IC");
    acKiemTra->setIcon(QIcon("://resources/KiemTra.png"));
    thanhCongCu->addSeparator();
    thanhCongCu->addAction(acKiemTra);
    QAction *acXemThuVien = new QAction("Chuyển tới trang xem thư viện");
    acXemThuVien->setIcon(QIcon("://resources/XemThuVien.png"));
    thanhCongCu->addSeparator();
    thanhCongCu->addAction(acXemThuVien);
    thanhCongCu->addSeparator();
    thanhLienHe->addAction(fB);
    QAction *setting = new QAction("Cài đặt");
    setting->setIcon(QIcon("://resources/setting.png"));
    thanhCongCu->addSeparator();
    thanhCongCu->addAction(setting);
    QAction *thoat = new QAction("Thoát Phần Mềm");
    thoat->setIcon(QIcon("://resources/power.png"));
    thanhCongCu->addSeparator();
    thanhCongCu->addAction(thoat);
    connect(nutBackHome, SIGNAL(clicked(bool)), this, SLOT(opHome()));
    connect(thoat, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(acKiemTra, SIGNAL(triggered(bool)), this, SLOT(opKiemTra()));
    thanhCongCu->setIconSize(QSize(20, 20));
    thanhLienHe->setAllowedAreas(Qt::RightToolBarArea);
    thanhLienHe->setMovable(0);
    addToolBar(thanhLienHe);

    //    cau hinh vung trung tam
    khongGianLamViec = new QStackedWidget;

    trangHome = new QWidget;
    trangHome->setStyleSheet("background-color: #9AC7BF;");
    trangKiemTra = new KiemTra;
    trangKiemTra->setStyleSheet("background-color: #E3E3E3;");
    trangTaoThuVien = new TaoThuVien;
    khongGianLamViec->addWidget(trangHome);
    khongGianLamViec->addWidget(trangKiemTra);
    khongGianLamViec->addWidget(trangTaoThuVien);

    trangHome->setLayout(lopHome);
    khongGianLamViec->setCurrentWidget(trangHome);
    connect(nutKiemTra, SIGNAL(clicked(bool)), this, SLOT(opKiemTra()));
    connect(nutTaoThuVien, SIGNAL(clicked(bool)), this, SLOT(opTaoThuVien()));
    setCentralWidget(khongGianLamViec);
}
void MainWindow::opHome()
{
    khongGianLamViec->setCurrentWidget(trangHome);
}
void MainWindow::opKiemTra()
{
    khongGianLamViec->setCurrentWidget(trangKiemTra);
}
void MainWindow::opTaoThuVien()
{
    khongGianLamViec->setCurrentWidget(trangTaoThuVien);
}
MainWindow::~MainWindow() {}
