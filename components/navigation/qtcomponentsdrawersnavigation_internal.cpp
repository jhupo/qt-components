#include "qtcomponentsdrawersnavigation.h"
#include "qtcomponentsdrawersnavigation_internal.h"
#include "lib/qtcomponentseventstatemachine.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QPixmap>
#include <QPainter>
#include <QLayout>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

namespace Components {

    QtComponentsSidebarWidget::QtComponentsSidebarWidget(QtComponentsDrawersNavigation *parent)
        : QtComponentsAppBar(parent,Qt::Vertical)
        , _parent(parent)
        , _minimum(65)
        , _maximum(165)
    {
        setFixedWidth(_minimum);
    }

    QtComponentsSidebarWidget::~QtComponentsSidebarWidget()
    {

    }

    QtComponentsSidebarButton::QtComponentsSidebarButton(QtComponentsDrawersNavigation *parent, QtComponentsSidebarWidget *sidebar)
        : QtComponentsIconButton(parent)
        , _parent(parent)
        , _sidebar(sidebar)
        , _angle(0)
        , _stateMachine(new QtComponentsEventStateMachine(this))
    {
        _stateMachine->setNormalEventTransition(QEvent::Enter);
        _stateMachine->setTargetEventTransition(QEvent::Leave);
        _stateMachine->setDefaultAnimationPropertyName("angle");
        _stateMachine->assignNormalProperty(0);
        _stateMachine->assignTargetProperty(180);

        setupProperty();

        _stateMachine->start();
    }

    QtComponentsSidebarButton::~QtComponentsSidebarButton()
    {

    }

    void QtComponentsSidebarButton::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.fillRect(rect(),Qt::transparent);

        QPixmap pixmap = icon().pixmap(iconSize());
        QPointF center(pixmap.width() / 2, pixmap.height() / 2);

        painter.translate(center);
        painter.rotate(_angle);
        painter.translate(-center);
        painter.drawPixmap(0,0,pixmap);

    }

    bool QtComponentsSidebarButton::eventFilter(QObject *watched, QEvent *event)
    {
        if(QEvent::Resize == event->type()){
            const QRect r = _sidebar->rect();
            move(r.width() - 7, r.y() + 70);
        }
        return QtComponentsIconButton::eventFilter(watched,event);
    }

    void QtComponentsSidebarButton::drawersExpand(bool expand)
    {
        execPropertyAnimation(_sidebar,
                              "minimumWidth",
                              _sidebar->width(),
                              expand ? _sidebar->sidebarMaximum() : _sidebar->sidebarMinimum());

        execPropertyAnimation(_sidebar,
                              "roundedRadiusRatios",
                              _sidebar->roundedRadiusRatios(),
                              expand ? 10 : 50);

        _stateMachine->reverse();
    }

    void QtComponentsSidebarButton::execPropertyAnimation(QObject *object, const QByteArray &propertyName, const QVariant &start, const QVariant &target, const int msec)
    {
        QPropertyAnimation* animation = new QPropertyAnimation(object,propertyName);
        animation->setDuration(msec);
        animation->setStartValue(start);
        animation->setEndValue(target);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
    }

    void QtComponentsSidebarButton::setupProperty()
    {
        raise();
        setUseThemeColors(false);
        setIconSize(QSize(28,28));
        resize(sizeHint());
        setCheckable(true);

        QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
        effect->setBlurRadius(16);
        effect->setColor(Qt::darkGray);
        effect->setOffset(2, 3);
        setGraphicsEffect(effect);

        connect(this,SIGNAL(clicked(bool)),SLOT(drawersExpand(bool)));

        _parent->installEventFilter(this);
        _sidebar->installEventFilter(this);
    }

    QtComponentsDrawersTab::QtComponentsDrawersTab(QtComponentsDrawersNavigation *parent)
        : QtComponentsPushButton(parent)
        , _parent(parent)
    {
        setCheckable(true);
        setAutoExclusive(true);
        connect(this,SIGNAL(clicked()),SLOT(activateTab()));
    }

    QtComponentsDrawersTab::~QtComponentsDrawersTab()
    {

    }

    QSize QtComponentsDrawersTab::sizeHint() const
    {
        return QSize(-1,qMax(32,iconSize().height()));
    }

    void QtComponentsDrawersTab::activateTab()
    {
        _parent->setCurrentDrawersTab(this);
    }

    void QtComponentsDrawersTab::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        painter.fillRect(rect(),color());
        painter.setFont(font());

        if (!icon().isNull()){
            QRect iconRect(QPoint(0, (height() - iconSize().height()) / 2), iconSize());
            painter.drawPixmap(iconRect,QtComponentsTheme::icon2Color(icon().pixmap(iconSize()),color(QPalette::Foreground)));
        }

        if(_parent->isDrawersExpand()){
            painter.setPen(color(QPalette::ButtonText));
            QRect textRect(QPoint(iconSize().width() + 6,0),QSize(fontMetrics().width(text()),height()));
            painter.drawText(textRect,Qt::AlignCenter, text());
        }

    }

}
