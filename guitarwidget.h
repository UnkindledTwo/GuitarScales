#ifndef GUITARWIDGET_H
#define GUITARWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QColor>

#include "globals.h"

#define FRET_COUNT 26
#define STRING_COUNT 6

class GuitarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GuitarWidget(QWidget *parent = nullptr);

    void setScale(QString note, QString name);
    void refresh();

    QVector<QString> notes = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    QVector<QString> intervals = {};

    bool showIntervals = false;

    QColor highlightNoteColor = QColor("#B19CD9");
    QColor noteColor = QColor("#C0C0C0");

    QString scaleName = "Major";
    QString scaleNote = "A";

    QVector<QString> ignoredIntervals = {};
protected:
    void paintEvent(QPaintEvent*);
signals:

private:
    int strings[6] = {7, 2, 10, 5, 0, 7};

    QVector<QString> notesToDraw = {};

    void drawNote(int fret, int string, int fret_width, int fret_height, int fretboard_padding, QString note, QPainter& painter);
    QRect noteRect(int fret, int string, int fret_width, int fret_height, const int fretboard_padding);
    QString noteFromLocation(int fret, int string);
    QVector<QPoint> locationFromNote(QString note);

    QVector<int> majorScale;

    QString m_note;
    QString m_name;
};

#endif // GUITARWIDGET_H
