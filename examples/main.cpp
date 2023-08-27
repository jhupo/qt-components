#include <QApplication>

#include <QDebug>
#include <QVBoxLayout>
#include <QAbstractButton>

#include <lib/qtcomponentstheme.h>
#include <button/qtcomponentspushbutton.h>
#include <button/qtcomponentsiconbutton.h>
#include <appbar/qtcomponentsappbar.h>
#include <divider/qtcomponentsdivider.h>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QWidget w;
    w.resize(500,400);
    w.setPalette(QPalette(Qt::white));
    //QVBoxLayout* layout = new QVBoxLayout(&w);

    Components::QtComponentsIconButton* btn = new Components::QtComponentsIconButton(&w);
    btn->move(100,100);
    btn->resize(20,20);
    btn->setIcon(Components::QtComponentsTheme::icon("window","menu"));

    Components::QtComponentsAppBar* bar = new Components::QtComponentsAppBar(&w);
    bar->resize(150,30);
    bar->move(150,150);

    Components::QtComponentsDivider* divider = new Components::QtComponentsDivider(&w);
    divider->move(50,170);
    divider->resize(1,150);

    w.show();
    return a.exec();
}
