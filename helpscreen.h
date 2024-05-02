#ifndef HELPSCREEN_H
#define HELPSCREEN_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Jonathan Bodily

#include <QMainWindow>
#include <QPushButton>
#include "interactivetutorialdialog.h"
#include "animationworld.h"

namespace Ui {
class HelpScreen;
}

/// @brief
class HelpScreen : public QWidget
{
    Q_OBJECT
public:
    /// @brief constructor for helpscreen ui window
    HelpScreen(QWidget *parent = nullptr);

    /// @brief deconstructor for helpscreen
    ~HelpScreen();

    /// @brief ui window for helpscreen
    Ui::HelpScreen *ui;

private:

    /// @brief Pointer to the animation world object.
    AnimationWorld* world;

    /// @brief Timer for the background animation.
    QTimer *timer;
public slots:
    void updateAnimation();

protected:
    void paintEvent(QPaintEvent *event) override;

    /// @brief Resizes the Box2d world with the ui window.
    void resizeEvent(QResizeEvent *event) override;



signals:
    /// @brief signal to go back to the homepage from teh helpscreen
    void homeButtonClicked();

};

#endif // HELPSCREEN_H
