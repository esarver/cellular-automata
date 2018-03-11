#ifndef GOLBOARD_H
#define GOLBOARD_H


#include <QBasicTimer>
#include <QFrame>
#include <vector>


class GolBoard : public QFrame {
  Q_OBJECT

 public:
    explicit GolBoard(QWidget *parent = 0);
    QSize sizeHint() const;

 public slots:
    void pause();
    void populate();
    void reset();
    void setBoardSize(int w, int h);
    void setPopRatio(int value);
    void setTimeoutTime(int timeout);
    void start();

 signals:
    void changeLabel(QString, QString);
    void checkPauseBtn();
    void justifyBoardZoom(int x, int y);
    void setMinSizeScrollArea();

 protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void wheelEvent(QWheelEvent *event);

 private:
    int boardHeight;
    int boardWidth;
    int cellsize;
    int countAliveCells();
    void drawCell(QPainter &painter, int x, int y);
    QList<int> grid;
    bool isPaused;
    void iterate();
    int iteration;
    QString iterationText;
    int neighbor_count(int cellnumber);
    double popRatio;
    int timeoutTime;
    QBasicTimer timer;
    QList<int> tmp_grid;
};

#endif // GOLBOARD_H
