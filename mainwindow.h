#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/// CS3505 - Digital Circuit Design Game
/// Reviewed by Philippe Gonzalez

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    /// \brief homeButtonClicked Emmitted when the home button is clicked
    void homeButtonClicked();

    /// emmited when the tutorial button is clicked in sandbox mode
    void tutorialButtonClicked();

};

#endif // MAINWINDOW_H
