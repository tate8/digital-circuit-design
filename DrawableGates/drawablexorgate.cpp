// #include "DrawableGates/drawablexorgate.h"
// #include "Gates/xorgate.h"
// #include <QPixmap>

// DrawableXorGate::DrawableXorGate(XorGate* gate) : DrawableGate(gate)
// {
// }

// int DrawableXorGate::getInputOffsetX(int input) {
//     return 0;
// }

// int DrawableXorGate::getInputOffsetY(int input) {
//     if (input == 0) {
//         return 13;
//     } else if (input == 1) {
//         return 52;
//     }

//     return 0;
// }

// int DrawableXorGate::getOutputOffsetX() {
//     return 120;
// }

// int DrawableXorGate::getOutputOffsetY() {
//     return 33; // Adjusted output offset
// }

// QPixmap DrawableXorGate::getImage() {
//     return QPixmap(":/gatePorts/xorGatePorts.png").scaled(120, 120);
// }

// QSize DrawableXorGate::getBounds() {
//     return QSize(120, 65);
// }

// int DrawableXorGate::getNumInputs() {
//     return 2;
// }
