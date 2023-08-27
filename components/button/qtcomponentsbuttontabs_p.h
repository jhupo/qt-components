#ifndef __QTCOMPONENTSBUTTONTABS_P_H__
#define __QTCOMPONENTSBUTTONTABS_P_H__

#include <QtGlobal>

#include "lib/qtcomponentsoverlaywidget.h"

namespace Components{

    class QtComponentsButtonTabs;

    class QtComponentsButtonTabsPrivate
    {
        Q_DISABLE_COPY(QtComponentsButtonTabsPrivate)
        Q_DECLARE_PUBLIC(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabsPrivate(QtComponentsButtonTabs* q);
        ~QtComponentsButtonTabsPrivate();

        void init();

        QtComponentsButtonTabs*const            q_ptr;
        int                                     _index;

    };

    class QtComponentsButtonOverlayWidget : public QtComponentsOverlayWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonOverlayWidget)

    public:

        QtComponentsButtonOverlayWidget(QtComponentsButtonTabs* tabs);
        virtual~QtComponentsButtonOverlayWidget();

    private:

        QtComponentsButtonTabs*const                _tabs;

    };


}


#endif
