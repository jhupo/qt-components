#include "qtcomponentscheckable.h"
#include "qtcomponentscheckable_p.h"
#include "lib/qtcomponentstheme.h"

#include <QDebug>
#include <QState>
#include <QEvent>
#include <QPainter>
#include <QStateMachine>
#include <QEventTransition>
#include <QCoreApplication>
#include <QSignalTransition>

namespace Components {

    QtComponentsCheckablePrivate::QtComponentsCheckablePrivate(QtComponentsCheckable *q)
        : q_ptr(q)
    {

    }

    QtComponentsCheckablePrivate::~QtComponentsCheckablePrivate()
    {

    }

    void QtComponentsCheckablePrivate::init()
    {
        Q_Q(QtComponentsCheckable);

        _checkedIcon = new QtComponentsCheckableIcon(QtComponentsTheme::icon("checkable","checked","checkbox"),q);
        _unCheckedIcon = new QtComponentsCheckableIcon(QtComponentsTheme::icon("checkable","outline","checkbox"),q);

        q->setCheckable(true);

        q->setIconColor(QColor("#F26521"),QPalette::Active);
        q->setIconColor(QColor("#CACCD4"),QPalette::Inactive);
        q->setIconColor(Qt::darkGray,QPalette::Disabled);
        q->setTextColor(QColor("#303133"));
        q->setTextColor(Qt::darkGray,QPalette::Disabled);

        _stateMachine           = new QStateMachine(q);
        _uncheckedState         = new QState;
        _checkedState           = new QState;
        _disabledUncheckedState = new QState;
        _disabledCheckedState   = new QState;
        _uncheckedTransition    = new QSignalTransition(q, SIGNAL(toggled(bool)));
        _checkedTransition      = new QSignalTransition(q, SIGNAL(toggled(bool)));

        _stateMachine->addState(_uncheckedState);
        _stateMachine->addState(_checkedState);
        _stateMachine->addState(_disabledUncheckedState);
        _stateMachine->addState(_disabledCheckedState);
        _stateMachine->setInitialState(_uncheckedState);
        _uncheckedTransition->setTargetState(_checkedState);
        _uncheckedState->addTransition(_uncheckedTransition);
        _checkedTransition->setTargetState(_uncheckedState);
        _checkedState->addTransition(_checkedTransition);

        QAbstractTransition *transition;

        transition = new QEventTransition(q, QEvent::EnabledChange);
        transition->setTargetState(_disabledUncheckedState);
        _uncheckedState->addTransition(transition);

        transition = new QEventTransition(q, QEvent::EnabledChange);
        transition->setTargetState(_uncheckedState);
        _disabledUncheckedState->addTransition(transition);

        transition = new QEventTransition(q, QEvent::EnabledChange);
        transition->setTargetState(_disabledCheckedState);
        _checkedState->addTransition(transition);

        transition = new QEventTransition(q, QEvent::EnabledChange);
        transition->setTargetState(_checkedState);
        _disabledCheckedState->addTransition(transition);

        transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
        transition->setTargetState(_disabledCheckedState);
        _disabledUncheckedState->addTransition(transition);

        transition = new QSignalTransition(q, SIGNAL(toggled(bool)));
        transition->setTargetState(_disabledUncheckedState);
        _disabledCheckedState->addTransition(transition);

        _checkedState->assignProperty(_checkedIcon, "opacity", 1);
        _checkedState->assignProperty(_unCheckedIcon, "opacity", 0);

        _uncheckedState->assignProperty(_checkedIcon, "opacity", 0);
        _uncheckedState->assignProperty(_unCheckedIcon, "opacity", 1);

        _disabledCheckedState->assignProperty(_checkedIcon, "opacity", 1);
        _disabledCheckedState->assignProperty(_unCheckedIcon, "opacity", 0);

        _disabledUncheckedState->assignProperty(_checkedIcon, "opacity", 0);
        _disabledUncheckedState->assignProperty(_unCheckedIcon, "opacity", 1);

        _checkedState->assignProperty(_checkedIcon, "color", q->checkedColor());
        _checkedState->assignProperty(_unCheckedIcon, "color", q->checkedColor());

        _uncheckedState->assignProperty(_unCheckedIcon, "color", q->unCheckedColor());
        _uncheckedState->assignProperty(_unCheckedIcon, "color", q->unCheckedColor());

        _disabledUncheckedState->assignProperty(_unCheckedIcon, "color", q->disabledColor());
        _disabledCheckedState->assignProperty(_checkedIcon, "color", q->disabledColor());

        _stateMachine->start();

        QCoreApplication::processEvents();
    }

    QtComponentsCheckable::QtComponentsCheckable(QWidget *parent)
        : QtComponentsPushButton(parent)
        , d_ptr(new QtComponentsCheckablePrivate(this))
    {
        d_func()->init();
    }

    QtComponentsCheckable::~QtComponentsCheckable()
    {

    }

