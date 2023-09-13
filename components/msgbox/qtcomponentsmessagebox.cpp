#include "qtcomponentsmessagebox.h"
#include "label/qtcomponentslabel.h"
#include "button/qtcomponentspushbutton.h"
#include "lib/qtcomponentstheme.h"
#include "lib/qtcomponentsstyle.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QApplication>
#include <QDialogButtonBox>

namespace Components {

    class QtComponentsMessageBoxPrivate
    {
        Q_DISABLE_COPY(QtComponentsMessageBoxPrivate)
        Q_DECLARE_PUBLIC(QtComponentsMessageBox)

    public:

        QtComponentsMessageBoxPrivate(QtComponentsMessageBox* q);
        ~QtComponentsMessageBoxPrivate();

        void init(const QString &title = QString(), const QString &text = QString());

        void setupLayout();

        void _qc_button_box_clicked(QAbstractButton*btn);

        QPixmap standardIcon(QMessageBox::Icon icon);

        QtComponentsMessageBox*const                q_ptr;
        QtComponentsLabel*                          _label;
        QMessageBox::Icon                           _icon;
        QtComponentsLabel*                          _iconLabel;
        QDialogButtonBox*                           _buttonBox;
        QPushButton*                                _defaultButton;
        QPushButton*                                _clickedButton;
    };

    QtComponentsMessageBox::QtComponentsMessageBox(QWidget *parent)
        : QtComponentsDialog(parent)
        , d_ptr(new QtComponentsMessageBoxPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsMessageBox::QtComponentsMessageBox(QMessageBox::Icon icon,
                                                   const QString &title,
                                                   const QString &text,
                                                   QMessageBox::StandardButtons buttons,
                                                   QWidget *parent)
        : QtComponentsDialog(parent)
        , d_ptr(new QtComponentsMessageBoxPrivate(this))
    {
        Q_D(QtComponentsMessageBox);
        d_func()->init(title,text);
        d->_buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
        setIcon(icon);
    }

    QtComponentsMessageBox::~QtComponentsMessageBox()
    {

    }

    void QtComponentsMessageBox::addButton(QPushButton *button, QMessageBox::ButtonRole role)
    {
        Q_D(QtComponentsMessageBox);
        d->_buttonBox->addButton(button,(QDialogButtonBox::ButtonRole)role);
    }

    QPushButton *QtComponentsMessageBox::addButton(const QString &text, QMessageBox::ButtonRole role)
    {
        Q_D(QtComponentsMessageBox);
        return d->_buttonBox->addButton(text,(QDialogButtonBox::ButtonRole)role);
    }

    QPushButton *QtComponentsMessageBox::addButton(QMessageBox::StandardButton button)
    {
        Q_D(QtComponentsMessageBox);
        return d->_buttonBox->addButton((QDialogButtonBox::StandardButton)button);
    }

    void QtComponentsMessageBox::removeButton(QPushButton *button)
    {
        Q_D(QtComponentsMessageBox);
        d->_buttonBox->removeButton(button);
    }

    QList<QAbstractButton *> QtComponentsMessageBox::buttons() const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_buttonBox->buttons();
    }

    QMessageBox::ButtonRole QtComponentsMessageBox::buttonRole(QPushButton *button) const
    {
        Q_D(const QtComponentsMessageBox);
        return (QMessageBox::ButtonRole)d->_buttonBox->buttonRole(button);
    }

    void QtComponentsMessageBox::setStandardButtons(QMessageBox::StandardButtons buttons)
    {
        Q_D(QtComponentsMessageBox);
        d->_buttonBox->setStandardButtons(QDialogButtonBox::StandardButtons(int(buttons)));
    }

    QMessageBox::StandardButtons QtComponentsMessageBox::standardButtons() const
    {
        Q_D(const QtComponentsMessageBox);
        return QMessageBox::StandardButtons(int(d->_buttonBox->standardButtons()));
    }

    QMessageBox::StandardButton QtComponentsMessageBox::standardButton(QAbstractButton *button) const
    {
        Q_D(const QtComponentsMessageBox);
        return (QMessageBox::StandardButton)d->_buttonBox->standardButton(button);
    }

