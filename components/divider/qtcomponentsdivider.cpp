#include "qtcomponentsdivider.h"
#include "lib/qtcomponentstheme.h"

#include <QIcon>
#include <QPainter>

namespace Components {

    class QtComponentsDividerPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsDivider)

    public:

        QtComponentsDividerPrivate(QtComponentsDivider* q);
        ~QtComponentsDividerPrivate();

        void init();

        QtComponentsDivider*const               q_ptr;
        qreal                                   _lineWidth;
        Qt::PenStyle                            _style;
    };

    QtComponentsDivider::QtComponentsDivider(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsDividerPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsDivider::~QtComponentsDivider()
    {

    }

    void QtComponentsDivider::setColor(const QColor &color)
    {
        setPalette(QPalette(color));
    }

    QColor QtComponentsDivider::color() const
    {
        return palette().color(QPalette::Window);
    }

    void QtComponentsDivider::setLineStyle(Qt::PenStyle style)
    {
        Q_D(QtComponentsDivider);
        d->_style = style;
        update();
    }

    Qt::PenStyle QtComponentsDivider::lineStyle() const
    {
        Q_D(const QtComponentsDivider);
        return d->_style;
    }

    QSize QtComponentsDivider::sizeHint() const
    {
        Q_D(const QtComponentsDivider);
        ensurePolished();

        QSize s = QWidget::sizeHint();

        s.width() > s.height() ?
            s.setHeight(d->_lineWidth) :
            s.setWidth(d->_lineWidth);

        return s;
    }

    void QtComponentsDivider::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsDivider);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        painter.setPen(QPen(color(),d->_lineWidth,d->_style));

        painter.drawLine(rect().topLeft(),rect().bottomRight());
    }

    QtComponentsDividerPrivate::QtComponentsDividerPrivate(QtComponentsDivider *q)
        : q_ptr(q)
    {

    }

    QtComponentsDividerPrivate::~QtComponentsDividerPrivate()
    {

    }

    void QtComponentsDividerPrivate::init()
    {
        Q_Q(QtComponentsDivider);

        _lineWidth = 1;
        _style = Qt::DotLine;
        q->setColor(Qt::darkGray);
    }

}
