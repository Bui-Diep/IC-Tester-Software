#include "kiemtra.h"

KiemTra::KiemTra()
{
    QLabel *label = new QLabel("Trang 1");
    QPushButton *nutBackHome = new QPushButton("Home");
    QMenu *pinType = new QMenu;
    pinType->addAction(new QAction("VCC"));
    pinType->addAction(new QAction("GND"));
    pinType->addAction(new QAction("CLK"));
    pinType->addAction(new QAction("DATA_IN"));
    pinType->addAction(new QAction("DATA_OUT"));
    pinType->addAction(new QAction("NC"));
    nutBackHome->setMenu(pinType);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(nutBackHome);
    setLayout(layout);
    connect(nutBackHome, SIGNAL(clicked(bool)), this, SLOT(backHome()));
}
void KiemTra::backHome()
{
    qDebug() << "ok";
}
KiemTra::~KiemTra() {}
