#include "qtcomponentspopup.h"
#include "lib/qtcomponentsoverlaywidget.h"
#include "lib/qtcomponentstheme.h"

#include <QBitmap>
#include <QEvent>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>

namespace Components {

    class QtComponentsPopupOverlayWidget : public QtComponentsOverlayWidget
    {
        Q_DISABLE_COPY(QtComponentsPopupOverlayWidget)

    public:

        QtComponentsPopupOverlayWidget(QtComponentsPopup* parent);
        virtual~QtComponentsPopupOverlayWidget();

    protected:

        virtual QRect overlayGeometry()const;
        virtual void paintEvent(QPaintEvent *);

    private:

        QtComponentsPopup*const             _parent;

    };

    class QtComponentsPopupPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsPopup)

    public:

        QtComponentsPopupPrivate(QtComponentsPopup* q, Qt::Edge edge);
        ~QtComponentsPopupPrivate();

        QtComponentsPopup*const                     q_ptr;
        Qt::Edge                                    _edge;
        QColor                                      _color;
        QtComponentsPopupOverlayWidget*const        _overlay;
    };

    QtComponentsPopupPrivate::QtComponentsPopupPrivate(QtComponentsPopup *q, Qt::Edge edge)
        : q_ptr(q)
        , _edge(edge)
        , _overlay(new QtComponentsPopupOverlayWidget(q))
        , _color(Qt::white)
    {

    }

    QtComponentsPopupPrivate::~QtComponentsPopupPrivate()
    {

    }

    QtComponentsPopup::QtComponentsPopup(QWidget *parent, Qt::Edge edge)
        : QWidget(parent,Qt::FramelessWindowHint | Qt::Tool)
        , d_ptr(new QtComponentsPopupPrivate(this,edge))
    {
        setAttribute(Qt::WA_DeleteOnClose);
        setAttribute(Qt::WA_TranslucentBackground);
        QApplication::instance()->installEventFilter(this);
    }

    QtComponentsPopup::~QtComponentsPopup()
    {

    }

    QLayout *QtComponentsPopup::layout() const
    {
        Q_D(const QtComponentsPopup);
        return d->_overlay->layout();
    }

    void QtComponentsPopup::setColor(const QColor &color)
    {
        Q_D(QtComponentsPopup);
        d->_color = color;
        d->_overlay->update();
    }

    QColor QtComponentsPopup::color() const
    {
        Q_D(const QtComponentsPopup);
        return d->_color;
    }

    Qt::Edge QtComponentsPopup::edge() const
    {
        Q_D(const QtComponentsPopup);
        return d->_edge;
    }

    bool QtComponentsPopup::event(QEvent *event)
    {
        Q_D(QtComponentsPopup);
        if(QEvent::Show == event->type()){
            if(QWidget* parent = parentWidget()){
                const int margins = 16;
                QPoint target = rect().center();
                if(Qt::LeftEdge == d->_edge){
                    target = parent->rect().center() - QPoint(-margins,0);
                }else if(Qt::RightEdge == d->_edge){
                    target = parent->rect().center() + QPoint(margins,0);
                }else if(Qt::TopEdge == d->_edge){
                    target = parent->rect().center() + QPoint(0,-margins -height() / 2);
                }else{
                    target = parent->rect().center() + QPoint(0,margins + height() / 2);
                }
                QRect newGeometry = rect();
                newGeometry.moveCenter(parent->mapToGlobal(target));
                setGeometry(newGeometry);
            }
        }
        return QWidget::event(event);
    }

    bool QtComponentsPopup::eventFilter(QObject *watched, QEvent *event)
    {
        const QEvent::Type type = event->type();
        switch (type) {
        case QEvent::DeferredDelete:
        {
            if(!isVisible()){
                event->ignore();
            }
            break;
        }
        case QEvent::MouseMove:
        case QEvent::MouseButtonPress:
        case QEvent::MouseButtonRelease:
        case QEvent::MouseButtonDblClick:
        {
            if(rect().contains(static_cast<QMouseEvent*>(event)->pos())){
                break;
            }
        }
        case QEvent::Wheel:
        case QEvent::WindowActivate:
        case QEvent::WindowDeactivate:
        {
            if (QApplication::activeWindow() != this){
                if(isVisible()){
                    close();
                }
            }
            break;
        }
        default:
            break;
        }
        return QWidget::eventFilter(watched,event);
    }

    void QtComponentsPopup::setLayout(QLayout *layout)
    {
        Q_D(QtComponentsPopup);
        if(d->_overlay->layout()){
            delete d->_overlay->layout();
        }
        d->_overlay->setLayout(layout);
    }

    QtComponentsPopupOverlayWidget::QtComponentsPopupOverlayWidget(QtComponentsPopup *parent)
        : QtComponentsOverlayWidget(parent)
        , _parent(parent)
    {
        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(11);
        effect->setColor(Qt::darkGray);
        effect->setOffset(0, 0);
        setGraphicsEffect(effect);
    }

    QtComponentsPopupOverlayWidget::~QtComponentsPopupOverlayWidget()
    {

    }

    QRect QtComponentsPopupOverlayWidget::overlayGeometry() const
    {
        return QtComponentsOverlayWidget::overlayGeometry().adjusted(6,6,-6,-6);
    }

    void QtComponentsPopupOverlayWidget::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        const int margins = 8;
        const int radius = QtComponentsTheme::radiusRatios(2,rect());

        painter.setPen(Qt::NoPen);
        painter.setBrush(_parent->color());

        QRect r = rect();
        QPolygon polygon = QPolygon();
        switch (_parent->edge()) {
        case Qt::TopEdge:
        {
            r = rect().adjusted(0,0,-margins,-margins);
            polygon << QPoint(width() / 2 - margins / 2, height() - margins)
                    << QPoint(width() / 2, height())
                    << QPoint(width() / 2 + margins / 2, height() - margins);
            break;
        }
        case Qt::LeftEdge:
        {
            r = rect().adjusted(0,0,-margins,-margins);
            polygon << QPoint(width() - margins, height() / 2 - margins / 2)
                    << QPoint(width(), height() / 2)
                    << QPoint(width() - margins, height() / 2 + margins / 2);
            break;
        }
        case Qt::RightEdge:
        {
            r = rect().adjusted(margins,margins,0,0);
            polygon << QPoint(margins, height() / 2 - margins / 2)
                    << QPoint(0, height() / 2)
                    << QPoint(margins, height() / 2 + margins / 2);
            break;
        }
        case Qt::BottomEdge:
        {
            r = rect().adjusted(margins,margins,0,0);
            polygon << QPoint(width() / 2 - margins / 2, margins)
                    << QPoint(width() / 2, 0)
                    << QPoint(width() / 2 + margins / 2, margins);
            break;
        }
        default:
            break;
        }
        painter.drawRoundedRect(r,radius,radius);
        painter.drawPolygon(polygon);
    }


}
