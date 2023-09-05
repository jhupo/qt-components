#include "qtcomponentseventstatemachine.h"

#include <QEventTransition>
#include <QPropertyAnimation>

namespace Components {

    class QtComponentsEventStateMachinePrivate
    {
        Q_DISABLE_COPY(QtComponentsEventStateMachinePrivate)
        Q_DECLARE_PUBLIC(QtComponentsEventStateMachine)

    public:

        QtComponentsEventStateMachinePrivate(QtComponentsEventStateMachine* q);
        ~QtComponentsEventStateMachinePrivate();

        void init();

        QtComponentsEventStateMachine*const                 q_ptr;
        QState*                                             _normal;
        QState*                                             _target;
        QPropertyAnimation*                                 _animation;
        QObject*                                            _parent;
    };

    QtComponentsEventStateMachinePrivate::QtComponentsEventStateMachinePrivate(QtComponentsEventStateMachine *q)
        : q_ptr(q)
    {

    }

    QtComponentsEventStateMachinePrivate::~QtComponentsEventStateMachinePrivate()
    {

    }

    void QtComponentsEventStateMachinePrivate::init()
    {
        Q_Q(QtComponentsEventStateMachine);

        Q_ASSERT(q->parent());

        _parent = q->parent();

        _normal = new QState;
        _target = new QState;

        _animation = new QPropertyAnimation(q);
        _animation->setDuration(350);

        q->addState(_normal);
        q->addState(_target);
        q->addDefaultAnimation(_animation);
        q->setInitialState(_normal);
    }

    QtComponentsEventStateMachine::QtComponentsEventStateMachine(QObject *parent)
        : QStateMachine(parent)
        , d_ptr(new QtComponentsEventStateMachinePrivate(this))
    {
        d_func()->init();
    }

    QtComponentsEventStateMachine::~QtComponentsEventStateMachine()
    {

    }

    void QtComponentsEventStateMachine::setDefaultAnimationPropertyName(const QByteArray &propertyName)
    {
        Q_D(QtComponentsEventStateMachine);
        d->_animation->setTargetObject(d->_parent);
        d->_animation->setPropertyName(propertyName);
    }

    void QtComponentsEventStateMachine::setNormalEventTransition(QEvent::Type type)
    {
        Q_D(QtComponentsEventStateMachine);
        QEventTransition* transition = new QEventTransition(d->_parent,type);
        transition->setTargetState(d->_target);
        transition->addAnimation(d->_animation);
        d->_normal->addTransition(transition);
    }

    void QtComponentsEventStateMachine::setTargetEventTransition(QEvent::Type type)
    {
        Q_D(QtComponentsEventStateMachine);
        QEventTransition* transition = new QEventTransition(d->_parent,type);
        transition->setTargetState(d->_normal);
        transition->addAnimation(d->_animation);
        d->_target->addTransition(transition);
    }

    void QtComponentsEventStateMachine::assignNormalProperty(const QVariant &value)
    {
        Q_D(QtComponentsEventStateMachine);
        d->_normal->setProperty(d->_animation->propertyName(),value);
        d->_normal->assignProperty(d->_parent,d->_animation->propertyName(),value);
    }

    void QtComponentsEventStateMachine::assignTargetProperty(const QVariant &value)
    {
        Q_D(QtComponentsEventStateMachine);
        d->_target->setProperty(d->_animation->propertyName(),value);
        d->_target->assignProperty(d->_parent,d->_animation->propertyName(),value);
    }

    void QtComponentsEventStateMachine::reverse()
    {
        Q_D(QtComponentsEventStateMachine);
        const QByteArray property = d->_animation->propertyName();
        const QVariant normal = d->_normal->property(property);
        const QVariant target = d->_target->property(property);
        assignNormalProperty(target);
        assignTargetProperty(normal);
    }

}

