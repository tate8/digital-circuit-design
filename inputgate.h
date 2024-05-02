#ifndef INPUTGATE_H
#define INPUTGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include "Gate.h"

/// @brief The Input class is a subclass of Gate.
/// It implements specific logic to compute its output
class InputGate : public Gate
{
public:
    /// @brief Creates a new Input Gate
    InputGate(QObject* parent = nullptr, GateType type = GateType::InputGateType);

    /// @brief Constant bit output
    void calculateOutput() override;

    /// @brief Input state will be decided by user input
    void setInputPortState(int port, bool state) override;


private:
    /// @brief The list of inputs to the Input gate
    bool inputStates[1];
};

#endif // INPUTGATE_H
