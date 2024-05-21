/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "circuitmodel.h"
#include "Gates/andgate.h"
#include "Gates/orgate.h"
#include "Gates/inputgate.h"
#include "Gates/outputgate.h"
#include "Gates/sandboxoutputgate.h"
#include "Gates/notgate.h"
#include "Gates/nandgate.h"
#include "Gates/xorgate.h"
#include "Gates/norgate.h"
#include <memory>

CircuitModel::CircuitModel(QObject* parent) : QObject(parent)
{
}

CircuitModel::~CircuitModel()
{
}

bool CircuitModel::simulateCircuit(bool value1, bool value2)
{
    auto inputGate1 = findGateById(inputGate1Id)->get();
    auto inputGate2 = findGateById(inputGate2Id)->get();
    auto outputGate = findGateById(outputGateId)->get();

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
    auto inputGate1 = findGateById(inputGate1Id)->get();
    auto inputGate2 = findGateById(inputGate2Id)->get();
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
    auto inputGate1 = findGateById(inputGate1Id)->get();
    auto inputGate2 = findGateById(inputGate2Id)->get();
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

void CircuitModel::addWireConnection(int outputGateId, int inputGateId, int port)
{
    // Check if wire already exists and exit if so
    bool found = false;
    for (auto const& wire : wires)
    {
        if (wire.get()->endGate->id == inputGateId &&
            wire.get()->inputPort == port)
        {
            found = true;
        }
    }
    if (found)
    {
        return;
    }

    // Create new wire
    auto outputGate = findGateById(outputGateId)->get();
    auto inputGate = findGateById(inputGateId)->get();

    auto newWire = std::make_unique<Wire>(outputGate, inputGate, port);

    int newWireId = newWire.get()->id;
    bool newWireValue = newWire.get()->getValue();
    int newWireStartGateId = newWire.get()->startGate->id;
    int newWireEndGateId = newWire.get()->endGate->id;
    int newWirePort = newWire.get()->inputPort;

    // When wire changes, send signal
    connect(newWire.get(), &Wire::updated, this, [this, newWireId](bool value){
        emit wireUpdated(newWireId, value);
    });

    // When wire dies, send signal
    connect(newWire.get(), &Wire::removed, this, [this, newWireId](){
        emit wireRemoved(newWireId);
    });

    wires.push_back(std::move(newWire));
    emit wireAdded(newWireId, newWireValue, newWireStartGateId, newWireEndGateId, newWirePort);
}

void CircuitModel::reset()
{
    wires.clear();
    gates.clear();

    // Add input and output gates at the start
    inputGate1Id = addGate(GateType::InputGateType);
    inputGate2Id = addGate(GateType::InputGateType);
    outputGateId = addGate(GateType::OutputGateType);
}

int CircuitModel::addGate(GateType gateType)
{
    std::unique_ptr<Gate> newGate;
    // Add the correct gate depending on the input gate type
    switch (gateType)
    {
    case GateType::AndGateType:
        newGate = std::make_unique<AndGate>(nullptr);
        break;
    case GateType::OrGateType:
        newGate = std::make_unique<OrGate>(nullptr);
        break;
    case GateType::NotGateType:
        newGate = std::make_unique<NotGate>(nullptr);
        break;
    case GateType::InputGateType:
        newGate = std::make_unique<InputGate>(nullptr);
        break;
    case GateType::OutputGateType:
        newGate = std::make_unique<OutputGate>(nullptr);
        break;
    case GateType::NorGateType:
        newGate = std::make_unique<NorGate>(nullptr);
        break;
    case GateType::XorGateType:
        newGate = std::make_unique<XorGate>(nullptr);
        break;
    case GateType::NandGateType:
        newGate = std::make_unique<NandGate>(nullptr);
        break;
    case GateType::SandboxOutputGateType:
        newGate = std::make_unique<SandboxOutputGate>(nullptr);
        break;
    default:
        assert(false);
        return -1;
    }

    int newGateId = newGate.get()->id;
    bool newGateValue = newGate.get()->getOutputState();
    GateType newGateType = gateType;

    // When gate changes, send signal
    connect(newGate.get(), &Gate::outputChanged, this, [this, newGateId](bool value){
        emit gateUpdated(newGateId, value);
    });

    // When gate dies, send signal
    connect(newGate.get(), &Gate::removed, this, [this, newGateId](){
        emit gateRemoved(newGateId);
    });

    gates.push_back(std::move(newGate));
    emit gateAdded(newGateId, newGateValue, newGateType);
    return newGateId;

}

void CircuitModel::removeGateAndConnections(int gateId)
{
    // Find all wires connected to this gate and remove them
    QList<int> wiresToRemove;
    for (auto const& wire : wires)
    {
        if (wire->endGate->id == gateId
            || wire->startGate->id == gateId)
        {
            wiresToRemove.append(wire->id);
        }
    }

    for (auto const& wireId : wiresToRemove)
    {
        removeWireConnection(wireId);
    }

    gates.erase(std::remove_if(gates.begin(), gates.end(),
                               [gateId](const std::unique_ptr<Gate>& gate) {
                                   return gate->id == gateId && gate->type != GateType::InputGateType && gate->type != GateType::OutputGateType;
                }),
                gates.end()
    );
}

void CircuitModel::removeWireConnection(int wireId)
{
    wires.erase(
        std::remove_if(wires.begin(), wires.end(),
                       [wireId](const std::unique_ptr<Wire>& wire) {
                           bool shouldRemove = wire->id == wireId;
                            if (shouldRemove) {
                               wire->onInputChanged(false);
                           }
                           return shouldRemove;
                        }),
            wires.end()
            );
}

std::unique_ptr<Gate>* CircuitModel::findGateById(int gateId) {
    for (auto& gate : gates) {
        if (gate->id == gateId) {
            return &gate;
        }
    }
    return nullptr; // Gate with the specified ID not found
}
