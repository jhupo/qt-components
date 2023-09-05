#ifndef __QTCOMPONENTSCHECKABLE_H__
#define __QTCOMPONENTSCHECKABLE_H__

#include "button/qtcomponentspushbutton.h"

namespace Components {

    class QtComponentsCheckablePrivate;

    class COMPONENTS_EXPORT QtComponentsCheckable : public QtComponentsPushButton
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsCheckable)
        Q_DECLARE_PRIVATE(QtComponentsCheckable)

    public:

        QtComponentsCheckable(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsCheckable();

        void setCheckedIcon(const QIcon& icon);
        QIcon checkedIcon()const;

        void setUnCheckedIcon(const QIcon& icon);
        QIcon unCheckedIcon()const;

        void setCheckedColor(const QColor& color);
        QColor checkedColor()const;

        void setUnCheckedColor(const QColor& color);
        QColor unCheckedColor()const;

        void setDisabledColor(const QColor& color);
        QColor disabledColor()const;

        virtual QSize sizeHint()const;

    protected:
        virtual void setupProperties();
        virtual bool event(QEvent *event);
        virtual void paintEvent(QPaintEvent *);
        const QScopedPointer<QtComponentsCheckablePrivate>          d_ptr;

    };

}


#endif
