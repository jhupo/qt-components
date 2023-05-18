#ifndef __QTCOMPONENTSTABS_H__
#define __QTCOMPONENTSTABS_H__

#include "components_global.h"

#include "appbar/qtcomponentsappbar.h"

class QAbstractButton;

namespace Components {

    class QtComponentsTab;
    class QtComponentsTabsPrivate;

    class COMPONENTS_EXPORT QtComponentsTabs : public QtComponentsAppBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTabs)
        Q_DECLARE_PRIVATE(QtComponentsTabs)

    public:

        QtComponentsTabs(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsTabs();

        void setInkColor(const QColor &color);
        QColor inkColor() const;

        void setActiveColor(const QColor& color);
        QColor activeColor()const;

        void setCurrentTab(QtComponentsTab *tab);
        void setCurrentTab(int index);

        QAbstractButton* addTab(const QString& text);
        QAbstractButton* insertTab(const QString& text, int index);
        void removeTab(QAbstractButton* tab);

        int currentIndex() const;

    Q_SIGNALS:

        void currentChanged(int);

    protected:

        void setTabActive(int index, bool active = true);

        const QScopedPointer<QtComponentsTabsPrivate>           d_ptr;

    };

}

#endif
