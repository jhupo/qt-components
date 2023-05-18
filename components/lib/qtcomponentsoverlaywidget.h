#ifndef __QTCOMPONENTSOVERLAYWIDGET_H__
#define __QTCOMPONENTSOVERLAYWIDGET_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class COMPONENTS_EXPORT QtComponentsOverlayWidget : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsOverlayWidget)

    public:

        QtComponentsOverlayWidget(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsOverlayWidget();

    protected:

        virtual bool event(QEvent *event);
        virtual bool eventFilter(QObject *watched, QEvent *event);
        virtual QRect overlayGeometry()const;

    };

}

#endif
