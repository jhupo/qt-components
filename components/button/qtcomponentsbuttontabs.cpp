#include "qtcomponentsbuttontabs.h"
#include "qtcomponentsbuttontabs_p.h"


namespace Components {

    QtComponentsButtonTabsPrivate::QtComponentsButtonTabsPrivate(QtComponentsButtonTabs *q)
        : q_ptr(q)
    {

    }

    QtComponentsButtonTabsPrivate::~QtComponentsButtonTabsPrivate()
    {

    }

    void QtComponentsButtonTabsPrivate::init()
    {
        _index = 0;
    }

    QtComponentsButtonTabs::QtComponentsButtonTabs(QWidget *parent, Qt::Orientation orientaion)
        : QtComponentsAppBar(parent,orientaion)
        , d_ptr(new QtComponentsButtonTabsPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsButtonTabs::~QtComponentsButtonTabs()
    {

    }

    void QtComponentsButtonTabs::setCurrentIndex(int index)
    {
        Q_D(QtComponentsButtonTabs);
        d->_index = index;
    }

    int QtComponentsButtonTabs::currentIndex() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_index;
    }




}
