/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily
#include "mainwindow.h"
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
#include "tutorialconfig.h"

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

    // Create a single AnimationWorld instance
    AnimationWorld* world = new AnimationWorld(centralWidget->size().width(), centralWidget->size().height());

    // Create the screens
    LevelPicker* levelPicker = new LevelPicker(world);
    LevelScreen* inLevel = new LevelScreen();
    HomeScreen* homeScreen = new HomeScreen(this, world);

    // Add the screens to the stacked layout
    stackedLayout->addWidget(levelPicker);
    stackedLayout->addWidget(inLevel);
    stackedLayout->addWidget(homeScreen);

    // set the current widget to be the in-level for now (for model testing purposes to minimize clicks to get to level screen)
    stackedLayout->setCurrentWidget(homeScreen);

    // Logic to switch between screens
    connect(levelPicker->ui->homeButton, &QPushButton::clicked, this, [=](){
        stackedLayout->setCurrentWidget(homeScreen);
    });


    // level screen to home
    connect(inLevel->ui->homeButton, &QPushButton::clicked, this, [=](){
        stackedLayout->setCurrentWidget(homeScreen);
    });

    // home screen to levelpicker
    connect(homeScreen->ui->levelsButton, &QPushButton::clicked, this, [=](){
        stackedLayout->setCurrentWidget(levelPicker);
    });

    connect(homeScreen->ui->sandboxButton, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(SandboxTutorialConfig);
        inLevel->ui->runButton->hide();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level1Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial1Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level2Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial2Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level3Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial3Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level4Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial4Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level5Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial5Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });

    connect(levelPicker->ui->level6Button, &QPushButton::clicked, this, [=](){
        inLevel->setupLevel(Tutorial6Config);
        inLevel->ui->runButton->show();
        stackedLayout->setCurrentWidget(inLevel);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
