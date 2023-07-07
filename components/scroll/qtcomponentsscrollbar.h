#ifndef __QTCOMPONENTSCROLLBAR_H__
#define __QTCOMPONENTSCROLLBAR_H__

#include "components_global.h"

#include <QScrollBar>

namespace Components {

    class QtComponentsScrollBarPrivate;

    class COMPONENTS_EXPORT QtComponentsScrollBar : public QScrollBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsScrollBar)
        Q_DECLARE_PRIVATE(QtComponentsScrollBar)

    public:

        QtComponentsScrollBar(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsScrollBar();

        void setCanvasColor(const QColor &color);
        QColor canvasColor() const;

        void setBackgroundColor(const QColor &color);
        QColor backgroundColor() const;

        void setSliderColor(const QColor &color);
        QColor sliderColor() const;

        virtual QSize sizeHint()const;

    protected:

        virtual void paintEvent(QPaintEvent *);

        const QScopedPointer<QtComponentsScrollBarPrivate>      d_ptr;

    };


}


#endif
