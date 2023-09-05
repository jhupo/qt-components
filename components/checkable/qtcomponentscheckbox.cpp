#include "qtcomponentscheckbox.h"
#include "qtcomponentscheckable_p.h"

#include <QState>
#include <QPropertyAnimation>
#include <QSignalTransition>

namespace Components {

    QtComponentsCheckBox::QtComponentsCheckBox(QWidget *parent)
        : QtComponentsCheckable(parent)
    {
        d_ptr->_checkedState->assignProperty(d_ptr->_checkedIcon, "iconSize", 16);
        d_ptr->_uncheckedState->assignProperty(d_ptr->_checkedIcon, "iconSize", 0);

        QPropertyAnimation *animation;

        animation = new QPropertyAnimation(d_ptr->_checkedIcon, "iconSize", this);
        animation->setDuration(300);
        d_ptr->_uncheckedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_checkedIcon, "iconSize", this);
        animation->setDuration(1300);
        d_ptr->_checkedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_checkedIcon, "opacity", this);
        animation->setDuration(440);
        d_ptr->_checkedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_checkedIcon, "opacity", this);
        animation->setDuration(440);
        d_ptr->_uncheckedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_unCheckedIcon, "opacity", this);
        animation->setDuration(440);
        d_ptr->_checkedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_unCheckedIcon, "opacity", this);
        animation->setDuration(440);
        d_ptr->_uncheckedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_unCheckedIcon, "color", this);
        animation->setDuration(440);
        d_ptr->_checkedTransition->addAnimation(animation);

        animation = new QPropertyAnimation(d_ptr->_unCheckedIcon, "color", this);
        animation->setDuration(440);
        d_ptr->_uncheckedTransition->addAnimation(animation);

    }

    QtComponentsCheckBox::~QtComponentsCheckBox()
    {

    }



}
