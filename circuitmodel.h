#ifndef CIRCUITMODEL_H
#define CIRCUITMODEL_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include <QObject>
#include "Gates/gate.h"
#include "wire.h"
#include "GateTypes.h"

/// @brief The CircuitModel holds all logic for a digital circuit
/// This includes things like adding and removing gates and wires, simulating
/// the circuit, etc.
class CircuitModel : public QObject
{
    Q_OBJECT
public:
    /// @brief Initializes a new CircuitModel
    CircuitModel(QObject* parent = nullptr);

    /// @brief Destroys the CircuitModel by cleaining up gates and wires
    ~CircuitModel();

private:
    /// @brief The list of circuit gates
    QList<Gate*> gates;

    /// @brief The list of circuit wires
    QList<Wire*> wires;

    /// @brief The first input gate
    Gate* inputGate1;

    /// @brief The second input gate
    Gate* inputGate2;

    /// @brief The output gate
    Gate* outputGate;

    /// @brief Simulates the circuit with given inputs, and returns the result
    /// @param input1 - The first input
    /// @param input2 - The second input
    bool simulateCircuit(bool input1, bool input2);

public slots:
    /// @brief Adds a connection between the output of a specified gate to the input of another
    /// @param outputGate - The gate whose output is being connected
    /// @param inputGate - The gate whose input is being connected
    /// @param port - The input port which is being connected to
    void addWireConnection(Gate* outputGate, Gate* inputGate, int port);

    /// @brief Prepares the level by clearing it then placing two input gates
    void reset();

    /// @brief Removes a wire from between two gates
    /// If the wire with the specified id doesn't exist, this method will exit
    /// @param wireId - The id of the wire to remove
    void removeWireConnection(int wireId);

    /// @brief Removes a wire from between two gates
    /// @param startGate - The wire's start gate
    /// @param endGate - The wire's end gate
    /// @param inputPort - Which port's input to remove
    void removeWireConnection(Gate* startGate, Gate* endGate, int inputPort);

    /// @brief Adds a gate to the circuit
    /// @param gateType - What type of gate to create
    /// @return A pointer to the new gate
    Gate* addGate(GateType gateType);

    /// @brief Removes a gate and its connections from the circuit
    /// @param gate - gate to remove
    void removeGateAndConnections(Gate* gate);

    /// @brief Changes the output value of the specified input gate
    /// @param shouldChangeFirstGate - If you should change the first gate, otherwise
    /// this changes the second gate
    /// @param newValue - The new boolean value to set it to
    void changeInputGateValue(bool shouldChangeFirstGate, bool newValue);

    /// @brief Runs the circuit on a truth table.
    /// Emits runSuccess or runFailure depending on the results
    /// @param expected - An array of 4 booleans representing the expected results
    /// when trying the circuit with inputs (0,0), (0,1), (1,0), and (1,1)
    void run(const QVector<bool>&);

signals:
    /// @brief Emitted when a gate is added
    /// @param gate - The new gate
    void gateAdded(Gate* gate);

    /// @brief Emitted when a gate is removed
    /// @param gate - The removed gate
    void gateRemoved(Gate* gate);

    /// @brief Emitted when a gate is updated
    /// @param gate - The updated gate
    void gateUpdated(Gate* gate);

    /// @brief Emitted when a wire is added
    /// @param wire - The added wire
    void wireAdded(Wire* wire);

    /// @brief Emitted when a wire is removed
    /// @param wire - The removed wire
    void wireRemoved(Wire* wire);

    /// @brief Emitted when a wire is updated
    /// @param wire - The updated wire
    void wireUpdated(Wire* wire);

    /// @brief Emitted when the circuit's run is a success
    void runSuccess();

    /// @brief Emitted when the circuit's run is a failure
    void runFailure();
};

#endif // CIRCUITMODEL_H
