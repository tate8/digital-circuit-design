/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "inputgate.h"

InputGate::InputGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = true;
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
