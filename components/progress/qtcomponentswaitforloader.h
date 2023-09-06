#ifndef __QTCOMPONENTSWAITFORLOADER_H__
#define __QTCOMPONENTSWAITFORLOADER_H__

#include "lib/qtcomponentsoverlaywidget.h"

namespace Components {

    class QtComponentsWaitForLoaderPrivate;

    class COMPONENTS_EXPORT QtComponentsWaitForLoader : public QtComponentsOverlayWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsWaitForLoader)
        Q_DECLARE_PRIVATE(QtComponentsWaitForLoader)

    public:

        QtComponentsWaitForLoader(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsWaitForLoader();

        void setInterval(int msec);
        int interval()const;

        void setBackgroundColor(const QColor& color);
        QColor backgroundColor()const;

        void setCircularColor(const QColor& color);
        QColor circularColor()const;

    protected:
        virtual void paintEvent(QPaintEvent *);
        const QScopedPointer<QtComponentsWaitForLoaderPrivate>              d_ptr;

    };

}


#endif
