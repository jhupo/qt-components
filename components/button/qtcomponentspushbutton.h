#ifndef __QTCOMPONENTSPUSHBUTTON_H__
#define __QTCOMPONENTSPUSHBUTTON_H__

#include "components_global.h"

#include <QPushButton>

namespace Components {

    class QtComponentsPushButtonPrivate;

    class COMPONENTS_EXPORT QtComponentsPushButton : public QPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsPushButton)
        Q_DECLARE_PRIVATE(QtComponentsPushButton)

    public:

        QtComponentsPushButton(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsPushButton();

        void setRoundedRadiusRatios(const qreal ratios);
        qreal roundedRadiusRatios()const;

        qreal roundedRadius()const;

        virtual void setColor(const QColor& color,
                              QPalette::ColorRole role = QPalette::Button,
                              QPalette::ColorGroup group = QPalette::NColorGroups);

        virtual QColor color(QPalette::ColorRole role = QPalette::Button)const;

        virtual void setUserData(const QVariant& data);
        virtual QVariant userData()const;

        virtual void setIcon(const QString& category, const QString& icon);

    public Q_SLOTS:

        virtual void setIcon(const QIcon& icon);

    protected:

        virtual bool event(QEvent *event);
        virtual void paintEvent(QPaintEvent *);
        const QScopedPointer<QtComponentsPushButtonPrivate>     d_ptr;

    };

}


#endif
