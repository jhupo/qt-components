#include "qtcomponentsprogressbar.h"
#include "qtcomponentsprogressbar_p.h"

#include <QPainter>
#include <QPropertyAnimation>

namespace Components {

    QtComponentsProgressBarPrivate::QtComponentsProgressBarPrivate(QtComponentsProgressBar *q)
        : q_ptr(q)
    {

    }

    QtComponentsProgressBarPrivate::~QtComponentsProgressBarPrivate()
    {

    }

    void QtComponentsProgressBarPrivate::init()
    {
        Q_Q(QtComponentsProgressBar);

        q->setDisabledColor(Qt::darkGray);
        q->setBackgroundColor(QColor("#ECEEF5"));
        q->setProgressColor(QColor("#F26521"));

        _type = QtComponentsProgressBar::DeterminateProgress;
        _delegate = new QtComponentsProgressDelegate(q);

        _animation = new QPropertyAnimation(q);
        _animation->setPropertyName("offset");
        _animation->setTargetObject(_delegate);
        _animation->setStartValue(0);
        _animation->setEndValue(1);
        _animation->setDuration(1000);

        _animation->setLoopCount(-1);

    }

    QtComponentsProgressDelegate::QtComponentsProgressDelegate(QtComponentsProgressBar *progress)
        : QObject(progress)
        , _progress(progress)
        , _offset(0)
    {

    }

    QtComponentsProgressDelegate::~QtComponentsProgressDelegate()
    {

    }

    QtComponentsProgressBar::QtComponentsProgressBar(QWidget *parent)
        : QProgressBar(parent)
        , d_ptr(new QtComponentsProgressBarPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsProgressBar::~QtComponentsProgressBar()
    {

    }

    void QtComponentsProgressBar::setBackgroundColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::Inactive,QPalette::Background,color);
        setPalette(pale);
    }

    QColor QtComponentsProgressBar::backgroundColor() const
    {
        return palette().color(QPalette::Inactive,QPalette::Background);
    }

    void QtComponentsProgressBar::setProgressColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::Inactive,QPalette::Foreground,color);
        setPalette(pale);
    }

    QColor QtComponentsProgressBar::progressColor() const
    {
        return palette().color(QPalette::Inactive,QPalette::Foreground);
    }

    void QtComponentsProgressBar::setDisabledColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::Disabled,QPalette::Background,color);
        setPalette(pale);
    }

    QColor QtComponentsProgressBar::disabledColor() const
    {
        return palette().color(QPalette::Disabled,QPalette::Background);
    }

    void QtComponentsProgressBar::setProgressType(QtComponentsProgressBar::ProgressType type)
    {
        Q_D(QtComponentsProgressBar);
        if(IndeterminateProgress == type){
            d->_animation->start();
        }else{
            d->_animation->stop();
        }
        d->_type = type;
    }

    QtComponentsProgressBar::ProgressType QtComponentsProgressBar::progressType() const
    {
        Q_D(const QtComponentsProgressBar);
        return d->_type;
    }

    void QtComponentsProgressBar::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsProgressBar);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(isEnabled() ? backgroundColor()
                                   : disabledColor());
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);

        QPainterPath path;
        path.addRoundedRect(0, height()/2-3, width(), 6, 3, 3);
        painter.setClipPath(path);

        painter.drawRect(0, 0, width(), height());

        if (isEnabled())
        {
            brush.setColor(progressColor());
            painter.setBrush(brush);

            if (IndeterminateProgress == d->_type) {
                painter.drawRect(d->_delegate->offset()*width()*2-width(), 0, width(), height());
            } else {
                qreal p = static_cast<qreal>(width())*(value()-minimum())/(maximum()-minimum());
                painter.drawRect(0, 0, p, height());
            }
        }
    }

}
