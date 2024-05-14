#include <QRect>
#include <QPixmap>
#include "Gates/gate.h"

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Christina Cao

#ifndef DRAWABLEGATE_H
#define DRAWABLEGATE_H

/// \brief The DrawableGate class is an abstract class that represents a drawable logic gate
///
/// This class is the base class for the various logic gates that will position, obtain input and output positions
/// and set the gate's image.
class DrawableGate
{
private:
    /// \brief gate a Gate pointer to this gate
    Gate* gate;

    /// \brief pos a QPoint object with the X,Y coordinates of this gate
    QPoint pos;

protected:
    /// \brief getInputOffsetX Gets the offset value for the X position of the specified input port
    /// \param input an int for which port to get the offset for
    /// \return an int for the offset
    virtual int getInputOffsetX(int input) = 0;

    /// \brief getInputOffsetY Gets the offset value for the Y position of the specified input port
    /// \param input an int for which port to get the offset for
    /// \return an int for the offset
    virtual int getInputOffsetY(int input)= 0;

    /// \brief getOutputOffsetX Gets the offset value for the X position of the specified output port
    /// \return an int for the offset
    virtual int getOutputOffsetX() = 0;

    /// \brief getOutputOffsetY Gets the offset value for the Y position of the specified output port
    /// \return an int for the offset
    virtual int getOutputOffsetY() = 0;

public:
    DrawableGate(Gate* gate);
    virtual ~DrawableGate() {}

    /// \brief getPos Gets the cucrrent positions of this gate
    /// \return a QPoint object with the X,Y coordinates of this gate
    QPoint getPos();

    /// \brief setPos Sets the cucrrent positions of this gate
    /// \param x an int for the x positions
    /// \param y an int for the y position
    void setPos(int x, int y);

    /// \brief getInputPos Gets the input position of the specified port
    /// \param input an int for the ID of the port
    /// \return a QPoint object of the X,Y position of the port
    QPoint getInputPos(int input);

    /// \brief getOutputPos Gets the output position of the port
    /// \return a QPoint object of the X,Y position of the port
    QPoint getOutputPos();

    /// \brief getBounds Gets the bounds of this gate
    /// \return a QSize object with the bounds
    virtual QSize getBounds() = 0;

    /// \brief getImage Gets the image for this gate
    /// \return a QPixmap object with the image
    virtual QPixmap getImage() = 0;

    /// \brief getNumInputs Gets how many input ports this gate has
    /// \return and int with the number of ports
    virtual int getNumInputs() = 0;

    Gate* getGate();
};
#endif // DRAWABLEGATE_H
