#include "qtcomponentslabel.h"

#include <QIcon>

namespace Components {

    QtComponentsLabel::QtComponentsLabel(QWidget *parent)
        : QLabel(parent)
    {

    }

    QtComponentsLabel::~QtComponentsLabel()
    {

    }

    void QtComponentsLabel::setColor(const QColor &color)
    {
        QPalette pale = palette();
        pale.setColor(QPalette::WindowText, color);
        setPalette(pale);
    }

    QColor QtComponentsLabel::color() const
    {
        return palette().color(QPalette::WindowText);
    }

    void QtComponentsLabel::setIcon(const QIcon &icon)
    {
        setPixmap(icon.pixmap(size()));
    }

}
