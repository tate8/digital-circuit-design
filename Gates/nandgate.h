#ifndef NANDGATE_H
#define NANDGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "Gates/gate.h"

/// @brief The NandGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class NandGate : public Gate
{
public:
    /// @brief Creates a new Nand Gate
    NandGate(QObject* parent = nullptr, GateType type = GateType::NandGateType);

    /// @brief Implement NAND functionality
    void calculateOutput() override;

    /// @brief Sets the state of the specified input port
    /// @param port - The port to set
    /// @param state - The new state
    void setInputPortState(int port, bool state) override;

private:
    /// @brief The list of inputs to the Nand gate
    bool inputStates[2];
};

#endif // NANDGATE_H
