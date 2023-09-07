#ifndef __QTCOMPONENTSBUTTONTABS_P_H__
#define __QTCOMPONENTSBUTTONTABS_P_H__

#include <QtGlobal>

#include "lib/qtcomponentsoverlaywidget.h"
#include "qtcomponentspushbutton.h"

class QMutex;
class QPropertyAnimation;

namespace Components{

    class QtComponentsButtonTabs;
    class QtComponentsTabsInkBar;

    class QtComponentsButtonTabsPrivate
    {
        Q_DISABLE_COPY(QtComponentsButtonTabsPrivate)
        Q_DECLARE_PUBLIC(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabsPrivate(QtComponentsButtonTabs* q);
        ~QtComponentsButtonTabsPrivate();

        void init();

        QtComponentsButtonTabs*const            q_ptr;
        bool                                    _autoSort;
        int                                     _index;
        int                                     _iconSize;
        bool                                    _animate;
        bool                                    _checkable;
        Qt::Edge                                _edge;
        QPalette                                _tabPalette;
        QtComponentsTabsInkBar*                 _inkBar;
        QMutex                                  _mutex;
    };

    class QtComponentsTabsInkBar : public QtComponentsOverlayWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTabsInkBar)
        Q_PROPERTY(qreal tweenValue WRITE setTweenValue READ tweenValue)

    public:

        QtComponentsTabsInkBar(QtComponentsButtonTabs* tabs);
        virtual~QtComponentsTabsInkBar();

        inline void setTweenValue(qreal value);
        inline qreal tweenValue() const;

        void refreshGeometry();
        void animate();

    protected:

        virtual void paintEvent(QPaintEvent*);
        virtual bool eventFilter(QObject *watched, QEvent *event);

    private:

        QtComponentsButtonTabs*const                _tabs;
        QPropertyAnimation *const                   _animation;
        QRect                                       _geometry;
        QRect                                       _previousGeometry;
        qreal                                       _tween;
    };

    inline void QtComponentsTabsInkBar::setTweenValue(qreal value)
    {
        _tween = value;
        refreshGeometry();
    }

    inline qreal QtComponentsTabsInkBar::tweenValue() const
    {
        return _tween;
    }

    class QtComponentsButtonTab : public QtComponentsPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTab)

    public:

        QtComponentsButtonTab(QtComponentsButtonTabs* parent);
        virtual~QtComponentsButtonTab();

    protected Q_SLOTS:

        void activateTab();

    private:

        QtComponentsButtonTabs*const            _parent;
    };

}


#endif
