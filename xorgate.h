#ifndef XORGATE_H
#define XORGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "gate.h"

class XorGate : public Gate
{
public:
    XorGate(QObject* parent = nullptr, GateType type = GateType::XorGateType);

    /// @brief Implement XOR functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:

    /// @brief The list of inputs to the XOR gate
    bool inputStates[2];
};

#endif // XORGATE_H
