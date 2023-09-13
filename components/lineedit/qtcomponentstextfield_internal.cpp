#include "qtcomponentstextfield.h"
#include "qtcomponentstextfield_p.h"
#include "qtcomponentstextfield_internal.h"

#include <QPainter>
#include <QPropertyAnimation>
#include <QEventTransition>

namespace Components {

    QtComponentsTextFieldStateMachine::QtComponentsTextFieldStateMachine(QtComponentsTextField *parent)
        : QStateMachine(parent),
          _textField(parent),
          _normalState(new QState),
          _focusedState(new QState),
          _label(0),
          _offsetAnimation(0),
          _colorAnimation(0),
          _progress(0.0)
    {
        Q_ASSERT(parent);

        addState(_normalState);
        addState(_focusedState);

        setInitialState(_normalState);

        QEventTransition *transition;
        QPropertyAnimation *animation;

        transition = new QEventTransition(parent, QEvent::FocusIn);
        transition->setTargetState(_focusedState);
        _normalState->addTransition(transition);

        animation = new QPropertyAnimation(this, "progress", this);
        animation->setEasingCurve(QEasingCurve::InCubic);
        animation->setDuration(310);
        transition->addAnimation(animation);

        transition = new QEventTransition(parent, QEvent::FocusOut);
        transition->setTargetState(_normalState);
        _focusedState->addTransition(transition);

        animation = new QPropertyAnimation(this, "progress", this);
        animation->setEasingCurve(QEasingCurve::OutCubic);
        animation->setDuration(310);
        transition->addAnimation(animation);

        _normalState->assignProperty(this, "progress", 0);
        _focusedState->assignProperty(this, "progress", 1);

        setupProperties();

        connect(_textField, SIGNAL(textChanged(QString)), this, SLOT(setupProperties()));
    }

    QtComponentsTextFieldStateMachine::~QtComponentsTextFieldStateMachine()
    {

    }

    void QtComponentsTextFieldStateMachine::setLabel(QtComponentsTextFieldLabel *label)
    {
        if (_label) {
            delete _label;
        }

        if (_offsetAnimation) {
            removeDefaultAnimation(_offsetAnimation);
            delete _offsetAnimation;
        }

        if (_colorAnimation) {
            removeDefaultAnimation(_colorAnimation);
            delete _colorAnimation;
        }

        _label = label;

        if (_label)
        {
            _offsetAnimation = new QPropertyAnimation(_label, "offset", this);
            _offsetAnimation->setDuration(210);
            _offsetAnimation->setEasingCurve(QEasingCurve::OutCubic);
            addDefaultAnimation(_offsetAnimation);

            _colorAnimation = new QPropertyAnimation(_label, "color", this);
            _colorAnimation->setDuration(210);
            addDefaultAnimation(_colorAnimation);
        }

        setupProperties();
    }

    void QtComponentsTextFieldStateMachine::setupProperties()
    {
        if (_label)
        {
            const int m = _textField->textMargins().top();

            if (_textField->text().isEmpty()) {
                _normalState->assignProperty(_label, "offset", QPointF(0, 26));
            } else {
                _normalState->assignProperty(_label, "offset", QPointF(0, 0-m));
            }

            _focusedState->assignProperty(_label, "offset", QPointF(0, 0-m));
            _focusedState->assignProperty(_label, "color", _textField->inkColor());
            _normalState->assignProperty(_label, "color", _textField->labelColor());

            if (0 != _label->offset().y() && !_textField->text().isEmpty()) {
                _label->setOffset(QPointF(0, 0-m));
            } else if (!_textField->hasFocus() && _label->offset().y() <= 0 && _textField->text().isEmpty()) {
                _label->setOffset(QPointF(0, 26));
            }
        }

        _textField->update();
    }

    QtComponentsTextFieldLabel::QtComponentsTextFieldLabel(QtComponentsTextField *parent)
        : QWidget(parent),
          _textField(parent),
          _scale(1),
          _posX(0),
          _posY(26),
          _color(parent->labelColor())
    {
        Q_ASSERT(parent);

        QFont f = font();
        f.setPointSize(parent->labelFontSize());
        f.setWeight(QFont::Medium);
        f.setLetterSpacing(QFont::PercentageSpacing, 102);
        setFont(f);
    }

    QtComponentsTextFieldLabel::~QtComponentsTextFieldLabel()
    {

    }

    void QtComponentsTextFieldLabel::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event)

        if (!_textField->hasLabel()) {
            return;
        }

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.scale(_scale, _scale);
        painter.setPen(_color);
        painter.setOpacity(1);

        QPointF pos(2+_posX, height()-36+_posY);
        painter.drawText(pos.x(), pos.y(), _textField->label());
    }

}
