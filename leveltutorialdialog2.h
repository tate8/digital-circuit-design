#ifndef LEVELTUTORIALDIALOG2_H
#define LEVELTUTORIALDIALOG2_H

#include <QDialog>

namespace Ui {
class LevelTutorialDialog2;
}

///
/// \brief custom tutorial level dialog popup to instruct users on how to complete levels
///
class LevelTutorialDialog2 : public QDialog
{
    Q_OBJECT
public:
    /// \brief Constructor for LevelTutorialDialog
    explicit LevelTutorialDialog2(QWidget *parent = nullptr);

    /// \brief deconstructor
    ~LevelTutorialDialog2();
private:
    /// \brief pointer to UI object
    Ui::LevelTutorialDialog2 *ui;
};
#endif // LEVELTUTORIALDIALOG2_H
