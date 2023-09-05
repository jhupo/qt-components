#include "qtcomponentsappbar.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QPainter>
#include <QBoxLayout>
#include <QGraphicsDropShadowEffect>

namespace Components {

    class QtComponentsAppBarPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsAppBar)

    public:

        QtComponentsAppBarPrivate(QtComponentsAppBar* q,Qt::Orientation orientation);
        ~QtComponentsAppBarPrivate();

        void init();

        QtComponentsAppBar*const                q_ptr;
        qreal                                   _ratios;
        qreal                                   _radius;
        Qt::Orientation                         _orientation;
    };

    QtComponentsAppBarPrivate::QtComponentsAppBarPrivate(QtComponentsAppBar *q, Qt::Orientation orientation)
        : q_ptr(q)
        , _orientation(orientation)
    {

    }

    QtComponentsAppBarPrivate::~QtComponentsAppBarPrivate()
    {

    }

    void QtComponentsAppBarPrivate::init()
    {
        Q_Q(QtComponentsAppBar);

        _radius = 0;

        q->setRoundedRadiusRatios(15);

        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
        effect->setBlurRadius(16);
        effect->setColor(Qt::darkGray);
        effect->setOffset(0, 0);

        q->setGraphicsEffect(effect);

        q->setColor(Qt::white);
        q->setColor(Qt::transparent,QPalette::Shadow);

        q->setLayout(new QBoxLayout(Qt::Vertical != _orientation ?
                    QBoxLayout::LeftToRight : QBoxLayout::TopToBottom));
    }

    QtComponentsAppBar::QtComponentsAppBar(QWidget *parent, Qt::Orientation orientaion)
        : QWidget(parent)
        , d_ptr(new QtComponentsAppBarPrivate(this,orientaion))
    {
        d_func()->init();
    }

    QtComponentsAppBar::~QtComponentsAppBar()
    {

    }

    void QtComponentsAppBar::setRoundedRadiusRatios(const qreal ratios)
    {
        Q_D(QtComponentsAppBar);
        d->_ratios = ratios;
        update();
    }

    qreal QtComponentsAppBar::roundedRadiusRatios() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_ratios;
    }

    void QtComponentsAppBar::setRoundedRadius(const qreal radius)
    {
        Q_D(QtComponentsAppBar);
        d->_radius = radius;
        update();
    }

    qreal QtComponentsAppBar::roundedRadius() const
    {
        Q_D(const QtComponentsAppBar);
        if(qFuzzyIsNull(d->_radius)){
            return QtComponentsTheme::radiusRatios(d->_ratios,rect());
        }
        return d->_radius;
    }

    void QtComponentsAppBar::setShadowBorderColor(const QColor &color, QPalette::ColorGroup group)
    {
        setColor(color,QPalette::Shadow,group);
    }

    QColor QtComponentsAppBar::shadowBorderColor(QPalette::ColorGroup group) const
    {
        return color(QPalette::Shadow,group);
    }

    void QtComponentsAppBar::setBackgroundColor(const QColor &color, QPalette::ColorGroup group)
    {
        setColor(color,QPalette::Window,group);
    }

    QColor QtComponentsAppBar::backgroundColor(QPalette::ColorGroup group) const
    {
        return color(QPalette::Window,group);
    }

    void QtComponentsAppBar::setColor(const QColor &color, QPalette::ColorRole role, QPalette::ColorGroup group)
    {
        QPalette pale = palette();
        if(QPalette::NColorGroups != group){
            pale.setColor(group,role,color);
        }else{
            pale.setColor(QPalette::Disabled,role,color);
            pale.setColor(QPalette::Inactive,role,color);
            pale.setColor(QPalette::Active,role,color);
        }
        setPalette(pale);
    }

    QColor QtComponentsAppBar::color(QPalette::ColorRole role, QPalette::ColorGroup group) const
    {
        if(QPalette::NColorGroups != group){
            return palette().color(role);
        }
        return palette().color(!isEnabled() ?
                QPalette::Disabled : underMouse() ?
                                       QPalette::Active : QPalette::Inactive,role);
    }

    Qt::Orientation QtComponentsAppBar::orientaion() const
    {
        Q_D(const QtComponentsAppBar);
        return d->_orientation;
    }

    bool QtComponentsAppBar::event(QEvent *event)
    {
        QEvent::Type type = event->type();
        switch (type) {
        case QEvent::Leave:
        case QEvent::Enter:{
            update();
            break;
        }
        default:
            break;
        }
        return QWidget::event(event);
    }

    void QtComponentsAppBar::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsAppBar);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        painter.setPen(color(QPalette::Shadow));
        painter.setBrush(color());

        painter.drawRoundedRect(rect(),roundedRadius(),roundedRadius());

    }

}
