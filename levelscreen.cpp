#include "ui_leveltutorialdialog.h"
#include "levelscreen.h"
#include "leveltutorialdialog.h"
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
    , levelDialog(new Ui::LevelTutorialDialog)
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
    connect(ui->infoButton, &QPushButton::clicked, this, &LevelScreen::showTutorialModal);
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

    // Wires and Gates
    connect(ui->infoButton, &QPushButton::clicked, this, &LevelScreen::showTutorialBasedOnLevel);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedConnection, &model, &CircuitModel::addWireConnection);
    connect(&model, &CircuitModel::circuitChanged, this, &LevelScreen::updateCircuitCanvas);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteGate, &model, &CircuitModel::removeGateAndConnections);
    connect(ui->circuitCanvas, &CircuitCanvas::requestedDeleteWire, &model, qOverload<Gate*, Gate*, int>(&CircuitModel::removeWireConnection));
    connect(ui->circuitCanvas, &CircuitCanvas::requestedChangeInput, &model, &CircuitModel::changeInputGateValue);
    connect(this, &LevelScreen::prepareLevel, &model, [this](){
        // Reset model state
        model.prepareLevel();
        // Reset canvas state
        ui->circuitCanvas->resetState();
        // Reset model state
        model.prepareLevel();

        ui->truthTableHeaderLabel->setStyleSheet(
            "color: red;"
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


    });

    // Truth tables & Run Button
    connect(ui->button_3, &QPushButton::clicked, this, &LevelScreen::runButtonClicked);
    connect(table, &TruthTable::tableUpdated, this, &LevelScreen::updateTruthTableUI);
    connect(&model, &CircuitModel::runSuccess, this, &LevelScreen::startConfetti);
    connect(&model, &CircuitModel::runFailure, this, [this]() {
        ui->truthTableHeaderLabel->setText("Circuit INCORRECT!");
        ui->truthTableHeaderLabel->setStyleSheet(
            "border-style: solid;"
            "border-width: 5px 5px 3px 5px;"
            "border-color: #e3343c;"
            "border-top-left-radius: 3px;"
            "border-top-right-radius: 3px;"
            "border-bottom-left-radius: 0px;"
            "border-bottom-right-radius: 0px;"
            "background-color: #ff4d55;"
            "color: white;"
            "font: bold 18px;"
            "padding: 5px;"
            "min-width: 50px;"
            "min-height: 30px;"
            );
    });
    connect(animation, &AnimationWorld::confettiUpdated, this, &LevelScreen::updateConfetti);

    // Prepare Levels
    model.prepareLevel();
}

LevelScreen::~LevelScreen()
{
    delete ui;
    delete table;
}

void LevelScreen::showTutorialModal(int tutorial)
{
    emit prepareLevel();

    ui->circuitCanvas->tutorialOpened(tutorial);
    ui->tableWidget->clearContents();

    QString titleText = getTutorialTitleText(tutorial);
    QString descriptionText = getTutorialDescriptionText(tutorial);

    level = tutorial;

    LevelTutorialDialog *modal = new LevelTutorialDialog(this);
    ui->norButton->show();
    modal->ui->titleLabel->setText(titleText);
    modal->ui->descriptionLabel->setText(descriptionText);
    modal->exec();

    // Updates the truth table
    table->updateTableBasedOnLevel(tutorial);
    ui->circuitCanvas->tutorialClosed();
}

