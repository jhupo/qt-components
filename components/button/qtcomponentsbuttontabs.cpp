#include "qtcomponentsbuttontabs.h"
#include "qtcomponentsbuttontabs_internal.h"
#include "qtcomponentsbutton.h"
#include "qtcomponentsiconbutton.h"

#include <QBoxLayout>
#include <QAbstractButton>

namespace Components {

    class QtComponentsButtonTabsPrivate
    {
        Q_DISABLE_COPY(QtComponentsButtonTabsPrivate)
        Q_DECLARE_PUBLIC(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabsPrivate(Qt::Orientation orientation, QtComponentsButtonTabs* q);
        ~QtComponentsButtonTabsPrivate();

        void init();

        QtComponentsButtonTabs*const                q_ptr;
        Qt::Orientation                             _orientation;
        int                                         _index;
        QtComponentsButtonTabsOverlayWidget*        _overlay;
        bool                                        _animate;

    };

    QtComponentsButtonTabsPrivate::QtComponentsButtonTabsPrivate(Qt::Orientation orientation, QtComponentsButtonTabs *q)
        : q_ptr(q)
        , _orientation(orientation)
    {

    }

    QtComponentsButtonTabsPrivate::~QtComponentsButtonTabsPrivate()
    {

    }

    void QtComponentsButtonTabsPrivate::init()
    {
        Q_Q(QtComponentsButtonTabs);

        _index = 0;

        _animate = false;

        delete q->appBarLayout();

        _overlay = new QtComponentsButtonTabsOverlayWidget(q);

        QBoxLayout* layout = new QBoxLayout(QBoxLayout::LeftToRight,q);
        layout->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);

        if(Qt::Vertical == _orientation){
            layout->setDirection(QBoxLayout::TopToBottom);
        }

        QPalette pale = q->palette();
        pale.setColor(QPalette::Active,QPalette::ButtonText,Qt::white);
        pale.setColor(QPalette::Inactive,QPalette::ButtonText,Qt::black);

        pale.setColor(QPalette::Active,QPalette::Background,QColor("#F36424"));
        pale.setColor(QPalette::Inactive,QPalette::Background,Qt::white);

        pale.setColor(QPalette::Active,QPalette::Foreground,QColor("#F36424"));
        pale.setColor(QPalette::Inactive,QPalette::Foreground,Qt::black);

        q->setColor(Qt::white);
        q->setPalette(pale);

        q->setLayout(layout);
        q->setRadiusRatios(50);
    }

    QtComponentsButtonTabs::QtComponentsButtonTabs(Qt::Orientation orientation, QWidget *parent)
        : QtComponentsAppBar(parent)
        , d_ptr(new QtComponentsButtonTabsPrivate(orientation,this))
    {
        d_func()->init();
    }

    QtComponentsButtonTabs::~QtComponentsButtonTabs()
    {

    }

    void QtComponentsButtonTabs::addTab(const QString &text)
    {
        layout()->addWidget(new QtComponentsButtonTab(text,this));
    }

    void QtComponentsButtonTabs::addTab(const QIcon &icon)
    {
        layout()->addWidget(new QtComponentsIconButtonTab(icon,this));
    }

    void QtComponentsButtonTabs::setCurrentTab(QtComponentsButtonTab *tab)
    {
        setCurrentTab(layout()->indexOf(tab));
    }

    void QtComponentsButtonTabs::setCurrentTab(int index)
    {
        Q_D(QtComponentsButtonTabs);

        for(int i = 0; i < layout()->count(); ++i)
            setTabActive(i, false);

        setTabActive(index);

        if(d->_animate){
            d->_overlay->animate();
        }

        emit currentChanged(index);
    }

    int QtComponentsButtonTabs::currentIndex() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_index;
    }

    Qt::Orientation QtComponentsButtonTabs::orientation() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_orientation;
    }

    void QtComponentsButtonTabs::setAnimate(bool animate)
    {
        Q_D(QtComponentsButtonTabs);
        d->_animate = animate;
    }

    bool QtComponentsButtonTabs::animate() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_animate;
    }

    void QtComponentsButtonTabs::setTabActive(int index, bool active)
    {
        Q_D(QtComponentsButtonTabs);

        QtComponentsButtonTab *tab = NULL;

        if (index > -1) {
            tab = static_cast<QtComponentsButtonTab *>(layout()->itemAt(index)->widget());
            if (tab) {
                d->_index = index;
                tab->setActive(active);
            }
        }
    }

}
