#ifndef __QTCOMPONENTSDRAWERSNAVIGATION_H__
#define __QTCOMPONENTSDRAWERSNAVIGATION_H__

#include "components_global.h"

#include <QWidget>

namespace Components {

    class QtComponentsDrawersTab;
    class QtComponentsDrawersNavigationPrivate;

    class COMPONENTS_EXPORT QtComponentsDrawersNavigation : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsDrawersNavigation)
        Q_DECLARE_PRIVATE(QtComponentsDrawersNavigation)

    public:

        QtComponentsDrawersNavigation(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsDrawersNavigation();

        void setSidebarButtonIcon(const QIcon& icon);
        QIcon sidebarButtonIcon()const;

        void setDrawersSidebarRange(int min, int max);
        int drawersSidebarMinimum()const;
        int drawersSidebarMaximum()const;
        void setDrawersTabIconSize(int size);
        int drawersTabIconSize()const;

        bool isDrawersExpand()const;

        void addDrawersTab(const QIcon& icon, const QString& text, QWidget* w);
        void insertDrawersTab(int index, const QIcon& icon, const QString& text, QWidget* w);

        void eraseDrawersTab(int index);
        void removeDrawersTab(int index);

        void setCurrentDrawersTab(int index);
        void setCurrentDrawersTab(QtComponentsDrawersTab* tab);
        int currentDrawersTab();
        int findDrawerTabsByUserId(int index);

        void setDrawersTabsColor(const QColor& color,
                                 QPalette::ColorRole role = QPalette::Button,
                                 QPalette::ColorGroup group = QPalette::NColorGroups);

        void sort();
        void setAutoSort(bool sort);
        bool autoSort() const;

    Q_SIGNALS:

        void currentChanged(int);

    protected:

        const QScopedPointer<QtComponentsDrawersNavigationPrivate>         d_ptr;

    };


}


#endif
