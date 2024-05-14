#ifndef ANDGATE_H
#define ANDGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "Gates/gate.h"

/// @brief The AndGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class AndGate : public Gate
{
public:
    /// @brief Creates an AndGate
    AndGate(QObject* parent = nullptr, GateType type = GateType::AndGateType);

    /// @brief Implements logical AND functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:
    /// @brief The list of inputs to the AND gate
    bool inputStates[2];
};

#endif
