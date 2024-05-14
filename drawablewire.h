#ifndef DRAWABLEWIRE_H
#define DRAWABLEWIRE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Leo Ramirez

#include "DrawableGates/drawablegate.h"

/// \brief The DrawableWire class hold methods to deal with the drawable state of a wire
/// as well as a Gates to record the connections of this wire
class DrawableWire
{
private:
    /// \brief line holds the x and y location of the wire
    QLineF line;

    /// \brief startGate a Gate reference to the start gate of this wire
    Gate* startGate;

    /// \brief endGate a Gate reference to the end of this wire
    Gate* endGate;

    /// \brief inputPort an int for the start gate this wire is connected to
    int inputPort;

public:
    /// \brief DrawableWire A constructor
    /// \param startGate a Gate for the start of the wire
    /// \param endGate a Gate for the end of the wire
    /// \param inputPort a int for th eport the start of the wire is connected to
    /// \param start a Qpoint for the x and y begginig of this wire
    /// \param end a Qpoint for the x and y end of this wire
    DrawableWire(Gate* startGate, Gate* endGate, int inputPort, QPoint start, QPoint end);

    /// \brief getLine Gets the line of this obgect
    /// \return a QLineF object holding this objects x and y locations
    QLineF getLine();

    /// \brief getStartGate gets the gate this cable comes from
    /// \return a Gate
    Gate* getStartGate();

    /// \brief getEndGate gets the gate this cable ends at
    /// \return a Gate
    Gate* getEndGate();

    /// \brief getInputPort gets the port this wire's start comes from
    /// \return an int
    int getInputPort();

    /// \brief collision detects wether this wire crasshes against the point at the given x and y
    /// \param x an int for the x location
    /// \param y and int for the y location
    /// \return a bool
    bool collision(int x, int y);
};

#endif // DRAWABLEWIRE_H
