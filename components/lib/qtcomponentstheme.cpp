#include "qtcomponentstheme.h"
#include "constants.h"

#include <QMap>
#include <QColor>
#include <QIcon>
#include <QPainter>
#include <QFont>
#include <QFile>
#include <QWidget>
#include <QSvgRenderer>

Q_LOGGING_CATEGORY(logger_components,"logger.components")

namespace Components {

    class QtComponentsThemePrivate
    {
        Q_DISABLE_COPY(QtComponentsThemePrivate)
        Q_DECLARE_PUBLIC(QtComponentsTheme)

    public:

        QtComponentsThemePrivate(QtComponentsTheme* q);
        virtual~QtComponentsThemePrivate();

        void init();

        QtComponentsTheme*const                 q_ptr;
        QString                                 _family;
        QMap<_Color,QColor>                     _colors;

    };

    QtComponentsThemePrivate::QtComponentsThemePrivate(QtComponentsTheme *q)
        : q_ptr(q)
    {
        Q_ASSERT(q);
    }

    QtComponentsThemePrivate::~QtComponentsThemePrivate()
    {

    }

    void QtComponentsThemePrivate::init()
    {
        static const QColor palette[] = {
            QColor("#fff1f0"), QColor("#ffccc7"), QColor("#ffa39e"), QColor("#ff7875"), QColor("#ff4d4f"),
            QColor("#f5222d"), QColor("#cf1322"), QColor("#a8071a"), QColor("#820014"), QColor("#5c0011"),
            QColor("#fff2e8"), QColor("#ffd8bf"), QColor("#ffbb96"), QColor("#ff9c6e"), QColor("#ff7a45"),
            QColor("#fa541c"), QColor("#d4380d"), QColor("#ad2102"), QColor("#871400"), QColor("#610b00"),
            QColor("#fff7e6"), QColor("#ffe7ba"), QColor("#ffd591"), QColor("#ffc069"), QColor("#ffa940"),
            QColor("#fa8c16"), QColor("#d46b08"), QColor("#ad4e00"), QColor("#873800"), QColor("#612500"),
            QColor("#fffbe6"), QColor("#fff1b8"), QColor("#ffe58f"), QColor("#ffd666"), QColor("#ffc53d"),
            QColor("#faad14"), QColor("#d48806"), QColor("#ad6800"), QColor("#874d00"), QColor("#613400"),
            QColor("#feffe6"), QColor("#ffffb8"), QColor("#fffb8f"), QColor("#fff566"), QColor("#ffec3d"),
            QColor("#fadb14"), QColor("#d4b106"), QColor("#ad8b00"), QColor("#876800"), QColor("#614700"),
            QColor("#fcffe6"), QColor("#f4ffb8"), QColor("#eaff8f"), QColor("#d3f261"), QColor("#bae637"),
            QColor("#a0d911"), QColor("#7cb305"), QColor("#5b8c00"), QColor("#3f6600"), QColor("#254000"),
            QColor("#f6ffed"), QColor("#d9f7be"), QColor("#b7eb8f"), QColor("#95de64"), QColor("#73d13d"),
            QColor("#52c41a"), QColor("#389e0d"), QColor("#237804"), QColor("#135200"), QColor("#092b00"),
            QColor("#e6fffb"), QColor("#b5f5ec"), QColor("#87e8de"), QColor("#5cdbd3"), QColor("#36cfc9"),
            QColor("#13c2c2"), QColor("#08979c"), QColor("#006d75"), QColor("#00474f"), QColor("#002329"),
            QColor("#e6f7ff"), QColor("#bae7ff"), QColor("#91d5ff"), QColor("#69c0ff"), QColor("#40a9ff"),
            QColor("#1890ff"), QColor("#096dd9"), QColor("#0050b3"), QColor("#003a8c"), QColor("#002766"),
            QColor("#f0f5ff"), QColor("#d6e4ff"), QColor("#adc6ff"), QColor("#85a5ff"), QColor("#597ef7"),
            QColor("#2f54eb"), QColor("#1d39c4"), QColor("#10239e"), QColor("#061178"), QColor("#030852"),
            QColor("#f9f0ff"), QColor("#efdbff"), QColor("#d3adf7"), QColor("#b37feb"), QColor("#9254de"),
            QColor("#722ed1"), QColor("#531dab"), QColor("#391085"), QColor("#22075e"), QColor("#120338"),
            QColor("#fff0f6"), QColor("#ffd6e7"), QColor("#ffadd2"), QColor("#ff85c0"), QColor("#f759ab"),
            QColor("#eb2f96"), QColor("#c41d7f"), QColor("#9e1068"), QColor("#780650"), QColor("#520339"),
            QColor("#ffffff"), QColor("#fafafa"), QColor("#f5f5f5"), QColor("#f0f0f0"), QColor("#d9d9d9"),
            QColor("#bfbfbf"), QColor("#8c8c8c"), QColor("#595959"), QColor("#434343"), QColor("#262626"),
            QColor("#1f1f1f"), QColor("#141414"), QColor("#000000"), QColor("#67C23A"), QColor("#E6A23C"),
            QColor("#F56C6C"), QColor("#909399")
        };

        for(int i = 0; i <= LastColor; ++i)
            _colors.insert(static_cast<_Color>(i),palette[i]);
    }

