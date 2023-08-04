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

        void setWindowTitleBar(QWidget* title);
        QWidget *windowTitleBar()const;

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        const QScopedPointer<QtComponentsWidgetPrivate>     d_ptr;

    };

}

#endif
