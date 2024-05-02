#ifndef HOMESCREEN_H
#define HOMESCREEN_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily

#include "helpscreen.h"
#include <QWidget>
#include <mainwindow.h>
#include <QStackedWidget>

namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(MainWindow *window, QWidget *parent = nullptr);
    ~HomeScreen();
    Ui::HomeScreen *ui;

private:
    /// @brief sandbox ui window
    MainWindow* sandbox;

    /// @brief help ui window
    HelpScreen* help;

    /// @brief stack that controls switching between ui windows
    QStackedWidget stack;

    /// @brief Pointer to the animation world object.
    AnimationWorld* world;

    /// @brief Timer for the background animation.
    QTimer *timer;

public slots:
    /// \brief openSandbox Changes the current screen to the sandbox window
    void openSandbox();

    /// \brief openHomeMenu Changes the current screen to the home window
    void openHomeMenu();

    /// @brief openHelpScreen Changes the current screen to the help window
    void openHelpScreen();

    void updateAnimation();

protected:
    /// @brief Handles painting bodies from the animation world into the ui frame.
    /// @param The paint event that needs to be updated/redrawn
    void paintEvent(QPaintEvent *event) override;

    /// @brief Resizes the Box2d world with the ui window.
    void resizeEvent(QResizeEvent *event) override;

};

#endif // HOMESCREEN_H
