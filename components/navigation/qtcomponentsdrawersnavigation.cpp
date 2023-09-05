#include "qtcomponentsdrawersnavigation.h"
#include "qtcomponentsdrawersnavigation_p.h"
#include "qtcomponentsdrawersnavigation_internal.h"
#include "lib/qtcomponentstheme.h"
#include "lib/qtcomponentsstackedwidget.h"

#include <QMutexLocker>
#include <QHBoxLayout>
#include <QStackedWidget>
#include <QGraphicsDropShadowEffect>

namespace Components {

    QtComponentsDrawersNavigationPrivate::QtComponentsDrawersNavigationPrivate(QtComponentsDrawersNavigation *q)
        : q_ptr(q)
    {

    }

    QtComponentsDrawersNavigationPrivate::~QtComponentsDrawersNavigationPrivate()
    {

    }

    void QtComponentsDrawersNavigationPrivate::init()
    {
        Q_Q(QtComponentsDrawersNavigation);

        _index = -1;
        _iconSize = 32;
        _autoSort = false;

        QtComponentsTheme::setPaletteColor(QColor("#BCBCBC"),_palette,QPalette::Foreground);
        QtComponentsTheme::setPaletteColor(QColor("#F26521"),_palette,QPalette::Foreground,QPalette::Active);

        QtComponentsTheme::setPaletteColor(QColor("#17243E"),_palette,QPalette::ButtonText);
        QtComponentsTheme::setPaletteColor(QColor("#F26521"),_palette,QPalette::ButtonText,QPalette::Active);

        QtComponentsTheme::setPaletteColor(Qt::transparent,_palette,QPalette::Button);
        QtComponentsTheme::setPaletteColor(QColor("#FFF4EF"),_palette,QPalette::Button,QPalette::Active);

        QFont font = q->font();
        font.setWeight(QFont::Normal);
        font.setPixelSize(12);

        q->setFont(font);

        QHBoxLayout* layout = new QHBoxLayout(q);
        layout->setSpacing(16);

        _sidebarWidget = new QtComponentsSidebarWidget(q);
        _sidebarWidget->setRoundedRadiusRatios(50);

        QBoxLayout* sidebarLayout = qobject_cast<QBoxLayout*>(_sidebarWidget->layout());
        sidebarLayout->setSpacing(24);
        sidebarLayout->setContentsMargins(16,36,16,36);
        sidebarLayout->addStretch();

        _stackedWidget = new QtComponentsStackedWidget(q);

        _sidebarButton = new QtComponentsSidebarButton(q,_sidebarWidget);
        _sidebarButton->setIcon(QtComponentsTheme::icon("navigation","sidebar","button"));

        layout->addWidget(_sidebarWidget);
        layout->addWidget(_stackedWidget);

        q->setLayout(layout);
    }

    void QtComponentsDrawersNavigationPrivate::setupDrawersTabsPaletteColor()
    {
        QMutexLocker locker(&_mutex);
        int index = 0;
        while(QLayoutItem* item = _sidebarWidget->layout()->itemAt(index++)){
            if(QtComponentsDrawersTab* tab = qobject_cast<QtComponentsDrawersTab*>(item->widget())){
                tab->setPalette(_palette);
                tab->update();
            }
        }
    }

    QtComponentsDrawersNavigation::QtComponentsDrawersNavigation(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsDrawersNavigationPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsDrawersNavigation::~QtComponentsDrawersNavigation()
    {

    }

    void QtComponentsDrawersNavigation::setSidebarButtonIcon(const QIcon &icon)
    {
        Q_D(QtComponentsDrawersNavigation);
        d->_sidebarButton->setIcon(icon);
    }

    QIcon QtComponentsDrawersNavigation::sidebarButtonIcon() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_sidebarButton->icon();
    }

    void QtComponentsDrawersNavigation::setDrawersSidebarRange(int min, int max)
    {
        Q_D(QtComponentsDrawersNavigation);
        d->_sidebarWidget->setSidebarRange(min,max);
    }

