#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QWidget
{
    Q_OBJECT

public:
    SettingsWindow(int * probabilities, QWidget *parent = 0);
    ~SettingsWindow();

signals:
    void setShapeProbabilities(int *probabilities);
    void pauseGame();

private slots:
    void on_btSave_clicked();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::SettingsWindow *ui;

    int * probabilities;

    int * getNormalizedProbabilities();
};

#endif // SETTINGSWINDOW_H
