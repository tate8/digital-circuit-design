#ifndef CIRCUITMODEL_H
#define CIRCUITMODEL_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include <QObject>
#include "Gates/gate.h"
#include "wire.h"
#include "GateTypes.h"
#include "memory"
#include <QTimer>

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

    static constexpr int RUN_ANIMATION_DELAY_MS = 500;

private:
    /// @brief The list of circuit gates
    std::vector<std::unique_ptr<Gate>> gates;

    /// @brief The list of circuit wires
    std::vector<std::unique_ptr<Wire>> wires;

    /// @brief The ids of the input gates
    std::vector<int> inputGateIds;

    /// @brief The output gate
    int outputGateId;

    /// @brief A timer for the run simulation animation
    QTimer* animationTimer;

    /// @brief Sets the circuit's inputs, and returns the result
    /// @param inputs - A list of the inputs to try
    bool setInputs(const std::vector<bool>& inputs);

    /// @brief Changes the output value of the specified input gate
    /// @param gateId - The id of the input gate to change
    /// @param newValue - The new boolean value to set it to
    void setInputGateValue(int gateId, bool newValue);

    /// @brief Gets a gate by its id
    /// @param gateId - The gate's id
    /// @return A pointer to the gate's unique pointer
    std::unique_ptr<Gate>* findGateById(int gateId);

public slots:
    /// @brief Adds a connection between the output of a specified gate to the input of another
    /// @param outputGateId - The id of the gate whose output is being connected
    /// @param inputGateId - The id of the gate whose input is being connected
    /// @param port - The input port which is being connected to
    void addWireConnection(int outputGateId, int inputGateId, int port);

    /// @brief Prepares the level by clearing it then placing two input gates
    /// @param numInputs - How many inputs should be added
    void reset(int numInputs);

    /// @brief Removes a wire from between two gates
    /// If the wire with the specified id doesn't exist, this method will exit
    /// @param wireId - The id of the wire to remove
    void removeWireConnection(int wireId);

    /// @brief Adds a gate to the circuit
    /// @param gateType - What type of gate to create
    /// @return The new gate's id
    int addGate(GateType gateType);

    /// @brief Removes a gate and its connections from the circuit
    /// @param gateId - The id of the gate to remove
    void removeGateAndConnections(int gateId);

    /// @brief Changes the output value of the specified input gate
    /// @param gateId - The id of the input gate to toggle
    void toggleInputGateValue(int gateId);

    /// @brief Runs the circuit on a truth table.
    /// Emits runSuccess or runFailure depending on the results
    /// @param expected - An array of booleans representing the expected results
    /// when trying the circuit with all combinations of inputs.
    /// If there are 4 inputs, for example, there should be 16 entries
    void run(const std::vector<bool>& expected);

signals:
    /// @brief Emitted when a gate is added
    /// @param gateId - The id of the gate
    /// @param value - The value of the gate
    /// @param type - The type of the gate
    void gateAdded(int gateId, bool value, GateType type);

    /// @brief Emitted when a gate is removed
    /// @param gateId - The id of the gate
    void gateRemoved(int gateId);

    /// @brief Emitted when a gate is updated
    /// @param gateId - The id of the gate
    /// @param value - The value of the gate
    void gateUpdated(int gateId, bool value);

    /// @brief Emitted when a wire is added
    /// @param wireId - The id of the wire
    /// @param value - The value of the wire
    /// @param startGateId - The id of the start gate
    /// @param endGateId - The id of the end gate
    /// @param port - Which port on the end gate the wire connects
    void wireAdded(int wireId, bool value, int startGateId, int endGateId, int port);

    /// @brief Emitted when a wire is removed
    /// @param wireId - The id of the wire
    void wireRemoved(int wireId);

    /// @brief Emitted when a wire is updated
    /// @param wireId - The id of the wire
    /// @param value - The value of the wire
    void wireUpdated(int wireId, bool value);

    /// @brief Emitted when the circuit's run is a success
    void runSuccess();

    /// @brief Emitted when the circuit's run is a failure
    void runFailure();
};

#endif // CIRCUITMODEL_H
