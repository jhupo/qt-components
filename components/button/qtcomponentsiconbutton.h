#ifndef __QTCOMPONENTSICONBUTTON_H__
#define __QTCOMPONENTSICONBUTTON_H__

#include "qtcomponentspushbutton.h"

namespace Components {

    class COMPONENTS_EXPORT QtComponentsIconButton : public QtComponentsPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsIconButton)

    public:

        QtComponentsIconButton(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsIconButton();

        virtual QSize sizeHint()const;

        void setDotDisabled(bool disable);
        bool isDotDisabled()const;

    protected:

        virtual void paintEvent(QPaintEvent *);

    };

}


#endif
