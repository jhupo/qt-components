#ifndef __QTCOMPONENTSBUTTON_H__
#define __QTCOMPONENTSBUTTON_H__

#include "components_global.h"

#include <QPushButton>

namespace Components {

    class QtComponentsButtonPrivate;

    class COMPONENTS_EXPORT QtComponentsButton : public QPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsButton)
        Q_DECLARE_PRIVATE(QtComponentsButton)

    public:

        QtComponentsButton(QWidget* parent = Q_NULLPTR);
        QtComponentsButton(const QString& text, QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsButton();

        void setRadiusRatios(qreal radius);
        qreal radiusRatios() const;

        virtual QColor color(QPalette::ColorRole role)const;

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        virtual void paintEvent(QPaintEvent *);

        const QScopedPointer<QtComponentsButtonPrivate>         d_ptr;

    };

}


#endif
