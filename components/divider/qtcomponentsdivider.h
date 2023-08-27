#ifndef __QTCOMPONENTSDIVIDER_H__
#define __QTCOMPONENTSDIVIDER_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class QtComponentsDividerPrivate;

    class COMPONENTS_EXPORT QtComponentsDivider : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsDivider)
        Q_DECLARE_PRIVATE(QtComponentsDivider)

    public:

        QtComponentsDivider(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsDivider();

        void setColor(const QColor& color);
        QColor color()const;

        void setLineStyle(Qt::PenStyle style);
        Qt::PenStyle lineStyle()const;

        void setLineWidth(qreal width);
        qreal lineWidth()const;

        virtual QSize sizeHint()const;

    protected:

        const QScopedPointer<QtComponentsDividerPrivate>            d_ptr;

        virtual void paintEvent(QPaintEvent *);
    };

}

#endif
