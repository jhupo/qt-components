#ifndef __QTCOMPONENTSDRAWERSNAVIGATION_P_H__
#define __QTCOMPONENTSDRAWERSNAVIGATION_P_H__

#include <QtGlobal>

#include "button/qtcomponentsbuttontabs.h"

class QMutex;

namespace Components {

    class QtComponentsDrawersNavigation;
    class QtComponentsSidebarWidget;
    class QtComponentsSidebarButton;
    class QtComponentsStackedWidget;
    class QtComponentsSidebarStateMachine;

    class QtComponentsDrawersNavigationPrivate
    {
        Q_DISABLE_COPY(QtComponentsDrawersNavigationPrivate)
        Q_DECLARE_PUBLIC(QtComponentsDrawersNavigation)

    public:

        QtComponentsDrawersNavigationPrivate(QtComponentsDrawersNavigation* q);
        ~QtComponentsDrawersNavigationPrivate();

        void init();

        void setupDrawersTabsPaletteColor();

        QtComponentsDrawersNavigation*const             q_ptr;
        QMutex                                          _mutex;
        int                                             _index;
        int                                             _iconSize;
        bool                                            _autoSort;
        QPalette                                        _palette;
        QtComponentsSidebarWidget*                      _sidebarWidget;
        QtComponentsStackedWidget*                      _stackedWidget;
        QtComponentsSidebarButton*                      _sidebarButton;
    };

}

#endif
