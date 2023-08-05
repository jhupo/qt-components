#ifndef __QTCOMPONENTSPOPUP_H__
#define __QTCOMPONENTSPOPUP_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class QtComponentsPopupPrivate;

    class COMPONENTS_EXPORT QtComponentsPopup : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsPopup)
        Q_DECLARE_PRIVATE(QtComponentsPopup)

    public:

        QtComponentsPopup(QWidget* parent, Qt::Edge edge = Qt::BottomEdge);
        virtual~QtComponentsPopup();

        virtual QLayout* layout() const;

        void setColor(const QColor& color);
        QColor color()const;

        Qt::Edge edge()const;

    protected:

        virtual bool event(QEvent *event);
        virtual bool eventFilter(QObject *watched, QEvent *event);
        virtual void setLayout(QLayout* layout);
        const QScopedPointer<QtComponentsPopupPrivate>      d_ptr;

    };

}


#endif
