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
        QColor                                  _color;
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

        _color = Qt::white;

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

    void QtComponentsAppBar::setColor(const QColor &color)
    {
        Q_D(QtComponentsAppBar);
        d->_color = color;
        update();
    }

    QColor QtComponentsAppBar::color() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_color;
    }

    void QtComponentsAppBar::setRadiusRatios(const qreal radius)
    {
        Q_D(QtComponentsAppBar);
        d->_radius = radius;
        update();
    }

    qreal QtComponentsAppBar::radiusRatios() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_radius;
    }

    void QtComponentsAppBar::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsAppBar);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        const QRect r = rect().adjusted(0,0,-1,-1);

        QPainterPath path;
        path.addRoundedRect(r, QtComponentsTheme::radiusRatios(d->_radius,r), QtComponentsTheme::radiusRatios(d->_radius,r));
        painter.setClipPath(path);
        painter.setClipping(true);

        painter.setPen(Qt::NoPen);
        painter.setBrush(d->_color);
        painter.drawRect(r);
    }

}
