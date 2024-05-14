#ifndef ORGATE_H
#define ORGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "Gates/gate.h"

/// @brief The OrGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class OrGate : public Gate
{
public:
    /// @brief Creates an OrGate
    OrGate(QObject* parent = nullptr, GateType type = GateType::OrGateType);

    /// @brief Implements logical OR functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:
    /// @brief The list of inputs to the OR gate
    bool inputStates[2];
};

#endif
