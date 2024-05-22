#include "levelscreen.h"
#include "ui_levelscreen.h"
#include "GateTypes.h"
#include <QPushButton>
#include <QPainter>
#include <QDialog>
#include <QMessageBox>


LevelScreen::LevelScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelScreen)
    , model()
{
    ui->setupUi(this);

    connect(ui->runButton, &QPushButton::clicked, this, [this](){
        model.run(currentConfig.expectedResults);
    });

    connect(&model, &CircuitModel::runSuccess, this, &LevelScreen::handleRunSuccess);
    connect(&model, &CircuitModel::runFailure, this, &LevelScreen::handleRunFailure);

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
    // Connect utility buttons to circuit canvas
    connect(ui->zoomSlider, &QSlider::valueChanged, this, [this](int position){
        const double minZoom = 0.1;
        const double maxZoom = 2.0;
        double zoomLevel = minZoom + (maxZoom - minZoom) * (position / 100.0);
        ui->circuitCanvas->zoomToValue(zoomLevel);
    });
}

LevelScreen::~LevelScreen()
{
    delete ui;
}

void LevelScreen::handleRunSuccess()
{
    // Create a QMessageBox
    QMessageBox successBox;
    successBox.setWindowTitle("Congratulations!");
    successBox.setText("You have completed the level successfully.");

    // Set a custom icon
    successBox.setIconPixmap(QPixmap(":/images/success_icon.png"));

    // Add a detailed message
    successBox.setInformativeText("Well done! You can now proceed to the next level.");

    // Add a "Close" button
    QPushButton* closeButton = successBox.addButton(tr("Close"), QMessageBox::AcceptRole);
    closeButton->setStyleSheet("QPushButton { color: white; background-color: #4CAF50; border: none; padding: 8px 16px; }"
                               "QPushButton:hover { background-color: #45a049; }");

    // Connect the button to close the message box
    connect(closeButton, &QPushButton::clicked, &successBox, &QMessageBox::close);

    // Set the size of the message box
    successBox.setMinimumWidth(400);

    // Set the font size and style
    QFont font = successBox.font();
    font.setPointSize(12);
    font.setBold(true);
    successBox.setFont(font);

    // Show the message box
    successBox.exec();
}

void LevelScreen::handleRunFailure()
{
}

void LevelScreen::setupLevel(const TutorialConfig& config)
{
    currentConfig = config;  // Store the config

    // Set title text
    ui->titleText->setText(QString::fromStdString(config.titleText));

    // Set tutorial text
    ui->tutorialText->setText(QString::fromStdString(config.tutorialText));

    // Reset the model with the number of inputs specified in the config
    model.reset(config.numInputs);

    // Set allowed gates
    ui->andButton->setVisible(false);
    ui->orButton->setVisible(false);
    ui->notButton->setVisible(false);
    ui->norButton->setVisible(false);
    ui->xorButton->setVisible(false);
    ui->nandButton->setVisible(false);
    ui->outputButton->setVisible(false);

    for (const auto& gateType : config.allowedGates) {
        switch (gateType) {
        case GateType::AndGateType:
            ui->andButton->setVisible(true);
            break;
        case GateType::OrGateType:
            ui->orButton->setVisible(true);
            break;
        case GateType::NotGateType:
            ui->notButton->setVisible(true);
            break;
        case GateType::NorGateType:
            ui->norButton->setVisible(true);
            break;
        case GateType::XorGateType:
            ui->xorButton->setVisible(true);
            break;
        case GateType::NandGateType:
            ui->nandButton->setVisible(true);
            break;
        case GateType::SandboxOutputGateType:
            ui->outputButton->setVisible(true);
            break;
        default:
            break;
        }
    }
}
