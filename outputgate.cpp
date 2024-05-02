/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "outputgate.h"

OutputGate::OutputGate(QObject* parent, GateType type) : Gate(parent,type)
{
    inputStates[0] = false;
}

void OutputGate::calculateOutput()
{
    setOutputState(inputStates[0]);
}

void OutputGate::setInputPortState(int port, bool state)
{
    if(port == 0)
    {
        inputStates[0] = state;
        inputChanged();
    }
}
