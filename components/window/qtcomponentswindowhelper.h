#ifndef __QTCOMPONENTSWINDOWHELPER_H__
#define __QTCOMPONENTSWINDOWHELPER_H__

#include "components_global.h"

namespace Components {

    class QtComponentsWindowHelperPrivate;

    class COMPONENTS_EXPORT QtComponentsWindowHelper : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsWindowHelper)
        Q_DECLARE_PRIVATE(QtComponentsWindowHelper)

    public:

        QtComponentsWindowHelper(QWidget* parent,bool drag = false, bool move = true);
        virtual~QtComponentsWindowHelper();

        void setDragWindow(bool drag);
        bool dragWindow()const;

        void setMoveWindow(bool move);
        bool moveWinodw()const;

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);

    protected:

        const QScopedPointer<QtComponentsWindowHelperPrivate>           d_ptr;


    };

}


#endif
