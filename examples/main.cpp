#include <QApplication>

#include <QDebug>
#include <QVBoxLayout>
#include <QAbstractButton>

#include <lib/qtcomponentstheme.h>
#include <button/qtcomponentspushbutton.h>
#include <button/qtcomponentsiconbutton.h>
#include <appbar/qtcomponentsappbar.h>
#include <divider/qtcomponentsdivider.h>
#include <button/qtcomponentsbuttontabs.h>
#include <avatar/qtcomponentsavatar.h>
#include <window/qtcomponentswidget.h>
#include <window/qtcomponentsdwmapi.h>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

#ifdef DWM_AVAILABLE
    Components::QtDwmapiNativeEventFilter filter;
#endif

    Components::QtComponentsWidget w;
    w.resize(500,400);
    w.setPalette(QPalette(Qt::white));
    //QVBoxLayout* layout = new QVBoxLayout(&w);

    Components::QtComponentsAvatar* avatar = new Components::QtComponentsAvatar(&w);
    avatar->setLetter('C');
    avatar->move(190,240);

    Components::QtComponentsIconButton* btn = new Components::QtComponentsIconButton(&w);
    btn->move(100,100);
    btn->resize(20,20);
    btn->setIcon(Components::QtComponentsTheme::icon("window","menu"));

    Components::QtComponentsButtonTabs* tTabs = new Components::QtComponentsButtonTabs(&w);
    tTabs->move(150,60);
    tTabs->addTab(QString::fromLocal8Bit("你好"));
    tTabs->addTab("222 22");
    tTabs->addTab("333 33");
    tTabs->addTab(QString::fromUtf8("你好"));

    Components::QtComponentsPushButton* pushButton = new Components::QtComponentsPushButton(&w);
    pushButton->setIcon(Components::QtComponentsTheme::icon("window","menu"));
    pushButton->setText("123123");
    pushButton->move(50,30);

    Components::QtComponentsAppBar* bar = new Components::QtComponentsAppBar(&w);
    bar->resize(150,30);
    bar->move(150,150);

    Components::QtComponentsDivider* divider = new Components::QtComponentsDivider(&w);
    divider->move(50,170);
    divider->resize(1,150);

    w.show();
    return a.exec();
}
