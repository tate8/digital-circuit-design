/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily
#include "homescreen.h"
#include "ui_homescreen.h"
#include "mainwindow.h"
#include "animationworld.h"
#include <QPainter>

HomeScreen::HomeScreen(MainWindow* window, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeScreen)
    , sandbox(window)
{

    ui->setupUi(this);

    // Initialize Animation World with the ui width and height dimensions
    world = new AnimationWorld(size().width(), size().height());
    timer = new QTimer(this);

    // Run the simulation while on the level-picker screen
    connect(timer, &QTimer::timeout, this, &HomeScreen::updateAnimation);
    timer->start(30);

}

void HomeScreen::updateAnimation()
{
    world->simulateWorld();
    update();
}


HomeScreen::~HomeScreen()
{
    delete ui;
    delete timer;
}

void HomeScreen::openSandbox()
{
    stack.setCurrentWidget(sandbox);
}

void HomeScreen::openHomeMenu()
{
    stack.setCurrentWidget(this);
}

void HomeScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    int gateWidth = 100; // Set the width for all gate images

    for (auto body : world->getBodies())
    {
        // Get the position and angle of the body
        b2Vec2 position = body->GetPosition();
        float pixelX = position.x * world->SCALE;
        float pixelY = position.y * world->SCALE;
        float angle = body->GetAngle() * (180.0 / M_PI);

        QString imageString = world->getImageForBody(body);
        if (imageString.isEmpty()) {
            continue; // Skip if invalid
        }

        QPixmap image(imageString);
        image = image.scaledToWidth(gateWidth);

        // Draw the selected gate image
        painter.save();
        painter.translate(pixelX, pixelY);
        painter.rotate(angle);
        painter.drawPixmap(-image.width() / 2, -image.height() / 2, image);
        painter.restore();
    }
}

void HomeScreen::resizeEvent(QResizeEvent *event)
{
    if (world) {
        world->resizeWorld(size().width(), size().height());
    }
    QWidget::resizeEvent(event);
}
