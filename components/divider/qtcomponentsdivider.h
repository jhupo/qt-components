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
        QtComponentsDivider(Qt::Orientation orientation, QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsDivider();

        void setColor(const QColor& color);
        QColor color()const;

        void setText(const QString& text);
        QString text()const;

        void setIcon(const QIcon& icon);
        QIcon icon()const;

        void setIconSize(const QSize& size);
        QSize iconSize()const;

        void setAlignment(Qt::AlignmentFlag flag);
        Qt::AlignmentFlag alignment()const;

        void setLineStyle(Qt::PenStyle style);
        Qt::PenStyle lineStyle()const;

        void setOrientation(Qt::Orientation orientation);
        Qt::Orientation orientation()const;

        virtual QSize sizeHint()const;

    protected:

        const QScopedPointer<QtComponentsDividerPrivate>            d_ptr;

        virtual void paintEvent(QPaintEvent *event);
    };

}

#endif
