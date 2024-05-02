#ifndef LEVELTUTORIALDIALOG3_H
#define LEVELTUTORIALDIALOG3_H

#include <QDialog>

namespace Ui {
class LevelTutorialDialog3;
}

///
/// \brief custom tutorial level dialog popup to instruct users on how to complete levels
///
class LevelTutorialDialog3 : public QDialog
{
    Q_OBJECT
public:
    /// \brief Constructor for LevelTutorialDialog
    explicit LevelTutorialDialog3(QWidget *parent = nullptr);

    /// \brief deconstructor
    ~LevelTutorialDialog3();
private:
    /// \brief pointer to UI object
    Ui::LevelTutorialDialog3 *ui;
};
#endif // LEVELTUTORIALDIALOG3_H
