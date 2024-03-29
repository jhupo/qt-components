#include "qtcomponentsdialog.h"
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

namespace Components {

    class QtComponentsDialogPrivate
    {
        Q_DISABLE_COPY(QtComponentsDialogPrivate)
        Q_DECLARE_PUBLIC(QtComponentsDialog)

    public:

        QtComponentsDialogPrivate(QtComponentsDialog* q);
        ~QtComponentsDialogPrivate();

        void init();

        QtComponentsDialog*const                q_ptr;
        QWidget*                                _titleBar;

    };

    QtComponentsDialogPrivate::QtComponentsDialogPrivate(QtComponentsDialog *q)
        : q_ptr(q)
    {

    }

    QtComponentsDialogPrivate::~QtComponentsDialogPrivate()
    {

    }

    void QtComponentsDialogPrivate::init()
    {
        Q_Q(QtComponentsDialog);
        q->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
#ifdef DWM_AVAILABLE
        registerNativeEventFilter(q->winId());
        extendFrameIntoStyle(q);
        extendFrameIntoClientArea(q,1,1,1,1);
#endif
        _titleBar = new QWidget(q);
        _titleBar->setMinimumHeight(35);
        _titleBar->setObjectName("QtComponentsDialogTitleBar");
        _titleBar->setStyleSheet(QStringLiteral("#QtComponentsDialogTitleBar {border-bottom: 1px solid #E9EBF0;}"));

        QHBoxLayout* layout = new QHBoxLayout(_titleBar);

        Components::QtComponentsLabel* icon = new Components::QtComponentsLabel(_titleBar);
        icon->setFixedSize(19,19);
        QObject::connect(q,SIGNAL(windowIconChanged(QIcon)),icon,SLOT(setIcon(QIcon)));

        Components::QtComponentsLabel* title = new Components::QtComponentsLabel(_titleBar);
        title->setFont(Components::QtComponentsTheme::inst()->font(14,QFont::Medium));
        QObject::connect(q,SIGNAL(windowTitleChanged(QString)),title,SLOT(setText(QString)));

        Components::QtComponentsIconButton* close = new Components::QtComponentsIconButton(_titleBar);
        close->setIcon(Components::QtComponentsTheme::icon("window","close"));
        close->setIconColor(Qt::darkGray);
        close->setIconColor(Qt::red,QPalette::Active);
        QObject::connect(close,SIGNAL(clicked()),q,SLOT(close()));

        layout->setContentsMargins(19,9,19,9);
        layout->addWidget(icon);
        layout->addWidget(title);
        layout->addStretch();
        layout->addWidget(close);

        _titleBar->setLayout(layout);

        new QtComponentsWindowHelper(_titleBar);

        q->setAttribute(Qt::WA_DeleteOnClose);

        q->installEventFilter(q);

        q->setPalette(QPalette(Qt::white));
    }

    QtComponentsDialog::QtComponentsDialog(QWidget *parent)
        : QDialog(parent)
        , d_ptr(new QtComponentsDialogPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsDialog::~QtComponentsDialog()
    {

    }

    QHBoxLayout *QtComponentsDialog::appBarLayout() const
    {
        Q_D(const QtComponentsDialog);
        return qobject_cast<QHBoxLayout*>(d->_titleBar->layout());
    }

    void QtComponentsDialog::paintEvent(QPaintEvent * event)
    {
        QDialog::paintEvent(event);
#ifndef DWM_AVAILABLE
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(palette().color(QPalette::Shadow));
        painter.setBrush(palette().color(QPalette::Window));
        painter.drawRect(rect());
#endif
    }

    bool QtComponentsDialog::eventFilter(QObject *watched, QEvent *event)
    {
        Q_D(QtComponentsDialog);
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
        return QDialog::eventFilter(watched,event);
    }

}
