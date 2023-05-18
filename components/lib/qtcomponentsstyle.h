#ifndef __QTCOMPONENTSSTYLE_H__
#define __QTCOMPONENTSSTYLE_H__

#include "components_global.h"

#include <QCommonStyle>

namespace Components {

    class QtComponentsStylePrivate;

    class COMPONENTS_EXPORT QtComponentsStyle : public QCommonStyle
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsStyle)
        Q_DECLARE_PRIVATE(QtComponentsStyle)

    private:

        QtComponentsStyle();
        virtual~QtComponentsStyle();

    public:

        inline static QtComponentsStyle* inst();

        virtual void drawPrimitive(PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w  = 0 )const;

    protected:

        const QScopedPointer<QtComponentsStylePrivate>      d_ptr;

    };

    inline QtComponentsStyle* QtComponentsStyle::inst()
    {
        static QtComponentsStyle _inst_;
        return &_inst_;
    }


}


#endif
