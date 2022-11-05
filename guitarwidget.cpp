#include "guitarwidget.h"

GuitarWidget::GuitarWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setMinimumSize(QSize(840, 240));
    notesToDraw = {"C", "B", "A", "D", "E", "F", "G"};

    majorScale = {0, 2, 4, 5, 7, 9, 11};
}

void GuitarWidget::setScale(QString note, QString name)
{
    if(name == "") return;
    notesToDraw.clear();

    QVector<int> formula = {};

    qDebug() << name;
    qDebug() << Globals.scaleNames.indexOf(name);

    intervals = Globals.scaleIntervals[Globals.scaleNames.indexOf(name)];
    foreach (QString interval, Globals.scaleIntervals[Globals.scaleNames.indexOf(name)]) {
        qDebug() << interval;
        if (interval.startsWith('b')) {
            interval = interval.remove(0, 1);
            notesToDraw.append(notes[(majorScale[interval.toInt() - 1] + notes.indexOf(note) - 1) % 12]);
        }
        else if(interval.startsWith('#')) {
            interval = interval.remove(0, 1);
            notesToDraw.append(notes[(majorScale[interval.toInt() - 1] + notes.indexOf(note) + 1) % 12]);
        }
        else {
            notesToDraw.append(notes[(majorScale[interval.toInt() - 1] + notes.indexOf(note)) % 12]);
        }

    }
/*

    //Minor
    int minorStart = notes.indexOf(note);
    QVector<int> minorScale = {};

    QVector<int> minorformula = {2, 1, 2, 2, 1, 2};

    foreach (int i, minorformula) {
        minorScale.append(minorStart % 12);
        minorStart += i;
    }

    minorScale.append(minorStart % 12);


    switch (type) {
    case ScaleType::Major:
        foreach (int i, majorScale) {
            notesToDraw.append(notes[i]);
        }
        break;
    case ScaleType::Minor:
        foreach (int i, minorScale) {
            notesToDraw.append(notes[i]);
        }
        break;
    case ScaleType::MelodicMinor:{
        intervals = {"1", "2", "b3", "4", "5", "b6", "b7"};

        QVector<int> majorFormula = {2, 2, 1, 2, 2, 2};
        int majorStart = notes.indexOf(note);
        QVector<int> majorScale = {};

        foreach (int i, majorFormula) {
            majorScale.append(majorStart % 12);
            majorStart += i;
        }

        majorScale.append(majorStart % 12);

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1]) % 12]);
        notesToDraw.append(notes[(majorScale[2] - 1) % 12]);
        notesToDraw.append(notes[majorScale[3] % 12]);
        notesToDraw.append(notes[majorScale[4] % 12]);
        notesToDraw.append(notes[(majorScale[5] - 1) % 12]);
        notesToDraw.append(notes[(majorScale[6]) % 12]);

        break;
    }
    case ScaleType::PentatonicMajor:{
        intervals = {"1", "2", "3", "5", "6"};

        notesToDraw.append(notes[majorScale[0]]);
        notesToDraw.append(notes[majorScale[1]]);
        notesToDraw.append(notes[majorScale[2]]);
        notesToDraw.append(notes[majorScale[4]]);
        notesToDraw.append(notes[majorScale[5]]);
        break;
    }
    case ScaleType::PentatonicMinor:{
        intervals = {"1", "b3", "p4", "p5", "b7"};

        notesToDraw.append(notes[minorScale[0]]);
        notesToDraw.append(notes[minorScale[1]]);
        notesToDraw.append(notes[minorScale[2]]);
        notesToDraw.append(notes[minorScale[4]]);
        notesToDraw.append(notes[minorScale[5]]);
        break;
    }
    case ScaleType::Diminished: {
        intervals = {"1", "9", "b3", "11", "b5", "#5", "13", "7"};
        formula = {2, 1, 2, 1, 2, 1, 2};
        int start = notes.indexOf(note);
        notesToDraw.append(notes[start]);
        for(int i = 0; i < formula.count(); i++) {
            start += formula[i];
            notesToDraw.append(notes[start % 12]);
        }
        break;
    }
    case ScaleType::Phrygian: {
        intervals = {"1", "b2", "b3", "4", "5", "b6", "b7"};

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1] - 1) % 12]);
        notesToDraw.append(notes[(majorScale[2] - 1) % 12]);
        notesToDraw.append(notes[majorScale[3] % 12]);
        notesToDraw.append(notes[majorScale[4] % 12]);
        notesToDraw.append(notes[(majorScale[5] - 1) % 12]);
        notesToDraw.append(notes[(majorScale[6] - 1) % 12]);
        break;
    }
    case ScaleType::Lydian: {
        intervals = {"1", "2", "3", "#4", "5", "6", "7"};

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1]) % 12]);
        notesToDraw.append(notes[(majorScale[2]) % 12]);
        notesToDraw.append(notes[(majorScale[3] +1) % 12]);
        notesToDraw.append(notes[(majorScale[4]) % 12]);
        notesToDraw.append(notes[(majorScale[5]) % 12]);
        notesToDraw.append(notes[(majorScale[6]) % 12]);
        break;
    }
    case ScaleType::LydianAugmented: {
        intervals = {"1", "2", "3", "#4", "#5", "6", "7"};

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1]) % 12]);
        notesToDraw.append(notes[(majorScale[2]) % 12]);
        notesToDraw.append(notes[(majorScale[3] + 1) % 12]);
        notesToDraw.append(notes[(majorScale[4] + 1) % 12]);
        notesToDraw.append(notes[(majorScale[5]) % 12]);
        notesToDraw.append(notes[(majorScale[6]) % 12]);
        break;
    }
    case ScaleType::LydianMinor: {
        intervals = {"1", "2", "3", "#4", "5", "b6", "b7"};

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1]) % 12]);
        notesToDraw.append(notes[(majorScale[2]) % 12]);
        notesToDraw.append(notes[(majorScale[3] +1) % 12]);
        notesToDraw.append(notes[(majorScale[4]) % 12]);
        notesToDraw.append(notes[(majorScale[5] - 1) % 12]);
        notesToDraw.append(notes[(majorScale[6] - 1) % 12]);
        break;
    }
    case ScaleType::LydianDiminished: {
        intervals = {"1", "2", "b3", "#4", "5", "6", "7"};

        notesToDraw.append(notes[majorScale[0] % 12]);
        notesToDraw.append(notes[(majorScale[1]) % 12]);
        notesToDraw.append(notes[(majorScale[2] - 1) % 12]);
        notesToDraw.append(notes[(majorScale[3] +1) % 12]);
        notesToDraw.append(notes[(majorScale[4]) % 12]);
        notesToDraw.append(notes[(majorScale[5]) % 12]);
        notesToDraw.append(notes[(majorScale[6]) % 12]);
        break;
    }
    case ScaleType::Chromatic:
        intervals = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"};
        formula = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        int s = 0;
        foreach (int i, formula) {
            notesToDraw.append(notes[s]);
            s+=i;
        }
        break;
    }
*/
    this->repaint();
}

void GuitarWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter = QPainter(this);
    QRect geometry = this->geometry();

    const int FRETBOARD_PADDING = geometry.height() / STRING_COUNT;
    painter.setViewport(QRect(5, 5, geometry.width() - 10, geometry.height() - 10));

    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    qDebug() << "GuitarWidget geometry: " << geometry;

    int fret_width = (geometry.width()) / (FRET_COUNT);
    int fret_height = (geometry.height() - FRETBOARD_PADDING) / (STRING_COUNT);

    painter.fillRect(this->rect(), Qt::white);
    painter.setPen(Qt::black);

    //Draw strings
    painter.setPen(QPen(QColor("#A0A0A0"), 3));
    for(int i = 0; i < STRING_COUNT; i++) {
        painter.drawLine(QLine(
                     fret_width,
                     FRETBOARD_PADDING + (i * fret_height),
                     ((FRET_COUNT - 1) * fret_width),
                     FRETBOARD_PADDING + (i * fret_height)));
    }

    painter.setPen(Qt::black);
    //Draw frets
    for(int i = 1; i < FRET_COUNT; i++) {
        if(i == 1) {
        auto pen = painter.pen();
        painter.fillRect(QRect(i* fret_width - 2, FRETBOARD_PADDING - 12, 4, ((STRING_COUNT - 1) * fret_height) + 24), Qt::black);
        painter.setPen(pen);
        }
        else {
        painter.drawRect(QRect(i* fret_width - 2, FRETBOARD_PADDING - 12, 4, ((STRING_COUNT - 1) * fret_height) + 24));
        }
    }
    painter.setPen(Qt::black);

    QFont font = painter.font();
    font.setFamily(QFont().defaultFamily());
    font.setPointSize(12);
    font.setWeight(QFont::Bold);
    painter.setFont(font);

    //Draw fret numbers
    for(int i = 0; i < FRET_COUNT - 1; i++) {
        painter.drawText(QRect(i * fret_width + (fret_width / 2) - 5, 0, i * fret_width + 30, FRETBOARD_PADDING - (fret_height / 2)), Qt::AlignBottom, QString::number(i));
    }

    font.setWeight(QFont::Normal);
    painter.setFont(font);

    //Draw fret indicators (on 3, 5, 7, 9, 12...th frets)
    for(int i = 0; i < FRET_COUNT - 1; i++) {
        if(i % 12 == 3 || i % 12 == 5 || i % 12 == 7 || i % 12 == 9) {
            painter.setBrush(QColor("#C0C0C0"));
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2), fret_height * 6.7), fret_width / 7, fret_width / 7);/* QRect(i * fret_width - (fret_width / 2), fret_height * 6 + 15, 30, FRETBOARD_PADDING - (fret_height / 2)));*/

        }
        else if(i % 12 == 0 && i != 0) {
            painter.setBrush(QColor("#C0C0C0"));
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2) - 7, fret_height * 6.7), fret_width / 7, fret_width / 7);
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2) + 7, fret_height * 6.7), fret_width / 7, fret_width / 7);
        }
    }

    //Draw the scale
    for(int i = 0; i < notesToDraw.count(); i++) {
        if(i == 0) {
            painter.setBrush(highlightNoteColor);
        }
        else {
            painter.setBrush(noteColor);
        }
        foreach (QPoint p, locationFromNote(notesToDraw[i])) {
            //drawNote(noteRect(p.x(), p.y(), fret_width, fret_height, FRETBOARD_PADDING), notesToDraw[i], painter);
            drawNote(p.x(), p.y(), fret_width, fret_height, FRETBOARD_PADDING, notesToDraw[i], painter);
        }
    }
}

