#ifndef __QTCOMPONENTSWIDGET_H__
#define __QTCOMPONENTSWIDGET_H__

#include "components_global.h"

#include <QWidget>

class QHBoxLayout;

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

        QHBoxLayout* appBarLayout()const;

    protected:
        virtual bool eventFilter(QObject *watched, QEvent *event);
        const QScopedPointer<QtComponentsWidgetPrivate>     d_ptr;

    };

}

#endif
