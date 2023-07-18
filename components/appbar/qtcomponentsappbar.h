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

    public:

        QtComponentsAppBar(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsAppBar();

        void setColor(const QColor& color);
        QColor color()const;

        void setRadiusRatios(const qreal radius);
        qreal radiusRatios()const;

        inline QHBoxLayout *appBarLayout() const;

    protected:

        const QScopedPointer<QtComponentsAppBarPrivate>         d_ptr;

        virtual void paintEvent(QPaintEvent *);

    };

    inline QHBoxLayout *QtComponentsAppBar::appBarLayout() const
    {
        return static_cast<QHBoxLayout *>(layout());
    }


}



#endif
