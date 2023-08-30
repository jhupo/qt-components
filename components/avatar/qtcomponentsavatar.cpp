#include "qtcomponentsavatar.h"

#include <QIcon>
#include <QPainter>

namespace Components {

    class QtComponentsAvatarPrivate
    {
        Q_DECLARE_PUBLIC(QtComponentsAvatar)

    public:

        QtComponentsAvatarPrivate(QtComponentsAvatar* q);
        ~QtComponentsAvatarPrivate();

        void init();

        QtComponentsAvatar*const                q_ptr;

        int                                     _size;
        QtComponentsAvatar::AvatarType          _type;
        QPixmap                                 _pixmap;
        QChar                                   _letter;
        QColor                                  _backgroundColor;
        QColor                                  _textColor;

    };

    QtComponentsAvatarPrivate::QtComponentsAvatarPrivate(QtComponentsAvatar *q)
        : q_ptr(q)
    {

    }

    QtComponentsAvatarPrivate::~QtComponentsAvatarPrivate()
    {

    }

    void QtComponentsAvatarPrivate::init()
    {
        Q_Q(QtComponentsAvatar);
        _size           = 40;
        _type           = QtComponentsAvatar::LetterAvatar;

        QFont font(q->font());
        font.setPointSizeF(16);
        q->setFont(font);

        QSizePolicy policy(QSizePolicy::MinimumExpanding,
                           QSizePolicy::MinimumExpanding);
        q->setSizePolicy(policy);
        q->setBackgroundColor(Qt::darkGray);
        q->setTextColor(Qt::darkMagenta);
    }

    QtComponentsAvatar::QtComponentsAvatar(QWidget *parent)
        : QWidget(parent)
        , d_ptr(new QtComponentsAvatarPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsAvatar::~QtComponentsAvatar()
    {

    }

    void QtComponentsAvatar::setSize(int size)
    {
        Q_D(QtComponentsAvatar);
        d->_size = size;
        if(!d->_pixmap.isNull())
        {
            d->_pixmap = d->_pixmap.scaled(d->_size,d->_size,
                                           Qt::IgnoreAspectRatio,
                                           Qt::SmoothTransformation);
        }

        QFont f(font());
        f.setPointSizeF(size* 16 / 40);
        setFont(f);

        update();
    }

    int QtComponentsAvatar::size() const
    {
        Q_D(const QtComponentsAvatar);
        return d->_size;
    }

    void QtComponentsAvatar::setBackgroundColor(const QColor &color)
    {
        Q_D(QtComponentsAvatar);
        d->_backgroundColor = color;
        update();
    }

    QColor QtComponentsAvatar::backgroundColor() const
    {
        Q_D(const QtComponentsAvatar);
        return d->_backgroundColor;
    }

    void QtComponentsAvatar::setTextColor(const QColor &color)
    {
        Q_D(QtComponentsAvatar);
        d->_textColor = color;
        update();
    }

    QColor QtComponentsAvatar::textColor() const
    {
        Q_D(const QtComponentsAvatar);
        return d->_textColor;
    }

    void QtComponentsAvatar::setLetter(const QChar &letter)
    {
        Q_D(QtComponentsAvatar);
        d->_letter = letter;
        d->_type = QtComponentsAvatar::LetterAvatar;
        update();
    }

    void QtComponentsAvatar::setImage(const QImage &image)
    {
        Q_D(QtComponentsAvatar);
        d->_pixmap = QPixmap::fromImage(image.scaled(d->_size,d->_size,
                                                     Qt::IgnoreAspectRatio,
                                                     Qt::SmoothTransformation));
        d->_type = QtComponentsAvatar::ImageAvatar;
        update();
    }

    void QtComponentsAvatar::setIcon(const QIcon &icon)
    {
        Q_D(QtComponentsAvatar);
        d->_pixmap = icon.pixmap(d->_size / 2, d->_size / 2);
        d->_type = QtComponentsAvatar::IconAvatar;
        update();
    }

    QtComponentsAvatar::AvatarType QtComponentsAvatar::type() const
    {
        Q_D(const QtComponentsAvatar);
        return d->_type;
    }

    QSize QtComponentsAvatar::sizeHint() const
    {
        Q_D(const QtComponentsAvatar);
        return QSize(d->_size + 2, d->_size + 2);
    }

    void QtComponentsAvatar::paintEvent(QPaintEvent *event)
    {
        Q_UNUSED(event);
        Q_D(QtComponentsAvatar);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        QRect r = rect();
        const qreal hs = d->_size/2;
        if (!isEnabled())
        {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(Qt::darkGray);
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            painter.drawEllipse(QRectF((width()-d->_size)/2, (height()-d->_size)/2,
                                       d->_size, d->_size));
            return;
        }
        if (QtComponentsAvatar::ImageAvatar != d->_type)
        {
            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(backgroundColor());
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            painter.drawEllipse(QRectF((width()-d->_size)/2, (height()-d->_size)/2,
                                       d->_size, d->_size));
        }
        switch (d->_type)
        {
        case QtComponentsAvatar::ImageAvatar:
        {
            QPainterPath path;
            path.addEllipse(width()/2-hs, height()/2-hs, d->_size, d->_size);
            painter.setClipPath(path);

            painter.drawPixmap(QRect(width()/2-hs, height()/2-hs, d->_size, d->_size),
                               d->_pixmap);
            break;
        }
        case QtComponentsAvatar::IconAvatar:
        {
            QRect iconGeometry((width()-hs)/2, (height()-hs)/2, hs, hs);
            QPainter icon(&d->_pixmap);
            icon.setCompositionMode(QPainter::CompositionMode_SourceIn);
            icon.fillRect(d->_pixmap.rect(), textColor());
            painter.drawPixmap(iconGeometry, d->_pixmap);
            break;
        }
        case QtComponentsAvatar::LetterAvatar:
        {
            painter.setPen(textColor());
            painter.setBrush(Qt::NoBrush);
            painter.drawText(r, Qt::AlignCenter, QString(d->_letter));
            break;
        }
        default:
            break;
        }
    }

}
