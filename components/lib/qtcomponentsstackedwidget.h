#ifndef __QTCOMPONENTSSTACKEDWIDGET_H__
#define __QTCOMPONENTSSTACKEDWIDGET_H__

#include "components_global.h"

#include <QStackedWidget>


namespace Components {

    class QtComponentsStackedWidgetPrivate;

    class COMPONENTS_EXPORT QtComponentsStackedWidget : public QStackedWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsStackedWidget)
        Q_DECLARE_PRIVATE(QtComponentsStackedWidget)
        Q_PROPERTY(qreal radius READ radius WRITE setRadius)

    public:

        QtComponentsStackedWidget(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsStackedWidget();

        void setColor(const QColor& color);
        QColor color()const;

        void setRadius(const qreal& radius);
        qreal radius()const;

    protected:

        virtual void paintEvent(QPaintEvent *);
        const QScopedPointer<QtComponentsStackedWidgetPrivate>          d_ptr;

    };

}

#endif
