#include "guitarscales.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GuitarScales w;
    w.show();
    return a.exec();
}
