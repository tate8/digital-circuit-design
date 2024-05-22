/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily
#include "homescreen.h"
#include "ui_homescreen.h"
#include "mainwindow.h"
#include "animationworld.h"
#include <QPainter>

HomeScreen::HomeScreen(MainWindow* window, AnimationWorld* world, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HomeScreen)
    , world(world)
{
    Q_UNUSED(window);

    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        update();
    });
    timer->start(30);

}

HomeScreen::~HomeScreen()
{
    delete ui;
    delete timer;
}

void HomeScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
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
    if (world)
    {
        world->resizeWorld(size().width(), size().height());
    }
    QWidget::resizeEvent(event);
}
