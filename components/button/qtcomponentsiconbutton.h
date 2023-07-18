#ifndef __QTCOMPONENTSICONBUTTON_H__
#define __QTCOMPONENTSICONBUTTON_H__

#include "components_global.h"

#include "qtcomponentsbutton.h"

namespace Components {

    class QtComponentsIconButtonPrivate;

    class COMPONENTS_EXPORT QtComponentsIconButton : public QtComponentsButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsIconButton)
        Q_DECLARE_PRIVATE(QtComponentsIconButton)

    public:

        QtComponentsIconButton(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsIconButton();

        void setMarkColor(const QColor& color);
        QColor markColor()const;

        void setMarkDisabled(bool disabled);
        bool markDisabled()const;

        void setMarkDisplay(const bool display);
        bool markDisplay()const;

        virtual QSize sizeHint()const;

    protected:

        virtual void paintEvent(QPaintEvent *);

        const QScopedPointer<QtComponentsIconButtonPrivate>         d_ptr;

    private:

        Q_PRIVATE_SLOT(d_func(),void cleanMark())

    };


}

#endif
