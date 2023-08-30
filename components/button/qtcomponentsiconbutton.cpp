#include "qtcomponentsiconbutton.h"
#include "lib/qtcomponentstheme.h"

#include <QPainter>

namespace Components {

    QtComponentsIconButton::QtComponentsIconButton(QWidget *parent)
        : QtComponentsPushButton(parent)
    {
        setUserData(0);
        setDotDisabled(true);
        setUseThemeColors(true);
        setColor(Qt::darkGray,QPalette::ButtonText);
        setColor(Qt::red,QPalette::Foreground);
        setColor(Qt::transparent,QPalette::Shadow);
        setColor(Qt::transparent,QPalette::Button);
        setColor(QtComponentsTheme::inst()->color(Components::gray400),QPalette::Button,QPalette::Active);
        setRoundedRadiusRatios(0);
        setIconSize(QSize(16,16));
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    }

    QtComponentsIconButton::~QtComponentsIconButton()
    {

    }

    QSize QtComponentsIconButton::sizeHint() const
    {
        return iconSize();
    }

    void QtComponentsIconButton::setDotDisabled(bool disable)
    {
        setUserData(disable);
    }

    bool QtComponentsIconButton::isDotDisabled() const
    {
        return userData().toBool();
    }

    void QtComponentsIconButton::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.fillRect(rect(),Qt::transparent);

        QPixmap pixmap = icon().pixmap(iconSize());

        if(useThemeColors()){
            pixmap = QtComponentsTheme::icon2Color(icon().pixmap(iconSize()),color(QPalette::ButtonText));
        }

        if(size() != iconSize()){
            painter.setPen(color(QPalette::Shadow));
            painter.setBrush(color(QPalette::Button));
            painter.drawRoundedRect(rect(),roundedRadius(),roundedRadius());
            QRect r = QRect(rect().center(),iconSize());
            r.moveCenter(rect().center());
            painter.drawPixmap(r,pixmap);
        }else{
            painter.drawPixmap(rect(),pixmap);
        }

        if(!isDotDisabled()){
            const int dotRadius = 3;
            const QPoint pos = rect().topRight() - QPoint(dotRadius,-dotRadius);
            painter.setPen(Qt::NoPen);
            painter.setBrush(color(QPalette::Foreground));
            painter.drawEllipse(pos,dotRadius,dotRadius);
        }
    }

}
