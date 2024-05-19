/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "circuitmodel.h"
#include "QtCore/qdebug.h"
#include "Gates/andgate.h"
#include "Gates/orgate.h"
#include "Gates/inputgate.h"
#include "Gates/outputgate.h"
#include "Gates/sandboxoutputgate.h"
#include "Gates/notgate.h"
#include "Gates/nandgate.h"
#include "Gates/xorgate.h"
#include "Gates/norgate.h"

CircuitModel::CircuitModel(QObject* parent) : QObject(parent)
{
}

CircuitModel::~CircuitModel()
{
    // Delete all wires
    wires.removeIf([](Wire* wire) {
        delete wire;
        return true;
    });

    // Delete all gates
    gates.removeIf([](Gate* gate) {
        delete gate;
        return true;
    });
}

bool CircuitModel::simulateCircuit(bool value1, bool value2)
{
    if (!inputGate1 || !inputGate2 || !outputGate)
    {
        return false;
    }
    // Keep track of previous values to restore
    bool prevInput1Value = inputGate1->getOutputState();
    bool prevInput2Value = inputGate2->getOutputState();

    // Set new outputs for the inputs
    // This will start the signal propogation
    inputGate1->setOutputState(value1);
    inputGate2->setOutputState(value2);

    // Get the result
    bool result = outputGate->getOutputState();

    // Set input back to normal
    inputGate1->setOutputState(prevInput1Value);
    inputGate2->setOutputState(prevInput2Value);

    return result;
}

void CircuitModel::setInputGateValue(int gateId, bool newValue)
{

    if (inputGate1->id == gateId)
    {
        inputGate1->setOutputState(newValue);
    }
    else
    {
        inputGate2->setOutputState(newValue);
    }
}

void CircuitModel::toggleInputGateValue(int gateId)
{
    if (inputGate1->id == gateId)
    {
        inputGate1->setOutputState(!inputGate1->getOutputState());
    }
    else
    {
        inputGate2->setOutputState(!inputGate2->getOutputState());
    }
}

void CircuitModel::run(const QVector<bool>& expected)
{
    // 00, 01, 10, 11
    for (int i = 0; i < 4; i++)
    {
        // Extracts the second least significant bit in i
        bool input1 = (i >> 1) & 1;
        // Extracts the least significant bit in i
        bool input2 = i & 1;

        bool result = simulateCircuit(input1, input2);

        if (result != expected[i])
        {
            emit runFailure();
            return;
        }
    }

    emit runSuccess();
}

void CircuitModel::addWireConnection(Gate* outputGate, Gate* inputGate, int port)
{
    // Check if wire already exists and exit if so
    bool found = false;
    for (const Wire* wire : wires)
    {
        if (wire->endGate->id == inputGate->id &&
            wire->inputPort == port)
        {
            found = true;
        }
    }
    if (found)
    {
        return;
    }

    // Create new wire
    Wire* newWire = new Wire(outputGate, inputGate, port);

    // When wire changes, send signal
    connect(newWire, &Wire::updated, this, [this, newWire](){
        emit wireUpdated(newWire);
    });

    // When wire dies, send signal
    connect(newWire, &Wire::removed, this, [this, newWire](){
        emit wireRemoved(newWire);
    });

    wires.append(newWire);
    emit wireAdded(newWire);
}

void CircuitModel::reset()
{

    // Remove all wires
    wires.removeIf([](Wire* wire)
    {
        delete wire;
        return true;
    });

    gates.removeIf([](Gate* gate) {
        delete gate;
        return true;
    });

    // Add input and output gates at the start
    inputGate1 = addGate(GateType::InputGateType);
    inputGate2 = addGate(GateType::InputGateType);
    outputGate = addGate(GateType::OutputGateType);
}

Gate* CircuitModel::addGate(GateType gateType)
{
    Gate* newGate;
    // Add the correct gate depending on the input gate type
    switch (gateType)
    {
    case GateType::AndGateType:
        newGate = new AndGate(nullptr);
        break;
    case GateType::OrGateType:
        newGate = new OrGate(nullptr);
        break;
    case GateType::NotGateType:
        newGate = new NotGate(nullptr);
        break;
    case GateType::InputGateType:
        newGate = new InputGate(nullptr);
        break;
    case GateType::OutputGateType:
        newGate = new OutputGate(nullptr);
        break;
    case GateType::NorGateType:
        newGate = new NorGate(nullptr);
        break;
    case GateType::XorGateType:
        newGate = new XorGate(nullptr);
        break;
    case GateType::NandGateType:
        newGate = new NandGate(nullptr);
        break;
    case GateType::SandboxOutputGateType:
        newGate = new SandboxOutputGate(nullptr);
        break;
    default:
        qDebug() << "Invalid gate type";
        return nullptr;
    }

    // When gate changes, send signal
    connect(newGate, &Gate::outputChanged, this, [this, newGate](){
        emit gateUpdated(newGate);
    });

    // When gate dies, send signal
    connect(newGate, &Gate::removed, this, [this, newGate](){
        emit gateRemoved(newGate);
    });

    gates.append(newGate);
    emit gateAdded(newGate);
    return newGate;
}

void CircuitModel::removeGateAndConnections(int gateId)
{
    Gate* gateToRemove = nullptr;
    for (auto& gate : gates)
    {
        if (gate->id == gateId)
        {
            gateToRemove = gate;
            break;
        }
    }

    // Disallow removing the input and output gates
    if(gateToRemove == nullptr || gateToRemove->type == GateType::InputGateType || gateToRemove->type == GateType::OutputGateType)
    {
        return;
    }

    // Find all wires connected to this gate and remove them
    QList<int> wiresToRemove;
    for (Wire* wire : wires)
    {
        if (wire->endGate->id == gateId
            || wire->startGate->id == gateId)
            wiresToRemove.append(wire->id);
    }

    for (int wireId : wiresToRemove)
    {
        removeWireConnection(wireId);
    }

    gates.removeOne(gateToRemove);
    delete gateToRemove;
}

void CircuitModel::removeWireConnection(Gate* startGate, Gate* endGate, int inputPort)
{
    if(endGate == nullptr)
        return;

    // Find the wire's id and remove it
    for (auto& wire : wires)
    {
        if (wire->startGate->id == endGate->id
            && wire->endGate->id == startGate->id
            && wire->inputPort == inputPort)
        {
            removeWireConnection(wire->id);
            break;
        }
    }
}

void CircuitModel::removeWireConnection(int wireId)
{
    // Find the wire to remove
    Wire* wireToRemove;
    for (auto& wire : wires)
    {
        if (wire->id == wireId)
        {
            wireToRemove = wire;
            break;
        }
    }

    wires.removeOne(wireToRemove);
    wireToRemove->onInputChanged(false);

    delete wireToRemove;
}
