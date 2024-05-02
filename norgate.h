#ifndef NORGATE_H
#define NORGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "gate.h"

/// @brief The NorGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class NorGate : public Gate
{
public:
    /// @brief Creates a new Nor Gate
    NorGate(QObject* parent = nullptr, GateType type = GateType::NorGateType);

    /// @brief Implement NOR functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:
    /// @brief The list of inputs to the Nor gate
    bool inputStates[2];
};

#endif // NORGATE_H
