#ifndef GUITARWIDGET_H
#define GUITARWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QColor>

#define FRET_COUNT 26
#define STRING_COUNT 6

enum ScaleType {
    Major,
    Minor,
    MelodicMinor,
    PentatonicMinor,
    PentatonicMajor,
    Diminished,
    Phrygian,
    Lydian,
    LydianMinor,
    LydianAugmented,
    LydianDiminished,
    Chromatic,
};

class GuitarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GuitarWidget(QWidget *parent = nullptr);

    void setScale(QString note, ScaleType type);

    bool showIntervals = false;

    QColor highlightNoteColor = QColor("#B19CD9");
    QColor noteColor = QColor("#C0C0C0");

protected:
    void paintEvent(QPaintEvent*);
signals:

private:
    QVector<QString> notes = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    QVector<QString> intervals = {};
    int strings[6] = {7, 2, 10, 5, 0, 7};

    QVector<QString> notesToDraw = {};

    void drawNote(int fret, int string, int fret_width, int fret_height, int fretboard_padding, QString note, QPainter& painter);
    QRect noteRect(int fret, int string, int fret_width, int fret_height, const int fretboard_padding);
    QString noteFromLocation(int fret, int string);
    QVector<QPoint> locationFromNote(QString note);

};

#endif // GUITARWIDGET_H
