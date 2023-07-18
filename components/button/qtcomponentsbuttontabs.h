#ifndef __QTCOMPONENTSBUTTONTABS_H__
#define __QTCOMPONENTSBUTTONTABS_H__

#include "components_global.h"
#include "appbar/qtcomponentsappbar.h"

class QAbstractButton;

namespace Components {

    class QtComponentsButtonTab;
    class QtComponentsButtonTabsPrivate;

    class COMPONENTS_EXPORT QtComponentsButtonTabs : public QtComponentsAppBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTabs)
        Q_DECLARE_PRIVATE(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabs(Qt::Orientation orientation = Qt::Horizontal, QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsButtonTabs();

        void addTab(const QString& text);
        void addTab(const QIcon& icon);

        void setCurrentTab(QtComponentsButtonTab *tab);
        void setCurrentTab(int index);
        int currentIndex() const;

        Qt::Orientation orientation()const;
        void setAnimate(bool animate);
        bool animate()const;

    Q_SIGNALS:

        void currentChanged(int);

    protected:

        void setTabActive(int index, bool active = true);
        const QScopedPointer<QtComponentsButtonTabsPrivate>         d_ptr;

    };


}


#endif
