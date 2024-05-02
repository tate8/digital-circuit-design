#include "interactivetutorialdialog.h"
#include "ui_interactivetutorialdialog.h"
#include <QGridLayout>

InteractiveTutorialDialog::InteractiveTutorialDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InteractiveTutorialDialog)
{
    ui->setupUi(this);
    connect(ui->continueButton, &QPushButton::clicked, this, &InteractiveTutorialDialog::accept);
}

InteractiveTutorialDialog::~InteractiveTutorialDialog()
{
    delete input1;
    delete input2;
    delete notInput;
}

void InteractiveTutorialDialog::setRobotImage(const QPixmap &image)
{
    ui->robotImage->setPixmap(image);
    QSize labelSize = ui->robotImage->size();

    QPixmap scaledRobot = image.scaled(labelSize, Qt::KeepAspectRatio);
    ui->robotImage->setPixmap(scaledRobot);
}

void InteractiveTutorialDialog::setImageAndText(const QPixmap &image, const QString &text)
{
    //sets the image to the label's pixmap
    ui->imageLabel->setPixmap(image);
    ui->gateLabel->setText(text);

    ui->gateLabel->setAlignment(Qt::AlignCenter);
    ui->outputLabel->setAlignment(Qt::AlignCenter);
}

void InteractiveTutorialDialog::setDescriptionText(const QString &text)
{
    ui->descriptionLabel->setText(text);
}

void InteractiveTutorialDialog::onAndButtonClicked()
{
    disconnectInputButtons();

    if (notInput)
    {
        notInput->setVisible(false);
    }

    ui->outputLabel->setVisible(true);

    input1 = new QPushButton("0", this);
    input2 = new QPushButton("0", this);

    resetOutputLabel();

    input1->setGeometry(20, 215, 100, 100);
    input2->setGeometry(20, 385, 100, 100);

    input1->setFixedSize(100, 100);
    input2->setFixedSize(100, 100);


    QPixmap andImage(":/rainbowGates/andBlue.png");
    QPixmap robotImage(":/robot/robot_and.png");
    QString labelText = "WHAT IS AN AND GATE?";
    QString descriptionText = "An AND gate takes in two binary inputs (0s and 1s) and it outputs a single binary value based on those inputs. Just like the robot shows, both inputs need to be a '1' for the AND gate to output a '1'. If either or both inputs are '0', the output will be '0'.\n\n"
                              "Press the numbers on the left side of the gate to simulate to understand how this gate behaves. Experiment with various combinations of 0s and 1s for Input A and Input B, and observe how the output reacts accordingly.\n\n"
                              "Once you have a solid grasp of how this gate works, explore the other gates available in this game such as the OR or NOT, check out some of the other concepts related to logic gates and test your knowledge in the levels!";

    setRobotImage(robotImage);
    setImageAndText(andImage,labelText);
    setDescriptionText(descriptionText);

    ui->robotImage->setVisible(true);

    setInputStyleSheet(input1);
    setInputStyleSheet(input2);

    connect(input1, &QPushButton::clicked, this, &InteractiveTutorialDialog::toggleInput);
    connect(input2, &QPushButton::clicked, this, &InteractiveTutorialDialog::toggleInput);

    connect(input1, &QPushButton::clicked, this, [this]()
        {
        QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
        if (senderButton)
        {
            andUpdateResultLabel(input1, input2);
        }
    });
    connect(input2, &QPushButton::clicked, this, [this]()
        {
        QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
        if (senderButton)
        {
            andUpdateResultLabel(input1, input2);
        }
    });
}

void InteractiveTutorialDialog::onOrButtonClicked()
{
    disconnectInputButtons();

    if (notInput)
    {
        notInput->setVisible(false);
    }
    input1 = new QPushButton("0", this);
    input2 = new QPushButton("0", this);
    ui->outputLabel->setVisible(true);
    resetOutputLabel();

    input1->setGeometry(20, 215, 100, 100);
    input2->setGeometry(20, 385, 100, 100);

    input1->setFixedSize(100, 100);
    input2->setFixedSize(100, 100);
    QPixmap orImage(":/rainbowGates/orBlue.png");
    QString text = "WHAT IS AN OR GATE?";
    QPixmap robotImage(":/robot/robot_or.png");
    QString descriptionText = "An OR gate takes in two binary inputs (0s and 1s) and it outputs a single binary value based on those inputs. Similar to the AND gate where if both inputs are 1, then the output will be 1, however the OR gate behaves differently where if only 1 input is 1, then the output is 1.\n\n"
                              "Play around with the OR gate and compare and contrast this gate to the AND gate and refer to the robot for hints on how to achieve different gate outputs. Next, check out the NOT gate and think about how that could be useful when using the AND or OR gates.";

    setImageAndText(orImage,text);
    setRobotImage(robotImage);
    setDescriptionText(descriptionText);

    ui->robotImage->setVisible(true);

    setInputStyleSheet(input1);
    setInputStyleSheet(input2);

    connect(input1, &QPushButton::clicked, this, &InteractiveTutorialDialog::toggleInput);
    connect(input2, &QPushButton::clicked, this, &InteractiveTutorialDialog::toggleInput);

    connect(input1, &QPushButton::clicked, this, [this]()
            {
                QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
                if (senderButton)
                {
                    orUpdateResultLabel(input1, input2);
                }
            });
    connect(input2, &QPushButton::clicked, this, [this]()
            {
                QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
                if (senderButton)
                {
                    orUpdateResultLabel(input1, input2);
                }
            });
}

