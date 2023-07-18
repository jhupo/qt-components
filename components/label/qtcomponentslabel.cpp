#include "qtcomponentslabel.h"


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

}