    QAbstractButton *QtComponentsMessageBox::button(QMessageBox::StandardButton which) const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_buttonBox->button(QDialogButtonBox::StandardButton(which));
    }

    QAbstractButton *QtComponentsMessageBox::clickedButton() const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_clickedButton;
    }

    QPushButton *QtComponentsMessageBox::defaultButton() const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_defaultButton;
    }

    void QtComponentsMessageBox::setDefaultButton(QPushButton *button)
    {
        Q_D(QtComponentsMessageBox);
        if (!d->_buttonBox->buttons().contains(button))
            return;
        d->_defaultButton = button;
        button->setDefault(true);
        button->setFocus();
    }

    void QtComponentsMessageBox::setDefaultButton(QMessageBox::StandardButton button)
    {
        Q_D(QtComponentsMessageBox);
        setDefaultButton(d->_buttonBox->button(QDialogButtonBox::StandardButton(button)));
    }

    QString QtComponentsMessageBox::text() const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_label->text();
    }

    void QtComponentsMessageBox::setText(const QString &text)
    {
        Q_D(QtComponentsMessageBox);
        d->_label->setText(text);
    }

    QMessageBox::Icon QtComponentsMessageBox::icon() const
    {
        Q_D(const QtComponentsMessageBox);
        return d->_icon;
    }

    void QtComponentsMessageBox::setIcon(QMessageBox::Icon con)
    {
        Q_D(QtComponentsMessageBox);
        setIconPixmap(d->standardIcon(con));
        d->_icon = con;
    }

    QPixmap QtComponentsMessageBox::iconPixmap() const
    {
        Q_D(const QtComponentsMessageBox);
        if (d->_iconLabel && d->_iconLabel->pixmap())
            return *d->_iconLabel->pixmap();
        return QPixmap();
    }

    void QtComponentsMessageBox::setIconPixmap(const QPixmap &pixmap)
    {
        Q_D(QtComponentsMessageBox);
        d->_iconLabel->setPixmap(pixmap);
        d->_icon = QMessageBox::NoIcon;
        d->setupLayout();
    }

    static QMessageBox::StandardButton showNewMessageBox(QWidget *parent,
        QMessageBox::Icon icon,
        const QString& title, const QString& text,
        QMessageBox::StandardButtons buttons,
        QMessageBox::StandardButton defaultButton)
    {
        QtComponentsMessageBox msgBox(icon, title, text, QMessageBox::NoButton, parent);
        msgBox.setAttribute(Qt::WA_DeleteOnClose,false);
        QDialogButtonBox *buttonBox = msgBox.findChild<QDialogButtonBox*>();
        Q_ASSERT(buttonBox != 0);

        uint mask = QMessageBox::FirstButton;
        while (mask <= QMessageBox::LastButton) {
            uint sb = buttons & mask;
            mask <<= 1;
            if (!sb)
                continue;
            QPushButton *button = msgBox.addButton((QMessageBox::StandardButton)sb);
            if (msgBox.defaultButton())
                continue;
            if ((defaultButton == QMessageBox::NoButton && buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
                || (defaultButton != QMessageBox::NoButton && sb == uint(defaultButton)))
                msgBox.setDefaultButton(button);
        }
        if (msgBox.exec() == -1)
            return QMessageBox::Cancel;
        return msgBox.standardButton(msgBox.clickedButton());
    }

    QMessageBox::StandardButton QtComponentsMessageBox::information(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    {
        return showNewMessageBox(parent, QMessageBox::Information, title, text, buttons,
                                 defaultButton);
    }

    QMessageBox::StandardButton QtComponentsMessageBox::question(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    {
        return showNewMessageBox(parent, QMessageBox::Question, title, text, buttons,
                                 defaultButton);
    }

    QMessageBox::StandardButton QtComponentsMessageBox::warning(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    {
        return showNewMessageBox(parent, QMessageBox::Warning, title, text, buttons,
                                 defaultButton);
    }

    QMessageBox::StandardButton QtComponentsMessageBox::critical(QWidget *parent, const QString &title, const QString &text, QMessageBox::StandardButtons buttons, QMessageBox::StandardButton defaultButton)
    {
        return showNewMessageBox(parent, QMessageBox::Critical, title, text, buttons,
                                 defaultButton);
    }

    QtComponentsMessageBoxPrivate::QtComponentsMessageBoxPrivate(QtComponentsMessageBox *q)
        : q_ptr(q)
        , _defaultButton(0)
        , _clickedButton(0)
    {

    }

    QtComponentsMessageBoxPrivate::~QtComponentsMessageBoxPrivate()
    {

    }

    void QtComponentsMessageBoxPrivate::init(const QString &title, const QString &text)
    {
        Q_Q(QtComponentsDialog);

        if(q->parentWidget()){
            q->setWindowIcon(q->parentWidget()->windowIcon());
        }

        _label = new QtComponentsLabel(q);
        _label->setTextInteractionFlags(Qt::TextInteractionFlags(q->style()->styleHint(QStyle::SH_MessageBox_TextInteractionFlags, 0, q)));
        _label->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        _label->setOpenExternalLinks(true);

        _iconLabel = new QtComponentsLabel(q);
        _iconLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

        _buttonBox = new QDialogButtonBox(q);
        _buttonBox->setCenterButtons(q->style()->styleHint(QStyle::SH_MessageBox_CenterButtons, 0, q));
        QObject::connect(_buttonBox, SIGNAL(clicked(QAbstractButton*)),
                         q, SLOT(_qc_button_box_clicked(QAbstractButton*)));

        setupLayout();

        if(!title.isEmpty() || !text.isEmpty()){
            q->setWindowTitle(title);
            _label->setText(text);
        }

        q->setModal(true);

        _icon = QMessageBox::NoIcon;

//        q->setFixedSize(512,224);
    }

    void QtComponentsMessageBoxPrivate::setupLayout()
    {
        Q_Q(QtComponentsDialog);
        if(q->layout()){
            delete q->layout();
        }

        QGridLayout* layout = new QGridLayout(q);
        layout->setContentsMargins(19, 19, 19, 19);
        layout->addWidget(_iconLabel,0,0, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addWidget(_label,0,1, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
        layout->addItem(new QSpacerItem(1,1,QSizePolicy::Expanding,QSizePolicy::Fixed),0,2,2,1);
        layout->addWidget(_buttonBox, layout->rowCount(), layout->columnCount() - 1, 1, 1, Qt::AlignBottom | Qt::AlignRight);

        q->setLayout(layout);
    }

    void QtComponentsMessageBoxPrivate::_qc_button_box_clicked(QAbstractButton * btn)
    {
        Q_Q(QtComponentsMessageBox);
        q->done(_buttonBox->standardButton(btn));
    }

    QPixmap QtComponentsMessageBoxPrivate::standardIcon(QMessageBox::Icon icon)
    {
        QtComponentsMessageBox* mb = q_ptr;
        QStyle *style = mb->style();
        int iconSize = style->pixelMetric(QStyle::PM_MessageBoxIconSize, 0, mb);
        QIcon tmpIcon;
        switch (icon) {
        case QMessageBox::Information:
            return QtComponentsTheme::icon2Color(QtComponentsTheme::icon("msg","info").pixmap(QSize(iconSize, iconSize)),Components::info);
        case QMessageBox::Warning:
            return QtComponentsTheme::icon2Color(QtComponentsTheme::icon("msg","warn").pixmap(QSize(iconSize, iconSize)),Components::warning);
        case QMessageBox::Critical:
            tmpIcon = style->standardIcon(QStyle::SP_MessageBoxCritical, 0, mb);
            break;
        case QMessageBox::Question:
            tmpIcon = style->standardIcon(QStyle::SP_MessageBoxQuestion, 0, mb);
        default:
            break;
        }
        if (!tmpIcon.isNull()) {
            QWindow *window = Q_NULLPTR;
            if (mb) {
                window = mb->windowHandle();
                if (!window) {
                    if (const QWidget *nativeParent = mb->nativeParentWidget())
                        window = nativeParent->windowHandle();
                }
            }
            return tmpIcon.pixmap(window, QSize(iconSize, iconSize));
        }
        return QPixmap();
    }

}
#include "moc_qtcomponentsmessagebox.cpp"
