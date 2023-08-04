#include "qtcomponentswindowhelper.h"

#include <QWidget>
#include <QEvent>
#include <QHoverEvent>
#include <QMouseEvent>

namespace Components {

    class QtComponentsWindowHelperPrivate
    {
        Q_DISABLE_COPY(QtComponentsWindowHelperPrivate)
        Q_DECLARE_PUBLIC(QtComponentsWindowHelper)

    public:

        QtComponentsWindowHelperPrivate(QtComponentsWindowHelper* q);
        ~QtComponentsWindowHelperPrivate();

        typedef enum
        {
            ArrowShape,
            LeftShape,
            LeftTopShape,
            TopShape,
            RightTopShape,
            RightShape,
            RightBottomShape,
            BottomShape,
            LeftBottomShape
        }CursorShapePos;

        void cursorShapeProperty(const QRect& rect,
                                 const QPoint& pos,
                                 Qt::CursorShape& cursorShape,
                                 CursorShapePos& cursorShapePos);

        QRect overlayGeometry(const QRect& rect, const QPoint& point, CursorShapePos pos);

        QtComponentsWindowHelper*const                  q_ptr;
        bool                                            _drag;
        bool                                            _move;
        bool                                            _press;
        QPoint                                          _pos;
        CursorShapePos                                  _cursorShapePos;
        QWidget*                                        _window;

    };

    QtComponentsWindowHelperPrivate::QtComponentsWindowHelperPrivate(QtComponentsWindowHelper *q)
        : q_ptr(q)
        , _drag(false)
        , _move(true)
        , _press(false)
        , _pos(QPoint(0,0))
        , _cursorShapePos(ArrowShape)
        , _window(Q_NULLPTR)
    {

    }

    QtComponentsWindowHelperPrivate::~QtComponentsWindowHelperPrivate()
    {

    }

    void QtComponentsWindowHelperPrivate::cursorShapeProperty(const QRect &rect,
                                                              const QPoint &pos,
                                                              Qt::CursorShape &cursorShape,
                                                              QtComponentsWindowHelperPrivate::CursorShapePos &cursorShapePos)
    {
        static const int border = 3;
        const int w = rect.width();
        const int h = rect.height();
        if(QRect(0, 0, border, border).contains(pos)){
            cursorShape = Qt::SizeFDiagCursor;
            cursorShapePos = LeftTopShape;
        }else if(QRect(w - border, 0, border, border).contains(pos)){
            cursorShape = Qt::SizeBDiagCursor;
            cursorShapePos = RightTopShape;
        }else if(QRect(w - border, h - border, border, border).contains(pos)){
            cursorShape = Qt::SizeFDiagCursor;
            cursorShapePos = RightBottomShape;
        }else if(QRect(0, h - border, border, border).contains(pos)){
            cursorShape = Qt::SizeBDiagCursor;
            cursorShapePos = LeftBottomShape;
        }else if (QRect(border, 0, w - 2 * border, border).contains(pos)) {
            cursorShape = Qt::SizeVerCursor;
            cursorShapePos = TopShape;
        } else if (QRect(border, h - border, w - 2 * border, border).contains(pos)) {
            cursorShape = Qt::SizeVerCursor;
            cursorShapePos = BottomShape;
        } else if (QRect(0, border, border, h - 2 * border).contains(pos)) {
            cursorShape = Qt::SizeHorCursor;
            cursorShapePos = LeftShape;
        } else if (QRect(w - border, border, border, h - 2 * border).contains(pos)) {
            cursorShape = Qt::SizeHorCursor;
            cursorShapePos = RightShape;
        }
    }

    QRect QtComponentsWindowHelperPrivate::overlayGeometry(const QRect &rect, const QPoint &point, QtComponentsWindowHelperPrivate::CursorShapePos pos)
    {
        QRect geometry = rect;
        switch (pos) {
        case LeftShape:{
            geometry.setLeft(point.x());
            break;
        }
        case LeftTopShape:{
            geometry.setTopLeft(point);
            break;
        }
        case TopShape:{
            geometry.setTop(point.y());
            break;
        }
        case RightTopShape:{
            geometry.setTopRight(point);
            break;
        }
        case RightShape:{
            geometry.setRight(point.x());
            break;
        }
        case RightBottomShape:{
            geometry.setBottomRight(point);
            break;
        }
        case BottomShape:{
            geometry.setBottom(point.y());
            break;
        }
        case LeftBottomShape:{
            geometry.setBottomLeft(point);
            break;
        }
        default:
            break;
        }
        return geometry;
    }

