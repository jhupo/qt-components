#ifndef __QTCOMPONENTSBUTTONTABS_H__
#define __QTCOMPONENTSBUTTONTABS_H__

#include "components_global.h"
#include "appbar/qtcomponentsappbar.h"


namespace Components {

    class QtComponentsButtonTabsPrivate;

    class COMPONENTS_EXPORT QtComponentsButtonTabs : public QtComponentsAppBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTabs)
        Q_DECLARE_PRIVATE(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabs(QWidget* parent = Q_NULLPTR, Qt::Orientation orientaion = Qt::Horizontal);
        virtual~QtComponentsButtonTabs();

        virtual void setCurrentIndex(int index);
        virtual int currentIndex() const;

        virtual Qt::Orientation orientaion()const;

    Q_SIGNALS:

        void currentChanged(int);

    protected:

        virtual void setTabActive(int index, bool active = true) = 0;
        const QScopedPointer<QtComponentsButtonTabsPrivate>         d_ptr;

    };


}


#endif
