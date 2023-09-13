#ifndef __QTCOMPONENTSTEXTFIEDLD_INTERNAL_H__
#define __QTCOMPONENTSTEXTFIEDLD_INTERNAL_H__

#include <QStateMachine>
#include <QWidget>
#include "qtcomponentstextfield.h"

class QPropertyAnimation;

namespace Components {

    class QtComponentsTextField;
    class QtComponentsTextFieldLabel;

    class QtComponentsTextFieldStateMachine : public QStateMachine
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTextFieldStateMachine)
        Q_PROPERTY(qreal progress WRITE setProgress READ progress)

    public:
        QtComponentsTextFieldStateMachine(QtComponentsTextField *parent);
        ~QtComponentsTextFieldStateMachine();

        void setLabel(QtComponentsTextFieldLabel *label);

        inline void setProgress(qreal progress);
        inline qreal progress() const;

    public slots:
        void setupProperties();

    private:

        QtComponentsTextField *const        _textField;
        QState              *const          _normalState;
        QState              *const          _focusedState;
        QtComponentsTextFieldLabel  *       _label;
        QPropertyAnimation        *         _offsetAnimation;
        QPropertyAnimation        *         _colorAnimation;
        qreal                               _progress;
    };

    inline void QtComponentsTextFieldStateMachine::setProgress(qreal progress)
    {
        if(!qFuzzyCompare(_progress,progress)){
            _progress = progress;
            _textField->update();
        }
    }

    inline qreal QtComponentsTextFieldStateMachine::progress() const
    {
        return _progress;
    }

    class QtComponentsTextFieldLabel : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTextFieldLabel)
        Q_PROPERTY(qreal scale WRITE setScale READ scale)
        Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
        Q_PROPERTY(QColor color WRITE setColor READ color)

    public:
        QtComponentsTextFieldLabel(QtComponentsTextField *parent);
        ~QtComponentsTextFieldLabel();

        inline void setScale(qreal scale);
        inline qreal scale() const;

        inline void setOffset(const QPointF &pos);
        inline QPointF offset() const;

        inline void setColor(const QColor &color);
        inline QColor color() const;

    protected:
        void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

    private:

        QtComponentsTextField *const        _textField;
        qreal                               _scale;
        qreal                               _posX;
        qreal                               _posY;
        QColor                              _color;
    };

    inline void QtComponentsTextFieldLabel::setScale(qreal scale)
    {
        if(!qFuzzyCompare(_scale,scale)){
            _scale = scale;
            update();
        }
    }

    inline qreal QtComponentsTextFieldLabel::scale() const
    {
        return _scale;
    }

    inline void QtComponentsTextFieldLabel::setOffset(const QPointF &pos)
    {
        if(QPointF(_posX,_posY) != pos){
            _posX = pos.x();
            _posY = pos.y();
            update();
        }
    }

    inline QPointF QtComponentsTextFieldLabel::offset() const
    {
        return QPointF(_posX, _posY);
    }

    inline void QtComponentsTextFieldLabel::setColor(const QColor &color)
    {
        _color = color;
        update();
    }

    inline QColor QtComponentsTextFieldLabel::color() const
    {
        return _color;
    }

}

#endif
