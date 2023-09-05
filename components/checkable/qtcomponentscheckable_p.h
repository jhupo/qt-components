#ifndef __QTCOMPONENTSCHECKABLE_P_H__
#define __QTCOMPONENTSCHECKABLE_P_H__

#include <QWidget>
#include <QtGlobal>
#include <QIcon>

class QState;
class QStateMachine;
class QSignalTransition;

namespace Components {

    class QtComponentsCheckable;
    class QtComponentsCheckableIcon;

    class QtComponentsCheckablePrivate
    {
        Q_DISABLE_COPY(QtComponentsCheckablePrivate)
        Q_DECLARE_PUBLIC(QtComponentsCheckable)

    public:

        QtComponentsCheckablePrivate(QtComponentsCheckable* q);
        ~QtComponentsCheckablePrivate();

        void init();

        QtComponentsCheckable*const                 q_ptr;
        QtComponentsCheckableIcon*                  _unCheckedIcon;
        QtComponentsCheckableIcon*                  _checkedIcon;
        QStateMachine*                              _stateMachine;
        QState*                                     _uncheckedState;
        QState*                                     _checkedState;
        QState*                                     _disabledUncheckedState;
        QState*                                     _disabledCheckedState;
        QSignalTransition*                          _uncheckedTransition;
        QSignalTransition*                          _checkedTransition;

    };

    class QtComponentsCheckableIcon : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsCheckableIcon)
        Q_PROPERTY(qreal opacity  READ opacity  WRITE setOpacity)
        Q_PROPERTY(qreal iconSize READ iconSize WRITE setIconSize)
        Q_PROPERTY(QColor color READ color WRITE setColor)

    public:

        QtComponentsCheckableIcon(const QIcon& icon, QtComponentsCheckable* parent);
        virtual~QtComponentsCheckableIcon();

        inline void setOpacity(qreal opacity);
        inline qreal opacity() const;

        inline void setIconSize(qreal iconSize);
        inline qreal iconSize()const;

        inline void setColor(const QColor& color);
        inline QColor color()const;

        virtual QSize sizeHint()const;

        void setIcon(const QIcon& icon);
        QIcon icon()const;

    protected:

        virtual void paintEvent(QPaintEvent *);

    private:
        QtComponentsCheckable*const                     _parent;
        QIcon                                           _icon;
        QColor                                          _color;
        qreal                                           _opacity;
        qreal                                           _iconSize;
    };

    inline void QtComponentsCheckableIcon::setOpacity(qreal opacity)
    {
        if(!qFuzzyCompare(opacity,_opacity)){
            _opacity=opacity;
            update();
        }
    }

    inline qreal QtComponentsCheckableIcon::opacity()const
    {
        return _opacity;
    }

    inline void QtComponentsCheckableIcon::setIconSize(qreal iconSize)
    {
        if(!qFuzzyCompare(iconSize,_iconSize)){
            _iconSize = iconSize;
            update();
        }
    }

    inline qreal QtComponentsCheckableIcon::iconSize()const
    {
        return _iconSize;
    }

    inline void QtComponentsCheckableIcon::setColor(const QColor &color)
    {
        _color = color;
        update();
    }

    inline QColor QtComponentsCheckableIcon::color()const
    {
        return _color;
    }
}

#endif
