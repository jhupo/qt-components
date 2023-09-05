#include "qtcomponentsradiobutton.h"
#include "lib/qtcomponentstheme.h"

namespace Components {

    QtComponentsRadioButton::QtComponentsRadioButton(QWidget *parent)
        : QtComponentsCheckBox(parent)
    {
        setCheckedIcon(QtComponentsTheme::icon("checkable","checked","radiobutton"));
        setUnCheckedIcon(QtComponentsTheme::icon("checkable","outline","radiobutton"));
    }

    QtComponentsRadioButton::~QtComponentsRadioButton()
    {

    }




}
