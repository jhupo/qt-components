#include "qtcomponentsscrollbar.h"

#include "lib/qtcomponentsstyle.h"

#include <QPainter>

namespace Components {

    class QtComponentsScrollBarPrivate
    {
        Q_DISABLE_COPY(QtComponentsScrollBarPrivate)
        Q_DECLARE_PUBLIC(QtComponentsScrollBar)

    public:

        QtComponentsScrollBarPrivate(QtComponentsScrollBar* q);
        virtual~QtComponentsScrollBarPrivate();

        void init();

        QtComponentsScrollBar*const             q_ptr;
        QColor                                  _canvasColor;
        QColor                                  _backgroundColor;
        QColor                                  _sliderColor;

    };

    QtComponentsScrollBarPrivate::QtComponentsScrollBarPrivate(QtComponentsScrollBar *q)
        : q_ptr(q)
    {

    }

    QtComponentsScrollBarPrivate::~QtComponentsScrollBarPrivate()
    {

    }

    void QtComponentsScrollBarPrivate::init()
    {
        Q_Q(QtComponentsScrollBar);
        _backgroundColor = Qt::transparent;
        _canvasColor = Qt::transparent;
        _sliderColor = Qt::darkGray;

        q->setMouseTracking(true);
        q->setStyle(QtComponentsStyle::inst());
        q->setStyleSheet("QScrollBar:vertical { margin: 0; }"
            "QScrollBar::add-line:vertical { height: 0; margin: 0; }"
            "QScrollBar::sub-line:vertical { height: 0; margin: 0; }");
        q->setContextMenuPolicy(Qt::NoContextMenu);
    }

    QtComponentsScrollBar::QtComponentsScrollBar(QWidget *parent)
        : QScrollBar(parent)
        , d_ptr(new QtComponentsScrollBarPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsScrollBar::~QtComponentsScrollBar()
    {

    }

    void QtComponentsScrollBar::setCanvasColor(const QColor &color)
    {
        Q_D(QtComponentsScrollBar);
        d->_canvasColor = color;
        update();
    }

    QColor QtComponentsScrollBar::canvasColor() const
    {
        Q_D(const QtComponentsScrollBar);
        return d->_canvasColor;
    }

    void QtComponentsScrollBar::setBackgroundColor(const QColor &color)
    {
        Q_D(QtComponentsScrollBar);
        d->_backgroundColor = color;
        update();
    }

    QColor QtComponentsScrollBar::backgroundColor() const
    {
        Q_D(const QtComponentsScrollBar);
        return d->_backgroundColor;
    }

    void QtComponentsScrollBar::setSliderColor(const QColor &color)
    {
        Q_D(QtComponentsScrollBar);
        d->_sliderColor = color;
        update();
    }

    QColor QtComponentsScrollBar::sliderColor() const
    {
        Q_D(const QtComponentsScrollBar);
        return d->_sliderColor;
    }

    QSize QtComponentsScrollBar::sizeHint() const
    {
        if (Qt::Horizontal == orientation())
            return QSize(1, 10);
        return QSize(10, 1);
    }

    void QtComponentsScrollBar::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(rect(), canvasColor());

        int x, y, w, h;
        rect().getRect(&x, &y, &w, &h);

        QMargins margins(2, 2, 2, 2);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);

        QRect trimmed(rect().marginsRemoved(margins));

        QPainterPath path;
        path.addRoundedRect(trimmed, 3, 3);
        painter.setClipPath(path);

        painter.drawRect(trimmed);

        const qreal q = (Qt::Horizontal == orientation() ? w : h) /
            static_cast<qreal>(maximum() - minimum() + pageStep() - 1);

        QRect handle = Qt::Horizontal == orientation()
            ? QRect(sliderPosition()*q, y, pageStep()*q, h)
            : QRect(x, sliderPosition()*q, w, pageStep()*q);

        brush.setColor(sliderColor());
        painter.setBrush(brush);

        painter.drawRoundedRect(handle, 9, 9);

    }

}
