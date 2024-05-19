/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "Gates/inputgate.h"

InputGate::InputGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
}

void InputGate::calculateOutput()
{
    setOutputState(inputStates[0]);
}

void InputGate::setInputPortState(int port, bool state)
{
    if(port == 0)
    {
        inputStates[0] = state;
        inputChanged();
    }
}
