#include "guitarscales.h"

#include <QApplication>

#include "globals.h"
#include "scalefilereader.h"

struct global Globals;

int main(int argc, char *argv[])
{
    QCoreApplication::setApplicationName("GuitarScales");
    QCoreApplication::setOrganizationName("UnkindledTwo");

    ScaleFileReader::readFromFile(":/Resources/scales.json");
    ScaleFileReader::readFromFile("scales.json");

    QApplication a(argc, argv);
    GuitarScales w;
    w.show();
    return a.exec();
}
