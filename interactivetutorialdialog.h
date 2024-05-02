#ifndef INTERACTIVETUTORIALDIALOG_H
#define INTERACTIVETUTORIALDIALOG_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Christina Ccao

#include "ui_interactivetutorialdialog.h"
#include <QDialog>

/// \brief The InteractiveTutorialDialog class
///
/// This class represents a custom dialog class for an interactive tutorial that users can interact with to
/// understand the 3 standard logic gates: AND, OR and NOT.
/// This class also teaches users about truth tables, logic gates, and examples of logic gates in the real world.
///
/// Images Used:
/// - Logic gates icons created by joalfa - Flaticon
/// - Image by vectorjuice on Freepik
/// - Image by stockgiu on Freepik
/// - Image by rawpixel.com on Freepik
/// - Image by macrovector on Freepik
/// - Image by Freepik
class InteractiveTutorialDialog  : public QDialog
{
    Q_OBJECT

public:
    ///@brief constructor for the InteractiveTutorialDialog
    explicit InteractiveTutorialDialog(QWidget *parent = nullptr);

    ///@brief Sets the image and text for the main tutorial and the title of the tutorial of the ui
    void setImageAndText(const QPixmap &image, const QString &text);

    ///@brief sets the robot image to the ui
    void setRobotImage(const QPixmap &image);

    ///@brief sets the description text of the tutorial on the ui
    void setDescriptionText(const QString &text);

    /// @brief destructor
    ~InteractiveTutorialDialog();

public slots:
    ///@brief slot for handling the AND button clicked
    void onAndButtonClicked();

    ///@brief slot for handling the OR button clicked
    void onOrButtonClicked();

    ///@brief slot for handling the NOT button clicked
    void onNotButtonClicked();

    ///@brief slot for handling the "what are logic gates button"
    void onLogicButtonClicked();

    ///@brief slot for handling the examples button clicked
    void onExampleButtonClicked();

    ///@brief slot for handling truth button clicked.
    void onTruthButtonClicked();

private:
    ///@brief pointer for UI object
    Ui::InteractiveTutorialDialog *ui;

    ///@brief sets the style sheet of the input button
    void setInputStyleSheet(QPushButton *button);

    ///@brief toggles the input button between 0 and 1
    void toggleInput();

    ///@brief Updates the AND label result after player interactions
    void andUpdateResultLabel(QPushButton *input1, QPushButton *input2);

    ///@brief Updates the OR label result after player interactions
    void orUpdateResultLabel(QPushButton *input1, QPushButton *input2);

    ///@brief Updates the NOT label result after player interactions
    void notUpdateResultLabel(QPushButton *input1);

    ///@brief disconnects input buttons
    void disconnectInputButtons();

    ///@brief resets the color and value of the output vale
    void resetOutputLabel();

    ///@brief initializing the input1 QPushButton
    QPushButton *input1 = new QPushButton("0");

    ///@brief initializing the input2 QPushButton
    QPushButton *input2  = new QPushButton("0");

    ///@brief initializing the NOT QPushButton
    QPushButton *notInput  = new QPushButton("0");
};
#endif // INTERACTIVETUTORIALDIALOG_H
