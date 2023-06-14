#ifndef __QTCOMPONENTSAVATAR_H__
#define __QTCOMPONENTSAVATAR_H__

#include "components_global.h"

#include <QWidget>

namespace Components{

    class QtComponentsAvatarPrivate;

    class COMPONENTS_EXPORT QtComponentsAvatar : public QWidget
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsAvatar)
        Q_DECLARE_PRIVATE(QtComponentsAvatar)

    public:

        enum AvatarType{ImageAvatar,IconAvatar,LetterAvatar};

        QtComponentsAvatar(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsAvatar();

        void setSize(int size);
        int size() const;

        void setBackgroundColor(const QColor& color);
        QColor backgroundColor()const;

        void setTextColor(const QColor& color);
        QColor textColor()const;

        void setLetter(const QChar &letter);
        void setImage(const QImage &image);
        void setIcon(const QIcon &icon);

        QtComponentsAvatar::AvatarType type() const;

        virtual QSize sizeHint()const;

    protected:

        virtual void paintEvent(QPaintEvent *event);

        const QScopedPointer<QtComponentsAvatarPrivate>         d_ptr;

    };

}

#endif
