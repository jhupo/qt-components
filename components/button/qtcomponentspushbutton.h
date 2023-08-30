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
        enum ButtonIconPlacement {
            LeftIcon,
            RightIcon
        };
        QtComponentsPushButton(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsPushButton();

        void setIconPlacement(ButtonIconPlacement placement);
        ButtonIconPlacement iconPlacement()const;

        void setRoundedRadiusRatios(const qreal ratios);
        qreal roundedRadiusRatios()const;

        qreal roundedRadius()const;

        virtual void setColor(const QColor& color,
                              QPalette::ColorRole role = QPalette::Button,
                              QPalette::ColorGroup group = QPalette::NColorGroups);

        virtual QColor color(QPalette::ColorRole role = QPalette::Button)const;

        virtual void setUserData(const QVariant& data);
        virtual QVariant userData()const;

        void setUseThemeColors(bool value);
        bool useThemeColors()const;

        void setTextAlignment(Qt::Alignment alignment);
        Qt::Alignment textAlignment() const;

        virtual void setIcon(const QString& category, const QString& icon);
        virtual QSize sizeHint()const;

        void setToolTipEdge(Qt::Edge edge);
        Qt::Edge toolTipEdge()const;

        void setMargins(int margins);
        int margins()const;

    public Q_SLOTS:

        virtual void setIcon(const QIcon& icon);

    protected:
        enum{IconPadding = 6};
        virtual bool event(QEvent *event);
        virtual void paintEvent(QPaintEvent *);
        virtual void paintBackground(QPainter *painter);
        virtual void paintForeground(QPainter *painter);
        const QScopedPointer<QtComponentsPushButtonPrivate>     d_ptr;

    };

}


#endif
