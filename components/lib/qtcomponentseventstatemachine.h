#ifndef __QTCOMPONENTSEVENTSTATEMACHINE_H__
#define __QTCOMPONENTSEVENTSTATEMACHINE_H__


#include "components_global.h"

#include <QStateMachine>

class QPropertyAnimation;

namespace Components {

    class QtComponentsEventStateMachinePrivate;

    class COMPONENTS_EXPORT QtComponentsEventStateMachine : public QStateMachine
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsEventStateMachine)
        Q_DECLARE_PRIVATE(QtComponentsEventStateMachine)

    public:

        QtComponentsEventStateMachine(QObject* parent);
        virtual~QtComponentsEventStateMachine();

        void setDefaultAnimationPropertyName(const QByteArray& propertyName);

        void setNormalEventTransition(QEvent::Type type);
        void setTargetEventTransition(QEvent::Type type);

        void assignNormalProperty(const QVariant& value);
        void assignTargetProperty(const QVariant& value);

        void reverse();

    protected:

        const QScopedPointer<QtComponentsEventStateMachinePrivate>          d_ptr;

    };

}


#endif
