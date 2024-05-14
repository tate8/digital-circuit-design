#ifndef DRAWABLEXORGATE_H
#define DRAWABLEXORGATE_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Christina Cao

#include "DrawableGates/drawablegate.h"
#include "Gates/xorgate.h"

/// \brief This class represents a drawable XOR gate that can be drawn on the circuit canvas
class DrawableXorGate : public DrawableGate
{
protected:
    /// \brief getInputOffsetX Gets the offset value for the X position of the specified input port
    /// \param input an int for which port to get the offset for
    /// \return an int for the offset
    virtual int getInputOffsetX(int input);

    /// \brief getInputOffsetY Gets the offset value for the Y position of the specified input port
    /// \param input an int for which port to get the offset for
    /// \return an int for the offset
    virtual int getInputOffsetY(int input);

    /// \brief getOutputOffsetX Gets the offset value for the X position of the specified output port
    /// \return an int for the offset
    virtual int getOutputOffsetX();

    /// \brief getOutputOffsetY Gets the offset value for the Y position of the specified output port
    /// \return an int for the offset
    virtual int getOutputOffsetY();

public:
    /// \brief constructor
    DrawableXorGate(XorGate* gate);

    /// \brief getBounds Gets the bounds of this gate
    /// \return a QSize object with the bounds
    virtual QSize getBounds();

    /// \brief getImage Gets the image for this gate
    /// \return a QPixmap object with the image
    virtual QPixmap getImage();

    /// \brief getNumInputs Gets how many input ports this gate has
    /// \return and int with the number of ports
    virtual int getNumInputs();
};
#endif // DRAWABLEXORGATE_H
