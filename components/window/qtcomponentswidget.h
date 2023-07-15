#ifndef __QTCOMPONENTSWIDGET_H__
#define __QTCOMPONENTSWIDGET_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class QtComponentsWidgetPrivate;

    class COMPONENTS_EXPORT QtComponentsWidget : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsWidget)
        Q_DECLARE_PRIVATE(QtComponentsWidget)

    public:

        QtComponentsWidget(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsWidget();

    protected:

        const QScopedPointer<QtComponentsWidgetPrivate>     d_ptr;

    };

}

#endif
