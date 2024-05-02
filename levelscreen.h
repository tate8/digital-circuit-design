#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jasmine Robbins

#include <QWidget>
#include "gate.h"
#include "truthtable.h"
#include "wire.h"
#include "circuitmodel.h"
#include "leveltutorialdialog.h"
#include "animationworld.h"

/// @brief This class manages and displays the ui for the levels and tutorials.
namespace Ui
{
class LevelScreen;
}

class LevelScreen : public QWidget
{
    Q_OBJECT

public:
    /// @brief Constructor to initialize the Level Screen
    /// @param parent - the parent widget
    explicit LevelScreen(QWidget *parent = nullptr);

    /// @brief Destructor to clean up resources.
    ~LevelScreen();

    /// @brief Shows the chosen tutorial modal
    /// @param Int determines which tutorial to show
    void showTutorialModal(int tutorial);

    /// @brief Shows tutorial modal based on level
    void showTutorialBasedOnLevel();

    /// @brief A pointer to the ui setup.
    Ui::LevelScreen *ui;

    /// @brief Pointer to the level dialog ui.
    Ui::LevelTutorialDialog *levelDialog;

    /// @brief Flag for the sandbox mode.
    bool sandboxMode = 0;

    /// @brief Updates the circuit canvas when gates and wires are added/changed.
    /// @param gates - the gates that are added to the canvas
    /// @param wires - the wires that are added to the canvas
    void updateCircuitCanvas(QList<Gate*> gates, QList<Wire*> wires);

    /// @brief A reference to the circuit model.
    CircuitModel model;

    /// @brief Pointer to the Truth Tables.
    TruthTable* table;

    /// @brief Pointer to the animation world.
    AnimationWorld* animation;

    /// @brief Flag to notify if the user circuit was completed successfully.
    bool runWasSuccessful = false;

    /// @brief Updates the current truth table.
    /// @param tableHeader - Displays the table boolean equation as text.
    /// @param data - contains the correct sequence
    void updateTruthTableUI(QString tableHeader, const QVector<QVector<QString>>& data);

    /// @brief When the run button is clicked, this gets the
    /// current truth table to compare with the circuit sequence.
    void runButtonClicked();

    /// @brief Sets the current level to sandbox mode which adds more buttons and disables truth table
    /// @param mode - passing 1 sets the screen to sandbox mode, and 0 resets it to level mode
    void prepareSandbox(bool mode);

signals:
    /// @brief Emitted when a new level should be prepared
    void prepareLevel();

public slots:
    /// @brief Starts the confetti simulation.
    void startConfetti();

    /// @brief Stops the confetti simulation.
    void stopConfetti();

    /// @brief Updates the Ui for the confetti.
    void updateConfetti();

protected:
    /// @brief Triggers the paintEvent to redraw the screen.
    void paintEvent(QPaintEvent *event) override;

private:
    /// @brief Gets the current tutorial title.
    QString getTutorialTitleText(int tutorial);

    /// @brief Gets the tutorial description text from a specified tutorial.
    QString getTutorialDescriptionText(int tutorial);

    /// @brief keeps track of the current level.
    int level;
};

#endif // LEVELSCREEN_H
