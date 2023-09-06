#include "qtcomponentseventtransition.h"


namespace Components {

    class QtComponentsEventTransitionPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsEventTransition)

    public:

        QtComponentsEventTransitionPrivate(QtComponentsEventTransition* q, QEvent::Type type);
        ~QtComponentsEventTransitionPrivate();

        QtComponentsEventTransition*const           q_ptr;
        QEvent::Type                                _type;

    };

    QtComponentsEventTransitionPrivate::QtComponentsEventTransitionPrivate(QtComponentsEventTransition *q, QEvent::Type type)
        : q_ptr(q)
        , _type(type)
    {

    }

    QtComponentsEventTransitionPrivate::~QtComponentsEventTransitionPrivate()
    {

    }

    QtComponentsEventTransition::QtComponentsEventTransition(QObject *parent, QEvent::Type type)
        : QObject(parent)
        , d_ptr(new QtComponentsEventTransitionPrivate(this,type))
    {
        Q_ASSERT(parent);
        parent->installEventFilter(this);
    }

    QtComponentsEventTransition::~QtComponentsEventTransition()
    {

    }

    bool QtComponentsEventTransition::eventFilter(QObject *watched, QEvent *event)
    {
        Q_D(QtComponentsEventTransition);
        if(event->type() == d->_type){
            emit triggered();
        }
        return QObject::eventFilter(watched,event);
    }

}
