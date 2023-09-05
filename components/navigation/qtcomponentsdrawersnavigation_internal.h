#ifndef __QTCOMPONENTSDRAWERSNAVIGATION_INTERNAL_H__
#define __QTCOMPONENTSDRAWERSNAVIGATION_INTERNAL_H__

#include "appbar/qtcomponentsappbar.h"
#include "button/qtcomponentsiconbutton.h"
#include "button/qtcomponentspushbutton.h"

namespace Components {

    class QtComponentsDrawersNavigation;
    class QtComponentsEventStateMachine;

    class QtComponentsSidebarWidget : public QtComponentsAppBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsSidebarWidget)

    public:

        QtComponentsSidebarWidget(QtComponentsDrawersNavigation* parent);
        virtual~QtComponentsSidebarWidget();

        inline void setSidebarRange(int min, int max){_minimum = min;_maximum = max;}

        inline int sidebarMinimum()const{return _minimum;}
        inline int sidebarMaximum()const{return _maximum;}

    private:

        QtComponentsDrawersNavigation*const                _parent;
        int                                                _minimum;
        int                                                _maximum;
    };

    class QtComponentsSidebarButton : public QtComponentsIconButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsSidebarButton)
        Q_PROPERTY(qreal angle READ angle WRITE setAngle)

    public:

        QtComponentsSidebarButton(QtComponentsDrawersNavigation* parent, QtComponentsSidebarWidget* sidebar);
        virtual~QtComponentsSidebarButton();

    protected:

        virtual void paintEvent(QPaintEvent *);
        virtual bool eventFilter(QObject *watched, QEvent *event);

    protected Q_SLOTS:

        void drawersExpand(bool expand);

    private:
        void execPropertyAnimation(QObject *object, const QByteArray& propertyName, const QVariant& start, const QVariant& target, const int msec = 350);
        void setupProperty();
        qreal angle()const{return _angle;}
        void setAngle(qreal angle){if(!qFuzzyCompare(_angle,angle)){_angle=angle;update();}}
        QtComponentsDrawersNavigation*const                 _parent;
        QtComponentsSidebarWidget*const                     _sidebar;
        qreal                                               _angle;
        QtComponentsEventStateMachine*                      _stateMachine;
    };

    class QtComponentsDrawersTab : public QtComponentsPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsDrawersTab)

    public:

        QtComponentsDrawersTab(QtComponentsDrawersNavigation* parent);
        virtual~QtComponentsDrawersTab();

        virtual QSize sizeHint()const;

    protected Q_SLOTS:

        void activateTab();

    protected:

        virtual void paintEvent(QPaintEvent *);

    private:

        QtComponentsDrawersNavigation*const                 _parent;

    };


}

#endif
