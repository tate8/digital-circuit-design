/// CS3505 - Digital Circuit Design Game
/// Reviewed by leo Ramirez

#include "circuitcanvas.h"
#include "DrawableGates/drawableandgate.h"
#include "DrawableGates/drawablenotgate.h"
#include "DrawableGates/drawableorgate.h"
#include "DrawableGates/drawableinputgate.h"
#include "DrawableGates/drawableoutputgate.h"
#include "DrawableGates/drawablenorgate.h"
#include "DrawableGates/drawablexorgate.h"
#include "DrawableGates/drawablenandgate.h"
#include "DrawableGates/drawablesandboxoutputgate.h"
#include <QMouseEvent>
#include <QPainter>

CircuitCanvas::CircuitCanvas(QWidget *parent) : QWidget(parent)
{
    this->setMouseTracking(true);
    hoveredInPin = -1;
    hoveredGate = nullptr;
    selectedInPin = -1;
    selectedGate = nullptr;
    hoveredWire = nullptr;
    machine = CanvasStateMachine::DEFAULT;
    tutorialImage = 0;
    this->setFocusPolicy(Qt::StrongFocus);
}

CircuitCanvas::~CircuitCanvas()
{
}

void CircuitCanvas::resetState()
{
    for (DrawableGate* gate : gates)
    {
        delete gate;
    }
    for (DrawableWire* wire : wires)
    {
        delete wire;
    }
    outputGate1 = nullptr;
    inputGate1 = nullptr;
    inputGate2 = nullptr;
    gates.clear();
    wires.clear();
    update();
}

void CircuitCanvas::tutorialOpened(int tutorial)
{
    tutorialImage = tutorial;
    update();
}

void CircuitCanvas::tutorialClosed()
{
    tutorialImage = 0;
    update();
}

DrawableGate* CircuitCanvas::getGateAtPos(int x, int y)
{
    for (DrawableGate* gate : gates)
    {
        //Check is whithin bounds
        if(x > gate->getPos().x() && x < gate->getPos().x() + gate->getBounds().width() &&
            y > gate->getPos().y() && y < gate->getPos().y() + gate->getBounds().height())
        {
            return gate;
        }
    }

    //no gate found
    return nullptr;
}

