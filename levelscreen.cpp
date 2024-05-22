#include "levelscreen.h"
#include "ui_levelscreen.h"
#include "GateTypes.h"
#include <QPushButton>
#include <QPainter>
#include <QDialog>

LevelScreen::LevelScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelScreen)
    , model()
    , table(new TruthTable)
    , animation(new AnimationWorld())
{
    ui->setupUi(this);

    connect(ui->runButton, &QPushButton::clicked, this, [this](){
        std::vector<bool> expected { false, false, false, false };
        model.run(expected);
    });

    // Add Gate Buttons
    connect(ui->andButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::AndGateType);
    });
    connect(ui->orButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::OrGateType);
    });
    connect(ui->notButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::NotGateType);
    });
    connect(ui->norButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::NorGateType);
    });
    connect(ui->xorButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::XorGateType);
    });
    connect(ui->nandButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::NandGateType);
    });
    connect(ui->outputButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::SandboxOutputGateType);
    });

    // Updating Circuit Canvas based on model changes
    connect(&model, &CircuitModel::gateAdded, ui->circuitCanvas, &CircuitCanvas::addDrawableGate);
    connect(&model, &CircuitModel::gateRemoved, ui->circuitCanvas, &CircuitCanvas::removeDrawableGate);
    connect(&model, &CircuitModel::gateUpdated, ui->circuitCanvas, &CircuitCanvas::updateDrawableGate);
    connect(&model, &CircuitModel::wireAdded, ui->circuitCanvas, &CircuitCanvas::addDrawableWire);
    connect(&model, &CircuitModel::wireRemoved, ui->circuitCanvas, &CircuitCanvas::removeDrawableWire);
    connect(&model, &CircuitModel::wireUpdated, ui->circuitCanvas, &CircuitCanvas::updateDrawableWire);

    // Updating the model based on Circuit Canvas
    connect(ui->circuitCanvas, &CircuitCanvas::requestedConnection, &model, &CircuitModel::addWireConnection);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteGate, &model, &CircuitModel::removeGateAndConnections);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteWire, &model, qOverload<int>(&CircuitModel::removeWireConnection));
    connect(ui->circuitCanvas, &CircuitCanvas::requestedToggleInput, &model, &CircuitModel::toggleInputGateValue);
    connect(this, &LevelScreen::prepareLevel, &model, [this](){
        // Reset model state
        model.reset(2);
    });

    // Connect utility buttons to circuit canvas
    connect(ui->zoomSlider, &QSlider::valueChanged, this, [this](int position){
        const double minZoom = 0.1;
        const double maxZoom = 2.0;
        double zoomLevel = minZoom + (maxZoom - minZoom) * (position / 100.0);
        ui->circuitCanvas->zoomToValue(zoomLevel);
    });


    model.reset(2);
}

LevelScreen::~LevelScreen()
{
    delete ui;
    delete table;
}

void LevelScreen::prepareSandbox(bool mode)
{
    emit prepareLevel();
    // setup level to sandbox mode
    if(mode == 1)
    {
        ui->runButton->hide();
        ui->norButton->show();
        ui->xorButton->show();
        ui->nandButton->show();
        ui->outputButton->show();
    }
    // reset screen to level mode
    else
    {
        ui->runButton->show();
        ui->norButton->hide();
        ui->xorButton->hide();
        ui->nandButton->hide();
        ui->outputButton->hide();

    }
}

void LevelScreen::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen(Qt::black, 2);
    painter.setPen(pen);

    if (runWasSuccessful)
    {
        for (const auto& pair : animation->getConfettiBodies())
        {
            b2Vec2 position = pair.first->GetPosition();
            int x = static_cast<int>(position.x * animation->SCALE - 5);
            int y = static_cast<int>(300 - position.y * animation->SCALE - 5);

            painter.setBrush(pair.second);
            painter.drawRect(x, y, 10, 10);
        }
    }
}

void LevelScreen::startConfetti()
{
    this->runWasSuccessful = true;
    int centerX = this->width() / 2;
    int centerY = this->height();
    centerY = this->height() - centerY;
    animation->createConfetti(centerX, centerY);
    animation->startConfetti();

    QTimer* animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &LevelScreen::stopConfetti);
    animationTimer->setSingleShot(true);
    animationTimer->start(3000); // play for 3 sec.
}

void LevelScreen::stopConfetti()
{
    this->runWasSuccessful = false;
    this->update();
}

void LevelScreen::updateConfetti()
{
    this->update();
}
