#ifndef __QTCOMPONENTSCHECKBOX_H__
#define __QTCOMPONENTSCHECKBOX_H__

#include "qtcomponentscheckable.h"

namespace Components {

    class COMPONENTS_EXPORT QtComponentsCheckBox : public QtComponentsCheckable
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsCheckBox)

    public:

        QtComponentsCheckBox(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsCheckBox();

    };



}

#endif
