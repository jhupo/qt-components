#include "qtcomponentswaitforloader.h"
#include "qtcomponentswaitforloader_p.h"
#include "lib/qtcomponentseventtransition.h"

#include <QTimer>
#include <QEvent>
#include <QPainter>
#include <QEventTransition>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

namespace Components {

    QtComponentsWaitForLoaderPrivate::QtComponentsWaitForLoaderPrivate(QtComponentsWaitForLoader *q)
        : q_ptr(q)
    {

    }

    QtComponentsWaitForLoaderPrivate::~QtComponentsWaitForLoaderPrivate()
    {

    }

    void QtComponentsWaitForLoaderPrivate::init()
    {
        Q_Q(QtComponentsWaitForLoader);

        q->setBackgroundColor(Qt::darkGray);
        q->setCircularColor(QColor("#00BCD4"));

        _singleTimer = new QTimer(q);
        _singleTimer->setSingleShot(true);
        _singleTimer->setInterval(5 * 60 * 1000);

        _delegate = new QtComponentsWaitForLoaderDelegate(q);

        _animation = new QParallelAnimationGroup(q);
        _animation->setLoopCount(-1);

        QtComponentsEventTransition* showEventTransition = new QtComponentsEventTransition(q,QEvent::Show);
        QtComponentsEventTransition* hideEventTransition = new QtComponentsEventTransition(q,QEvent::Hide);

        QObject::connect(showEventTransition,SIGNAL(triggered()),_singleTimer,SLOT(start()));
        QObject::connect(showEventTransition,SIGNAL(triggered()),_animation,SLOT(start()));

        QObject::connect(hideEventTransition,SIGNAL(triggered()),_singleTimer,SLOT(stop()));
        QObject::connect(hideEventTransition,SIGNAL(triggered()),_animation,SLOT(stop()));

        QObject::connect(_singleTimer,SIGNAL(timeout()),q,SLOT(hide()));
        QObject::connect(_singleTimer,SIGNAL(timeout()),_animation,SLOT(stop()));

        QPropertyAnimation *animation;

        animation = new QPropertyAnimation(q);
        animation->setPropertyName("dashLength");
        animation->setTargetObject(_delegate);
        animation->setEasingCurve(QEasingCurve::InOutQuad);
        animation->setStartValue(0.1);
        animation->setKeyValueAt(0.15, 0.2);
        animation->setKeyValueAt(0.6, 20);
        animation->setKeyValueAt(0.7, 20);
        animation->setEndValue(20);
        animation->setDuration(2050);

        _animation->addAnimation(animation);

        animation = new QPropertyAnimation(q);
        animation->setPropertyName("dashOffset");
        animation->setTargetObject(_delegate);
        animation->setEasingCurve(QEasingCurve::InOutSine);
        animation->setStartValue(0);
        animation->setKeyValueAt(0.15, 0);
        animation->setKeyValueAt(0.6, -7);
        animation->setKeyValueAt(0.7, -7);
        animation->setEndValue(-25);
        animation->setDuration(2050);

        _animation->addAnimation(animation);

        animation = new QPropertyAnimation(q);
        animation->setPropertyName("angle");
        animation->setTargetObject(_delegate);
        animation->setStartValue(0);
        animation->setEndValue(719);
        animation->setDuration(2050);

        _animation->addAnimation(animation);

    }

    QtComponentsWaitForLoader::QtComponentsWaitForLoader(QWidget *parent)
        : QtComponentsOverlayWidget(parent)
        , d_ptr(new QtComponentsWaitForLoaderPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsWaitForLoader::~QtComponentsWaitForLoader()
    {

    }

    void QtComponentsWaitForLoader::setInterval(int msec)
    {
        Q_D(QtComponentsWaitForLoader);
        d->_singleTimer->setInterval(msec);
    }

    int QtComponentsWaitForLoader::interval() const
    {
        Q_D(const QtComponentsWaitForLoader);
        return d->_singleTimer->interval();
    }

    void QtComponentsWaitForLoader::setBackgroundColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::Background,color);
        setPalette(pale);
    }

    QColor QtComponentsWaitForLoader::backgroundColor() const
    {
        return palette().color(QPalette::Background);
    }

    void QtComponentsWaitForLoader::setCircularColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::Foreground,color);
        setPalette(pale);
    }

    QColor QtComponentsWaitForLoader::circularColor() const
    {
        return palette().color(QPalette::Foreground);
    }

    void QtComponentsWaitForLoader::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsWaitForLoader);

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing);
        painter.setOpacity(0.25);
        painter.fillRect(rect(), backgroundColor());

        painter.translate(width() / 2, height() / 2);
        painter.rotate(d->_delegate->angle());

        const qreal pw = 6.25;
        const int s = 64;

        painter.setOpacity(1);

        QPen pen;
        pen.setCapStyle(Qt::RoundCap);
        pen.setWidthF(pw);
        pen.setColor(circularColor());

        QVector<qreal> pattern;
        pattern << d->_delegate->dashLength()*s/50 << 30*s/50;

        pen.setDashOffset(d->_delegate->dashOffset()*s/50);
        pen.setDashPattern(pattern);

        painter.setPen(pen);

        painter.drawEllipse(QPoint(0, 0), s/2, s/2);

    }

    QtComponentsWaitForLoaderDelegate::QtComponentsWaitForLoaderDelegate(QtComponentsWaitForLoader *parent)
        : QObject(parent)
        , _parent(parent)
        , _dashLength(89)
        , _angle(0)
        , _dashOffset(0)
    {

    }

    QtComponentsWaitForLoaderDelegate::~QtComponentsWaitForLoaderDelegate()
    {

    }

}
