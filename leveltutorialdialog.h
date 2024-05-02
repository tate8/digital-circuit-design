#ifndef LEVELTUTORIALDIALOG_H
#define LEVELTUTORIALDIALOG_H

#include <QDialog>

namespace Ui {
class LevelTutorialDialog;
}
///
/// \brief custom tutorial level dialog popup to instruct users on how to complete levels
///
class LevelTutorialDialog : public QDialog
{
    Q_OBJECT
public:
    /// \brief Constructor for LevelTutorialDialog
    explicit LevelTutorialDialog(QWidget *parent = nullptr);

    /// \brief deconstructor
    ~LevelTutorialDialog();

    /// \brief pointer to UI object
    Ui::LevelTutorialDialog *ui;
};
#endif // LEVELTUTORIALDIALOG_H
