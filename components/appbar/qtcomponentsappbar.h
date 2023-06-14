#ifndef __QTCOMPONENTSAPPBAR_H__
#define __QTCOMPONENTSAPPBAR_H__

#include "components_global.h"

#include <QWidget>
#include <QHBoxLayout>

namespace Components {

    class QtComponentsAppBarPrivate;

    class COMPONENTS_EXPORT QtComponentsAppBar : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsAppBar)
        Q_DECLARE_PRIVATE(QtComponentsAppBar)
        Q_PROPERTY(QColor foregroundColor WRITE setForegroundColor READ foregroundColor)
        Q_PROPERTY(QColor backgroundColor WRITE setBackgroundColor READ backgroundColor)

    public:

        QtComponentsAppBar(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsAppBar();

        void setForegroundColor(const QColor &color);
        QColor foregroundColor() const;

        void setBackgroundColor(const QColor &color);
        QColor backgroundColor() const;

        void setRadius(const qreal radius);
        qreal radius()const;

        inline QHBoxLayout *appBarLayout() const;

    protected:

        const QScopedPointer<QtComponentsAppBarPrivate>         d_ptr;

        virtual void paintEvent(QPaintEvent *event);

    };

    inline QHBoxLayout *QtComponentsAppBar::appBarLayout() const
    {
        return static_cast<QHBoxLayout *>(layout());
    }


}



#endif
