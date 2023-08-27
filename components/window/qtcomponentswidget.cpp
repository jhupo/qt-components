#include "qtcomponentswidget.h"
#include "qtcomponentsdwmapi.h"
#include "qtcomponentswindowhelper.h"
#include "label/qtcomponentslabel.h"
#include "button/qtcomponentsiconbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
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

    void QtComponentsWidget::setWindowTitleBar(QWidget *title)
    {
        Q_D(QtComponentsWidget);
        if(d->_titleBar){
            delete d->_titleBar;
        }
        new QtComponentsWindowHelper(title,true);
        d->_titleBar = title;
    }

    QWidget *QtComponentsWidget::windowTitleBar() const
    {
        Q_D(const QtComponentsWidget);
        return d->_titleBar;
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
#ifdef DWM_AVAILABLE
        q->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        extendFrameIntoStyle(q);
        extendFrameIntoClientArea(q,1,1,1,1);
        QCoreApplication::instance()->installNativeEventFilter(&_dwm_filter);
#endif
        _titleBar = new QWidget(q);
        _titleBar->setMinimumHeight(46);
        _titleBar->setObjectName("QtComponentsWidgetTitleBar");

        QHBoxLayout* layout = new QHBoxLayout(_titleBar);

        Components::QtComponentsLabel* icon = new Components::QtComponentsLabel(_titleBar);
        icon->setFixedSize(19,19);
        QObject::connect(q,SIGNAL(windowIconChanged(QIcon)),icon,SLOT(setIcon(QIcon)));

        Components::QtComponentsLabel* title = new Components::QtComponentsLabel(_titleBar);
        title->setFont(Components::QtComponentsTheme::inst()->font(16,QFont::Medium));
        QObject::connect(q,SIGNAL(windowTitleChanged(QString)),title,SLOT(setText(QString)));

        Components::QtComponentsIconButton* minus = new Components::QtComponentsIconButton(_titleBar);
        minus->setIconSize(QSize(16,16));
        minus->setIcon(Components::QtComponentsTheme::icon("window","minus"));
        minus->setColor(Qt::darkGray);
        QObject::connect(minus,SIGNAL(clicked()),q,SLOT(showMinimized()));

        Components::QtComponentsIconButton* close = new Components::QtComponentsIconButton(_titleBar);
        close->setIcon(Components::QtComponentsTheme::icon("window","close"));
        close->setColor(Qt::darkGray);
        close->setColor(Qt::red,QPalette::Button, QPalette::Active);
        QObject::connect(close,SIGNAL(clicked()),q,SLOT(close()));

        layout->setContentsMargins(19,9,19,9);
        layout->setSpacing(24);
        layout->addWidget(icon);
        layout->addWidget(title);
        layout->addStretch();
        layout->addWidget(minus);
        layout->addWidget(close);

        _titleBar->setLayout(layout);

        new QtComponentsWindowHelper(_titleBar,true);

        q->installEventFilter(q);

        q->setPalette(QPalette(Qt::white));
    }


}
