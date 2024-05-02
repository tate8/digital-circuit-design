#ifndef OUTPUTGATE_H
#define OUTPUTGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "Gate.h"

/// @brief The OutputGate class is a subclass of Gate.
/// It implements specific logic to compute its output
class OutputGate : public Gate
{
public:
    /// @brief Creates a new Output Gate
    OutputGate(QObject* parent = nullptr, GateType type = GateType::OutputGateType);

    /// @brief No output on a output gate
    void calculateOutput() override;

    /// @brief 1 input which controls what is displayed on the gate and the truth table
    void setInputPortState(int port, bool state) override;

private:
    /// @brief The list of inputs to the Output gate
    bool inputStates[1];
};

#endif // OUTPUTGATE_H
