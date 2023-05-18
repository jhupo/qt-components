#include <QApplication>

#include <QDebug>
#include <QAbstractButton>

#include <divider/qtcomponentsdivider.h>
#include <tabs/qtcomponentstabs.h>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QWidget w;
    w.resize(500,100);

    QVBoxLayout* layout = new QVBoxLayout(&w);

    Components::QtComponentsTabs* tabs = new Components::QtComponentsTabs(&w);
    tabs->addTab("1111111111");
    tabs->addTab("2222222222");
    QAbstractButton* btn = tabs->addTab("3333333");
    qDebug()<<btn->geometry();
    tabs->addTab("44444");
    tabs->addTab("55555");
    tabs->removeTab(btn);
    layout->addWidget(tabs);
    layout->addWidget(new Components::QtComponentsDivider);
    layout->addStretch();

    w.show();
    return a.exec();
}