void GuitarWidget::drawNote(int fret, int string, int fret_width, int fret_height, int fretboard_padding, QString note, QPainter &painter)
{
    int x = fret * fret_width + fret_width / 2;
    int y = fretboard_padding + fret_height * string;

    int size = qMin(fret_width, fret_height) / 2.5;

    auto pen = painter.pen();
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(QPoint(x, y), size, size);
    painter.setPen(pen);

    QFont font = painter.font();
    font.setPointSizeF(qMin(fret_width / 4, fret_height / 4));
    painter.setFont(font);

    if(showIntervals) {
        int index = notesToDraw.indexOf(note);
        painter.drawText(QRect(fret * fret_width, fretboard_padding + fret_height * (string) - (fret_height / 2), fret_width, fret_height),
                Qt::AlignCenter, intervals[index]);
    }
    else {
        painter.drawText(QRect(fret * fret_width, fretboard_padding + fret_height * (string) - (fret_height / 2), fret_width, fret_height),
                Qt::AlignCenter, note);
    }
}

QRect GuitarWidget::noteRect(int fret, int string, int fret_width, int fret_height, const int fretboard_padding)
{
    return QRect ((fret * fret_width) + (fret_width / 7),
              fretboard_padding + fret_height * string - (fret_height / 4),
              fret_width / 1.5,
              fret_height / 1.5);
}

QString GuitarWidget::noteFromLocation(int fret, int string)
{
    int starting = strings[string];
    for(int i = 0; i < fret; i++) {
        starting++;
    }

    return notes[starting % 12];
}

QVector<QPoint> GuitarWidget::locationFromNote(QString note)
{
    QVector<QPoint> ret;
    for(int i = 0; i < FRET_COUNT - 1; i++) {
        for(int j = 0; j < STRING_COUNT; j++) {
            if(noteFromLocation(i, j) == note) {
                ret.append(QPoint(i, j));
            }
        }
    }
    return ret;
}
