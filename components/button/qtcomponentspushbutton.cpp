#include "qtcomponentspushbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QPainter>

namespace Components {

    class QtComponentsPushButtonPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsPushButton)

    public:

        QtComponentsPushButtonPrivate(QtComponentsPushButton* q);
        ~QtComponentsPushButtonPrivate();

        void init();

        QtComponentsPushButton*const                q_ptr;
        qreal                                       _ratios;
        QVariant                                    _userData;

    };

    QtComponentsPushButtonPrivate::QtComponentsPushButtonPrivate(QtComponentsPushButton *q)
        : q_ptr(q)
    {

    }

    QtComponentsPushButtonPrivate::~QtComponentsPushButtonPrivate()
    {

    }

    void QtComponentsPushButtonPrivate::init()
    {
        Q_Q(QtComponentsPushButton);

        q->setRoundedRadiusRatios(25);
    }

    QtComponentsPushButton::QtComponentsPushButton(QWidget *parent)
        : QPushButton(parent)
        , d_ptr(new QtComponentsPushButtonPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsPushButton::~QtComponentsPushButton()
    {

    }

    void QtComponentsPushButton::setRoundedRadiusRatios(const qreal ratios)
    {
        Q_D(QtComponentsPushButton);
        d->_ratios = ratios;
        update();
    }

    qreal QtComponentsPushButton::roundedRadiusRatios() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_ratios;
    }

    qreal QtComponentsPushButton::roundedRadius() const
    {
        Q_D(const QtComponentsPushButton);
        return QtComponentsTheme::radiusRatios(d->_ratios,rect());
    }

    void QtComponentsPushButton::setColor(const QColor &color, QPalette::ColorRole role, QPalette::ColorGroup group)
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

    QColor QtComponentsPushButton::color(QPalette::ColorRole role) const
    {
        return palette().color(!isEnabled() ?
                QPalette::Disabled : underMouse() || isChecked() ?
                QPalette::Active : QPalette::Inactive,role);
    }

    void QtComponentsPushButton::setUserData(const QVariant &data)
    {
        Q_D(QtComponentsPushButton);
        d->_userData = data;
    }

    QVariant QtComponentsPushButton::userData() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_userData;
    }

    void QtComponentsPushButton::setIcon(const QString &category, const QString &icon)
    {
        QPushButton::setIcon(QtComponentsTheme::icon(category,icon));
    }

    void QtComponentsPushButton::setIcon(const QIcon &icon)
    {
        QPushButton::setIcon(icon);
    }

    bool QtComponentsPushButton::event(QEvent *event)
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
        return QPushButton::event(event);
    }

    void QtComponentsPushButton::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        painter.setPen(color(QPalette::Shadow));
        painter.setBrush(color(QPalette::Button));
        painter.drawRoundedRect(rect(),roundedRadius(),roundedRadius());

        painter.setFont(font());
        painter.setPen(color(QPalette::ButtonText));
        painter.drawText(rect(),Qt::AlignCenter,text());

    }

}
