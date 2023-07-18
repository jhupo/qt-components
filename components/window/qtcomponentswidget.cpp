#include "qtcomponentswidget.h"
#include "qtcomponentsdwmapi.h"
#include "qtcomponentswindowhelper.h"

#include <QCoreApplication>


namespace Components{

    class QtComponentsWidgetPrivate
    {
        Q_DISABLE_COPY(QtComponentsWidgetPrivate)
        Q_DECLARE_PUBLIC(QtComponentsWidget)

    public:

        QtComponentsWidgetPrivate(QtComponentsWidget* q);
        ~QtComponentsWidgetPrivate();

        void init();

        QtComponentsWidget*const                q_ptr;
        QtComponentsWindowHelper*               _helper;
    };

    QtComponentsWidget::QtComponentsWidget(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsWidgetPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsWidget::~QtComponentsWidget()
    {

    }

    QtComponentsWidgetPrivate::QtComponentsWidgetPrivate(QtComponentsWidget *q)
        : q_ptr(q)
    {

    }

    QtComponentsWidgetPrivate::~QtComponentsWidgetPrivate()
    {

    }

    void QtComponentsWidgetPrivate::init()
    {
        Q_Q(QtComponentsWidget);
#ifdef DWM_AVAILABLE
        q->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        extendFrameIntoStyle(q);
        extendFrameIntoClientArea(q,1,1,1,1);
        QCoreApplication::instance()->installNativeEventFilter(&_dwm_filter);
#endif
        _helper = new QtComponentsWindowHelper(q,true);

        q->setObjectName("QtComponentsWidget");
    }


}
