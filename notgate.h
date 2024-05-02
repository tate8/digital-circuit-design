#ifndef NOTGATE_H
#define NOTGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include "gate.h"

/// @brief The NotGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class NotGate : public Gate
{
public:
    /// @brief Creates a NotGate
    NotGate(QObject* parent = nullptr, GateType type = GateType::NotGateType);

    /// @brief Implements logical NOT functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:
    /// @brief Creates an NotGate. Not only requires one input
    bool inputStates[1];
};

#endif
