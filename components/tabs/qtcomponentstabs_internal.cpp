#include "qtcomponentstabs.h"
#include "qtcomponentstabs_internal.h"

#include <QPainter>
#include <QEvent>
#include <QDebug>
#include <QPropertyAnimation>

namespace Components {

    QtComponentsOverlayTabs::QtComponentsOverlayTabs(QtComponentsTabs *tabs)
        : QtComponentsOverlayWidget(tabs)
        , _tabs(tabs)
        , _animation(new QPropertyAnimation(tabs))
    {
        _animation->setPropertyName("tweenValue");
        _animation->setEasingCurve(QEasingCurve::OutCirc);
        _animation->setTargetObject(this);
        _animation->setDuration(700);

        _tabs->installEventFilter(this);

        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);
    }

    QtComponentsOverlayTabs::~QtComponentsOverlayTabs()
    {

    }

    void QtComponentsOverlayTabs::refreshGeometry()
    {
        QLayoutItem *item = _tabs->layout()->itemAt(_tabs->currentIndex());

        if (item)
        {
            const QRect r(item->geometry());
            const qreal s = 1-_tween;

            if (QAbstractAnimation::Running != _animation->state()) {
                _geometry = QRect(r.left(), r.bottom()-1, r.width(), 2);
            } else {
                const qreal left = _previousGeometry.left()*s + r.left()*_tween;
                const qreal width = _previousGeometry.width()*s + r.width()*_tween;
                _geometry = QRect(left, r.bottom()-1, width, 2);
            }
            _tabs->update();
        }

    }

    void QtComponentsOverlayTabs::animate()
    {
        raise();

        _previousGeometry = _geometry;

        _animation->stop();
        _animation->setStartValue(0);
        _animation->setEndValue(1);
        _animation->start();

    }

    bool QtComponentsOverlayTabs::eventFilter(QObject *watched, QEvent *event)
    {
        switch (event->type())
        {
        case QEvent::Move:
        case QEvent::Resize:
        {
            refreshGeometry();
            break;
        }
        default:
            break;
        }
        return QtComponentsOverlayWidget::eventFilter(watched, event);
    }

    void QtComponentsOverlayTabs::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        QPainter painter(this);

        painter.setOpacity(1);
        painter.fillRect(_geometry, _tabs->inkColor());
    }

    QtComponentsTab::QtComponentsTab(QtComponentsTabs *tabs)
        : QAbstractButton(tabs)
        , _tabs(tabs)
        , _active(false)
    {
        setMinimumHeight(30);
        connect(this,SIGNAL(clicked()),SLOT(activateTab()));
    }

    QtComponentsTab::~QtComponentsTab()
    {

    }

    QSize QtComponentsTab::sizeHint() const
    {
        ensurePolished();
        return fontMetrics().size(Qt::TextSingleLine, text()) + QSize(10,10);
    }

    void QtComponentsTab::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setFont(_tabs->font());
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(_active ? _tabs->activeColor() : _tabs->color());
        painter.drawText(rect(), Qt::AlignCenter, text());
    }

    void QtComponentsTab::activateTab()
    {
        _tabs->setCurrentTab(this);
    }


}
