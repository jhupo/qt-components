#ifndef __QTCOMPONENTSTEXTFIEDLD_H__
#define __QTCOMPONENTSTEXTFIEDLD_H__

#include "components_global.h"

#include <QLineEdit>

namespace Components {

    class QtComponentsTextFieldPrivate;

    class COMPONENTS_EXPORT QtComponentsTextField : public QLineEdit
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsTextField)
        Q_DECLARE_PRIVATE(QtComponentsTextField)

    public:

        QtComponentsTextField(QWidget* parent = Q_NULLPTR);
        virtual ~QtComponentsTextField();

        void setClearButtonIcon(const QIcon& icon);
        QIcon clearButtonIcon()const;

        void setTextColor(const QColor& color);
        QColor textColor()const;

        void setShowLabel(bool value);
        bool hasLabel() const;

        void setLabelFontSize(qreal size);
        qreal labelFontSize() const;

        void setLabel(const QString &label);
        QString label() const;

        void setLabelColor(const QColor &color);
        QColor labelColor() const;

        void setInkColor(const QColor &color);
        QColor inkColor() const;

        void setInputLineColor(const QColor &color);
        QColor inputLineColor() const;

        void setShowInputLine(bool value);
        bool hasInputLine() const;

    protected:
        virtual bool event(QEvent *event);
        virtual void paintEvent(QPaintEvent *event);
        const QScopedPointer<QtComponentsTextFieldPrivate>           d_ptr;

    };

}



#endif
