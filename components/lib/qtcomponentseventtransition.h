#ifndef __QTCOMPONENTSEVENTTRANSITION_H__
#define __QTCOMPONENTSEVENTTRANSITION_H__

#include "components_global.h"

#include <QEvent>

namespace Components {

    class QtComponentsEventTransitionPrivate;

    class COMPONENTS_EXPORT QtComponentsEventTransition : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsEventTransition)
        Q_DECLARE_PRIVATE(QtComponentsEventTransition)

    public:

        QtComponentsEventTransition(QObject* parent, QEvent::Type type);
        ~QtComponentsEventTransition();

    Q_SIGNALS:

        void triggered();

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        const QScopedPointer<QtComponentsEventTransitionPrivate>            d_ptr;

    };

}

#endif
