#ifndef GATE_H
#define GATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include <QList>
#include <QMap>
#include <QObject>
#include <QPointF>
#include "GateTypes.h"

/// @brief The Gate class represents a digital gate in a circuit.
/// A gate has a list of inputs, and custom logic to compute an output
/// based on those inputs
class Gate : public QObject
{
    Q_OBJECT
public:
    /// @brief Instansiates a new gate
    /// @param type - The type of the new gate
    Gate(QObject* parent = nullptr, GateType type = GateType::GenericGateType);

    /// @brief Overridable method to calculate the output.
    /// Will depend on what type of gate it is
    virtual void calculateOutput() = 0;

    /// @brief Sets the input port state
    /// @param port - The index of which port to set
    /// @param state - The state to set the port to
    virtual void setInputPortState(int port, bool state) = 0;

    /// @brief Return the current output state
    bool getOutputState() const;

    /// @brief Adds a new input to the list of inputs
    /// @param newInput - The new input gate to add
    /// @param inputPort - The port to assign the input to
    void addInput(Gate* newInput, int inputPort);

    /// @brief Removes an input at specified port if it exists
    /// @param inputPort - The input port to remove
    void removeInput(int inputPort);

    /// @brief Sets the output state to a new value
    /// @param state - The new output state
    void setOutputState(bool state);

    /// @brief A map from input port to gate
    QMap<int, Gate*> inputs;

    /// @brief This gate's id
    int id;

    /// @brief The type of the gate
    GateType type;

protected:
    /// @brief The id for the next gate which is created
    static int nextId;

private:
    /// @brief The current output state
    bool outputState;

signals:
    /// @brief Emitted when the current output changes
    /// @param newOutput - The new output
    void outputChanged(bool newOutput);

public slots:
    /// @brief Slot for when an input has changed
    void inputChanged();
};

#endif // GATE_H
