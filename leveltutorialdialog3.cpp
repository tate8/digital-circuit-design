#include "leveltutorialdialog3.h"
#include "ui_leveltutorialdialog3.h"

LevelTutorialDialog3::LevelTutorialDialog3(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LevelTutorialDialog3)
{
    ui->setupUi(this);
    setWindowTitle("Level Tutorial");
    setModal(true);

    connect(ui->continueButton, &QPushButton::clicked, this, &LevelTutorialDialog3::accept);
}

LevelTutorialDialog3::~LevelTutorialDialog3()
{
    delete ui;
}
