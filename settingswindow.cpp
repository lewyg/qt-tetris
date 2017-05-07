#include "settingswindow.h"
#include "ui_settingswindow.h"

SettingsWindow::SettingsWindow(int * probabilities, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    this->probabilities = probabilities;

    ui->hsZShape->setValue(probabilities[0]);
    ui->hsSShape->setValue(probabilities[1]);
    ui->hsLineShape->setValue(probabilities[2]);
    ui->hsTShape->setValue(probabilities[3]);
    ui->hsSquareShape->setValue(probabilities[4]);
    ui->hsLShape->setValue(probabilities[5]);
    ui->hsJShape->setValue(probabilities[6]);
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::on_btSave_clicked()
{
    probabilities = getNormalizedProbabilities();

    emit setShapeProbabilities(probabilities);
    close();
}

void SettingsWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
    emit pauseGame();
}

int * SettingsWindow::getNormalizedProbabilities()
{
    int sum = 0;
    sum += ui->hsZShape->value();
    sum += ui->hsSShape->value();
    sum += ui->hsLineShape->value();
    sum += ui->hsTShape->value();
    sum += ui->hsSquareShape->value();
    sum += ui->hsLShape->value();
    sum += ui->hsJShape->value();

    double factor = sum / 100.0;

    int * newProbabilities = new int[7] {
        int(ui->hsZShape->value() / factor),
        int(ui->hsSShape->value() / factor),
        int(ui->hsLineShape->value() / factor),
        int(ui->hsTShape->value() / factor),
        int(ui->hsSquareShape->value() / factor),
        int(ui->hsLShape->value() / factor),
        int(ui->hsJShape->value() / factor),
    };

    return newProbabilities;
}
