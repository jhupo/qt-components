#include "qtcomponentsstyle.h"

#include <QFontDatabase>

namespace Components {

    class QtComponentsStylePrivate
    {
        Q_DISABLE_COPY(QtComponentsStylePrivate)
        Q_DECLARE_PUBLIC(QtComponentsStyle)

    public:

        QtComponentsStylePrivate(QtComponentsStyle *q);
        virtual~QtComponentsStylePrivate();

        void init();

        QtComponentsStyle*const                 q_ptr;

    };

    QtComponentsStylePrivate::QtComponentsStylePrivate(QtComponentsStyle *q)
        : q_ptr(q)
    {
        Q_ASSERT(q);
    }

    QtComponentsStylePrivate::~QtComponentsStylePrivate()
    {

    }

    void QtComponentsStylePrivate::init()
    {

    }

    QtComponentsStyle::QtComponentsStyle()
        : QCommonStyle()
        , d_ptr(new QtComponentsStylePrivate(this))
    {
        d_func()->init();
    }

    QtComponentsStyle::~QtComponentsStyle()
    {

    }

    void QtComponentsStyle::drawPrimitive(QStyle::PrimitiveElement pe, const QStyleOption *opt, QPainter *p, const QWidget *w) const
    {
        if (pe == QStyle::PE_FrameFocusRect)
            return;
        QCommonStyle::drawPrimitive(pe, opt, p, w);
    }


}
