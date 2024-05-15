#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jasmine Robbins

#include <QWidget>
#include "Gates/gate.h"
#include "truthtable.h"
#include "wire.h"
#include "circuitmodel.h"
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

    /// @brief A pointer to the ui setup.
    Ui::LevelScreen *ui;

    /// @brief Flag for the sandbox mode.
    bool sandboxMode = 0;

    /// @brief A reference to the circuit model.
    CircuitModel model;

    /// @brief Pointer to the Truth Tables.
    TruthTable* table;

    /// @brief Pointer to the animation world.
    AnimationWorld* animation;

    /// @brief Flag to notify if the user circuit was completed successfully.
    bool runWasSuccessful = false;

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
};

#endif // LEVELSCREEN_H
