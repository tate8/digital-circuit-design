#ifndef CIRCUITCANVAS_H
#define CIRCUITCANVAS_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Leo Ramirez

#include <QWidget>
#include <QVector>
#include <QPen>
#include "DrawableGates/drawablegate.h"
#include "DrawableGates/drawableinputgate.h"
#include "Gates/andgate.h"
#include "drawablewire.h"
#include "Gates/orgate.h"
#include "DrawableGates/drawableoutputgate.h"
#include "Gates/sandboxoutputgate.h"
#include "Gates/inputgate.h"
#include "Gates/notgate.h"
#include "Gates/norgate.h"
#include "Gates/nandgate.h"
#include "Gates/xorgate.h"

/// \brief A stateless circuit canvas widget
class CircuitCanvas : public QWidget
{
    Q_OBJECT
public:
    /// \brief CircuitCanvas Constructor
    explicit CircuitCanvas(QWidget *parent = nullptr);

    /// \brief Destructor
    ~CircuitCanvas();

    /// \brief The CanvasStateMachine enum Possible estates of where the cursor
    /// is currently located
    enum CanvasStateMachine
    {
        DEFAULT, ONGATE, ONINPIN, ONOUTPIN, ONWIRE, DRAG, CONNECTTOIN, CONNECTTOOUT
    };

    /// \brief Clears the state of the canvas
    void resetState();

private:
    /// \brief gates A Map with all the gates in the circuit and a corresponding value of a drawable gate
    QMap<Gate*, DrawableGate*> gates;

    /// \brief A vector with all wires
    QVector<DrawableWire*> wires;

    /// \brief getGateAtPos Gets the gate at the specified x and y position
    /// \param x an int for the x position
    /// \param y an int for the y position
    /// \return the corresponding drawable gate to this gate
    DrawableGate* getGateAtPos(int x, int y);

    /// \brief Input gates for levels
    drawableInputGate* inputGate1 = nullptr;

    /// \brief Input gates for levels
    drawableInputGate* inputGate2 = nullptr;

    /// \brief outputGate1 Outout gate for levels
    DrawableOutputGate* outputGate1 = nullptr;

    /// \brief mousePos X and Y position
    QPoint mousePos;

    /// \brief dragStartPos X and Y position of where drag was started
    QPoint dragStartPos;

    /// \brief hoveredGate a DrawableGate for the end gate of the connection
    DrawableGate* hoveredGate;

    /// \brief selectedGate a DrawableGate for the start gate from which the connection is coming
    DrawableGate* selectedGate;

    /// \brief hoveredWire a DrawableWire for the wire the pointer is currently hovering over
    DrawableWire* hoveredWire;

    /// \brief hoveredOutPin int value of the pin currently hovering over
    bool hoveredOutput;

    /// \brief hoveredInPin int value of the pin currently hovering over
    int hoveredInPin;

    /// \brief selectedInPin int value of the pin currently selected
    int selectedInPin;

    /// \brief tutorialImage int value of tutorial message to be displayed
    int tutorialImage;

    /// \brief machine A CanvasStateMachine that hold the value of the current state of the cursor
    CanvasStateMachine machine;

    /// \brief pinBounds and int that determines the radious of the pin's bounds
    static const int pinBounds = 15;

    //settings for the drawing pens

    static QPen wirePen() {
        static QPen pen(Qt::black);
        pen.setWidth(3);
        return pen;
    }

    static QPen hoveredPinPen() {
        QPen pen(Qt::red);
        pen.setWidth(4);
        return pen;
    }

    static QPen selectedPinPen() {
        QPen pen(Qt::blue);
        pen.setWidth(3);
        return pen;
    }

    static QPen hoverSquarePen() {
        QPen pen(Qt::blue);
        pen.setStyle(Qt::DashLine);
        return pen;
    }

    static QPen hoveredWirePen() {
        QPen pen(Qt::blue);
        pen.setWidth(4);
        return pen;
    }

protected:
    /// \brief Handles mouse press events on the canvas
    void mousePressEvent(QMouseEvent *event) override;

    /// \brief Handles mouse release events on the canvas
    void mouseReleaseEvent(QMouseEvent *event) override;

    /// \brief Handles mouse movement events on the canvas
    void mouseMoveEvent(QMouseEvent *event) override;

    /// \brief Renders the canvas and its contents
    void paintEvent(QPaintEvent *event) override;

    /// \brief Handles key press events
    void keyPressEvent(QKeyEvent *event) override;


public slots:
    /// \brief insertAndGate Creates a new AND gate
    /// \param gate a AndGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertAndGate(AndGate* gate, int x = 0, int y = 0);

    /// \brief insertOrGate Creates a new OR gate
    /// \param gate a OrGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertOrGate(OrGate* gate, int x = 0, int y = 0);

    /// \brief insertOrGate Creates a new OR gate
    /// \param gate a OrGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertNorGate(NorGate* gate, int x = 0, int y = 0);

    /// \brief insertOrGate Creates a new OR gate
    /// \param gate a OrGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertXorGate(XorGate* gate, int x = 0, int y = 0);

    /// \brief insertOrGate Creates a new OR gate
    /// \param gate a OrGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertNandGate(NandGate* gate, int x = 0, int y = 0);

    /// \brief insertSandboxOutputGate Creates a new OUTPUT gate for the sandbox
    /// \param gate a OrGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertSandboxOutputGate(SandboxOutputGate* gate, int x = 0, int y = 0);

    /// \brief insertOrGate Creates a new NOT gate
    /// \param gate a NotGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertNotGate(NotGate* gate, int x = 0, int y = 0);

    /// \brief insertInputGate Creates a new input gate
    /// \param gate a InputGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertInputGate(InputGate* gate, int x = 0, int y =0);

    /// \brief intserOutputGate creates a new output gate
    /// \param a outputGate pointer to the new gate
    /// \param x an int x position for the gate
    /// \param y an int y position for the gate
    void insertOutputGate(OutputGate* gate, int x = 0, int y = 0);

    /// \brief tutorialOpened updates paint and determines which tutorial images are displayed
    /// \param an int value representing which tutorial is up
    void tutorialOpened(int tutorial);

    /// \brief tutorialClosed updates paint to remove tutorial images
    void tutorialClosed();

    /// \brief circuitUpdated Makes the circuit update the values, positions and conections,
    /// of all gates and wires.
    void circuitUpdated();

signals:
    /// \brief requestedConnection Signals for a new connection between the two gates to be created
    /// \param startGate a Gate where the connection originates
    /// \param endGate a Gate with the destination of the connection
    /// \param inputPort and int for which port to connect
    void requestedConnection(Gate* startGate, Gate* endGate, int inputPort);

    /// \brief requestedDeleteGate Signals for the a gate to be deleted
    /// \param gate the gate to be removed
    void requestedDeleteGate(Gate* gate);

    /// \brief requestedDeleteWire Signals for the wire connected to these 2 gates to be deleted
    /// \param startGate a Gate from which the wire is coming
    /// \param endGate a Gate in which the wire ends
    /// \param inputPort int the port from which the wire is originating
    void requestedDeleteWire(Gate* startGate, Gate* endGate, int inputPort);

    /// \brief Emitted when a input is changed
    /// \param changeFirstGate - If the first gate should be changed, otherwise the second
    /// \param newValue - The new value
    void requestedChangeInput(bool changeFirstGate, bool newValue);

};

#endif // CIRCUITCANVAS_H
