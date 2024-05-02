/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "notgate.h"

NotGate::NotGate(QObject* parent, GateType type) : Gate(parent, type)
{
    // Default to false
    inputStates[0] = false;
}

void NotGate::calculateOutput()
{
    // Logical NOT functionality is implemented with !
    setOutputState(!inputStates[0]);
}

void NotGate::setInputPortState(int port, bool state)
{
    if (port == 0)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
