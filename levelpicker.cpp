#include "levelpicker.h"
#include "ui_levelpicker.h"

LevelPicker::LevelPicker(AnimationWorld* world, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelPicker)
    , world(world)

{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this](){
        update();
    });
    timer->start(30);
}

LevelPicker::~LevelPicker()
{
    delete ui;
    delete timer;
}

void LevelPicker::paintEvent(QPaintEvent *event)
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

void LevelPicker::resizeEvent(QResizeEvent *event)
{
    if (world)
    {
        world->resizeWorld(size().width(), size().height());
    }
    QWidget::resizeEvent(event);
}
