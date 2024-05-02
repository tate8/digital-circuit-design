/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily
#include "mainwindow.h"
#include "ui_helpscreen.h"
#include "ui_homescreen.h"
#include "ui_mainwindow.h"
#include <QStackedLayout>
#include "levelpicker.h"
#include "levelscreen.h"
#include <QPushButton>
#include "ui_levelscreen.h"
#include "ui_levelpicker.h"
#include <QAbstractItemView>
#include <Box2D/Box2D.h>
#include "homescreen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create a stacked layout to hold all of our screens.
    // This way we can switch between the level picker and the in-level screens
    QStackedLayout *stackedLayout = new QStackedLayout(centralWidget);

    // Create the screens
    LevelPicker *levelPicker = new LevelPicker();
    LevelScreen *inLevel = new LevelScreen();
    HomeScreen *homeScreen = new HomeScreen(this);
    HelpScreen *helpScreen = new HelpScreen(this);

    // Add the screens to the stacked layout
    stackedLayout->addWidget(levelPicker);
    stackedLayout->addWidget(inLevel);
    stackedLayout->addWidget(homeScreen);
    stackedLayout->addWidget(helpScreen);

    inLevel->ui->norButton->hide();
    inLevel->ui->xorButton->hide();
    inLevel->ui->nandButton->hide();
    inLevel->ui->outputButton->hide();

    // set the current widget to be the in-level for now (for model testing purposes to minimize clicks to get to level screen)
    stackedLayout->setCurrentWidget(homeScreen);

    // Logic to switch between screens
    connect(levelPicker->ui->button, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
        // Show the tutorial by default
        // And
        inLevel->showTutorialModal(1);
    });

    // level screen to home
    connect(inLevel->ui->homeButton, &QPushButton::clicked, [=](){
        if(inLevel->sandboxMode)
        {
            // if in sandbox mode, return to level mode when going home
            inLevel->prepareSandbox(0);
            inLevel->sandboxMode = 0;
        }
        stackedLayout->setCurrentWidget(homeScreen);
    });

    // home screen to levelpicker
    connect(homeScreen->ui->levelsButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(levelPicker);
    });

    // sandbox to level screen
    connect(homeScreen->ui->sandboxButton, &QPushButton::clicked, [=](){
        inLevel->prepareSandbox(1);
        inLevel->sandboxMode = 1;
        stackedLayout->setCurrentWidget(inLevel);
    });

    // level picker to home
    connect(levelPicker->ui->homeButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(homeScreen);
    });

    // help screen to home
    connect(helpScreen->ui->homeButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(homeScreen);
    });

    // home screen to help
    connect(homeScreen->ui->helpButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(helpScreen);
    });

    // level screen to levelpicker
    connect(inLevel->ui->levelsButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(levelPicker);
    });

    // Connect each button to screen switch
    connect(levelPicker->ui->pushButton_2, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
        // Or tutorial
        inLevel->showTutorialModal(2);
    });
    connect(levelPicker->ui->pushButton_3, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
        // Not tutorial
        inLevel->showTutorialModal(3);
    });
    connect(levelPicker->ui->pushButton_4, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
         inLevel->showTutorialModal(4);
    });
    connect(levelPicker->ui->pushButton_5, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
         inLevel->showTutorialModal(5);
    });
    connect(levelPicker->ui->pushButton_6, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
         inLevel->showTutorialModal(6);
    });
    connect(levelPicker->ui->pushButton_7, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
         inLevel->showTutorialModal(7);
    });
    connect(levelPicker->ui->pushButton_8, &QPushButton::clicked, [=](){
        inLevel->showTutorialModal(8);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