void InteractiveTutorialDialog::onNotButtonClicked()
{
    input1->setVisible(false);
    input2->setVisible(false);

    ui->outputLabel->setVisible(true);

    resetOutputLabel();
    notInput = new QPushButton("0", this);

    QPixmap notImage(":/rainbowGates/notBlue.png");

    int shiftAmount = 10;
    QPixmap shiftedImage = notImage.copy(-shiftAmount, 0, notImage.width(), notImage.height());

    QString text = "WHAT IS A NOT GATE?";
    QPixmap robotImage(":/robot/robot_not.png");
    QString descriptionText = "A NOT gate takes a single binary input (0 or 1) and produces the opposite binary value as output. For example, if the input is 1, then 0 is the output, essentially inverting the input. \n\n"
                              "Experiment with the NOT gate and observe how it changes the input value to its opposite.  Refer to the robot for hints on how to use the NOT gate effectively Also think about ways where you could possible combine previously learned gates such as AND or OR to create new gates .\n\n"
                              "After understanding how the NOT gate works, learn about truth tables to master the puzzles, or explore why logic gates are necessary, and examples in the world!";

    setImageAndText(shiftedImage,text);
    setRobotImage(robotImage);
    setDescriptionText(descriptionText);

    ui->robotImage->setVisible(true);

    notInput->setGeometry(30, 300, 100, 100);

    notInput->setText("1");
    notInput->setStyleSheet("QPushButton {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #87ff9b;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }\
                           QPushButton:hover {\
                               background-color: #D8D8D8;\
                           }\
                           QPushButton:pressed {\
                               background-color: #CACACA;\
                           }");

    connect(notInput, &QPushButton::clicked, this, &InteractiveTutorialDialog::toggleInput);

    connect(notInput, &QPushButton::clicked, this, [this]()
            {
                QPushButton *senderButton = qobject_cast<QPushButton*>(sender());
                if (senderButton)
                {
                    notUpdateResultLabel(notInput);
                }
            });
}

void InteractiveTutorialDialog::onLogicButtonClicked()
{
    //sets the button inputs to not visible for the non-interactive tutorials
    if (input1)
    {
        input1->setVisible(false);
    }
    if (input2)
    {
        input2->setVisible(false);
    }
    if (notInput)
    {
        notInput->setVisible(false);
    }

    QPixmap logicImage(":/rainbowGates/gateFaces.png");
    QPixmap scaledPixmap = logicImage.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio);

    QString text = "WHAT ARE LOGIC GATES?";
    QString descriptionText =
        "Logic gates are used in digital circuits to process binary data by implementing basic logical operations such as AND, OR, and NOT. \n\n"
        "They are crucial for designing and building digital systems. Some of these include computers, calculators, digital watches, and communication devices through a combination of circuits to perform arithmetic calculations, decision control, and data storage. \n\n"
        "Logic gates use basic logical functions such as AND, OR, and NOT seen in this game, and using binary inputs, will produce a binary output based on the logic of that gate. \n"
        "These logic gates can then be combined into a much larger scale to create digital systems.";

    setImageAndText(scaledPixmap,text);
    setDescriptionText(descriptionText);

    ui->outputLabel->setVisible(false);
    ui->robotImage->setVisible(false);
}