    QtComponentsWindowHelper::QtComponentsWindowHelper(QWidget *parent, bool drag, bool move)
        : QObject(parent)
        , d_ptr(new QtComponentsWindowHelperPrivate(this))
    {
        Q_ASSERT(d_func());
        Q_D(QtComponentsWindowHelper);
        d->_move = move;
        d->_drag = drag;
        d->_window = parent;

        if(parent->window()){
            d->_window = parent->window();
            if(drag){
                d->_window->setAttribute(Qt::WA_MouseTracking);
                d->_window->installEventFilter(this);
            }
        }

        parent->setAttribute(Qt::WA_MouseTracking);
        parent->installEventFilter(this);
        setObjectName("QtComponentsWindowHelper");
    }

    QtComponentsWindowHelper::~QtComponentsWindowHelper()
    {

    }

    void QtComponentsWindowHelper::setDragWindow(bool drag)
    {
        Q_D(QtComponentsWindowHelper);
        d->_drag = drag;
    }

    bool QtComponentsWindowHelper::dragWindow() const
    {
        Q_D(const QtComponentsWindowHelper);
        return d->_drag;
    }

    void QtComponentsWindowHelper::setMoveWindow(bool move)
    {
        Q_D(QtComponentsWindowHelper);
        d->_move = move;
    }

    bool QtComponentsWindowHelper::moveWinodw() const
    {
        Q_D(const QtComponentsWindowHelper);
        return d->_move;
    }

    bool QtComponentsWindowHelper::eventFilter(QObject *watched, QEvent *event)
    {
        Q_D(QtComponentsWindowHelper);
        QEvent::Type type = event->type();
        switch (type) {
        case QEvent::MouseMove:
        {
            if(QMouseEvent* mouse = reinterpret_cast<QMouseEvent*>(event)){
                if(d->_drag){
                    Qt::CursorShape shape = Qt::ArrowCursor;
                    QtComponentsWindowHelperPrivate::CursorShapePos pos = QtComponentsWindowHelperPrivate::ArrowShape;
                    d->cursorShapeProperty(d->_window->rect(),mouse->pos(),shape,pos);
                    d->_window->setCursor(shape);
                    if(d->_press && watched == d->_window){
                        d->_window->setGeometry(d->overlayGeometry(d->_window->geometry(),mouse->globalPos(),d->_cursorShapePos));
                    }
                }
                if(d->_move && d->_press && watched == parent() &&
                   QtComponentsWindowHelperPrivate::ArrowShape == d->_cursorShapePos){
                    QPoint pos = mouse->pos();
                    int offsetX = pos.x() - d->_pos.x();
                    int offsetY = pos.y() - d->_pos.y();
                    d->_window->move(d->_window->x() + offsetX,d->_window->y() + offsetY);
                }
            }
            break;
        }
        case QEvent::MouseButtonPress:
        {
            if(QMouseEvent* mouse = reinterpret_cast<QMouseEvent*>(event)){
                if(Qt::LeftButton == mouse->button()){
                    d->_press = true;
                    d->_pos = mouse->pos();
                    Qt::CursorShape shape = Qt::ArrowCursor;
                    d->cursorShapeProperty(d->_window->rect(),mouse->pos(),shape,d->_cursorShapePos);
                    if(d->_drag){
                        d->_window->setCursor(shape);
                    }
                }
            }
            break;
        }
        case QEvent::MouseButtonRelease:
        {
            if(QMouseEvent* mouse = reinterpret_cast<QMouseEvent*>(event)){
                if(Qt::LeftButton == mouse->button()){
                    d->_press = false;
                    d->_pos = QPoint(0,0);
                    d->_cursorShapePos = QtComponentsWindowHelperPrivate::ArrowShape;
                    d->_window->setCursor(Qt::ArrowCursor);
                }
            }
            break;
        }
        default:
            break;
        }
        return QObject::eventFilter(watched,event);
    }

}