    QtComponentsTheme::QtComponentsTheme(QObject *parent)
        : QObject(parent)
        , d_ptr(new QtComponentsThemePrivate(this))
    {
        d_func()->init();
    }

    QtComponentsTheme::~QtComponentsTheme()
    {

    }

    Q_GLOBAL_STATIC(QtComponentsTheme,_theme_inst_)
    QtComponentsTheme *QtComponentsTheme::inst()
    {
        return _theme_inst_;
    }

    QColor QtComponentsTheme::color(const _Color color)
    {
        Q_D(QtComponentsTheme);
        return d->_colors.value(color);
    }

    void QtComponentsTheme::setColor(const _Color key, const QColor &color)
    {
        Q_D(QtComponentsTheme);
        d->_colors.insert(key,color);
    }

    void QtComponentsTheme::setCurrentFontFamily(const QString &family)
    {
        Q_D(QtComponentsTheme);
        d->_family = family;
    }

    QFont QtComponentsTheme::font(int pointSize, int weight, bool italic) const
    {
        Q_D(const QtComponentsTheme);
        return font(d->_family,pointSize,weight,italic);
    }

    QFont QtComponentsTheme::font(const QString &family, int pointSize, int weight, bool italic)
    {
        return QFont(family,pointSize,weight,italic);
    }

    QIcon QtComponentsTheme::icon(const QString &category, const QString &icon)
    {
        return QtComponentsTheme::icon(category,icon,QString());
    }

    QIcon QtComponentsTheme::icon(const QString &category, const QString &icon, const QString &state)
    {
        QString s = state;
        if(!s.isEmpty())
            s.insert(0,"_");
        QFile file(QString(":/icons/icons/%1/ic_%2%3.svg").arg(category).arg(icon).arg(s));
        if(!file.open(QFile::ReadOnly))
            return QIcon();
        QIcon image = QtComponentsTheme::icon(file.readAll());
        file.close();
        return image;
    }

    QIcon QtComponentsTheme::icon(const QString &details)
    {
        if(details.isEmpty())
            return QIcon();
        QSvgRenderer renderer;
        if(!renderer.load(details.toUtf8()))
            return QIcon();
        QImage image(renderer.defaultSize(), QImage::Format_ARGB32);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        renderer.render(&painter);
        return QPixmap::fromImage(image);
    }

    QPixmap QtComponentsTheme::icon2Color(const QPixmap &pixmap, const QColor &color)
    {
        if (!color.isValid() || !color.alpha())
            return pixmap;
        QPixmap map = pixmap;
        QPainter painter(&map);
        painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
        painter.fillRect(map.rect(), color);
        return map;
    }

    QPixmap QtComponentsTheme::icon2Color(const QPixmap &pixmap, const _Color color)
    {
        return QtComponentsTheme::icon2Color(pixmap,QtComponentsTheme::inst()->color(color));
    }

    QString QtComponentsTheme::elidedText(const QString &text, QWidget *widget, const quint16 &margin, Qt::TextElideMode mode)
    {
        return widget->fontMetrics().elidedText(text, mode, widget->width() + margin);
    }

    qreal QtComponentsTheme::radiusRatios(const qreal percentage, const QRect &rect)
    {
        return qMin(rect.width(),rect.height()) * percentage / 100.;
    }

    void QtComponentsTheme::setPaletteColor(const QColor &color, QPalette &palette, QPalette::ColorRole role, QPalette::ColorGroup group)
    {
        if(QPalette::NColorGroups != group){
            palette.setColor(group,role,color);
        }else{
            palette.setColor(QPalette::Disabled,role,color);
            palette.setColor(QPalette::Inactive,role,color);
            palette.setColor(QPalette::Active,role,color);
        }
    }

    void QtComponentsTheme::setPaletteColor(const QColor &color, QWidget *w, QPalette::ColorRole role, QPalette::ColorGroup group)
    {
        Q_ASSERT(w);
        QPalette pale = w->palette();
        QtComponentsTheme::setPaletteColor(color,pale,role,group);
        w->setPalette(pale);
    }



}
