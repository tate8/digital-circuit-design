#include "leveltutorialdialog2.h"
#include "ui_leveltutorialdialog2.h"

LevelTutorialDialog2::LevelTutorialDialog2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LevelTutorialDialog2)
{
    ui->setupUi(this);
    setWindowTitle("Level Tutorial");
    setModal(true);

    connect(ui->continueButton, &QPushButton::clicked, this, &LevelTutorialDialog2::accept);
}

LevelTutorialDialog2::~LevelTutorialDialog2()
{
    delete ui;
}
