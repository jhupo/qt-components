#include "qtcomponentsstackedwidget.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>

namespace Components {

    class QtComponentsStackedWidgetPrivate
    {
        Q_DISABLE_COPY(QtComponentsStackedWidgetPrivate)
        Q_DECLARE_PUBLIC(QtComponentsStackedWidget)

    public:

        QtComponentsStackedWidgetPrivate(QtComponentsStackedWidget* q);
        ~QtComponentsStackedWidgetPrivate();

        void init();

        QtComponentsStackedWidget*const                 q_ptr;
        qreal                                           _radius;

    };

    QtComponentsStackedWidgetPrivate::QtComponentsStackedWidgetPrivate(QtComponentsStackedWidget *q)
        : q_ptr(q)
    {

    }

    QtComponentsStackedWidgetPrivate::~QtComponentsStackedWidgetPrivate()
    {

    }

    void QtComponentsStackedWidgetPrivate::init()
    {
        Q_Q(QtComponentsStackedWidget);

        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(q);
        effect->setBlurRadius(16);
        effect->setColor(Qt::darkGray);
        effect->setOffset(0, 0);

        q->setGraphicsEffect(effect);

        q->setColor(Qt::white);
        q->setRadius(24);
    }

    QtComponentsStackedWidget::QtComponentsStackedWidget(QWidget *parent)
        : QStackedWidget(parent)
        , d_ptr(new QtComponentsStackedWidgetPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsStackedWidget::~QtComponentsStackedWidget()
    {

    }

    void QtComponentsStackedWidget::setColor(const QColor &color)
    {
        setPalette(QPalette(color));
    }

    QColor QtComponentsStackedWidget::color() const
    {
        return palette().button().color();
    }

    void QtComponentsStackedWidget::setRadius(const qreal &radius)
    {
        Q_D(QtComponentsStackedWidget);
        d->_radius = radius;
        update();
    }

    qreal QtComponentsStackedWidget::radius() const
    {
        Q_D(const QtComponentsStackedWidget);
        return d->_radius;
    }

    void QtComponentsStackedWidget::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsStackedWidget);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        QPainterPath path;
        path.addRoundedRect(rect(),d->_radius,d->_radius);
        painter.setClipPath(path);
        painter.setClipping(true);

        painter.setPen(color());
        painter.setBrush(color());
        painter.drawRect(rect());
    }

}
