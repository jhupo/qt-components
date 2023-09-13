#ifndef __QTCOMPONENTSTEXTFIEDLD_P_H__
#define __QTCOMPONENTSTEXTFIEDLD_P_H__

#include <QtGlobal>

namespace Components {

    class QtComponentsTextField;
    class QtComponentsTextFieldLabel;
    class QtComponentsTextFieldStateMachine;

    class QtComponentsTextFieldPrivate
    {
        Q_DISABLE_COPY(QtComponentsTextFieldPrivate)
        Q_DECLARE_PUBLIC(QtComponentsTextField)

    public:

        QtComponentsTextFieldPrivate(QtComponentsTextField* q);
        ~QtComponentsTextFieldPrivate();

        void init();

        QtComponentsTextField*const                     q_ptr;
        QtComponentsTextFieldStateMachine *             _stateMachine;
        QtComponentsTextFieldLabel        *             _label;
        QString                                         _labelString;
        qreal                                           _labelFontSize;
        bool                                            _showLabel;
        bool                                            _showInputLine;

    };

}

#endif
