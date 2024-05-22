#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include <QWidget>
#include "circuitmodel.h"
#include "tutorialconfig.h"

/// @brief This class manages and displays the ui for the levels and tutorials.
namespace Ui
{
class LevelScreen;
}

class LevelScreen : public QWidget
{
    Q_OBJECT

private:
    TutorialConfig currentConfig;

public:
    /// @brief Constructor to initialize the Level Screen
    /// @param parent - the parent widget
    explicit LevelScreen(QWidget *parent = nullptr);

    /// @brief Sets up the current config for a new level
    /// @param config - The config for the new level
    void setupLevel(const TutorialConfig& config);

    /// @brief Destructor to clean up resources.
    ~LevelScreen();

    /// @brief A pointer to the ui setup.
    Ui::LevelScreen *ui;

    /// @brief A reference to the circuit model.
    CircuitModel model;

public slots:
    void handleRunSuccess();
    void handleRunFailure();
};

#endif // LEVELSCREEN_H
