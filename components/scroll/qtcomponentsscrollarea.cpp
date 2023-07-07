#include "qtcomponentsscrollarea.h"
#include "qtcomponentsscrollbar.h"
#include "lib/qtcomponentsstyle.h"

#include <QPainter>
#include <QVBoxLayout>

namespace Components {

    class QtComponentsScrollAreaPrivate
    {
        Q_DISABLE_COPY(QtComponentsScrollAreaPrivate)
        Q_DECLARE_PUBLIC(QtComponentsScrollArea)

    public:

        QtComponentsScrollAreaPrivate(QtComponentsScrollArea* q);
        virtual~QtComponentsScrollAreaPrivate();

        void init();

        QtComponentsScrollArea*const                q_ptr;

    };

    QtComponentsScrollAreaPrivate::QtComponentsScrollAreaPrivate(QtComponentsScrollArea *q)
        : q_ptr(q)
    {

    }

    QtComponentsScrollAreaPrivate::~QtComponentsScrollAreaPrivate()
    {

    }

    void QtComponentsScrollAreaPrivate::init()
    {
        Q_Q(QtComponentsScrollArea);
        q->setStyle(QtComponentsStyle::inst());
        q->setFrameShape(QFrame::NoFrame);
        q->setHorizontalScrollBar(new QtComponentsScrollBar);
        q->setVerticalScrollBar(new QtComponentsScrollBar);
        QWidget* widget = new QWidget(q);
        QVBoxLayout* layout = new QVBoxLayout(widget);
        widget->setLayout(layout);
        q->setWidget(widget);
        q->setWidgetResizable(true);
    }

    QtComponentsScrollArea::QtComponentsScrollArea(QWidget *parent)
        : QScrollArea(parent)
        , d_ptr(new QtComponentsScrollAreaPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsScrollArea::~QtComponentsScrollArea()
    {

    }

    QLayout *QtComponentsScrollArea::layout() const
    {
        if(!widget()){
            qCWarning(logger_components)<<"The center window is a null pointer";
            return Q_NULLPTR;
        }
        if(!widget()->layout()){
            qCWarning(logger_components)<<"Center window without layout";
            return Q_NULLPTR;
        }
        return widget()->layout();
    }

}
