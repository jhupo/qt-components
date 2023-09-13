#ifndef __QTCOMPONENTSMESSAGEBOX_H__
#define __QTCOMPONENTSMESSAGEBOX_H__

#include "window/qtcomponentsdialog.h"

#include <QMessageBox>

class QPushButton;

namespace Components {

    class QtComponentsMessageBoxPrivate;

    class COMPONENTS_EXPORT QtComponentsMessageBox : public QtComponentsDialog
    {
        Q_OBJECT
        Q_DISABLE_COPY(QtComponentsMessageBox)
        Q_DECLARE_PRIVATE(QtComponentsMessageBox)

    public:

        QtComponentsMessageBox(QWidget* parent = Q_NULLPTR);
        QtComponentsMessageBox(QMessageBox::Icon icon, const QString &title, const QString &text,
                    QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget *parent = Q_NULLPTR);

        virtual~QtComponentsMessageBox();

        void addButton(QPushButton *button, QMessageBox::ButtonRole role);
        QPushButton *addButton(const QString &text, QMessageBox::ButtonRole role);
        QPushButton *addButton(QMessageBox::StandardButton button);
        void removeButton(QPushButton *button);

        QList<QAbstractButton *> buttons() const;
        QMessageBox::ButtonRole buttonRole(QPushButton *button) const;

        void setStandardButtons(QMessageBox::StandardButtons buttons);
        QMessageBox::StandardButtons standardButtons() const;
        QMessageBox::StandardButton standardButton(QAbstractButton *button) const;
        QAbstractButton *button(QMessageBox::StandardButton which) const;

        QAbstractButton *clickedButton() const;

        QPushButton *defaultButton() const;
        void setDefaultButton(QPushButton *button);
        void setDefaultButton(QMessageBox::StandardButton button);

        QString text() const;
        void setText(const QString &text);

        QMessageBox::Icon icon() const;
        void setIcon(QMessageBox::Icon con);

        QPixmap iconPixmap() const;
        void setIconPixmap(const QPixmap &pixmap);

        static QMessageBox::StandardButton information(QWidget *parent, const QString &title,
             const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
             QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

        static QMessageBox::StandardButton question(QWidget *parent, const QString &title,
             const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::StandardButtons(QMessageBox::Yes | QMessageBox::No),
             QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

        static QMessageBox::StandardButton warning(QWidget *parent, const QString &title,
             const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
             QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

        static QMessageBox::StandardButton critical(QWidget *parent, const QString &title,
             const QString &text, QMessageBox::StandardButtons buttons = QMessageBox::Ok,
             QMessageBox::StandardButton defaultButton = QMessageBox::NoButton);

    protected:
        const QScopedPointer<QtComponentsMessageBoxPrivate>             d_ptr;

    private:
        Q_PRIVATE_SLOT(d_func(),void _qc_button_box_clicked(QAbstractButton*))
    };

}


#endif
