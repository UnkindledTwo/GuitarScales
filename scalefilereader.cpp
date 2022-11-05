#include "scalefilereader.h"

ScaleFileReader::ScaleFileReader()
{

}

void ScaleFileReader::readFromFile(QString fileName)
{
    QJsonDocument doc;
    {
        QFile f(fileName);
        f.open(QIODevice::ReadOnly);

        doc = QJsonDocument::fromJson(f.readAll());
    }

    QJsonArray array = doc.array();

    qDebug() << array.toVariantList();

    for(auto o : array) {
        QJsonObject jObject = o.toObject();

        qDebug() << jObject["Name"];
        Globals.scaleNames.append(jObject["Name"].toString());

        QJsonArray intervalArray = jObject["Intervals"].toArray();

        Globals.scaleIntervals.append(QVector<QString>());
        for (auto iO : intervalArray) {
            Globals.scaleIntervals.last().append(iO.toString());
        }
    }
}
