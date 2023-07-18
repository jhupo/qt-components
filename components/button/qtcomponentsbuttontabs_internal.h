#ifndef __QTCOMPONENTSBUTTONTABS_INTERNAL_H__
#define __QTCOMPONENTSBUTTONTABS_INTERNAL_H__

#include "lib/qtcomponentsoverlaywidget.h"
#include "qtcomponentsbutton.h"

class QPropertyAnimation;

namespace Components {

    class QtComponentsButtonTabs;

    class QtComponentsButtonTabsOverlayWidget : public QtComponentsOverlayWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTabsOverlayWidget)
        Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

    public:

        QtComponentsButtonTabsOverlayWidget(QtComponentsButtonTabs* parent);
        virtual~QtComponentsButtonTabsOverlayWidget();

        inline void setTweenValue(qreal value){_tween = value;refreshGeometry();}
        inline qreal tweenValue() const{return _tween;}

        void refreshGeometry();
        void animate();

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        virtual void paintEvent(QPaintEvent *);

    private:

        QtComponentsButtonTabs*const            _parent;
        QPropertyAnimation*const                _animation;
        QRect                                   _previousGeometry;
        QRect                                   _geometry;
        qreal                                   _tween;

    };

    class QtComponentsButtonTab : public QtComponentsButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTab)

    public:

        QtComponentsButtonTab(QtComponentsButtonTabs *parent);
        QtComponentsButtonTab(const QString& text, QtComponentsButtonTabs* parent);
        virtual~QtComponentsButtonTab();

        inline void setActive(bool state){_active=state;update();}
        inline bool isActive() const{return _active;}

    protected:

        virtual void paintEvent(QPaintEvent *);

    protected Q_SLOTS:

        void activateTab();

    private:

        QtComponentsButtonTabs*const             _parent;
        bool                                     _active;

    };

    class QtComponentsIconButtonTab : public QtComponentsButtonTab
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsIconButtonTab)

    public:

        QtComponentsIconButtonTab(const QIcon& icon, QtComponentsButtonTabs* parent);
        virtual~QtComponentsIconButtonTab();

    protected:

        virtual void paintEvent(QPaintEvent *);

    private:

        QtComponentsButtonTabs*const              _parent;

    };


}


#endif