void CircuitCanvas::insertAndGate(AndGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableAndGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertNorGate(NorGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableNorGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertSandboxOutputGate(SandboxOutputGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableSandboxOutputGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertXorGate(XorGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableXorGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertNandGate(NandGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableNandGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertOrGate(OrGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableOrGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertNotGate(NotGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    gates[gate] = new DrawableNotGate(gate);

    ///Check to ensure a new gate isn't accidentally made
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertInputGate(InputGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    if(inputGate1 == nullptr)
    {
        inputGate1 = new drawableInputGate(gate);
        gates[gate] = inputGate1;
        x = -40;
        y = 100;
    }
    else if(inputGate2 == nullptr)
    {
        inputGate2 = new drawableInputGate(gate);
        gates[gate] = inputGate2;
        x = -40;
        y = 280;
    }
    else
        return;

    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::insertOutputGate(OutputGate* gate, int x, int y)
{
    DrawableGate* prevGate = gates.value(gate);
    if(outputGate1 == nullptr)
    {
        outputGate1 = new DrawableOutputGate(gate);
        gates[gate] = outputGate1;
        x = 900;
        y = 200;
    }
    if (prevGate)
    {
        gates[gate]->setPos(prevGate->getPos().x(), prevGate->getPos().y());
    }
    else
    {
        gates[gate]->setPos(x, y);
    }

    circuitUpdated();
}

void CircuitCanvas::circuitUpdated()
{
    for(auto wire : wires)
    {
        delete wire;
    }
    wires.clear();

    ///update the values of the connections of the wires
    for (DrawableGate* gate : gates)
    {
        for (auto it = gate->getGate()->inputs.begin(); it != gate->getGate()->inputs.end(); ++it)
        {
            int input = it.key();
            Gate* endGate = it.value();

            wires.push_back(new DrawableWire(gate->getGate(), endGate, input, gates[endGate]->getOutputPos(), gate->getInputPos(input)));
        }
    }

    update();
}


void CircuitCanvas::mousePressEvent(QMouseEvent *event)
{
    //Determines what the next state of the machine should be based on the current states
    if(machine == CanvasStateMachine::ONGATE || machine == CanvasStateMachine::ONINPIN || machine == CanvasStateMachine::ONOUTPIN)
    {
        selectedGate = hoveredGate;
    }
    if(machine == CanvasStateMachine::ONINPIN || machine == CanvasStateMachine::ONOUTPIN)
    {
        dragStartPos = mousePos;
    }
    if(machine == CanvasStateMachine::ONGATE)
    {
        machine = CanvasStateMachine::DRAG;
    }
    else if(machine == CanvasStateMachine::ONINPIN)
    {
        selectedInPin = hoveredInPin;
        machine = CanvasStateMachine::CONNECTTOOUT;
    }
    else if(machine == CanvasStateMachine::ONOUTPIN)
    {
        machine = CanvasStateMachine::CONNECTTOIN;
    }

    update();
}

void CircuitCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    ///Change the values of the output gates when clicked
    if(hoveredGate != nullptr && hoveredGate->getGate()->type == GateType::InputGateType && machine != CanvasStateMachine::CONNECTTOIN && machine != CanvasStateMachine::CONNECTTOOUT)
    {
        bool state = hoveredGate->getGate()->getOutputState();
        if(hoveredGate == inputGate1) {
            emit requestedChangeInput(true, !state);
        }
        else if(hoveredGate == inputGate2) {
            emit requestedChangeInput(false, !state);
        }
    }
    // Output port being connected to input port
    else if(machine == CanvasStateMachine::CONNECTTOIN)
    {
        if(hoveredGate != nullptr)
        {
            if(hoveredGate != selectedGate && hoveredInPin != -1) {
                emit requestedConnection(selectedGate->getGate(),hoveredGate->getGate(), hoveredInPin);
            }
            else if(hoveredGate == selectedGate && hoveredOutput) {
                // Recover hover state
                machine = CanvasStateMachine::ONOUTPIN;
            }
        }
    }
    // Input port being connected to output port
    else if(machine == CanvasStateMachine::CONNECTTOOUT)
    {
        if(hoveredGate != nullptr)
        {
            if(hoveredGate != selectedGate && selectedInPin != -1 && hoveredOutput) {
                emit requestedConnection(hoveredGate->getGate(), selectedGate->getGate(), selectedInPin);
            }
            else if(hoveredGate == selectedGate && hoveredInPin != -1) {
                // Recover hover state
                machine = CanvasStateMachine::ONINPIN;
            }
        }
    }
    // not trying to make a connection
    if(machine == CanvasStateMachine::DRAG || machine == CanvasStateMachine::CONNECTTOIN || machine == CanvasStateMachine::CONNECTTOOUT)
    {
        selectedGate = nullptr;
        machine = CanvasStateMachine::DEFAULT;
    }

    update();
}

void CircuitCanvas::mouseMoveEvent(QMouseEvent *event)
{
    mousePos = event->pos();

    // Update hovered elements
    hoveredInPin = -1;
    hoveredOutput = false;
    hoveredGate = getGateAtPos(mousePos.x(), mousePos.y());
    hoveredWire = nullptr;

    // Check whether any wire is hovered
    for(auto wire : wires)
    {
        if(wire->collision(mousePos.x(), mousePos.y()))
        {
            hoveredWire = wire;
            break;
        }
    }

    //The pointer is currently on a gate
    if(hoveredGate != nullptr)
    {
        if(machine == CanvasStateMachine::DEFAULT || machine == CanvasStateMachine::ONWIRE)
        {
            machine = CanvasStateMachine::ONGATE;
        }
        //Check the positions of the ports for the hovered gate
        for(int input = 0; input < hoveredGate->getNumInputs(); input++)
        {
            QPoint inputPos = hoveredGate->getInputPos(input);

            if(mousePos.x() > inputPos.x() - pinBounds && mousePos.x() < inputPos.x() + pinBounds &&
                mousePos.y() > inputPos.y() - pinBounds && mousePos.y() < inputPos.y() + pinBounds)
            {
                hoveredInPin = input;
                //If there was an overlap, pointer is on a port
                if(machine == CanvasStateMachine::DEFAULT || machine == CanvasStateMachine::ONGATE ||
                    machine == CanvasStateMachine::ONWIRE || machine == CanvasStateMachine::ONOUTPIN)
                {
                    machine = CanvasStateMachine::ONINPIN;
                }
                break;
            }
            else if(machine == CanvasStateMachine::ONINPIN)
            {
                machine = CanvasStateMachine::ONGATE;
            }
        }

        QPoint outputPos = hoveredGate->getOutputPos();

        if(mousePos.x() > outputPos.x() - pinBounds && mousePos.x() < outputPos.x() + pinBounds &&
            mousePos.y() > outputPos.y() - pinBounds && mousePos.y() < outputPos.y() + pinBounds)
        {
            hoveredOutput = true;
            if(machine == CanvasStateMachine::DEFAULT || machine == CanvasStateMachine::ONGATE ||
                machine == CanvasStateMachine::ONWIRE || machine == CanvasStateMachine::ONINPIN)
            {
                machine = CanvasStateMachine::ONOUTPIN;
            }
        }
        else if(machine == CanvasStateMachine::ONOUTPIN)
        {
            machine = CanvasStateMachine::ONGATE;
        }
    }
    // Pointer is on a wire
    else if(hoveredWire != nullptr && machine != CanvasStateMachine::CONNECTTOIN && machine != CanvasStateMachine::CONNECTTOOUT) {
        machine = CanvasStateMachine::ONWIRE;
    }
    // Pointer is on nothing
    else if(machine == CanvasStateMachine::ONGATE || machine == CanvasStateMachine::ONINPIN || machine == CanvasStateMachine::ONOUTPIN || machine == CanvasStateMachine::ONWIRE)
    {
        machine = CanvasStateMachine::DEFAULT;
    }

    // Make gate follow mouse
    if(machine == CanvasStateMachine::DRAG)
    {
        if(selectedGate->getGate()->type != GateType::InputGateType && selectedGate->getGate()->type != GateType::OutputGateType)
        {
            selectedGate->setPos(mousePos.x() - selectedGate->getBounds().width() / 2, mousePos.y() - selectedGate->getBounds().height() / 2);
        }

        // Update wire positions
        circuitUpdated();
        return;
    }

    update();
}

void CircuitCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // Draw gates
    for(DrawableGate* gate : gates)
    {
        painter.drawPixmap(QRect(gate->getPos(), gate->getBounds()), gate->getImage());
    }

    // Draw wires
    for(DrawableWire* wire : wires)
    {
        if(hoveredWire == wire)
        {
            painter.setPen(hoveredWirePen());
        }
        else if(wire->getEndGate()->getOutputState())
        {
            QPen penG(Qt::green);
            penG.setWidth(2);
            painter.setPen(penG);
        }
        else
        {
            QPen penR(Qt::red);
            penR.setWidth(2);
            painter.setPen(penR);
        }

        painter.drawLine(wire->getLine());
    }

    // Draw square on hover
    if(hoveredGate != nullptr)
    {
        painter.setPen(hoverSquarePen());
        painter.drawRect(QRect(hoveredGate->getPos(), hoveredGate->getBounds()));
    }

    // Draw circle on input on hover
    if(machine == CanvasStateMachine::ONINPIN)
    {
        QPoint inputPos = hoveredGate->getInputPos(hoveredInPin);
        painter.setPen(hoveredPinPen());
        inputPos.setX(inputPos.x() + 6);

        if(hoveredGate->getGate()->type==GateType::OutputGateType)
        {
            painter.drawEllipse(inputPos, 12, 12);
        }else
        {
            painter.drawEllipse(inputPos, 6, 6);
        }
    }

    // Draw circle on output on hover
    else if(machine == CanvasStateMachine::ONOUTPIN)
    {
        if(hoveredGate->getGate()->type == GateType::OutputGateType){return;}
        QPoint outputPos = hoveredGate->getOutputPos();
        painter.setPen(hoveredPinPen());
        outputPos.setX(outputPos.x() - 6);

        if(hoveredGate->getGate()->type==GateType::InputGateType)
        {
            painter.drawEllipse(outputPos, 12, 12);
        }else
        {
            painter.drawEllipse(outputPos, 5, 5);
        }
    }

    // Draw selected input pin
    else if(machine == CanvasStateMachine::CONNECTTOOUT)
    {
        QPoint inputPos = selectedGate->getInputPos(selectedInPin);
        painter.setPen(selectedPinPen());
        inputPos.setX(inputPos.x() + 6);
        painter.drawEllipse(inputPos, 3, 3);

        // Draw on hover only for outputs in different gate
        if(hoveredGate != nullptr && hoveredOutput) {
            if(selectedGate == hoveredGate) return;

            QPoint outputPos = hoveredGate->getOutputPos();
            painter.setPen(hoveredPinPen());
            outputPos.setX(outputPos.x() - 6);
            painter.drawEllipse(outputPos, 4, 4);
        }
    }

    // Draw selected output pin
    else if(machine == CanvasStateMachine::CONNECTTOIN)
    {
        QPoint outputPos = selectedGate->getOutputPos();
        painter.setPen(selectedPinPen());
        outputPos.setX(outputPos.x() - 6);
        painter.drawEllipse(outputPos, 4, 4);

        // Draw on hover only for inputs in different gate
        if(hoveredGate != nullptr && hoveredInPin != -1)
        {
            if(selectedGate == hoveredGate) return;

            QPoint inputPos = hoveredGate->getInputPos(hoveredInPin);
            painter.setPen(hoveredPinPen());
            inputPos.setX(inputPos.x() + 6);
            painter.drawEllipse(inputPos, 4, 4);
        }
    }

    // Draw creating wire
    if(machine == CanvasStateMachine::CONNECTTOIN || machine == CanvasStateMachine::CONNECTTOOUT)
    {
        painter.setPen(wirePen());
        painter.drawLine(dragStartPos, mousePos);
    }

    // calculating dimensions to fit robot image on different sized windows
    int windowWidth = this->width();
    int windowHeight = this->height();

    int pixmapWidth = 300;
    int pixmapHeight = 300;

    int rightX = windowWidth - (windowWidth / 10) - pixmapWidth;
    int secondImageY = (windowHeight - pixmapHeight) / 2;


    // And Gate tutorial images
    if (tutorialImage == 1)
    {
        painter.drawPixmap(QRect(QPoint(0,-80), QSize(200,200)), QPixmap(":/robot/robot_point.png").scaled(200, 200));
        painter.drawPixmap(QRect(QPoint(rightX, secondImageY), QSize(pixmapWidth, pixmapHeight)), QPixmap(":/robot/robot_and.png").scaled(pixmapWidth, pixmapHeight));
    }

    // Or Gate tutorial images
    if (tutorialImage == 2)
    {
        painter.drawPixmap(QRect(QPoint(0,0), QSize(200,200)), QPixmap(":/robot/robot_point.png").scaled(200, 200));
        painter.drawPixmap(QRect(QPoint(rightX, secondImageY), QSize(pixmapWidth, pixmapHeight)), QPixmap(":/robot/robot_or.png").scaled(pixmapWidth, pixmapHeight));
    }

    // Not Gate tutorial images
    if (tutorialImage == 3)
    {
        painter.drawPixmap(QRect(QPoint(0,80), QSize(200,200)), QPixmap(":/robot/robot_point.png").scaled(200, 200));
        painter.drawPixmap(QRect(QPoint(rightX, secondImageY), QSize(pixmapWidth, pixmapHeight)), QPixmap(":/robot/robot_not.png").scaled(pixmapWidth, pixmapHeight));
    }
}

void CircuitCanvas::keyPressEvent(QKeyEvent *event)
{
    if (event->key() != Qt::Key_Backspace)
        return;

    // Deleting a GAte
    if (hoveredGate != nullptr)
    {
        GateType gateType = hoveredGate->getGate()->type;
        if(gateType == GateType::InputGateType || gateType == GateType::OutputGateType)
            return;

        emit requestedDeleteGate(hoveredGate->getGate());
        gates.remove(hoveredGate->getGate());
        delete hoveredGate->getGate();
        hoveredGate = nullptr;
        update();
    }
    // Deleting a wire
    else if(machine == CanvasStateMachine::ONWIRE && hoveredWire != nullptr)
    {
        emit requestedDeleteWire(hoveredWire->getStartGate(), hoveredWire->getEndGate(), hoveredWire->getInputPort());
        hoveredWire = nullptr;
    }
}


