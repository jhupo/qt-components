#ifndef __QTCOMPONENTSRADIOBUTTON_H__
#define __QTCOMPONENTSRADIOBUTTON_H__

#include "qtcomponentscheckbox.h"

namespace Components {

    class COMPONENTS_EXPORT QtComponentsRadioButton : public QtComponentsCheckBox
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsRadioButton)

    public:

        QtComponentsRadioButton(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsRadioButton();

    };

}


#endif
