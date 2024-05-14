/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "Gates/andgate.h"

AndGate::AndGate(QObject* parent, GateType type) : Gate(parent, type)
{
    // Inputs default to false
    inputStates[0] = false;
    inputStates[1] = false;
}

void AndGate::calculateOutput()
{
    // Logical AND is implemented with &&
    setOutputState(inputStates[0] && inputStates[1]);
}

void AndGate::setInputPortState(int port, bool state)
{
    if (port >= 0 && port < 2)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
