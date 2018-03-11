#include "golwindow.h"

#include <QtWidgets>

#include "./golwindow.h"
#include "./golboard.h"

GolWindow::GolWindow() {
    board = new GolBoard;
    sidebar = new QWidget;
    scrollArea = new QScrollArea;
    scrollArea->setWidget(board);
    scrollArea->setWidgetResizable(false);
    setMinSizeScrollArea();

    /* Controls */
    QGroupBox *controlsBox = new QGroupBox("Controls");
    createControlsBox(controlsBox);

    /* Preferences */
    QGroupBox *prefsBox = new QGroupBox(tr("Preferences"));
    createPrefsBox(prefsBox);

    /* Statistics */
    QGroupBox *statsBox = new QGroupBox(tr("Statistics"));
    createStatsBox(statsBox);

    /* put sidebar together */
    QVBoxLayout *vbox = new QVBoxLayout(sidebar);
    vbox->addWidget(controlsBox, 0, Qt::AlignTop);
    vbox->addWidget(prefsBox, 0, Qt::AlignTop);
    vbox->addWidget(statsBox, 0, Qt::AlignTop);
    vbox->insertStretch(-1, 0);

    /* create signals */
    createSignals();

    /* put everything together */
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(sidebar, 0, Qt::AlignLeft|Qt::AlignTop);
    layout->addWidget(scrollArea);
    setWindowTitle(tr("Conway\'s Game of Life"));
    setLayout(layout);
}

void GolWindow::changeLabel(QString label, QString text) {
    if (0 == QString::compare(label, "iterationLabel")) {
        iterationLabel->setText(text);
        return;
    }
    if (0 == QString::compare(label, "aliveCellsLabel")) {
        aliveCellsLabel->setText(text);
        return;
    }
}
void GolWindow::changeSliderLabel(int value) {
    speedLabel->setText(QString(tr("%1 iterations/sec").arg(value)));
}

void GolWindow::checkPauseBtn() {
    pauseBtn->setChecked(true);
}

void GolWindow::createControlsBox(QGroupBox *controlsBox) {
    startBtn = new QPushButton(tr("&Start"));
    startBtn->setCheckable(true);
    startBtn->setAutoExclusive(true);
    pauseBtn = new QPushButton(tr("&Pause"));
    pauseBtn->setCheckable(true);
    pauseBtn->setChecked(true);
    pauseBtn->setAutoExclusive(true);
    populateBtn = new QPushButton(tr("&Random"));
    clearBtn = new QPushButton(tr("&Clear"));

    QVBoxLayout *vbox = new QVBoxLayout;
    speedLabel = new QLabel(tr("25 iterations/sec"));
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setValue(25);
    speedSlider->setTickInterval(1);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(100);

    vbox->addWidget(startBtn);
    vbox->addWidget(pauseBtn);
    vbox->addWidget(populateBtn);
    vbox->addWidget(clearBtn);
    vbox->addWidget(speedLabel);
    vbox->addWidget(speedSlider);
    controlsBox->setLayout(vbox);
}

void GolWindow::createPrefsBox(QGroupBox *prefsBox) {
    QVBoxLayout *vbox = new QVBoxLayout;

    /* TODO: connect gridSize */
    /* QLabel *gridSizeLabel = new QLabel(tr("Grid size")); */
    /* QHBoxLayout *hbox = new QHBoxLayout; */
    /* QLineEdit *xSizeEdit = new QLineEdit("100"); */
    /* xSizeEdit->setMaxLength(3); */
    /* QLineEdit *ySizeEdit = new QLineEdit("100"); */
    /* ySizeEdit->setMaxLength(3); */
    /* hbox->addWidget(xSizeEdit); */
    /* hbox->addWidget(new QLabel(tr("x"))); */
    /* hbox->addWidget(ySizeEdit); */

    QLabel *popRatioLabel = new QLabel(tr("Initial ratio of alive cells"));
    popRatioBox = new QSpinBox;
    popRatioBox->setRange(0, 100);
    popRatioBox->setSingleStep(1);
    popRatioBox->setValue(40);
    popRatioBox->setSuffix("%");
    /* QPushButton *setBtn = new QPushButton(tr("Set")); */

    /* vbox->addWidget(gridSizeLabel); */
    /* vbox->addLayout(hbox); */
    vbox->addWidget(popRatioLabel);
    vbox->addWidget(popRatioBox);
    /* vbox->addWidget(setBtn); */
    prefsBox->setLayout(vbox);
}

void GolWindow::createStatsBox(QGroupBox *statsBox) {
    QVBoxLayout *vbox = new QVBoxLayout;
    iterationLabel = new QLabel(tr("Iterations: 0"));
    aliveCellsLabel = new QLabel(tr("Alive cells: 0"));
    vbox->addWidget(iterationLabel);
    vbox->addWidget(aliveCellsLabel);
    statsBox->setLayout(vbox);
}
void GolWindow::createSignals() {
    connect(startBtn, &QPushButton::clicked, board, &GolBoard::start);
    connect(pauseBtn, &QPushButton::clicked, board, &GolBoard::pause);
    connect(populateBtn, &QPushButton::clicked, board, &GolBoard::populate);
    connect(clearBtn, &QPushButton::clicked, board, &GolBoard::reset);
    connect(speedSlider, &QSlider::valueChanged, board, &GolBoard::setTimeoutTime);
    connect(speedSlider, &QSlider::valueChanged, this, &GolWindow::changeSliderLabel);
    /* new connect syntax doesn't work with overloaded methods, using old one*/
    connect(popRatioBox, SIGNAL(valueChanged(int)), board, SLOT(setPopRatio(int)));

    connect(board, &GolBoard::changeLabel, this, &GolWindow::changeLabel);
    connect(board, &GolBoard::checkPauseBtn, this, &GolWindow::checkPauseBtn);
    connect(board, &GolBoard::setMinSizeScrollArea, this, &GolWindow::setMinSizeScrollArea);
    connect(board, &GolBoard::justifyBoardZoom, this, &GolWindow::justifyBoardZoom);
}

void GolWindow::justifyBoardZoom(int x, int y) {
    int offset_x = scrollArea->horizontalScrollBar()->value();
    int offset_y = scrollArea->verticalScrollBar()->value();
    scrollArea->horizontalScrollBar()->setValue(x+offset_x);
    scrollArea->verticalScrollBar()->setValue(y+offset_y);
}

void GolWindow::setMinSizeScrollArea() {
    QWidget *vp = scrollArea->viewport();
    int boardTotalWidth = board->width()+board->frameWidth()*2;
    int boardTotalHeight= board->height()+board->frameWidth()*2;

    if (vp->width() > boardTotalWidth || vp->height() > boardTotalHeight) {
        scrollArea->setMinimumSize(boardTotalWidth, boardTotalHeight);
    }
}
