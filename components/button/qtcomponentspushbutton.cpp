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
        bool                                        _useThemeColors;
        QtComponentsPushButton::ButtonIconPlacement _iconPlacement;
        Qt::Alignment                               _textAlignment;
        Qt::Edge                                    _edge;
        int                                         _margins;
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
        _iconPlacement = QtComponentsPushButton::LeftIcon;
        _textAlignment = Qt::AlignHCenter;
        _ratios = 0;
        _margins = 10;
        _useThemeColors = true;

        q->setColor(QColor("#adadad"),QPalette::Shadow);
        q->setColor(QColor("#0078d7"),QPalette::Shadow,QPalette::Active);
        q->setColor(QColor("#e1e1e1"),QPalette::Button);
        q->setColor(QColor("#e5f1fb"),QPalette::Button,QPalette::Active);
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

    void QtComponentsPushButton::setIconPlacement(QtComponentsPushButton::ButtonIconPlacement placement)
    {
        Q_D(QtComponentsPushButton);
        d->_iconPlacement = placement;
        update();
    }

    QtComponentsPushButton::ButtonIconPlacement QtComponentsPushButton::iconPlacement() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_iconPlacement;
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

    void QtComponentsPushButton::setUseThemeColors(bool value)
    {
        Q_D(QtComponentsPushButton);
        d->_useThemeColors = value;
        update();
    }

    bool QtComponentsPushButton::useThemeColors() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_useThemeColors;
    }

    void QtComponentsPushButton::setTextAlignment(Qt::Alignment alignment)
    {
        Q_D(QtComponentsPushButton);
        d->_textAlignment = alignment;
        update();
    }

    Qt::Alignment QtComponentsPushButton::textAlignment() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_textAlignment;
    }

    void QtComponentsPushButton::setIcon(const QString &category, const QString &icon)
    {
        QPushButton::setIcon(QtComponentsTheme::icon(category,icon));
    }

    QSize QtComponentsPushButton::sizeHint() const
    {
        Q_D(const QtComponentsPushButton);
        ensurePolished();
        QSize label = fontMetrics().size(Qt::TextSingleLine,text());
        int w = d->_margins + label.width();
        int h = label.height();
        if (!icon().isNull()) {
            w += iconSize().width() + QtComponentsPushButton::IconPadding;
            h = qMax(h, iconSize().height());
        }
        return QSize(w, d->_margins + h);
    }

    void QtComponentsPushButton::setToolTipEdge(Qt::Edge edge)
    {
        Q_D(QtComponentsPushButton);
        d->_edge = edge;
    }

    Qt::Edge QtComponentsPushButton::toolTipEdge() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_edge;
    }

    void QtComponentsPushButton::setMargins(int margins)
    {
        Q_D(QtComponentsPushButton);
        d->_margins = margins;
        updateGeometry();
    }

    int QtComponentsPushButton::margins() const
    {
        Q_D(const QtComponentsPushButton);
        return d->_margins;
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
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.fillRect(rect(),Qt::transparent);

        paintBackground(&painter);

        painter.setOpacity(1);
        painter.setClipping(false);

        paintForeground(&painter);
    }

    void QtComponentsPushButton::paintBackground(QPainter *painter)
    {
        painter->setPen(color(QPalette::Shadow));
        painter->setBrush(color(QPalette::Button));
        painter->drawRoundedRect(rect(),roundedRadius(),roundedRadius());
    }

    void QtComponentsPushButton::paintForeground(QPainter *painter)
    {
        Q_D(QtComponentsPushButton);

        painter->setFont(font());
        painter->setPen(color(QPalette::ButtonText));
        painter->setBrush(Qt::NoBrush);

        if(icon().isNull()){
            if (Qt::AlignLeft == d->_textAlignment) {
                painter->drawText(rect().adjusted(IconPadding, 0, 0, 0), Qt::AlignLeft | Qt::AlignVCenter, text());
            } else {
                painter->drawText(rect(), Qt::AlignCenter, text());
            }
            return;
        }

        QSize textSize(fontMetrics().size(Qt::TextSingleLine, text()));
        QSize base(size()-textSize);

        const int iw = iconSize().width() + IconPadding;
        QPoint pos(Qt::AlignLeft == d->_textAlignment ? IconPadding : (base.width()-iw)/2, 0);

        QRect textGeometry(pos + QPoint(0, base.height()/2), textSize);
        QRect iconGeometry(pos + QPoint(0, (height()-iconSize().height())/2), iconSize());

        if (QtComponentsPushButton::LeftIcon == d->_iconPlacement) {
            textGeometry.translate(iw, 0);
        } else {
            iconGeometry.translate(textSize.width() + IconPadding, 0);
        }

        painter->drawText(textGeometry, Qt::AlignCenter, text());

        QPixmap pixmap = icon().pixmap(iconSize());

        if(useThemeColors()){
            pixmap = QtComponentsTheme::icon2Color(icon().pixmap(iconSize()),color(QPalette::ButtonText));
        }

        painter->drawPixmap(iconGeometry, pixmap);

    }

}
