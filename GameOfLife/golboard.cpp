#include <QtWidgets>
#include <algorithm>
#include <numeric>
#include <functional>

#include "./golboard.h"

GolBoard::GolBoard(QWidget *parent) : QFrame(parent) {
    std::srand(time(0));
    setFrameStyle(QFrame::Panel);
    setMouseTracking(true);
    boardHeight = 100;
    boardWidth = 100;
    cellsize = 4;
    isPaused = true;
    iteration = 0;
    timeoutTime = 25;
    popRatio = 0.4f;
    populate();
}

int GolBoard::countAliveCells() {
  return std::accumulate(grid.begin(), grid.end(), 0, std::plus<int>());
}

void GolBoard::drawCell(QPainter &painter, int x, int y) {
    QColor color = Qt::black;
    painter.fillRect(x*cellsize+1, y*cellsize+1, cellsize, cellsize, color);
}

void GolBoard::iterate() {
    tmp_grid.clear();
    for (int i = 0; i < boardWidth*boardHeight; i++) {
        tmp_grid << 0;
    }
    for (int n = 0; n < boardWidth*boardHeight; n++) {
        int ncount = neighbor_count(n);

        if ((0 < grid.at(n)) && (2 == ncount || 3 == ncount)) {
            /* Any live cell with two or three live neighbours
             * lives on */
            tmp_grid[n] = 1;
        } else if ((0 == grid.at(n)) && (3 == ncount)) {
          /* Any dead cell with exactly three live neighbours becomes
           * alive */
          tmp_grid[n] = 1;
        }
    }
    grid = tmp_grid;

    iteration++;
    emit changeLabel("iterationLabel", tr("Iterations: %1").arg(iteration));
    emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg(countAliveCells()));
}

void GolBoard::mouseMoveEvent(QMouseEvent *event) {
    int x = (event->x()-frameWidth())/cellsize;
    int y = (event->y()-frameWidth())/cellsize;
    QToolTip::showText(event->globalPos(), tr("(%1,%2)").arg(x).arg(y));
}

void GolBoard::mousePressEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        int x = (event->x()-frameWidth())/cellsize;
        int y = (event->y()-frameWidth())/cellsize;
        int idx = (y*boardWidth + x);

        if (idx < 0 || idx >= boardWidth*boardHeight)
            return;

        if (grid[idx]) {
            grid[idx] = 0;
        } else {
          grid[idx] = 1;
        }
        emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg(countAliveCells()));
        update();
    }
}

int GolBoard::neighbor_count(int n) {
    /* | n-w-1 | n-w | n-w+1 | */
    /* | n-1   | n   | n+1   | */
    /* | n+w-1 | n+w | n+w+1 | */

    int w = boardWidth;
    int ncount = 0;
    /* x- and y-coordinate of n */
    int xCoord = n%w;
    int yCoord = n/w;

    /* check row above n */
    if (yCoord > 0) {
        /* check neighbor NW */
        if (xCoord > 0 && grid.at(n-w-1)) ncount++;
        /* check neighbor N */
        if (grid.at(n-w)) ncount++;
        /* check neighbor NE */
        if (xCoord+1 < w && grid.at(n-w+1)) ncount++;
    }

    /* check neighbor W */
    if (xCoord > 0 && grid.at(n-1)) ncount++;
    /* check neighbor E */
    if (xCoord+1 < w && grid.at(n+1)) ncount++;

    /* check row below n */
    if (yCoord+1 < boardHeight) {
        /* check neighbor SW */
        if (xCoord > 0 && grid.at(n+w-1)) ncount++;
        /* check neighbor S */
        if (grid.at(n+w)) ncount++;
        /* check neighbor SE */
        if (xCoord+1 < w && grid.at(n+w+1)) ncount++;
    }

    return ncount;
}

void GolBoard::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    for (int y = 0; y < boardHeight; y++) {
        for (int x = 0; x < boardWidth; x++) {
            if (grid[y*boardWidth + x]) {
                drawCell(painter, x, y);
            }
        }
    }
}

void GolBoard::pause() {
    if (isPaused) {
        iterate();
        update();
        return;
    }
    isPaused = true;
    timer.stop();
    update();
}

void GolBoard::populate() {
    grid.clear();
    iteration = 0;
    for (int i = 0; i < boardWidth*boardHeight; i++) {
        grid << (rand() < popRatio * static_cast<double>(RAND_MAX + 1.0));
    }
    emit changeLabel("iterationLabel", tr("Iterations: %1").arg(iteration));
    emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg(countAliveCells()));
    update();
}

void GolBoard::reset() {
    grid.clear();
    for (int i = 0; i < boardWidth*boardHeight; i++) {
        grid << 0;
    }
    isPaused = true;
    timer.stop();
    iteration = 0;
    emit changeLabel("iterationLabel", tr("Iterations: %1").arg(iteration));
    emit changeLabel("aliveCellsLabel", tr("Alive cells: %1").arg(countAliveCells()));
    emit checkPauseBtn();
    update();
}

void GolBoard::setBoardSize(int w, int h) {
    boardWidth = w;
    boardHeight = h;
}

void GolBoard::setPopRatio(int value) {
    popRatio = value / 100.0f;
}

void GolBoard::setTimeoutTime(int timeout) {
    timeoutTime = 1000/timeout;
}

QSize GolBoard::sizeHint() const {
    return QSize(boardWidth*cellsize+2*frameWidth(),
        boardHeight*cellsize+2*frameWidth());
}

void GolBoard::start() {
    if (isPaused) {
        isPaused = false;
    }
    timer.start(timeoutTime, this);
}

void GolBoard::timerEvent(QTimerEvent *event) {
    if (event->timerId() == timer.timerId()) {
        iterate();
        timer.start(timeoutTime, this);
        update();
    } else {
        QFrame::timerEvent(event);
    }
}

void GolBoard::wheelEvent(QWheelEvent *event) {
    int old_width = width();
    int old_height = height();
    int tmp_cellsize = cellsize + (event->angleDelta()/120).y();

    if (event->angleDelta().y() < 0) {
        emit setMinSizeScrollArea();
    }

    cellsize = std::max(1, tmp_cellsize);
    resize(boardWidth*cellsize+2*frameWidth(),
           boardHeight*cellsize+2*frameWidth());

    /* calculate new x- and y-position. substraction of old scrollbar value */
    /* is done in justifyBoardZoom() */
    int new_x = (width()*event->x()-old_width*event->x())/old_width;
    int new_y = (height()*event->y()-old_height*event->y())/old_height;
    emit justifyBoardZoom(new_x, new_y);
    update();
}
