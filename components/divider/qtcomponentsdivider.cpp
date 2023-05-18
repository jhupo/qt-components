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

        enum Theme{Text,Icon,Normal};

        void init();

        QtComponentsDivider*const               q_ptr;
        QColor                                  _color;
        QString                                 _text;
        QIcon                                   _icon;
        Theme                                   _theme;
        Qt::AlignmentFlag                       _alignment;
        Qt::PenStyle                            _penStyle;
        Qt::Orientation                         _orientation;
        QSize                                   _iconSize;
    };

    QtComponentsDivider::QtComponentsDivider(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsDividerPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsDivider::QtComponentsDivider(Qt::Orientation orientation, QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsDividerPrivate(this))
    {
        d_func()->init();
        d_ptr->_orientation = orientation;
    }

    QtComponentsDivider::~QtComponentsDivider()
    {

    }

    void QtComponentsDivider::setColor(const QColor &color)
    {
        Q_D(QtComponentsDivider);
        d->_color = color;
        update();
    }

    QColor QtComponentsDivider::color() const
    {
        Q_D(const QtComponentsDivider);
        return d->_color;
    }

    void QtComponentsDivider::setText(const QString &text)
    {
        Q_D(QtComponentsDivider);
        d->_text = text;
        d->_theme = QtComponentsDividerPrivate::Text;
        update();
    }

    QString QtComponentsDivider::text() const
    {
        Q_D(const QtComponentsDivider);
        return d->_text;
    }

    void QtComponentsDivider::setIcon(const QIcon &icon)
    {
        Q_D(QtComponentsDivider);
        d->_icon = icon;
        d->_theme = QtComponentsDividerPrivate::Icon;
        update();
    }

    QIcon QtComponentsDivider::icon() const
    {
        Q_D(const QtComponentsDivider);
        return d->_icon;
    }

    void QtComponentsDivider::setIconSize(const QSize &size)
    {
        Q_D(QtComponentsDivider);
        d->_iconSize = size;
        updateGeometry();
    }

    QSize QtComponentsDivider::iconSize() const
    {
        Q_D(const QtComponentsDivider);
        return d->_iconSize;
    }

    void QtComponentsDivider::setAlignment(Qt::AlignmentFlag flag)
    {
        Q_D(QtComponentsDivider);
        d->_alignment = flag;
        update();
    }

    Qt::AlignmentFlag QtComponentsDivider::alignment() const
    {
        Q_D(const QtComponentsDivider);
        return d->_alignment;
    }

    void QtComponentsDivider::setLineStyle(Qt::PenStyle style)
    {
        Q_D(QtComponentsDivider);
        d->_penStyle = style;
        update();
    }

    Qt::PenStyle QtComponentsDivider::lineStyle() const
    {
        Q_D(const QtComponentsDivider);
        return d->_penStyle;
    }

    void QtComponentsDivider::setOrientation(Qt::Orientation orientation)
    {
        Q_D(QtComponentsDivider);
        d->_orientation = orientation;
        updateGeometry();
    }

    Qt::Orientation QtComponentsDivider::orientation() const
    {
        Q_D(const QtComponentsDivider);
        return d->_orientation;
    }

    QSize QtComponentsDivider::sizeHint() const
    {
        Q_D(const QtComponentsDivider);
        ensurePolished();

        if(Qt::Vertical == d->_orientation)
            return QSize(1,-1);
        else
            if(QtComponentsDividerPrivate::Icon == d->_theme)
                return QSize(-1,d->_iconSize.height());
            else if(QtComponentsDividerPrivate::Normal == d->_theme)
                return QSize(-1,1);
            else
                return QSize(-1,fontMetrics().size(Qt::TextSingleLine, text()).height());
        return QWidget::sizeHint();
    }

    void QtComponentsDivider::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);

        Q_D(QtComponentsDivider);

        QPainter painter(this);
        painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        painter.fillRect(rect(),Qt::transparent);

        painter.setPen(QPen(d->_color,1,d->_penStyle));
        painter.setBrush(Qt::NoBrush);

        QPoint center = rect().center();
        int halfWidth = rect().width() / 2;

        painter.drawLine(QPoint(center.x() - halfWidth, center.y()),QPoint(center.x() + halfWidth, center.y()));
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
        _color = QtComponentsTheme::inst()->color(cyan400);
        _theme = Normal;
        _iconSize = QSize(21,21);
        _alignment = Qt::AlignCenter;
        _orientation = Qt::Horizontal;
        _penStyle = Qt::DotLine;
    }

}
