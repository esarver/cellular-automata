#ifndef GOLWINDOW_H
#define GOLWINDOW_H

#include <QFrame>
#include <QWidget>
#include "world.h"

class GolBoard;
class QGroupBox;
class QLabel;
class QPushButton;
class QScreen;
class QScrollArea;
class QSlider;
class QSpinBox;
class QString;

class GolWindow : public QWidget
{
    Q_OBJECT
public:
    GolWindow();

public slots:
    void changeLabel(QString, QString);
    void changeSliderLabel(int value);
    void checkPauseBtn();
    void justifyBoardZoom(int x, int y);
    void setMinSizeScrollArea();

 private:
    GolBoard *board;
    World *world_;
    QLabel *aliveCellsLabel;
    QLabel *iterationLabel;
    QLabel *speedLabel;
    QPushButton *clearBtn;
    QPushButton *pauseBtn;
    QPushButton *populateBtn;
    QPushButton *startBtn;
    QScrollArea *scrollArea;
    QSlider *speedSlider;
    QSpinBox *popRatioBox;
    QWidget *sidebar;
    void createControlsBox(QGroupBox* box);
    void createPrefsBox(QGroupBox* box);
    void createSignals();
void createStatsBox(QGroupBox* box);
};

#endif // GOLWINDOW_H
