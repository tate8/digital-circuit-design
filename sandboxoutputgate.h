#ifndef SANDBOXOUTPUTGATE_H
#define SANDBOXOUTPUTGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "gate.h"

/// @brief The Sandbox Output class is a subclass of Gate.
/// It implements an outputgate only for the sandbox mode
class SandboxOutputGate : public Gate
{
public:
    /// @brief Creates a new SandboxOutput Gate
    SandboxOutputGate(QObject* parent = nullptr, GateType type = GateType::SandboxOutputGateType);

    /// @brief No output on a output gate
    void calculateOutput() override;

    /// @brief 1 input which controls what is displayed on the gate and the truth table
    void setInputPortState(int port, bool state) override;

private:

    /// @brief The list of inputs to the Sandbox Output gate
    bool inputStates[1];
};


#endif // SANDBOXOUTPUTGATE_H
