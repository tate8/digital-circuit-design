/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "xorgate.h"

XorGate::XorGate(QObject* parent, GateType type) : Gate(parent, type)
{
    inputStates[0] = false;
    inputStates[1] = false;
}

void XorGate::calculateOutput()
{
    setOutputState(inputStates[0] ^ inputStates[1]);
}

void XorGate::setInputPortState(int port, bool state)
{
    if (port >= 0 && port < 2)
    {
        inputStates[port] = state;
        inputChanged();
    }
}
