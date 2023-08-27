#include "qtcomponentsbuttontabs.h"
#include "qtcomponentsbuttontabs_p.h"

#include <QEvent>
#include <QPainter>
#include <QLayout>
#include <QPropertyAnimation>

namespace Components {

    QtComponentsButtonTabsPrivate::QtComponentsButtonTabsPrivate(QtComponentsButtonTabs *q)
        : q_ptr(q)
    {

    }

    QtComponentsButtonTabsPrivate::~QtComponentsButtonTabsPrivate()
    {

    }

    void QtComponentsButtonTabsPrivate::init()
    {
        _index = 0;
    }

    QtComponentsButtonTabs::QtComponentsButtonTabs(QWidget *parent, Qt::Orientation orientaion)
        : QtComponentsAppBar(parent,orientaion)
        , d_ptr(new QtComponentsButtonTabsPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsButtonTabs::~QtComponentsButtonTabs()
    {

    }

    void QtComponentsButtonTabs::setCurrentIndex(int index)
    {
        Q_D(QtComponentsButtonTabs);
        d->_index = index;
    }

    int QtComponentsButtonTabs::currentIndex() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_index;
    }

    Qt::Orientation QtComponentsButtonTabs::orientaion() const
    {
        return QtComponentsAppBar::orientaion();
    }

    QtComponentsTabsInkBar::QtComponentsTabsInkBar(QtComponentsButtonTabs *tabs)
        : QtComponentsOverlayWidget(tabs)
        , _tabs(tabs)
        , _animation(new QPropertyAnimation(tabs))
        , _tween(0)
    {
        Q_ASSERT(tabs);
        _animation->setPropertyName("tweenValue");
        _animation->setEasingCurve(QEasingCurve::OutCirc);
        _animation->setTargetObject(this);
        _animation->setDuration(700);

        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);

        _tabs->installEventFilter(this);
    }

    QtComponentsTabsInkBar::~QtComponentsTabsInkBar()
    {

    }

    void QtComponentsTabsInkBar::refreshGeometry()
    {
        if(QLayoutItem *item = _tabs->layout()->itemAt(_tabs->currentIndex())){
            const QRect r(item->geometry());
            const qreal s = 1-_tween;

            if (QAbstractAnimation::Running != _animation->state()) {
                _geometry = r;
            } else {
                if(Qt::Horizontal == _tabs->orientaion()){
                    const qreal left = _previousGeometry.left() * s + r.left() * _tween;
                    const qreal width = _previousGeometry.width() * s + r.width() * _tween;
                    _geometry.setSize(QSize(width, r.height()));
                    _geometry.moveLeft(left);
                    _geometry.moveBottom(r.bottom() - 1);
                }else{
                    const qreal top = _previousGeometry.top() * s + r.top() * _tween;
                    const qreal height = _previousGeometry.height() * s + r.height() * _tween;
                    _geometry.setSize(QSize(r.width(), height));
                    _geometry.moveTop(top);
                    _geometry.moveRight(r.right() - 1);
                }
            }
            _tabs->update();
        }
    }

    void QtComponentsTabsInkBar::animate()
    {
        raise();

        _previousGeometry = _geometry;

        _animation->stop();
        _animation->setStartValue(0);
        _animation->setEndValue(1);
        _animation->start();
    }

    void QtComponentsTabsInkBar::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setOpacity(1);
        painter.fillRect(_geometry, _tabs->color(QPalette::Link));
    }

    bool QtComponentsTabsInkBar::eventFilter(QObject *watched, QEvent *event)
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
        return QtComponentsOverlayWidget::eventFilter(watched,event);
    }




}
