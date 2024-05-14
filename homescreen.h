#ifndef HOMESCREEN_H
#define HOMESCREEN_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily

#include <QWidget>
#include <mainwindow.h>
#include <QStackedWidget>
#include "animationworld.h"

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(MainWindow* window, AnimationWorld* world, QWidget *parent = nullptr);
    ~HomeScreen();
    Ui::HomeScreen *ui;

private:
    /// @brief Pointer to the animation world object.
    AnimationWorld* world;

    /// @brief Timer for the background animation.
    QTimer* timer;

protected:
    /// @brief Handles painting bodies from the animation world into the ui frame.
    /// @param The paint event that needs to be updated/redrawn
    void paintEvent(QPaintEvent *event) override;

    /// @brief Resizes the Box2d world with the ui window.
    void resizeEvent(QResizeEvent *event) override;

};

#endif // HOMESCREEN_H
