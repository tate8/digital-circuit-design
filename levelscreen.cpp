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
    connect(ui->inputButton, &QPushButton::clicked, &model, [this](){
        model.addGate(GateType::SandboxInputGateType);
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
    QMessageBox box;
    box.setWindowTitle("Success");
    box.setText("Congratulations! You have completed the level successfully.");

    // Add a close button
    box.addButton(QMessageBox::Close);

    // Connect the button to close the message box
    QObject::connect(box.button(QMessageBox::Close), &QAbstractButton::clicked, &box, &QMessageBox::close);
    box.exec();
}

void LevelScreen::handleRunFailure()
{
    QMessageBox box;
    box.setWindowTitle("Try Again");
    box.setText("Oops! Your circuit didn't work as expected. Don't give up! Double-check your connections and logic gates, and give it another shot.");

    // Add a close button
    box.addButton(QMessageBox::Close);

    // Connect the button to close the message box
    QObject::connect(box.button(QMessageBox::Close), &QAbstractButton::clicked, &box, &QMessageBox::close);
    box.exec();
}

void LevelScreen::setupLevel(const TutorialConfig& config)
{
    currentConfig = config;  // Store the config

    // Set title text
    ui->titleText->setText(QString::fromStdString(config.titleText));

    // Set tutorial text
    ui->tutorialText->setText(QString::fromStdString(config.tutorialText));

    // Reset the model with the number of inputs specified in the config
    model.reset(config.numInputs, config.numOutputs);

    // Show tutorial text
    ui->tabWidget->setCurrentIndex(0);

    // Set allowed gates
    ui->andButton->setVisible(false);
    ui->orButton->setVisible(false);
    ui->notButton->setVisible(false);
    ui->norButton->setVisible(false);
    ui->xorButton->setVisible(false);
    ui->nandButton->setVisible(false);
    ui->inputButton->setVisible(false);
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
        case GateType::InputGateType:
            ui->inputButton->setVisible(true);
            break;
        case GateType::SandboxOutputGateType:
            ui->outputButton->setVisible(true);
            break;
        default:
            break;
        }
    }
}
