#ifndef __QTCOMPONENTSDIALOG_H__
#define __QTCOMPONENTSDIALOG_H__

#include "components_global.h"

#include <QDialog>

namespace Components {

    class QtComponentsDialogPrivate;

    class COMPONENTS_EXPORT QtComponentsDialog : public QDialog
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsDialog)
        Q_DECLARE_PRIVATE(QtComponentsDialog)

    public:

        QtComponentsDialog(QWidget* parent = Q_NULLPTR);
        virtual~QtComponentsDialog();

        void setWindowTitleBar(QWidget* title);
        QWidget *windowTitleBar()const;

    protected:

        virtual bool eventFilter(QObject *watched, QEvent *event);
        const QScopedPointer<QtComponentsDialogPrivate>         d_ptr;

    };


}


#endif
