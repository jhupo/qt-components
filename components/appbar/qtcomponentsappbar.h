#ifndef __QTCOMPONENTSAPPBAR_H__
#define __QTCOMPONENTSAPPBAR_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class QtComponentsAppBarPrivate;

    class COMPONENTS_EXPORT QtComponentsAppBar : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsAppBar)
        Q_DECLARE_PRIVATE(QtComponentsAppBar)
        Q_PROPERTY(qreal roundedRadiusRatios READ roundedRadiusRatios WRITE setRoundedRadiusRatios)

    public:

        QtComponentsAppBar(QWidget* parent = Q_NULLPTR, Qt::Orientation orientaion = Qt::Horizontal);
        virtual~QtComponentsAppBar();

        void setRoundedRadiusRatios(const qreal ratios);
        qreal roundedRadiusRatios()const;

        void setRoundedRadius(const qreal radius);

        qreal roundedRadius()const;

        void setShadowBorderColor(const QColor& color, QPalette::ColorGroup group = QPalette::NColorGroups);
        QColor shadowBorderColor(QPalette::ColorGroup group = QPalette::Inactive)const;

        void setBackgroundColor(const QColor& color, QPalette::ColorGroup group = QPalette::NColorGroups);
        QColor backgroundColor(QPalette::ColorGroup group = QPalette::Inactive)const;

    protected:

        virtual void setColor(const QColor& color,
                              QPalette::ColorRole role = QPalette::Window,
                              QPalette::ColorGroup group = QPalette::NColorGroups);

        virtual QColor color(QPalette::ColorRole role = QPalette::Window, QPalette::ColorGroup group = QPalette::NColorGroups)const;
        Qt::Orientation orientaion()const;
        const QScopedPointer<QtComponentsAppBarPrivate>         d_ptr;
        virtual bool event(QEvent *event);
        virtual void paintEvent(QPaintEvent *);

    };


}



#endif