void LevelScreen::showTutorialBasedOnLevel()
{
    showTutorialModal(level);
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

void LevelScreen::updateCircuitCanvas(QList<Gate*> gates, QList<Wire*> wires)
{
    for (auto gate : gates)
    {
        switch (gate->type)
        {
        case GateType::AndGateType:
            ui->circuitCanvas->insertAndGate(dynamic_cast<AndGate*>(gate));
            break;
        case GateType::OrGateType:
            ui->circuitCanvas->insertOrGate(dynamic_cast<OrGate*>(gate));
            break;
        case GateType::NotGateType:
            ui->circuitCanvas->insertNotGate(dynamic_cast<NotGate*>(gate));
            break;
        case GateType::InputGateType:
            ui->circuitCanvas->insertInputGate(dynamic_cast<InputGate*>(gate));
            break;
        case GateType::OutputGateType:
            ui->circuitCanvas->insertOutputGate(dynamic_cast<OutputGate*>(gate));
            break;
        case GateType::NorGateType:
            ui->circuitCanvas->insertNorGate(dynamic_cast<NorGate*>(gate));
            break;
        case GateType::XorGateType:
            ui->circuitCanvas->insertXorGate(dynamic_cast<XorGate*>(gate));
            break;
        case GateType::NandGateType:
            ui->circuitCanvas->insertNandGate(dynamic_cast<NandGate*>(gate));
            break;
        case GateType::SandboxOutputGateType:
            ui->circuitCanvas->insertSandboxOutputGate(dynamic_cast<SandboxOutputGate*>(gate));
            break;
        default:
            break;
        }
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
        if (level == 3 )
        {
            model.runNot(expectedResults);
        }
        else
        {
            model.run(expectedResults);
        }
    }
    ui->circuitCanvas->setFocus();
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

QString LevelScreen::getTutorialTitleText(int tutorial)
{
    switch(tutorial)
    {
    case 4:
        return "Level 4: NAND (NOT-AND)";
        break;
    case 5:
        return "Level 5: NOR (NOT-OR)";
        break;
    case 6:
        return "Level 6: XOR (EXCLUSIVE OR)";
        break;
    case 7:
        return "Level 7: XNOR (EXCLUSIVE NOR)";
        break;
    case 8:
        return "CIRCUIT CRAFT PUZZLES";
        break;
    default:
        return "";
    }
}

QString LevelScreen::getTutorialDescriptionText(int tutorial)
{
    switch(tutorial)
    {
    case 4:
        return "Welcome to the fourth level of our circuit design game! Here, you’ll explore how a <b>NAND</b> gate functions.<br><br>"
               "<b>What is a NAND Gate?</b><br>"
               "<br>"
               "The <b>NAND gate</b> is a universal logic gate that outputs false (0) only when all its inputs are true; otherwise, it outputs a true (1) signal.<br>"
               "<br>"
               "<b>NAND</b> comes from “NOT AND”. In circuit design, this can be translated by connecting an AND gate followed by a NOT gate. The dual operation allows the <b>NAND gate</b> to function as a complete system, having the ability to construct any other type of logic gate or complex circuit.<br><br>"
               "<b>Getting Started:</b><br>"
               "<br>"
               "Identify the AND and NOT gates in the left sidebar and place them on the canvas.<br>"
               "Your task is to connect the inputs and output of the <b>NAND gate</b> correctly.<br>"
               "Refer to the truth table to understand how the circuit should be connected using Boolean equation (true (1), false (0)).<br>"
               "<br>"
               "Experiment with different configurations and click “Run” to see how your connections influence the result. Enjoy discovering how the <b>NAND gate</b> works through your own trials!";
    case 5:
        return "Welcome to the fifth level of our circuit design game! Here, you’ll explore how a <b>NOR</b> gate functions.<br><br>"
               "<b>What is a NOR Gate?</b><br>"
               "<br>"
               "The <b>NOR gate</b> is a fundamental digital logic gate that outputs true (1) only when all its inputs are false; otherwise, it outputs false (0).<br>"
               "<b>NOR</b> comes from “NOT OR”. In circuit design, this can be translated with an OR gate followed by a NOT gate. The dual operation allows the <b>NOR gate</b> to function as a complete system, making it versatile in circuit design and digital systems.<br><br>"
               "<b>Getting Started:</b><br>"
               "<br>"
               "Identify the OR and NOT gates in the left sidebar and place them on the canvas.<br>"
               "Your task is to connect the inputs and output of the <b>NOR circuit</b> correctly.<br>"
               "Refer to the truth table to understand how the circuit should be connected using Boolean equation (true (1), false (0)).<br>"
               "Experiment with different configurations and click “Run” to see how your connections influence the result. Enjoy discovering how the <b>NOR gate</b> works through your own trials!";
        break;
    case 6:
        return "Welcome to the sixth level of our circuit design game! Here, you’ll explore how the <b>XOR</b> gate functions.<br><br>"
               "<b>What is an XOR Gate?</b><br>"
               "<br>"
               "The <b>XOR gate</b> stands for “EXCLUSIVE OR”, it outputs true (1) when an odd number of its inputs are true. If none or an even number of its inputs are true, the output is false (0). This makes the <b>XOR gate</b> special because it only outputs true when exactly one of the inputs is true, or if there are multiple inputs and an odd number of them are true. <br>"
               "Unlike the standard OR gate, which outputs true when at least one input is true, the <b>XOR gate</b> is more selective, requiring an exclusive condition where the inputs differ from each other.<br>"
               "In circuit design, the <b>XOR gate</b> can be broken down into simpler components by combining the <b>NOT</b> and <b>AND</b> gates to ensure that each input's unique truth affects the output. Next, combine these signals using an <b>OR</b> gate to complete the exclusive condition. The <b>XOR gate</b> is essential in digital circuit design for its unique ability to detect discrepancies between two binary inputs.<br><br>"
               "<b>Getting Started:</b><br>"
               "<br>"
               "Identify all three gates (AND, OR, NOT) in the left sidebar and place them on the canvas.<br>"
               "Your task is to connect the inputs and output of the <b>XOR circuit</b> correctly.<br>"
               "Refer to the truth table to understand how the circuit should be connected using a Boolean equation (true (1), false (0)).<br>"
               "Experiment with different configurations and click “Run” to see how your connections influence the result. Enjoy discovering how the <b>XOR gate</b> works through your own trials!";
        break;
    case 7:
        return "Welcome to the sixth level of our circuit design game! Here, you’ll explore how the <b>XOR</b> gate functions.<br><br>"
               "<b>What is an XOR Gate?</b><br>"
               "<br>"
               "The <b>XOR gate</b> stands for “EXCLUSIVE OR”, it outputs true (1) when an odd number of its inputs are true. If none or an even number of its inputs are true, the output is false (0). This makes the <b>XOR gate</b> special because it only outputs true when exactly one of the inputs is true, or if there are multiple inputs and an odd number of them are true. <br>"
               "Unlike the standard OR gate, which outputs true when at least one input is true, the <b>XOR gate</b> is more selective, requiring an exclusive condition where the inputs differ from each other.<br>"
               "In circuit design, the <b>XOR gate</b> can be broken down into simpler components by combining the <b>NOT</b> and <b>AND</b> gates to ensure that each input's unique truth affects the output. Next, combine these signals using an <b>OR</b> gate to complete the exclusive condition. The <b>XOR gate</b> is essential in digital circuit design for its unique ability to detect discrepancies between two binary inputs.<br><br>"
               "<b>Getting Started:</b><br>"
               "<br>"
               "Identify all three gates (AND, OR, NOT) in the left sidebar and place them on the canvas.<br>"
               "Your task is to connect the inputs and output of the <b>XOR circuit</b> correctly.<br>"
               "Refer to the truth table to understand how the circuit should be connected using a Boolean equation (true (1), false (0)).<br>"
               "Experiment with different configurations and click “Run” to see how your connections influence the result. Enjoy discovering how the <b>XOR gate</b> works through your own trials!";
        break;

    case 8:
        return "Welcome to the puzzles of Circuit Craft! \n\n"
               "These puzzles will introduce and test out your knowledge on logic gates by using various gates to solve logic puzzles! \n\n"
               "If you are unfamiliar with logic gates, please check out the \"What are Logic Gates\" in the home screen. \n\n"
               "When you're ready to take on the challenge of solving the puzzles, click on the first puzzle and enjoy applying your knowledge about logic gates in this fun interactive puzzle!";
        break;
    default:
        return " ";
    }
}
