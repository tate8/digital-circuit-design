// #include "DrawableGates/drawableoutputgate.h"

// DrawableOutputGate::DrawableOutputGate(OutputGate* gate) : DrawableGate(gate)
// {
// }

// int DrawableOutputGate::getInputOffsetX(int input)
// {
//     return 23;
// }

// int DrawableOutputGate::getInputOffsetY(int input)
// {
//     return 40;
// }

// int DrawableOutputGate::getOutputOffsetX()
// {
//     return 5000;
// }

// int DrawableOutputGate::getOutputOffsetY()
// {
//     return 5000;
// }

// QPixmap DrawableOutputGate::getImage()
// {
//     QMap<int,Gate*> inputs = this->getGate()->inputs;
//     if(inputs.empty())
//     {
//         return QPixmap(":/gates/OutPutGateSpriteNoConnection.png").scaled(170,80);
//     }else {
//         int state = this->getGate()->getOutputState();
//         if(state == 1)
//         {
//             return QPixmap(":/gates/OutPutGateSpriteOn.png").scaled(170,80);

//         }else
//         {
//             return QPixmap(":/gates/OutPutGateSpriteOff.png").scaled(170,80);
//         }
//     }
// }

// QSize DrawableOutputGate::getBounds()
// {
//     return QSize(170,80);
// }

// int DrawableOutputGate::getNumInputs()
// {
//     return 1;
// }