    int QtComponentsDrawersNavigation::drawersSidebarMinimum() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_sidebarWidget->sidebarMinimum();
    }

    int QtComponentsDrawersNavigation::drawersSidebarMaximum() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_sidebarWidget->sidebarMaximum();
    }

    void QtComponentsDrawersNavigation::setDrawersTabIconSize(int size)
    {
        Q_D(QtComponentsDrawersNavigation);
        d->_iconSize = size;
    }

    int QtComponentsDrawersNavigation::drawersTabIconSize() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_iconSize;
    }

    bool QtComponentsDrawersNavigation::isDrawersExpand() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_sidebarButton->isChecked();
    }

    void QtComponentsDrawersNavigation::addDrawersTab(const QIcon &icon, const QString &text, QWidget *w)
    {
        Q_D(QtComponentsDrawersNavigation);
        insertDrawersTab(d->_sidebarWidget->layout()->count() - 1,icon,text,w);
    }

    void QtComponentsDrawersNavigation::insertDrawersTab(int index, const QIcon &icon, const QString &text, QWidget *w)
    {
        Q_D(QtComponentsDrawersNavigation);

        QMutexLocker locker(&d->_mutex);

        if(QBoxLayout* layout = qobject_cast<QBoxLayout*>(d->_sidebarWidget->layout())){

            QtComponentsDrawersTab* tab = new QtComponentsDrawersTab(this);
            tab->setIconSize(QSize(d->_iconSize,d->_iconSize));
            tab->setPalette(d->_palette);
            tab->setFont(font());
            tab->setIcon(icon);
            tab->setText(text);
            tab->setUserData(index);
            tab->setToolTip(text);

            layout->insertWidget(index,tab);
            d->_stackedWidget->insertWidget(index,w);

            if(-1 == d->_index){
                locker.unlock();
                setCurrentDrawersTab(0);
                locker.relock();
            }

            if(d->_autoSort){
                locker.unlock();
                sort();
            }

        }
    }

    void QtComponentsDrawersNavigation::eraseDrawersTab(int index)
    {
        Q_D(QtComponentsDrawersNavigation);

        QMutexLocker locker(&d->_mutex);

        if(QLayoutItem* item = d->_sidebarWidget->layout()->takeAt(index)){
            if(QWidget* w = item->widget()){
                delete w;
            }
            delete item;
        }

        if(QWidget* w = d->_stackedWidget->widget(index)){
            d->_stackedWidget->removeWidget(w);
            delete w;
        }

        if(layout()->count()){
            if(QtComponentsDrawersTab* tab = qobject_cast<QtComponentsDrawersTab*>(layout()->itemAt(0)->widget())){
                setCurrentDrawersTab(tab);
            }
        }
    }

    void QtComponentsDrawersNavigation::removeDrawersTab(int index)
    {
        Q_D(QtComponentsDrawersNavigation);

        QMutexLocker locker(&d->_mutex);

        if(QLayoutItem* item = d->_sidebarWidget->layout()->takeAt(index)){
            delete item;
        }

        if(QWidget* w = d->_stackedWidget->widget(index)){
            d->_stackedWidget->removeWidget(w);
        }
    }

    void QtComponentsDrawersNavigation::setCurrentDrawersTab(int index)
    {
        Q_D(QtComponentsDrawersNavigation);

        QMutexLocker locker(&d->_mutex);

        if(QLayoutItem* item = d->_sidebarWidget->layout()->itemAt(index)){

            if(QtComponentsDrawersTab* tab = qobject_cast<QtComponentsDrawersTab*>(item->widget())){
                tab->setChecked(true);
            }

            d->_stackedWidget->setCurrentIndex(index);

            d->_index = index;

            emit currentChanged(d->_index);
        }
    }

    void QtComponentsDrawersNavigation::setCurrentDrawersTab(QtComponentsDrawersTab *tab)
    {
        Q_D(QtComponentsDrawersNavigation);

        QMutexLocker locker(&d->_mutex);

        locker.unlock();

        setCurrentDrawersTab(d->_sidebarWidget->layout()->indexOf(tab));
    }

    int QtComponentsDrawersNavigation::currentDrawersTab()
    {
        Q_D(QtComponentsDrawersNavigation);
        QMutexLocker locker(&d->_mutex);
        return d->_index;
    }

    int QtComponentsDrawersNavigation::findDrawerTabsByUserId(int index)
    {
        Q_D(QtComponentsDrawersNavigation);
        QMutexLocker locker(&d->_mutex);
        int count = -1;
        QtComponentsDrawersTab* tab = Q_NULLPTR;
        while (QLayoutItem* item = d->_sidebarWidget->layout()->itemAt(++count)) {
             if(tab = qobject_cast<QtComponentsDrawersTab*>(item->widget())){
                 if(index == tab->userData().toInt()){
                     return tab->userData().toInt();
                 }
             }
        }
        return -1;
    }

    void QtComponentsDrawersNavigation::setDrawersTabsColor(const QColor &color, QPalette::ColorRole role, QPalette::ColorGroup group)
    {
        Q_D(QtComponentsDrawersNavigation);
        QtComponentsTheme::setPaletteColor(color,d->_palette,role,group);
        d->setupDrawersTabsPaletteColor();
    }

    void QtComponentsDrawersNavigation::sort()
    {
        Q_D(QtComponentsDrawersNavigation);
        QMutexLocker locker(&d->_mutex);

        QMap<int,QPair<QtComponentsDrawersTab*,QWidget*> > maps;

        while(QLayoutItem* item = d->_sidebarWidget->layout()->itemAt(0)){
            if(QtComponentsDrawersTab* tab = qobject_cast<QtComponentsDrawersTab*>(item->widget())){
                int index = d->_sidebarWidget->layout()->indexOf(tab);
                if(-1 != index){
                    maps.insert(tab->userData().toInt(),qMakePair(tab,d->_stackedWidget->widget(index)));
                }
            }
            d->_sidebarWidget->layout()->takeAt(0);
        }

        while(QWidget* w = d->_stackedWidget->currentWidget()){
            d->_stackedWidget->removeWidget(w);
        }

        foreach(int key, maps.keys()){
            QPair<QtComponentsDrawersTab*,QWidget*> pair = maps.value(key);
            if(pair.first && pair.second){
                d->_sidebarWidget->layout()->addWidget(pair.first);
                d->_stackedWidget->addWidget(pair.second);
            }
        }

        qobject_cast<QBoxLayout*>(d->_sidebarWidget->layout())->addStretch();

        locker.unlock();

        setCurrentDrawersTab(0);
    }

    void QtComponentsDrawersNavigation::setAutoSort(bool sort)
    {
        Q_D(QtComponentsDrawersNavigation);
        d->_autoSort = sort;
        if(sort){
            QtComponentsDrawersNavigation::sort();
        }
    }

    bool QtComponentsDrawersNavigation::autoSort() const
    {
        Q_D(const QtComponentsDrawersNavigation);
        return d->_autoSort;
    }

}
