#ifndef __QTCOMPONENTSPROGRESSBAR_P_H__
#define __QTCOMPONENTSPROGRESSBAR_P_H__

#include "qtcomponentsprogressbar.h"

class QPropertyAnimation;

namespace Components {

    class QtComponentsProgressDelegate;

    class QtComponentsProgressBarPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsProgressBar)

    public:

        QtComponentsProgressBarPrivate(QtComponentsProgressBar* q);
        ~QtComponentsProgressBarPrivate();

        void init();

        QtComponentsProgressBar*const                   q_ptr;
        QtComponentsProgressDelegate*                   _delegate;
        QtComponentsProgressBar::ProgressType           _type;
        QPropertyAnimation*                             _animation;
    };

    class QtComponentsProgressDelegate : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsProgressDelegate)
        Q_PROPERTY(qreal offset READ offset WRITE setOffset)

    public:

        QtComponentsProgressDelegate(QtComponentsProgressBar* progress);
        virtual~QtComponentsProgressDelegate();

        inline void setOffset(qreal offset);
        inline qreal offset()const;

    private:

        QtComponentsProgressBar*const           _progress;
        qreal                                   _offset;
    };

    inline void QtComponentsProgressDelegate::setOffset(qreal offset)
    {
        if(!qFuzzyCompare(_offset,offset)){
            _offset = offset;
            _progress->update();
        }
    }

    inline qreal QtComponentsProgressDelegate::offset()const
    {
        return _offset;
    }

}

#endif
