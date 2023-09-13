#include "qtcomponentstextfield.h"
#include "qtcomponentstextfield_p.h"
#include "qtcomponentstextfield_internal.h"
#include "lib/qtcomponentstheme.h"

#include <QEvent>
#include <QAction>
#include <QPainter>
#include <QToolButton>
#include <QCoreApplication>

namespace Components {

    QtComponentsTextField::QtComponentsTextField(QWidget *parent)
        : QLineEdit(parent)
        , d_ptr(new QtComponentsTextFieldPrivate(this))
    {
        d_func()->init();
    }

    QtComponentsTextField::~QtComponentsTextField()
    {

    }

    void QtComponentsTextField::setClearButtonIcon(const QIcon &icon)
    {
        if(isClearButtonEnabled()){
            if(QAction *clearAction = findChild<QAction *>(QLatin1String("_q_qlineeditclearaction"))){
                QList<QToolButton*> btns = findChildren<QToolButton*>();
                foreach(QToolButton* btn, btns){
                    if(btn->defaultAction() == clearAction){
                        btn->setObjectName(QLatin1String("_qc_qlineeditclearbutton"));
                        btn->setIcon(icon);
                    }
                }
            }
        }
    }

    QIcon QtComponentsTextField::clearButtonIcon() const
    {
        if(QToolButton* clear = findChild<QToolButton*>(QLatin1String("_qc_qlineeditclearbutton"))){
            return clear->icon();
        }
        return QIcon();
    }

    void QtComponentsTextField::setTextColor(const QColor &color)
    {
        Q_D(QtComponentsTextField);
        setStyleSheet(QString("QLineEdit { color: %1; }").arg(color.name()));
        QtComponentsTheme::setPaletteColor(color,this,QPalette::WindowText);
        d->_stateMachine->setupProperties();
    }

    QColor QtComponentsTextField::textColor() const
    {
        return palette().color(QPalette::WindowText);
    }

    void QtComponentsTextField::setShowLabel(bool value)
    {
        Q_D(QtComponentsTextField);

        if (d->_showLabel == value) {
            return;
        }

        d->_showLabel = value;

        if (!d->_label && value) {
            d->_label = new QtComponentsTextFieldLabel(this);
            d->_stateMachine->setLabel(d->_label);
        }

        if (value) {
            setContentsMargins(0, 23, 0, 0);
        } else {
            setContentsMargins(0, 0, 0, 0);
        }
    }

    bool QtComponentsTextField::hasLabel() const
    {
        Q_D(const QtComponentsTextField);
        return d->_showLabel;
    }

    void QtComponentsTextField::setLabelFontSize(qreal size)
    {
        Q_D(QtComponentsTextField);

        d->_labelFontSize = size;

        if (d->_label)
        {
            QFont font(d->_label->font());
            font.setPointSizeF(size);
            d->_label->setFont(font);
            d->_label->update();
        }
    }

    qreal QtComponentsTextField::labelFontSize() const
    {
        Q_D(const QtComponentsTextField);
        return d->_labelFontSize;
    }

    void QtComponentsTextField::setLabel(const QString &label)
    {
        Q_D(QtComponentsTextField);
        d->_labelString = label;
        setShowLabel(true);
        d->_label->update();
    }

    QString QtComponentsTextField::label() const
    {
        Q_D(const QtComponentsTextField);
        return d->_labelString;
    }

    void QtComponentsTextField::setLabelColor(const QColor &color)
    {
        Q_D(QtComponentsTextField);
        QtComponentsTheme::setPaletteColor(color,this,QPalette::WindowText,QPalette::Inactive);
        d->_stateMachine->setupProperties();
    }

    QColor QtComponentsTextField::labelColor() const
    {
        return palette().color(QPalette::Inactive,QPalette::WindowText);
    }

    void QtComponentsTextField::setInkColor(const QColor &color)
    {
        Q_D(QtComponentsTextField);
        QtComponentsTheme::setPaletteColor(color,this,QPalette::Link,QPalette::Inactive);
        d->_stateMachine->setupProperties();
    }

    QColor QtComponentsTextField::inkColor() const
    {
        return palette().color(QPalette::Inactive,QPalette::Link);
    }

    void QtComponentsTextField::setInputLineColor(const QColor &color)
    {
        Q_D(QtComponentsTextField);
        QtComponentsTheme::setPaletteColor(color,this,QPalette::Link,QPalette::Active);
        d->_stateMachine->setupProperties();
    }

    QColor QtComponentsTextField::inputLineColor() const
    {
        return palette().color(QPalette::Active,QPalette::Link);
    }

    void QtComponentsTextField::setShowInputLine(bool value)
    {
        Q_D(QtComponentsTextField);

        if (d->_showInputLine == value) {
            return;
        }

        d->_showInputLine = value;
        update();
    }

    bool QtComponentsTextField::hasInputLine() const
    {
        Q_D(const QtComponentsTextField);
        return d->_showInputLine;
    }

    bool QtComponentsTextField::event(QEvent *event)
    {
        Q_D(QtComponentsTextField);

        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            if (d->_label) {
                d->_label->setGeometry(rect());
            }
        }
        default:
            break;
        }
        return QLineEdit::event(event);
    }

    void QtComponentsTextField::paintEvent(QPaintEvent *event)
    {
        Q_D(QtComponentsTextField);

        QLineEdit::paintEvent(event);

        QPainter painter(this);

        const qreal progress = d->_stateMachine->progress();

        if (text().isEmpty() && progress < 1)
        {
            painter.setOpacity(1-progress);
            painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
        }

        const int y = height()-1;
        const int wd = width()-5;

        if (d->_showInputLine)
        {
            QPen pen;
            pen.setWidth(1);
            pen.setColor(inputLineColor());

            if (!isEnabled())
                pen.setStyle(Qt::DashLine);

            painter.setPen(pen);
            painter.setOpacity(1);
            painter.drawLine(QLineF(2.5, y, wd, y));

            QBrush brush;
            brush.setStyle(Qt::SolidPattern);
            brush.setColor(inkColor());

            if (progress > 0)
            {
                painter.setPen(Qt::NoPen);
                painter.setBrush(brush);
                const int w = (1-progress)*static_cast<qreal>(wd/2);
                painter.drawRect(w+2.5, height()-2, wd-w*2, 2);
            }
        }
    }

    QtComponentsTextFieldPrivate::QtComponentsTextFieldPrivate(QtComponentsTextField *q)
        : q_ptr(q)
    {

    }

    QtComponentsTextFieldPrivate::~QtComponentsTextFieldPrivate()
    {

    }

    void QtComponentsTextFieldPrivate::init()
    {
        Q_Q(QtComponentsTextField);

        _stateMachine   = new QtComponentsTextFieldStateMachine(q);
        _label          = 0;
        _labelFontSize  = 9.5;
        _showLabel      = false;
        _showInputLine  = true;

        q->setInputLineColor(Qt::darkGray);
        q->setLabelColor(Qt::darkGray);
        q->setInkColor(QColor("#01bbd3"));

        q->setFrame(false);
        q->setAttribute(Qt::WA_Hover);
        q->setMouseTracking(true);
        q->setTextMargins(0, 2, 0, 4);

        _stateMachine->start();
        QCoreApplication::processEvents();
    }


}
