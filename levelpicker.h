#ifndef LEVELPICKER_H
#define LEVELPICKER_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jasmine Robbins

#include "animationworld.h"
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QTimerEvent>

/// @brief This class handles the level picker ui screen.
namespace Ui
{
///
/// This class represents a component for selecting levels in the game
///
class LevelPicker;
}
class LevelPicker : public QWidget
{
    Q_OBJECT
public:
    /// @brief Constructor that initializes the Level Picker window.
    /// @param world - The animation world
    /// @param parent - The parent widget
    explicit LevelPicker(AnimationWorld* world, QWidget *parent = nullptr);

    /// @brief Destructor to clean up resources.
    ~LevelPicker();

    /// @brief A pointer to the ui setup.
    Ui::LevelPicker* ui;

protected:
    /// @brief Handles painting bodies from the animation world into the ui frame.
    /// @param The paint event that needs to be updated/redrawn
    void paintEvent(QPaintEvent *event) override;

    /// @brief Resizes the Box2d world with the ui window.
    /// @param event - the resize event that contains the new size
    void resizeEvent(QResizeEvent *event) override;

private:
    /// @brief Pointer to the animation world object.
    AnimationWorld* world;

    /// @brief Timer for the background animation.
    QTimer* timer;
};
#endif // LEVELPICKER_H
