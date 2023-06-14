#include "qtcomponentsappbar.h"
#include "lib/qtcomponentstheme.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

namespace Components {

    class QtComponentsAppBarPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsAppBar)

    public:

        QtComponentsAppBarPrivate(QtComponentsAppBar* q);
        ~QtComponentsAppBarPrivate();

        void init();

        QtComponentsAppBar*const                q_ptr;
        QColor                                  _foregroundColor;
        QColor                                  _backgroundColor;
        qreal                                   _radius;
    };

    QtComponentsAppBarPrivate::QtComponentsAppBarPrivate(QtComponentsAppBar *q)
        : q_ptr(q)
    {

    }

    QtComponentsAppBarPrivate::~QtComponentsAppBarPrivate()
    {

    }

    void QtComponentsAppBarPrivate::init()
    {
        Q_Q(QtComponentsAppBar);

        _radius = 8.;

        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(16);
        effect->setColor(Qt::darkGray);
        effect->setOffset(0, 0);

        q->setGraphicsEffect(effect);

        QHBoxLayout *layout = new QHBoxLayout;
        q->setLayout(layout);

        q->setBackgroundColor(QtComponentsTheme::inst()->color(cyan600));
        q->setForegroundColor(QtComponentsTheme::inst()->color(darkGray));

    }

    QtComponentsAppBar::QtComponentsAppBar(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsAppBarPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsAppBar::~QtComponentsAppBar()
    {

    }

    void QtComponentsAppBar::setForegroundColor(const QColor &color)
    {
        Q_D(QtComponentsAppBar);
        d->_foregroundColor = color;
        update();
    }

    QColor QtComponentsAppBar::foregroundColor() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_foregroundColor;
    }

    void QtComponentsAppBar::setBackgroundColor(const QColor &color)
    {
        Q_D(QtComponentsAppBar);
        d->_backgroundColor = color;
        update();
    }

    QColor QtComponentsAppBar::backgroundColor() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_backgroundColor;
    }

    void QtComponentsAppBar::setRadius(const qreal radius)
    {
        Q_D(QtComponentsAppBar);
        d->_radius = radius;
        update();
    }

    qreal QtComponentsAppBar::radius() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_radius;
    }

    void QtComponentsAppBar::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        Q_D(QtComponentsAppBar);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QPainterPath path;
        path.addRoundedRect(rect(),QtComponentsTheme::cornerRadius(d->_radius,rect()),QtComponentsTheme::cornerRadius(d->_radius,rect()));
        painter.setClipPath(path);

        painter.setPen(Qt::NoPen);
        painter.setBrush(backgroundColor());
        painter.drawRect(rect());
    }

}
