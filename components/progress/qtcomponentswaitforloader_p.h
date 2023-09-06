#ifndef __QTCOMPONENTSWAITFORLOADER_P_H__
#define __QTCOMPONENTSWAITFORLOADER_P_H__

#include <QObject>
#include <QtGlobal>

#include "qtcomponentswaitforloader.h"

class QParallelAnimationGroup;

namespace Components {

    class QtComponentsWaitForLoaderDelegate;

    class QtComponentsWaitForLoaderPrivate
    {
        Q_DISABLE_COPY(QtComponentsWaitForLoaderPrivate)
        Q_DECLARE_PUBLIC(QtComponentsWaitForLoader)

    public:

        QtComponentsWaitForLoaderPrivate(QtComponentsWaitForLoader* q);
        ~QtComponentsWaitForLoaderPrivate();

        void init();

        QtComponentsWaitForLoader*const                     q_ptr;
        QParallelAnimationGroup*                            _animation;
        QtComponentsWaitForLoaderDelegate*                  _delegate;
        QTimer*                                             _singleTimer;
    };

    class QtComponentsWaitForLoaderDelegate : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsWaitForLoaderDelegate)
        Q_PROPERTY(qreal dashOffset WRITE setDashOffset READ dashOffset)
        Q_PROPERTY(qreal dashLength WRITE setDashLength READ dashLength)
        Q_PROPERTY(int angle WRITE setAngle READ angle)

    public:

        QtComponentsWaitForLoaderDelegate(QtComponentsWaitForLoader* parent);
        virtual~QtComponentsWaitForLoaderDelegate();

        inline void setDashOffset(qreal offset);
        inline qreal dashOffset() const;

        inline void setDashLength(qreal length);
        inline qreal dashLength() const;

        inline void setAngle(int angle);
        inline int angle() const;

    private:
        QtComponentsWaitForLoader*const                 _parent;
        qreal                                           _dashOffset;
        qreal                                           _dashLength;
        int                                             _angle;
    };

    inline void QtComponentsWaitForLoaderDelegate::setDashOffset(qreal offset)
    {
        if(!qFuzzyCompare(_dashOffset,offset)){
            _dashOffset = offset;
            _parent->update();
        }
    }

    inline qreal QtComponentsWaitForLoaderDelegate::dashOffset() const
    {
        return _dashOffset;
    }

    inline void QtComponentsWaitForLoaderDelegate::setDashLength(qreal length)
    {
        if(!qFuzzyCompare(_dashLength,length)){
            _dashLength = length;
            _parent->update();
        }
    }

    inline qreal QtComponentsWaitForLoaderDelegate::dashLength() const
    {
        return _dashLength;
    }

    inline void QtComponentsWaitForLoaderDelegate::setAngle(int angle)
    {
        if(_angle != angle){
            _angle = angle;
            _parent->update();
        }
    }

    inline int QtComponentsWaitForLoaderDelegate::angle() const
    {
        return _angle;
    }

}

#endif
