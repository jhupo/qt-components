#ifndef __QTCOMPONENTSTHEME_H__
#define __QTCOMPONENTSTHEME_H__

#include "components_global.h"

#include "constants.h"

namespace Components {

    class QtComponentsThemePrivate;

    class COMPONENTS_EXPORT QtComponentsTheme : public QObject
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTheme)
        Q_DECLARE_PRIVATE(QtComponentsTheme)

    public:

        QtComponentsTheme(QObject* parent = Q_NULLPTR);
        virtual~QtComponentsTheme();

        static QtComponentsTheme* inst();

        QColor color(const _Color color);

        void setColor(const _Color key, const QColor& color);

        static QIcon icon(const QString& category, const QString& icon, QString& state = QString());

        static QIcon icon(const QString& details);

        static QPixmap icon2Color(const QPixmap& pixmap, const QColor& color);

        static QPixmap icon2Color(const QPixmap &pixmap, const _Color color);

        static QString elidedText(const QString& text,QWidget* widget,const quint16& margin = 9, Qt::TextElideMode mode = Qt::ElideMiddle);

        static qreal radiusRatios(const qreal percentage, const QRect& rect);

    protected:

        QScopedPointer<QtComponentsThemePrivate>            d_ptr;

    };


}


#endif
