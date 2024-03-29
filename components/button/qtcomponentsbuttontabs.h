#ifndef __QTCOMPONENTSBUTTONTABS_H__
#define __QTCOMPONENTSBUTTONTABS_H__

#include "components_global.h"
#include "appbar/qtcomponentsappbar.h"

#include <QIcon>

namespace Components {

    class QtComponentsPushButton;
    class QtComponentsButtonTabsPrivate;

    class COMPONENTS_EXPORT QtComponentsButtonTabs : public QtComponentsAppBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButtonTabs)
        Q_DECLARE_PRIVATE(QtComponentsButtonTabs)

    public:

        QtComponentsButtonTabs(QWidget* parent = Q_NULLPTR, Qt::Orientation orientaion = Qt::Horizontal);
        virtual~QtComponentsButtonTabs();

        void setCurrentIndex(int index);
        void setCurrentTab(QtComponentsPushButton* tab);
        int currentIndex() const;

        Qt::Orientation orientaion()const;

        void setAnimate(bool animate);
        bool isAnimate()const;

        bool isCheckable() const;
        void setCheckable(bool value);

        void setTabIconSize(int size);
        int tabIconSize()const;

        void addTab(const QString& text, const QIcon& icon = QIcon(), const QString& tips = QString());
        void addTab(const QIcon& icon, const QString& text, const QString& tips);

        void insertTab(const int index, const QString& text, const QIcon& icon, const QString& tips);

        void removeTab(const int index);
        void eraseTab(const int index);

        int findTabsByUserId(int index);

        void sort();
        void setAutoSort(bool sort);
        bool autoSort()const;

        void setToolTipEdge(Qt::Edge edge);
        Qt::Edge toolTipEdge()const;

        void setLinkColor(const QColor& color, QPalette::ColorGroup group = QPalette::NColorGroups);
        QColor linkColor(QPalette::ColorGroup group = QPalette::NColorGroups)const;

        void setIconColor(const QColor& color, QPalette::ColorGroup group = QPalette::NColorGroups);
        QColor iconColor(QPalette::ColorGroup group = QPalette::NColorGroups)const;

        void setTextColor(const QColor& color, QPalette::ColorGroup group = QPalette::NColorGroups);
        QColor textColor(QPalette::ColorGroup group = QPalette::NColorGroups)const;

    Q_SIGNALS:

        void currentChanged(int);

    protected:

        virtual void setTabActive(int index, bool active = true);
        const QScopedPointer<QtComponentsButtonTabsPrivate>         d_ptr;

    };


}


#endif
