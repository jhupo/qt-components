#include "qtcomponentsoverlaywidget.h"

#include <QEvent>

namespace Components {

    QtComponentsOverlayWidget::QtComponentsOverlayWidget(QWidget *parent)
        : QWidget(parent)
    {
        if (parent)
            parent->installEventFilter(this);
    }

    QtComponentsOverlayWidget::~QtComponentsOverlayWidget()
    {

    }

    bool QtComponentsOverlayWidget::event(QEvent *event)
    {
        if (!parent())
            return QWidget::event(event);
        switch (event->type())
        {
        case QEvent::ParentChange:
        {
            parent()->installEventFilter(this);
            setGeometry(overlayGeometry());
            break;
        }
        case QEvent::ParentAboutToChange:
        {
            parent()->removeEventFilter(this);
            break;
        }
        default:
            break;
        }
        return QWidget::event(event);
    }

    bool QtComponentsOverlayWidget::eventFilter(QObject *watched, QEvent *event)
    {
        switch (event->type())
        {
        case QEvent::Move:
        case QEvent::Resize:
            setGeometry(overlayGeometry());
            break;
        default:
            break;
        }
        return QWidget::eventFilter(watched, event);
    }

    QRect QtComponentsOverlayWidget::overlayGeometry() const
    {
        QWidget *widget = parentWidget();
        if (!widget)
            return QRect();
        return widget->rect();
    }



}
