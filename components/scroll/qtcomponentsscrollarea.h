#ifndef __QTCOMPONENTSCROLLAREA_H__
#define __QTCOMPONENTSCROLLAREA_H__

#include "components_global.h"

#include <QScrollArea>

namespace Components {

    class QtComponentsScrollAreaPrivate;

    class COMPONENTS_EXPORT QtComponentsScrollArea : public QScrollArea
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsScrollArea)
        Q_DECLARE_PRIVATE(QtComponentsScrollArea)

    public:

        QtComponentsScrollArea(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsScrollArea();

        virtual QLayout* layout() const;

    protected:

        const QScopedPointer<QtComponentsScrollAreaPrivate>     d_ptr;


    };


}



#endif
