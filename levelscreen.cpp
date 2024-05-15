#include "ui_leveltutorialdialog.h"
#include "levelscreen.h"
#include "ui_levelscreen.h"
#include "wire.h"
#include "GateTypes.h"
#include <QPushButton>
#include <QPainter>
#include <QDialog>
#include <qOverload>

LevelScreen::LevelScreen(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LevelScreen)
    , model()
    , table(new TruthTable)
    , animation(new AnimationWorld())
{
    ui->setupUi(this);

    // Hide the row header in table
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->verticalHeader()->setVisible(false);

    // Make columns fill available space
    QHeaderView* header = ui->tableWidget->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    // Tutorial modals
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
    connect(&model, &CircuitModel::gateAdded, this, [this](Gate* gate){
        ui->circuitCanvas->addDrawableGate(gate);
    });

    connect(&model, &CircuitModel::gateRemoved, this, [this](Gate* gate){
        ui->circuitCanvas->removeDrawableGate(gate);
    });

    connect(&model, &CircuitModel::gateUpdated, this, [this](Gate* gate){
        ui->circuitCanvas->updateDrawableGate(gate);
    });

    connect(&model, &CircuitModel::wireAdded, this, [this](Wire* wire){
        ui->circuitCanvas->addDrawableWire(wire);
    });

    connect(&model, &CircuitModel::wireRemoved, this, [this](Wire* wire){
        ui->circuitCanvas->removeDrawableWire(wire);
    });

    connect(&model, &CircuitModel::wireUpdated, this, [this](Wire* gate){
        ui->circuitCanvas->updateDrawableWire(gate);
    });

    // Updating the model based on Circuit Canvas
    connect(ui->circuitCanvas, &CircuitCanvas::requestedConnection, &model, &CircuitModel::addWireConnection);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteGate, &model, &CircuitModel::removeGateAndConnections);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteWire, &model, qOverload<Gate*, Gate*, int>(&CircuitModel::removeWireConnection));
    connect(ui->circuitCanvas, &CircuitCanvas::requestedChangeInput, &model, &CircuitModel::changeInputGateValue);
    connect(this, &LevelScreen::prepareLevel, &model, [this](){
        // Reset model state
        model.reset();
    });
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
        ui->tableFrame->hide();
        ui->button_3->hide();
        ui->norButton->show();
        ui->xorButton->show();
        ui->nandButton->show();
        ui->outputButton->show();
        ui->levelsButton->hide();
    }
    // reset screen to level mode
    else
    {
        ui->tableFrame->show();
        ui->button_3->show();
        ui->norButton->hide();
        ui->xorButton->hide();
        ui->nandButton->hide();
        ui->outputButton->hide();
         ui->levelsButton->show();

    }
}

void LevelScreen::updateTruthTableUI(QString tableHeader, const QVector<QVector<QString>> &data)
{
    ui->truthTableHeaderLabel->clear();
    ui->truthTableHeaderLabel->setText(tableHeader);
    ui->tableWidget->setRowCount(4);
    int columnCount = data.isEmpty() ? 0 : data[0].size();
    ui->tableWidget->setColumnCount(columnCount);

    // Sets the column names
    QStringList columnHeaders;
    columnHeaders << "Input A" << "Input B" << "Output Q";
    ui->tableWidget->setHorizontalHeaderLabels(columnHeaders);

    // Populate the table with new data
    for (int row = 0; row < data.size(); ++row)
    {
        for (int col = 0; col < data[row].size(); ++col)
        {
            QTableWidgetItem* item = new QTableWidgetItem(data[row][col]);
            ui->tableWidget->setItem(row, col, item);
        }
    }
}

void LevelScreen::runButtonClicked()
{
    if(!table->getCurrentTable().isEmpty())
    {
        QVector<bool> expectedResults = table->getCurrentTable();
        model.run(expectedResults);
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
    ui->truthTableHeaderLabel->setText("Circuit CORRECT!");
    ui->truthTableHeaderLabel->setStyleSheet(
        "border-style: solid;"
        "border-width: 5px 5px 3px 5px;"
        "border-color: #2A7F46;"
        "border-top-left-radius: 3px;"
        "border-top-right-radius: 3px;"
        "border-bottom-left-radius: 0px;"
        "border-bottom-right-radius: 0px;"
        "background-color: #34A853;"
        "color: white;"
        "font: bold 18px;"
        "padding: 5px;"
        "min-width: 50px;"
        "min-height: 30px;"
        );
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
