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
#include "QtCore/qdebug.h"
#include <memory>
#include <QEventLoop>
#include <QTimer>

CircuitModel::CircuitModel(QObject* parent) : QObject(parent), animationTimer(new QTimer(this))
{
}

CircuitModel::~CircuitModel()
{
}

bool CircuitModel::setInputs(const std::vector<bool>& inputs)
{
    if (inputs.size() != inputGateIds.size()) {
        qDebug() << "Wrong input size to CircuitModel::setInputs";
        return false;
    }

    for (size_t i = 0; i < inputGateIds.size(); i++)
    {
        int id = inputGateIds.at(i);
        int newValue = inputs.at(i);
        auto inputGate = findGateById(id)->get();
        inputGate->setOutputState(newValue);
    }

    auto outputGate = findGateById(outputGateId)->get();
    bool result = outputGate->getOutputState();
    return result;
}

void CircuitModel::setInputGateValue(int gateId, bool newValue)
{
    // Verify that the requested id is an input
    for (const auto& id : inputGateIds)
    {
        if (id == gateId)
        {
            auto inputGate = findGateById(id)->get();
            inputGate->setOutputState(newValue);
        }
    }
}

void CircuitModel::toggleInputGateValue(int gateId)
{
    // Verify that the requested id is an input
    for (const auto& id : inputGateIds)
    {
        if (id == gateId)
        {
            auto inputGate = findGateById(id)->get();
            inputGate->setOutputState(!inputGate->getOutputState());
        }
    }
}

void CircuitModel::run(const std::vector<bool>& expected)
{
    if (static_cast<int>(std::log2(expected.size())) != static_cast<int>(inputGateIds.size())) {
        qDebug() << "Wrong expected size to CircuitModel::run";
        return;
    }

    // Get a copy of all input values before the run
    std::vector<bool> prevInputValues;
    for (const auto& id : inputGateIds)
    {
        auto inputGate = findGateById(id)->get();
        bool inputGateValue = inputGate->getOutputState();
        prevInputValues.push_back(inputGateValue);
    }

    QEventLoop loop;
    connect(animationTimer, &QTimer::timeout, &loop, &QEventLoop::quit);

    // Iterate over all expected input combinations
    for (int i = 0; i < static_cast<int>(expected.size()); i++)
    {
        std::vector<bool> currentInputs;
        // Fill currentInputs with bits of i
        for (int bit = 0; bit < static_cast<int>(inputGateIds.size()); ++bit)
        {
            currentInputs.push_back((i >> bit) & 1);
        }

        bool result = setInputs(currentInputs);

        animationTimer->start(RUN_ANIMATION_DELAY_MS);
        loop.exec();

        if (result != expected[i])
        {
            for (size_t i = 0; i < inputGateIds.size(); i++)
            {
                auto inputGate = findGateById(inputGateIds.at(i))->get();
                inputGate->setOutputState(prevInputValues.at(i));
            }
            emit runFailure();
            return;
        }
    }

    for (size_t i = 0; i < inputGateIds.size(); i++)
    {
        auto inputGate = findGateById(inputGateIds.at(i))->get();
        inputGate->setOutputState(prevInputValues.at(i));
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

void CircuitModel::reset(int numInputs)
{
    wires.clear();
    gates.clear();

    // Add input and output gates at the start
    inputGateIds.clear();
    for (int i = 0; i < numInputs; i++)
    {
        inputGateIds.push_back(addGate(GateType::InputGateType));
    }

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
