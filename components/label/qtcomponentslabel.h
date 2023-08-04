#ifndef __QTCOMPONENTSLABEL_H__
#define __QTCOMPONENTSLABEL_H__

#include "components_global.h"

#include <QLabel>

namespace Components {

    class QtComponentsLabel : public QLabel
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsLabel)

    public:

        QtComponentsLabel(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsLabel();

        void setColor(const QColor& color);
        QColor color()const;

    public Q_SLOTS:

        void setIcon(const QIcon& icon);

    };

}


#endif
