#include "qtcomponentsbuttontabs.h"
#include "qtcomponentsbuttontabs_p.h"
#include "qtcomponentspushbutton.h"

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
        Q_Q(QtComponentsButtonTabs);

        _index = -1;
        _animate = true;
        _checkable = true;
        _edge = Qt::RightEdge;
        _inkBar = new QtComponentsTabsInkBar(q);

        q->setBackgroundColor(Qt::white);
        q->setShadowBorderColor(Qt::transparent);
        q->setLinkColor(QColor("#F26521"));

        q->setIconColor(Qt::darkGray);
        q->setIconColor(QColor("#F26521"),QPalette::Active);

        q->setTextColor(QColor("#606266"));
        q->setTextColor(QColor("#F26521"),QPalette::Active);
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
        setTabActive(d->_index,false);
        d->_index = index;
        setTabActive(index,true);
        if(d->_animate){
            d->_inkBar->animate();
        }
        emit currentChanged(index);
    }

    void QtComponentsButtonTabs::setCurrentTab(QtComponentsPushButton *tab)
    {
        setCurrentIndex(layout()->indexOf(tab));
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

    void QtComponentsButtonTabs::setAnimate(bool animate)
    {
        Q_D(QtComponentsButtonTabs);
        d->_animate = animate;
        update();
    }

    bool QtComponentsButtonTabs::isAnimate() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_animate;
    }

    bool QtComponentsButtonTabs::isCheckable() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_checkable;
    }

    void QtComponentsButtonTabs::setCheckable(bool value)
    {
        Q_D(QtComponentsButtonTabs);
        d->_checkable = value;
        updateTabs();
    }

    void QtComponentsButtonTabs::updateTabs()
    {
        Q_D(QtComponentsButtonTabs);
        QtComponentsPushButton *tab;
        for (int i = 0; i < layout()->count(); ++i) {
           QLayoutItem *item = layout()->itemAt(i);
           if (tab = static_cast<QtComponentsPushButton *>(item->widget())) {
               tab->setTextColor(textColor());
               tab->setIconColor(iconColor());
               tab->setBackgroundColor(Qt::transparent);
               tab->setShadowBorderColor(Qt::transparent);
               tab->setCheckable(d->_checkable);
               tab->setToolTipEdge(d->_edge);
           }
        }
    }

    void QtComponentsButtonTabs::setToolTipEdge(Qt::Edge edge)
    {
        Q_D(QtComponentsButtonTabs);
        d->_edge = edge;
        updateTabs();
    }

    Qt::Edge QtComponentsButtonTabs::toolTipEdge() const
    {
        Q_D(const QtComponentsButtonTabs);
        return d->_edge;
    }

    void QtComponentsButtonTabs::addTab(const QString &text, const QIcon &icon)
    {
        QtComponentsButtonTab* tab = new QtComponentsButtonTab(this);
        tab->setPalette(palette());
        tab->setFont(font());
        if(!icon.isNull()){
            tab->setIcon(icon);
            tab->setIconSize(QSize(16,16));
        }
        tab->setText(text);
        addTab(tab);
    }

    void QtComponentsButtonTabs::addTab(const QIcon &icon, const QString &tips)
    {
        Q_D(QtComponentsButtonTabs);
        QtComponentsButtonTab* tab = new QtComponentsButtonTab(this);
        tab->setPalette(palette());
        tab->setFont(font());
        tab->setIcon(icon);
        tab->setIconSize(QSize(16,16));
        tab->setToolTip(tips);
        tab->setToolTipEdge(d->_edge);
        addTab(tab);
    }

    void QtComponentsButtonTabs::addTab(const QString &text, const QIcon &icon, const QString &tips)
    {
        Q_D(QtComponentsButtonTabs);
        QtComponentsButtonTab* tab = new QtComponentsButtonTab(this);
        tab->setPalette(palette());
        tab->setFont(font());
        tab->setIcon(icon);
        tab->setIconSize(QSize(16,16));
        tab->setText(text);
        tab->setToolTip(tips);
        tab->setToolTipEdge(d->_edge);
        addTab(tab);
    }

    void QtComponentsButtonTabs::removeTab(int index)
    {
        if(-1 != index && index < layout()->count()){
            if(QLayoutItem* item = layout()->takeAt(index)){
                if(QWidget* w = item->widget()){
                    delete w;
                    emit destroyChanged(index);
                }
                delete item;
            }
        }
    }

    void QtComponentsButtonTabs::setLinkColor(const QColor &color, QPalette::ColorGroup group)
    {
        setColor(color,QPalette::Link,group);
    }

    QColor QtComponentsButtonTabs::linkColor(QPalette::ColorGroup group) const
    {
        return color(QPalette::Link,group);
    }

    void QtComponentsButtonTabs::setIconColor(const QColor &color, QPalette::ColorGroup group)
    {
        setColor(color,QPalette::AlternateBase,group);
    }

    QColor QtComponentsButtonTabs::iconColor(QPalette::ColorGroup group) const
    {
        return color(QPalette::AlternateBase,group);
    }

    void QtComponentsButtonTabs::setTextColor(const QColor &color, QPalette::ColorGroup group)
    {
        setColor(color,QPalette::ButtonText,group);
    }

    QColor QtComponentsButtonTabs::textColor(QPalette::ColorGroup group) const
    {
        return color(QPalette::ButtonText,group);
    }

    void QtComponentsButtonTabs::addTab(QtComponentsPushButton *tab)
    {
        Q_D(QtComponentsButtonTabs);
        layout()->addWidget(tab);
        if(-1 == d->_index){
            d->_index = 0;
            setTabActive(d->_index,true);
            if(d->_animate){
                d->_inkBar->refreshGeometry();
            }
        }
    }

    void QtComponentsButtonTabs::setTabActive(int index, bool active)
    {
        QtComponentsPushButton* tab = Q_NULLPTR;
        if(index > -1){
            if(tab = static_cast<QtComponentsPushButton*>(layout()->itemAt(index)->widget())){
                tab->setChecked(active);
            }
        }
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
                if(Qt::Horizontal == _tabs->orientaion()){
                    _geometry = QRect(r.left(), r.bottom()-1, r.width(), 2);
                }else{
                    _geometry = QRect(r.left(), r.top()-1, 2, r.height());
                }
            } else {
                if(Qt::Horizontal == _tabs->orientaion()){
                    const qreal left = _previousGeometry.left()*s + r.left()*_tween;
                    const qreal width = _previousGeometry.width()*s + r.width()*_tween;
                    _geometry = QRect(left, r.bottom()-1, width, 2);
                }else{
                    const qreal top = _previousGeometry.top()*s + r.top()*_tween;
                    const qreal height = _previousGeometry.height() * s + r.height() * _tween;
                    _geometry = QRect(r.left() - 1, top, 2, height + 1);
                }
            }
            _tabs->update();
        }
    }

    void QtComponentsTabsInkBar::animate()
    {
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
        if(_tabs->isAnimate()){
            painter.fillRect(_geometry, _tabs->linkColor());
        }
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

    QtComponentsButtonTab::QtComponentsButtonTab(QtComponentsButtonTabs *parent)
        : QtComponentsPushButton(parent)
        , _parent(parent)
    {
        setAutoExclusive(true);
        setCheckable(parent->isCheckable());
        connect(this,SIGNAL(clicked()),SLOT(activateTab()));
    }

    QtComponentsButtonTab::~QtComponentsButtonTab()
    {

    }

    void QtComponentsButtonTab::activateTab()
    {
        _parent->setCurrentTab(this);
    }


}
