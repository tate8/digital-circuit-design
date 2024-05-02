/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "orgate.h"

OrGate::OrGate(QObject* parent, GateType type) : Gate(parent, type)
{
    // Default to false
    inputStates[0] = false;
    inputStates[1] = false;
}

void OrGate::calculateOutput()
{
    // Logical OR functionality is implemented with ||
    setOutputState(inputStates[0] || inputStates[1]);
}

void OrGate::setInputPortState(int port, bool state)
{
    if (port >= 0 && port < 2)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
