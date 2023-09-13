#ifndef __QTCOMPONENTSTHEME_H__
#define __QTCOMPONENTSTHEME_H__

#include "components_global.h"

#include "constants.h"

#include <QPalette>

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

        void setCurrentFontFamily(const QString& family);
        QFont font(int pointSize = -1, int weight = -1, bool italic = false) const;

        static QFont font(const QString& family, int pointSize = -1, int weight = -1, bool italic = false);

        static QIcon icon(const QString& category, const QString& icon);

        static QIcon icon(const QString& category, const QString& icon, const QString& state);

        static QIcon icon(const QString& details);

        static QPixmap icon2Color(const QPixmap& pixmap, const QColor& color);

        static QPixmap icon2Color(const QPixmap &pixmap, const _Color color);

        static QString elidedText(const QString& text,QWidget* widget,const quint16& margin = 9, Qt::TextElideMode mode = Qt::ElideMiddle);

        static qreal radiusRatios(const qreal percentage, const QRect& rect);

        static void setPaletteColor(const QColor& color, QPalette& palette,
                                    QPalette::ColorRole role = QPalette::Window,
                                    QPalette::ColorGroup group = QPalette::NColorGroups);
        static void setPaletteColor(const QColor& color, QWidget* w,
                                    QPalette::ColorRole role = QPalette::Window,
                                    QPalette::ColorGroup group = QPalette::NColorGroups);

    protected:

        QScopedPointer<QtComponentsThemePrivate>            d_ptr;

    };


}


#endif
