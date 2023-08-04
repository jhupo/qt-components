#include "qtcomponentsiconbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QtMath>
#include <QPainter>
#include <QLoggingCategory>

namespace Components {

    class QtComponentsIconButtonPrivate
    {
        Q_DISABLE_COPY(QtComponentsIconButtonPrivate)
        Q_DECLARE_PUBLIC(QtComponentsIconButton)

    public:

        QtComponentsIconButtonPrivate(QtComponentsIconButton* q);
        ~QtComponentsIconButtonPrivate();

        void init();

        void cleanMark();

        QtComponentsIconButton*const            q_ptr;
        bool                                    _markDisplay;
        bool                                    _markDisabled;
        QColor                                  _markColor;

    };

    QtComponentsIconButton::QtComponentsIconButton(QWidget *parent)
        : QtComponentsButton(parent)
        , d_ptr(new QtComponentsIconButtonPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsIconButton::~QtComponentsIconButton()
    {

    }

    void QtComponentsIconButton::setMarkColor(const QColor &color)
    {
        Q_D(QtComponentsIconButton);
        d->_markColor = color;
        update();
    }

    QColor QtComponentsIconButton::markColor() const
    {
        Q_D(const QtComponentsIconButton);
        return d->_markColor;
    }

    void QtComponentsIconButton::setMarkDisabled(bool disabled)
    {
        Q_D(QtComponentsIconButton);
        d->_markDisabled = disabled;
    }

    bool QtComponentsIconButton::markDisabled() const
    {
        Q_D(const QtComponentsIconButton);
        return d->_markDisabled;
    }

    void QtComponentsIconButton::setMarkDisplay(const bool display)
    {
        Q_D(QtComponentsIconButton);
        if(d->_markDisabled){
            d->_markDisplay = display;
            update();
        }else{
            qCWarning(logger_components)<<"The label is disabled and the settings display is invalid.";
        }
    }

    bool QtComponentsIconButton::markDisplay() const
    {
        Q_D(const QtComponentsIconButton);
        return d->_markDisplay;
    }

    QSize QtComponentsIconButton::sizeHint() const
    {
        Q_D(const QtComponentsIconButton);
        ensurePolished();
        if(d->_markDisabled){
            return iconSize() + QSize(9,0);
        }
        return iconSize();
    }

    void QtComponentsIconButton::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsIconButton);

        static const int radius = 6;

        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing|QPainter::SmoothPixmapTransform);
        painter.fillRect(rect(),Qt::transparent);

        painter.drawPixmap(QRect(0,0,iconSize().width(),iconSize().height()),
                           QtComponentsTheme::icon2Color(icon().pixmap(iconSize()),color(QPalette::Button)));

        if(d->_markDisplay){
            painter.setPen(d->_markColor);
            painter.setBrush(d->_markColor);
            const int offsetX = rect().topRight().x() - radius;
            const int offsetY =rect().topRight().y() +  qFloor(radius / 2);
            painter.drawEllipse(offsetX,offsetY,radius,radius);
        }
    }

    QtComponentsIconButtonPrivate::QtComponentsIconButtonPrivate(QtComponentsIconButton *q)
        : q_ptr(q)
    {

    }

    QtComponentsIconButtonPrivate::~QtComponentsIconButtonPrivate()
    {

    }

    void QtComponentsIconButtonPrivate::init()
    {
        Q_Q(QtComponentsIconButton);

        _markDisplay = false;
        _markDisabled = false;
        _markColor = Qt::red;

        q->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

        QObject::connect(q,SIGNAL(clicked()),q,SLOT(cleanMark()));
    }

    void QtComponentsIconButtonPrivate::cleanMark()
    {
        Q_Q(QtComponentsIconButton);
        if(_markDisplay){
            _markDisplay = false;
            q->update();
        }
    }

}
#include "moc_qtcomponentsiconbutton.cpp"
