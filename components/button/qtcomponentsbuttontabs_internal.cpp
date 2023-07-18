#include "qtcomponentsbuttontabs_internal.h"
#include "qtcomponentsbuttontabs.h"
#include "lib/qtcomponentstheme.h"

#include <QPainter>
#include <QEvent>
#include <QPropertyAnimation>

namespace Components {

    QtComponentsButtonTabsOverlayWidget::QtComponentsButtonTabsOverlayWidget(QtComponentsButtonTabs *parent)
        : QtComponentsOverlayWidget(parent)
        , _parent(parent)
        , _animation(new QPropertyAnimation(parent))
    {
        _animation->setPropertyName("tweenValue");
        _animation->setEasingCurve(QEasingCurve::OutCirc);
        _animation->setTargetObject(this);
        _animation->setDuration(700);

        setAttribute(Qt::WA_TransparentForMouseEvents);
        setAttribute(Qt::WA_NoSystemBackground);

        parent->installEventFilter(this);
    }

    QtComponentsButtonTabsOverlayWidget::~QtComponentsButtonTabsOverlayWidget()
    {

    }

    void QtComponentsButtonTabsOverlayWidget::refreshGeometry()
    {
        if(QLayoutItem *item = _parent->layout()->itemAt(_parent->currentIndex())){
            const QRect r(item->geometry());
            const qreal s = 1-_tween;

            if (QAbstractAnimation::Running != _animation->state()) {
                _geometry = r;
            } else {
                if(Qt::Horizontal == _parent->orientation()){
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
            _parent->update();
        }
    }

    void QtComponentsButtonTabsOverlayWidget::animate()
    {
//        raise();
        _previousGeometry = _geometry;

        _animation->stop();
        _animation->setStartValue(0);
        _animation->setEndValue(1);
        _animation->start();
    }

    bool QtComponentsButtonTabsOverlayWidget::eventFilter(QObject *watched, QEvent *event)
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

    void QtComponentsButtonTabsOverlayWidget::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        if(_parent->animate()){
            QPainterPath path;
            path.addRoundedRect(_geometry, QtComponentsTheme::radiusRatios(_parent->radiusRatios(),_geometry),
                                QtComponentsTheme::radiusRatios(_parent->radiusRatios(),_geometry));
            painter.setClipPath(path);
            painter.setClipping(true);

            painter.setPen(_parent->palette().color(QPalette::Active,QPalette::Background));
            painter.setBrush(_parent->palette().color(QPalette::Active,QPalette::Background));

            painter.drawRect(_geometry);
        }
    }

    QtComponentsButtonTab::QtComponentsButtonTab(QtComponentsButtonTabs *parent)
        : QtComponentsButton(parent)
        , _parent(parent)
        , _active(false)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(this,SIGNAL(clicked()),SLOT(activateTab()));
    }

    QtComponentsButtonTab::QtComponentsButtonTab(const QString& text, QtComponentsButtonTabs *parent)
        : QtComponentsButton(text,parent)
        , _parent(parent)
        , _active(false)
    {
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        connect(this,SIGNAL(clicked()),SLOT(activateTab()));
    }

    QtComponentsButtonTab::~QtComponentsButtonTab()
    {

    }

    void QtComponentsButtonTab::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setFont(_parent->font());
        painter.setPen(_parent->palette().color(QPalette::Inactive,QPalette::ButtonText));
        if(_parent->animate()){
            if(_active){
                painter.setPen(_parent->palette().color(QPalette::Active,QPalette::ButtonText));
            }
        }else{
            if(underMouse()){
                painter.setPen(_parent->palette().color(QPalette::Active,QPalette::ButtonText));
            }
        }
        painter.drawText(rect(),Qt::AlignCenter,text());
    }

    void QtComponentsButtonTab::activateTab()
    {
        _parent->setCurrentTab(this);
    }

    QtComponentsIconButtonTab::QtComponentsIconButtonTab(const QIcon &icon, QtComponentsButtonTabs *parent)
        : QtComponentsButtonTab(parent)
        , _parent(parent)
    {
        setIcon(icon);
    }

    QtComponentsIconButtonTab::~QtComponentsIconButtonTab()
    {

    }

    void QtComponentsIconButtonTab::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::SmoothPixmapTransform);
        QPixmap pixmap = icon().pixmap(size());
        if(_parent->animate()){
            if(isActive()){
                pixmap = QtComponentsTheme::icon2Color(pixmap,
                            _parent->palette().color(QPalette::Active,QPalette::Foreground));
            }
        }else{
            if(underMouse()){
                pixmap = QtComponentsTheme::icon2Color(pixmap,
                            _parent->palette().color(QPalette::Active,QPalette::Foreground));
            }
        }
        painter.drawPixmap(rect(),pixmap);
    }



}
