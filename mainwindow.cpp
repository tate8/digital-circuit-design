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

    inLevel->ui->norButton->hide();
    inLevel->ui->xorButton->hide();
    inLevel->ui->nandButton->hide();
    inLevel->ui->outputButton->hide();

    // set the current widget to be the in-level for now (for model testing purposes to minimize clicks to get to level screen)
    stackedLayout->setCurrentWidget(homeScreen);

    // Logic to switch between screens
    connect(levelPicker->ui->homeButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(homeScreen);
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

    connect(levelPicker->ui->pushButton, &QPushButton::clicked, [=](){
        stackedLayout->setCurrentWidget(inLevel);
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}