void InteractiveTutorialDialog::onExampleButtonClicked()
{
    //sets the button inputs to not visible for the non-interactive tutorials
    if (input1)
    {
        input1->setVisible(false);
    }
    if (input2)
    {
        input2->setVisible(false);
    }
    if (notInput)
    {
        notInput->setVisible(false);
    }

    QPixmap exampleImages(":/examples.png");
    QPixmap scaledPixmap = exampleImages.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio);

    QString text = "REAL LIFE LOGIC GATE EXAMPLES";
    QString descriptionText = "Logic gates have many real-world applications, including managing your accounts with usernames and passwords, securing systems, operating home appliances, and controlling robots.\n\n"
                              "Even in your everyday appliances logic gates are used. For example, an AND gate may be used for a username/password by making sure both the username and password are entered correctly. "
                              "Or in a security camera, if the camera detects motion and an alarm is triggered, then the recording system is triggered to record. \n\n"
                              "In a typical home stove, there is more than one burner.  When you turn on a burner the indicator light that shows a burner is on is also turns on. This implements an or gate since only one burner is required to turn on the indicator light and can be any burner on the stove. ";

    setImageAndText(scaledPixmap,text);
    setDescriptionText(descriptionText);

    ui->outputLabel->setVisible(false);
    ui->robotImage->setVisible(false);
}

void InteractiveTutorialDialog::onTruthButtonClicked()
{
    //sets the button inputs to not visible for the non-interactive tutorials
    if (input1)
    {
        input1->setVisible(false);
    }
    if (input2)
    {
        input2->setVisible(false);
    }
    if (notInput)
    {
        notInput->setVisible(false);
    }

    QPixmap truthImage(":/gatePorts/truthTable.png");

    QString text = "WHAT ARE TRUTH TABLES?";
    QString descriptionText =
        "Truth tables are logic tools used to explore all possible combinations of inputs, represented by A and B, \n"
        "to determine the resulting output, represented by Q, based on logical operations like AND (.), OR (+), and negation (¬). \n\n"
        "By listing out all possible combinations of inputs and applying the logical operations, \n"
        "truth tables help visualize and understand how a logical expression behaves under different conditions.";

    setImageAndText(truthImage,text);
    setDescriptionText(descriptionText);

    ui->outputLabel->setVisible(false);
    ui->robotImage->setVisible(false);
}

void InteractiveTutorialDialog::setInputStyleSheet(QPushButton *button)
{
    button->setStyleSheet("QPushButton {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }\
                           QPushButton:hover {\
                               background-color: #D8D8D8;\
                           }\
                           QPushButton:pressed {\
                               background-color: #CACACA;\
                           }");
}

void InteractiveTutorialDialog::toggleInput()
{
    // get the pointer to the button which emitted the signal
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button)
        return;

    QString currentText = button->text();
    if (currentText == "0")
    {
        button->setText("1");
        button->setStyleSheet("QPushButton {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #87ff9b;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    } else
    {
        button->setText("0");
        button->setStyleSheet("QPushButton {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    }
}

void InteractiveTutorialDialog::andUpdateResultLabel(QPushButton *input1, QPushButton *input2)
{
    // Get the current text of both input buttons
    QString inputText1 = input1->text();
    QString inputText2 = input2->text();

    int input1int = inputText1.toInt();
    int input2int = inputText2.toInt();

    // Check if both inputs are 1, then update the label to 1,
    if (input1int == 1 && input2int == 1)
    {
        ui->outputLabel->setText("1");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #87ff9b;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    }
    else
    {
        ui->outputLabel->setText("0");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    }
}

void InteractiveTutorialDialog::orUpdateResultLabel(QPushButton *input1, QPushButton *input2)
{
    // Get the current text of both input buttons
    QString inputText1 = input1->text();
    QString inputText2 = input2->text();

    int input1int = inputText1.toInt();
    int input2int = inputText2.toInt();

    if (input1int == 1 || input2int == 1)
    {
        ui->outputLabel->setText("1");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #87ff9b;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");

    }
    else
    {
        ui->outputLabel->setText("0");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    }
}

void InteractiveTutorialDialog::notUpdateResultLabel(QPushButton *input1)
{
    QString inputText1 = input1->text();
    int input1int = inputText1.toInt();

    if (input1int == 0)
    {
        ui->outputLabel->setText("1");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #87ff9b;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");

    }
    else
    {
        ui->outputLabel->setText("0");
        ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
    }
}

void InteractiveTutorialDialog::disconnectInputButtons()
{
    if (input1)
    {
        disconnect(input1, &QPushButton::clicked, nullptr, nullptr);
        delete input1;
        input1 = nullptr;
    }
    if (input2)
    {  
        disconnect(input2, &QPushButton::clicked, nullptr, nullptr);
        delete input2;
        input2 = nullptr;
    }
}

void InteractiveTutorialDialog::resetOutputLabel()
{
    ui->outputLabel->setText("0");
    ui->outputLabel->setStyleSheet("QLabel {\
                               border: 5px solid #000000;\
                               border-radius: 10px;\
                               background-color: #ff9c9c;\
                               color: black;\
                               font: bold 24px;\
                               padding: 10px;\
                               min-width: 40px;\
                               min-height: 40px;\
                           }");
}
