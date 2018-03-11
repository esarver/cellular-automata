#include <QtWidgets>

#include "golwindow.h"

/*
 * NOTE: The base of this game was copied from https://github.com/sgelb/gameoflife
 * I did not create this from scratch. Thanks sgelb!
*/

int main(int argc, char *argv[])
{
    qsrand(3029);

    QApplication a(argc, argv);
    GolWindow window;
    window.show();
    return a.exec();
}
