/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "wire.h"

int Wire::nextId = 0;

Wire::Wire(Gate* startGate, Gate* endGate, int inputPort, QObject *parent) :
    QObject(parent),
    startGate(startGate),
    endGate(endGate),
    inputPort(inputPort)
{
    id = nextId++;
    endGate->addInput(startGate, inputPort);

    // Connect the start gate's output
    connect(startGate, &Gate::outputChanged, this, &Wire::onInputChanged);

    onInputChanged(startGate->getOutputState());
}

Wire::~Wire()
{
    // Disconnect and remove inputs
    if (startGate)
    {
        disconnect(startGate, &Gate::outputChanged, this, &Wire::onInputChanged);
    }
    if (endGate)
    {
        endGate->removeInput(inputPort);
    }

    emit removed();
}

void Wire::onInputChanged(bool newState)
{
    value = newState;
    endGate->setInputPortState(inputPort, newState);

    emit updated();
}

bool Wire::getValue()
{
    return value;
}
