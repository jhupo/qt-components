#include "qtcomponentsdialog.h"
#include "qtcomponentsdwmapi.h"
#include "qtcomponentswindowhelper.h"

namespace Components {

    class QtComponentsDialogPrivate
    {
        Q_DISABLE_COPY(QtComponentsDialogPrivate)
        Q_DECLARE_PUBLIC(QtComponentsDialog)

    public:

        QtComponentsDialogPrivate(QtComponentsDialog* q);
        ~QtComponentsDialogPrivate();

        void init();

        QtComponentsDialog*const                q_ptr;
        QtComponentsWindowHelper*               _helper;

    };

    QtComponentsDialogPrivate::QtComponentsDialogPrivate(QtComponentsDialog *q)
        : q_ptr(q)
    {

    }

    QtComponentsDialogPrivate::~QtComponentsDialogPrivate()
    {

    }

    void QtComponentsDialogPrivate::init()
    {
        Q_Q(QtComponentsDialog);
#ifdef DWM_AVAILABLE
        q->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
        extendFrameIntoStyle(q);
        extendFrameIntoClientArea(q,1,1,1,1);
        QCoreApplication::instance()->installNativeEventFilter(&_dwm_filter);
#endif
        _helper = new QtComponentsWindowHelper(q);

        q->setObjectName("QtComponentsDialog");
    }

    QtComponentsDialog::QtComponentsDialog(QWidget *parent)
        : QDialog(parent)
        , d_ptr(new QtComponentsDialogPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsDialog::~QtComponentsDialog()
    {

    }

}
