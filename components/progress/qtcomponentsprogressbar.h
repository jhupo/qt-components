#ifndef __QTCOMPONENTSPROGRESSBAR_H__
#define __QTCOMPONENTSPROGRESSBAR_H__

#include "components_global.h"

#include <QProgressBar>

namespace Components {

    class QtComponentsProgressBarPrivate;

    class COMPONENTS_EXPORT QtComponentsProgressBar : public QProgressBar
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsProgressBar)
        Q_DECLARE_PRIVATE(QtComponentsProgressBar)

    public:

        enum ProgressType{DeterminateProgress,IndeterminateProgress};

        QtComponentsProgressBar(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsProgressBar();

        void setBackgroundColor(const QColor& color);
        QColor backgroundColor()const;

        void setProgressColor(const QColor& color);
        QColor progressColor()const;

        void setDisabledColor(const QColor& color);
        QColor disabledColor()const;

        void setProgressType(ProgressType type);
        ProgressType progressType()const;

    protected:

        virtual void paintEvent(QPaintEvent *);
        const QScopedPointer<QtComponentsProgressBarPrivate>            d_ptr;

    };

}


#endif
