#ifndef SANDBOXINPUTGATE_H
#define SANDBOXINPUTGATE_H

#include "Gates/gate.h"

class SandboxInputGate : public Gate
{
public:
    /// @brief Creates a new SandboxInput Gate
    SandboxInputGate(QObject* parent = nullptr, GateType type = GateType::InputGateType);

    /// @brief Constant bit output
    void calculateOutput() override;

    /// @brief Input state will be decided by user input
    void setInputPortState(int port, bool state) override;


private:
    /// @brief The list of inputs to the gate
    bool inputStates[1];
};

#endif // SANDBOXINPUTGATE_H
