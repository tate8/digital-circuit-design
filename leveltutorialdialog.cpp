#include "leveltutorialdialog.h"
#include "QtWidgets/qboxlayout.h"
#include "QtWidgets/qscrollarea.h"
#include "ui_leveltutorialdialog.h"

LevelTutorialDialog::LevelTutorialDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LevelTutorialDialog)
{
    ui->setupUi(this);
    setWindowTitle("Level Tutorial");
    setModal(true);
    QLabel* titleLabel = ui->titleLabel;
    ui->descriptionLabel->setStyleSheet("QLabel { background-color: rgb(255, 255, 255); color: black; margin-left: 10px; margin-right: 10px;}");

    // Create the scroll area
    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { background: white; }");
    scrollArea->setBackgroundRole(QPalette::Base);
    scrollArea->setWidget(ui->descriptionLabel);
    scrollArea->setFrameShape(QFrame::NoFrame);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(titleLabel);
    mainLayout->addSpacing(15);
    mainLayout->addWidget(scrollArea);
    mainLayout->addWidget(ui->continueButton);
    this->setLayout(mainLayout);

    connect(ui->continueButton, &QPushButton::clicked, this, &LevelTutorialDialog::accept);
}

LevelTutorialDialog::~LevelTutorialDialog()
{
    delete ui;
}