    void QtComponentsCheckable::setCheckedIcon(const QIcon &icon)
    {
        Q_D(QtComponentsCheckable);
        d->_checkedIcon->setIcon(icon);
    }

    QIcon QtComponentsCheckable::checkedIcon() const
    {
        Q_D(const QtComponentsCheckable);
        return d->_checkedIcon->icon();
    }

    void QtComponentsCheckable::setUnCheckedIcon(const QIcon &icon)
    {
        Q_D(QtComponentsCheckable);
        d->_unCheckedIcon->setIcon(icon);
    }

    QIcon QtComponentsCheckable::unCheckedIcon() const
    {
        Q_D(const QtComponentsCheckable);
        return d->_unCheckedIcon->icon();
    }

    void QtComponentsCheckable::setCheckedColor(const QColor &color)
    {
        setIconColor(color,QPalette::Active);
        setupProperties();
    }

    QColor QtComponentsCheckable::checkedColor() const
    {
        return iconColor(QPalette::Active);
    }

    void QtComponentsCheckable::setUnCheckedColor(const QColor &color)
    {
        setIconColor(color,QPalette::Inactive);
        setupProperties();
    }

    QColor QtComponentsCheckable::unCheckedColor() const
    {
        return iconColor(QPalette::Inactive);
    }

    void QtComponentsCheckable::setDisabledColor(const QColor &color)
    {
        setIconColor(color,QPalette::Disabled);
        setTextColor(color,QPalette::Disabled);
        setupProperties();
    }

    QColor QtComponentsCheckable::disabledColor() const
    {
        return iconColor(QPalette::Disabled);
    }

    QSize QtComponentsCheckable::sizeHint() const
    {
        if(text().isEmpty()){
            return QSize(16,16);
        }
        return QSize(fontMetrics().size(Qt::TextShowMnemonic, text()).width()+30, 20);
    }

    void QtComponentsCheckable::setupProperties()
    {
        Q_D(QtComponentsCheckable);
        d->_checkedState->assignProperty(d->_checkedIcon, "color", checkedColor());
        d->_checkedState->assignProperty(d->_unCheckedIcon, "color", checkedColor());
        d->_uncheckedState->assignProperty(d->_unCheckedIcon, "color", unCheckedColor());
        d->_disabledUncheckedState->assignProperty(d->_unCheckedIcon, "color", disabledColor());
        d->_disabledCheckedState->assignProperty(d->_checkedIcon, "color", disabledColor());

        if (isEnabled()) {
            if (isChecked()) {
                d->_checkedIcon->setColor(checkedColor());
            } else {
                d->_unCheckedIcon->setColor(unCheckedColor());
            }
        } else {
            d->_checkedIcon->setColor(disabledColor());
            d->_unCheckedIcon->setColor(disabledColor());
        }

        update();
    }

    bool QtComponentsCheckable::event(QEvent *event)
    {
        Q_D(QtComponentsCheckable);
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move:
        {
            d->_checkedIcon->setGeometry(rect());
            d->_unCheckedIcon->setGeometry(rect());
            break;
        }
        default:
            break;
        }
        return QtComponentsPushButton::event(event);
    }

    void QtComponentsCheckable::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setFont(font());
        painter.setPen(textColor());

        if (QtComponentsPushButton::RightIcon == iconPlacement()) {
            painter.drawText(6, 14, text());
        } else {
            painter.drawText(25,14, text());
        }
    }

    QtComponentsCheckableIcon::QtComponentsCheckableIcon(const QIcon &icon, QtComponentsCheckable *parent)
        : QWidget(parent)
        , _parent(parent)
        , _icon(icon)
        , _opacity(1.0)
        , _iconSize(16.0)
    {
        setAttribute(Qt::WA_TransparentForMouseEvents);
    }

    QtComponentsCheckableIcon::~QtComponentsCheckableIcon()
    {

    }

    QSize QtComponentsCheckableIcon::sizeHint() const
    {
        return QSize(_iconSize,_iconSize);
    }

    void QtComponentsCheckableIcon::setIcon(const QIcon &icon)
    {
        _icon = icon;
        update();
    }

    QIcon QtComponentsCheckableIcon::icon() const
    {
        return _icon;
    }

    void QtComponentsCheckableIcon::paintEvent(QPaintEvent *)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setOpacity(_opacity);

         QPixmap pixmap = icon().pixmap(16, 16);

         if (!pixmap.isNull())
         {
             const qreal p = static_cast<qreal>((height())-_iconSize)/2;
             const qreal z = _iconSize / 16;
             QTransform t;
             if (QtComponentsPushButton::RightIcon == _parent->iconPlacement()) {
                 t.translate(p+width()-22, p);
             } else {
                 t.translate(p, p);
             }
             t.scale(z, z);
             painter.setTransform(t);

             QPainter icon(&pixmap);
             icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
             icon.fillRect(pixmap.rect(), _color);
             painter.drawPixmap(0, 0, pixmap);
         }

    }



}
