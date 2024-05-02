/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "nandgate.h"

NandGate::NandGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
    inputStates[1] = false;
}

void NandGate::calculateOutput()
{
    setOutputState(!(inputStates[0] && inputStates[1]));
}

void NandGate::setInputPortState(int port, bool state)
{
    if (port >= 0 && port < 2)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
