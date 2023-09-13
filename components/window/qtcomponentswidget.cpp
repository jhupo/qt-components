#include "qtcomponentswidget.h"
#include "qtcomponentsdwmapi.h"
#include "qtcomponentswindowhelper.h"
#include "label/qtcomponentslabel.h"
#include "button/qtcomponentsiconbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QPainter>
#include <QWidget>
#include <QHBoxLayout>
#include <QApplication>

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
        QWidget*                                _titleBar;
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

    QHBoxLayout *QtComponentsWidget::appBarLayout() const
    {
        Q_D(const QtComponentsWidget);
        return qobject_cast<QHBoxLayout*>(d->_titleBar->layout());
    }

    void QtComponentsWidget::paintEvent(QPaintEvent *event)
    {
        QWidget::paintEvent(event);
#ifndef DWM_AVAILABLE
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(palette().color(QPalette::Shadow));
        painter.setBrush(palette().color(QPalette::Window));
        painter.drawRect(rect());
#endif
    }

    bool QtComponentsWidget::eventFilter(QObject *watched, QEvent *event)
    {
        Q_D(QtComponentsWidget);
        const QEvent::Type type = event->type();
        switch (type) {
        case QEvent::Move:
        case QEvent::Resize:
        {
            if(d->_titleBar){
                const int h = d->_titleBar->height();
                const QRect r = rect();
                d->_titleBar->setGeometry(r.x(), r.y(), r.width(), h);
                setContentsMargins(0, h, 0, 0);
            }
            break;
        }
        default:
            break;
        }
        return QWidget::eventFilter(watched,event);
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
        q->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
#ifdef DWM_AVAILABLE
        registerNativeEventFilter(q->winId());
        extendFrameIntoStyle(q);
        extendFrameIntoClientArea(q,1,1,1,1);
#endif
        _titleBar = new QWidget(q);
        _titleBar->setMinimumHeight(35);
        _titleBar->setObjectName("QtComponentsWidgetTitleBar");

        QHBoxLayout* layout = new QHBoxLayout(_titleBar);
        _titleBar->setLayout(layout);

        new QtComponentsWindowHelper(_titleBar,true);

        q->setPalette(QPalette(Qt::white));
        q->installEventFilter(q);
    }


}
