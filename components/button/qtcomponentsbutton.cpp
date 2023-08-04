#include "qtcomponentsbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QDebug>
#include <QPainter>

namespace Components {

    class QtComponentsButtonPrivate
    {
        Q_DISABLE_COPY(QtComponentsButtonPrivate)
        Q_DECLARE_PUBLIC(QtComponentsButton)

    public:

        QtComponentsButtonPrivate(QtComponentsButton* q);
        ~QtComponentsButtonPrivate();

        void init();

        QtComponentsButton*const                q_ptr;
        qreal                                   _radius;

    };

    QtComponentsButtonPrivate::QtComponentsButtonPrivate(QtComponentsButton *q)
        : q_ptr(q)
    {

    }

    QtComponentsButtonPrivate::~QtComponentsButtonPrivate()
    {

    }

    void QtComponentsButtonPrivate::init()
    {
        Q_Q(QtComponentsButton);

        _radius = 2.;

        q->installEventFilter(q);
    }

    QtComponentsButton::QtComponentsButton(QWidget *parent)
        : QPushButton(parent)
        , d_ptr(new QtComponentsButtonPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsButton::QtComponentsButton(const QString &text, QWidget *parent)
        : QPushButton(text,parent)
        , d_ptr(new QtComponentsButtonPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsButton::~QtComponentsButton()
    {

    }

    void QtComponentsButton::setRadiusRatios(qreal radius)
    {
        Q_D(QtComponentsButton);
        d->_radius = radius;
        update();
    }

    qreal QtComponentsButton::radiusRatios() const
    {
        Q_D(const QtComponentsButton);
        return d->_radius;
    }

    void QtComponentsButton::setColor(const QColor &color, QPalette::ColorRole role, QPalette::ColorGroup group)
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

    QColor QtComponentsButton::color(QPalette::ColorRole role) const
    {
        return palette().color(!isEnabled() ?
                      QPalette::Disabled : underMouse() || isChecked() ?
                      QPalette::Active : QPalette::Inactive,role);
    }

    bool QtComponentsButton::eventFilter(QObject *watched, QEvent *event)
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
        return QPushButton::eventFilter(watched,event);
    }

    void QtComponentsButton::paintEvent(QPaintEvent *)
    {
        Q_D(QtComponentsButton);

        const QRect r = rect().adjusted(0,0,-1,-1);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(), Qt::transparent);

        QPainterPath path;
        path.addRoundedRect(r, QtComponentsTheme::radiusRatios(d->_radius,r), QtComponentsTheme::radiusRatios(d->_radius,r));
        painter.setClipPath(path);
        painter.setClipping(true);

        QColor penColor = color(QPalette::ButtonText);
        QColor brushColor = color(QPalette::Button);
        QColor shadowColor = color(QPalette::Shadow);

        painter.setPen(Qt::NoPen);
        painter.setBrush(brushColor);
        painter.drawRect(r);

        painter.setPen(shadowColor);
        painter.setBrush(Qt::NoBrush);
        painter.drawRect(r);

        painter.setPen(penColor);
        painter.drawText(r,Qt::AlignCenter,text());

    }

}
