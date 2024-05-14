#ifndef WIRE_H
#define WIRE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Tate Larkin

#include <QObject>
#include "Gates/gate.h"

/// @brief The Wire class represents a connection between two
/// logic gates in a digital circuit. The wire helps propogate
/// signals from one gate to another
class Wire : public QObject
{
    Q_OBJECT
public:
    /// @brief Instansiates a new wire from one gate to another
    /// @param startGate - The connection's start gate
    /// @param endGate - The connection's end gate
    /// @param inputPort - Which port on the endGate this wire connects
    Wire(Gate* startGate, Gate* endGate, int inputPort, QObject *parent = nullptr);

    /// @brief Destroys the wire, removing any connections
    ~Wire();

    /// @brief The id for the next wire which is created
    static int nextId;

    /// @brief This wire's id
    int id;

    /// @brief The gate the wire comes from
    Gate* startGate;

    /// @brief The gate the wire goes to
    Gate* endGate;

    /// @brief Identifies which input port of the gate this wire is connected to
    int inputPort;

public slots:
    /// @brief Called when the start gate's input changes.
    /// Sets the correct input port of the end gate to a specific value
    /// @param newState - The new value
    void onInputChanged(bool newState);
};

#endif
