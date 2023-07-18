#ifndef __QTCOMPONENTSTABS_INTERNAL_H__
#define __QTCOMPONENTSTABS_INTERNAL_H__

#include <QAbstractButton>

#include "qtcomponentstabs.h"
#include "lib/qtcomponentsoverlaywidget.h"

class QPropertyAnimation;

namespace Components {

    class QtComponentsOverlayTabs : public QtComponentsOverlayWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsOverlayTabs)
        Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

    public:

        QtComponentsOverlayTabs(QtComponentsTabs* tabs);
        virtual~QtComponentsOverlayTabs();

        inline void setTweenValue(qreal value){_tween = value;refreshGeometry();}
        inline qreal tweenValue() const{return _tween;}

        void refreshGeometry();
        void animate();

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        virtual void paintEvent(QPaintEvent *event);

    private:

        QtComponentsTabs*const                  _tabs;
        QPropertyAnimation*const                _animation;
        QRect                                   _geometry;
        QRect                                   _previousGeometry;
        qreal                                   _tween;


    };

    class COMPONENTS_EXPORT QtComponentsTab : public QAbstractButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTab)

    public:

        QtComponentsTab(QtComponentsTabs* tabs);
        virtual~QtComponentsTab();

        inline void setActive(bool state){_active=state;update();}
        inline bool isActive() const{return _active;}

        virtual QSize sizeHint() const;

    protected:

        virtual void paintEvent(QPaintEvent *);

    protected Q_SLOTS:

        void activateTab();

    private:

        QtComponentsTabs*const                  _tabs;
        bool                                    _active;

    };

}

#endif
