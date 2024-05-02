#include "levelpicker.h"
#include "ui_levelpicker.h"

LevelPicker::LevelPicker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelPicker)
{
    ui->setupUi(this);

    // Initialize Animation World with the ui width and height dimensions
    world = new AnimationWorld(size().width(), size().height());
    timer = new QTimer(this);

    // Run the simulation while on the level-picker screen
    connect(timer, &QTimer::timeout, this, &LevelPicker::updateAnimation);
    timer->start(30);
}

LevelPicker::~LevelPicker()
{
    delete ui;
    delete timer;
}

void LevelPicker::updateAnimation()
{
    world->simulateWorld();
    update();
}

void LevelPicker::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QPixmap andGate1(":/rainbowGates/andRed.png");
    QPixmap andGate2(":/rainbowGates/andOrange.png");
    QPixmap andGate3(":/rainbowGates/andYellow.png");
    QPixmap andGate4(":/rainbowGates/andGreen.png");
    QPixmap andGate5(":/rainbowGates/andBlue.png");
    QPixmap andGate6(":/rainbowGates/andPurple.png");
    QPixmap andGate7(":/rainbowGates/andPink.png");

    QPixmap orGate1(":/rainbowGates/orRed.png");
    QPixmap orGate2(":/rainbowGates/orOrange.png");
    QPixmap orGate3(":/rainbowGates/orYellow.png");
    QPixmap orGate4(":/rainbowGates/orGreen.png");
    QPixmap orGate5(":/rainbowGates/orBlue.png");
    QPixmap orGate6(":/rainbowGates/orPurple.png");
    QPixmap orGate7(":/rainbowGates/orPink.png");

    QPixmap notGate1(":/rainbowGates/notRed.png");
    QPixmap notGate2(":/rainbowGates/notOrange.png");
    QPixmap notGate3(":/rainbowGates/notYellow.png");
    QPixmap notGate4(":/rainbowGates/notGreen.png");
    QPixmap notGate5(":/rainbowGates/notBlue.png");
    QPixmap notGate6(":/rainbowGates/notPurple.png");
    QPixmap notGate7(":/rainbowGates/notPink.png");

    int gateWidth = 100; // Set the width for all gate images
    QVector<QPixmap> gateImages = {
        andGate1.scaledToWidth(gateWidth),
        andGate2.scaledToWidth(gateWidth),
        andGate3.scaledToWidth(gateWidth),
        andGate4.scaledToWidth(gateWidth),
        andGate5.scaledToWidth(gateWidth),
        andGate6.scaledToWidth(gateWidth),
        andGate7.scaledToWidth(gateWidth),
        orGate1.scaledToWidth(gateWidth),
        orGate2.scaledToWidth(gateWidth),
        orGate3.scaledToWidth(gateWidth),
        orGate4.scaledToWidth(gateWidth),
        orGate5.scaledToWidth(gateWidth),
        orGate6.scaledToWidth(gateWidth),
        orGate7.scaledToWidth(gateWidth),
        notGate1.scaledToWidth(gateWidth),
        notGate2.scaledToWidth(gateWidth),
        notGate3.scaledToWidth(gateWidth),
        notGate4.scaledToWidth(gateWidth),
        notGate5.scaledToWidth(gateWidth),
        notGate6.scaledToWidth(gateWidth),
        notGate7.scaledToWidth(gateWidth)
    };

    int i = 0;
    for (auto body : world->getBodies())
    {
        b2Vec2 position = body->GetPosition();
        float pixelX = position.x * world->SCALE;
        float pixelY = position.y * world->SCALE;
        float angle = body->GetAngle() * (180.0 / M_PI);

        painter.save();
        painter.translate(pixelX, pixelY);
        painter.rotate(angle);
        painter.drawPixmap(-gateImages[i].width() / 2, -gateImages[i].height() / 2, gateImages[i]);
        painter.restore();

        // Increment and wrap i
        i = (i + 1) % gateImages.size();
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
