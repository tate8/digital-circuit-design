#include "DrawableGates/drawableandgate.h"
#include "Gates/andgate.h"
#include <QPixmap>

constexpr int HEIGHT = 60;

DrawableAndGate::DrawableAndGate(AndGate* gate) : DrawableGate(gate) {}

int DrawableAndGate::getInputOffsetX(int input) {
    return 5;
}

int DrawableAndGate::getInputOffsetY(int input) {
    if(input == 0) {
        return HEIGHT * 0.2;
    }
    else if(input == 1) {
        return HEIGHT * 0.8;
    }

    return 0;
}

int DrawableAndGate::getOutputOffsetX() {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * HEIGHT / pixmap.height();
    return width - 5;
}

int DrawableAndGate::getOutputOffsetY() {
    return 30;
}

QPixmap DrawableAndGate::getImage() {
    return QPixmap(":/gatePorts/andGatePorts.png").scaledToHeight(HEIGHT, Qt::SmoothTransformation);
}

QSize DrawableAndGate::getBounds() const {
    QPixmap pixmap = QPixmap(":/gatePorts/andGatePorts.png");
    int width = pixmap.width() * HEIGHT / pixmap.height();
    return QSize(width, HEIGHT);}

int DrawableAndGate::getNumInputs() {
    return 2;
}
