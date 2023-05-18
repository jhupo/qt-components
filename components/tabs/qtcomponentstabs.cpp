#include "qtcomponentstabs.h"
#include "qtcomponentstabs_internal.h"
#include "lib/qtcomponentstheme.h"

#include <QDebug>

namespace Components {

    class QtComponentsTabsPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsTabs)

    public:

        QtComponentsTabsPrivate(QtComponentsTabs* q);
        ~QtComponentsTabsPrivate();

        void init();

        QtComponentsTabs*const          q_ptr;
        QtComponentsOverlayTabs*        _inkBar;
        QColor                          _inkColor;
        QColor                          _activeColor;
        int                             _index;

    };

    QtComponentsTabsPrivate::QtComponentsTabsPrivate(QtComponentsTabs *q)
        : q_ptr(q)
    {

    }

    QtComponentsTabsPrivate::~QtComponentsTabsPrivate()
    {

    }

    void QtComponentsTabsPrivate::init()
    {
        Q_Q(QtComponentsTabs);
        _inkBar = new QtComponentsOverlayTabs(q);
        _index = -1;
        q->setInkColor(QtComponentsTheme::inst()->color(gold200));
        q->setActiveColor(QtComponentsTheme::inst()->color(white));

        q->appBarLayout()->setMargin(0);
        q->appBarLayout()->setSpacing(15);
        q->appBarLayout()->addStretch();

        QFont font(q->font());
        font.setFamily("Normal");
        q->setFont(font);
    }

    QtComponentsTabs::QtComponentsTabs(QWidget *parent)
        : QtComponentsAppBar(parent)
        , d_ptr(new QtComponentsTabsPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsTabs::~QtComponentsTabs()
    {

    }

    void QtComponentsTabs::setInkColor(const QColor &color)
    {
        Q_D(QtComponentsTabs);
        d->_inkColor = color;
    }

    QColor QtComponentsTabs::inkColor() const
    {
        Q_D(const QtComponentsTabs);
        return d->_inkColor;
    }

    void QtComponentsTabs::setActiveColor(const QColor &color)
    {
        Q_D(QtComponentsTabs);
        d->_activeColor = color;
    }

    QColor QtComponentsTabs::activeColor() const
    {
        Q_D(const QtComponentsTabs);
        return d->_activeColor;
    }

    void QtComponentsTabs::setCurrentTab(QtComponentsTab *tab)
    {
        setCurrentTab(appBarLayout()->indexOf(tab));
    }

    void QtComponentsTabs::setCurrentTab(int index)
    {
        Q_D(QtComponentsTabs);

        for(int i = 0; i < appBarLayout()->count(); ++i)
            setTabActive(i, false);

        setTabActive(index);

        d->_inkBar->animate();

        emit currentChanged(index);
    }

    QAbstractButton *QtComponentsTabs::addTab(const QString &text)
    {
        Q_D(QtComponentsTabs);

        QtComponentsTab* tab = new QtComponentsTab(this);
        tab->setText(text);

        appBarLayout()->insertWidget(appBarLayout()->count() - 1, tab);

        if (-1 == d->_index) {
            d->_index = 0;
            d->_inkBar->refreshGeometry();
            d->_inkBar->raise();
            tab->setActive(true);
        }

        return tab;
    }

    QAbstractButton *QtComponentsTabs::insertTab(const QString &text, int index)
    {
        QtComponentsTab* tab = new QtComponentsTab(this);
        tab->setText(text);

        appBarLayout()->insertWidget(index,tab);

        return tab;
    }

    void QtComponentsTabs::removeTab(QAbstractButton *tab)
    {
        appBarLayout()->removeWidget(tab);
        delete tab;
        tab = Q_NULLPTR;
        setTabActive(0);
    }

    int QtComponentsTabs::currentIndex() const
    {
        Q_D(const QtComponentsTabs);
        return d->_index;
    }

    void QtComponentsTabs::setTabActive(int index, bool active)
    {
        Q_D(QtComponentsTabs);

        QtComponentsTab *tab = NULL;

        if (index > -1) {
            tab = static_cast<QtComponentsTab *>(appBarLayout()->itemAt(index)->widget());
            if (tab) {
                d->_index = index;
                tab->setActive(active);
            }
        }

    }

}
