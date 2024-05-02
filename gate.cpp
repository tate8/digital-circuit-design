/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "gate.h"

int Gate::nextId = 0;

Gate::Gate(QObject* parent, GateType type) :
    QObject(parent),
    type(type),
    outputState(false)
{
    id = nextId++;
}

void Gate::setOutputState(bool state)
{
    if (outputState != state)
    {
        outputState = state;
        emit outputChanged(outputState);
    }
}

bool Gate::getOutputState() const
{
    return outputState;
}

void Gate::addInput(Gate* newInput, int inputPort)
{
    inputs[inputPort] = newInput;
    connect(newInput, &Gate::outputChanged, this, &Gate::inputChanged);
}

void Gate::removeInput(int inputPort)
{
    if (inputs.contains(inputPort)) {
        Gate* inputGate = inputs.value(inputPort);

        // Disconnect the connection
        disconnect(inputGate, &Gate::outputChanged, this, &Gate::inputChanged);

        // Remove the gate from the inputs
        inputs.remove(inputPort);
    }
}

void Gate::inputChanged()
{
    calculateOutput();
}
