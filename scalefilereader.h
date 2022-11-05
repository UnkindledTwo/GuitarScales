#ifndef SCALEFILEREADER_H
#define SCALEFILEREADER_H

#include <QString>
#include <QVector>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonObject>

#include "globals.h"

class ScaleFileReader
{
public:
    ScaleFileReader();

    static void readFromFile(QString fileName);
};

#endif // SCALEFILEREADER_H
