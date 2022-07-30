#include "guitarwidget.h"

GuitarWidget::GuitarWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setMinimumSize(QSize(840, 240));
    notesToDraw = {"C", "B", "A", "D", "E", "F", "G"};
}

void GuitarWidget::setScale(QString note, ScaleType type)
{
    notesToDraw.clear();

    int start = notes.indexOf(note);
    QVector<int> formula = {};

    switch (type) {
    case ScaleType::Major:
        formula = {2, 2, 1, 2, 2, 2};
        intervals = {"1", "2", "3", "4", "5", "6", "7"};

        foreach (int i, formula) {
            notesToDraw.append(notes[start % 12]);
            start += i;
        }

        notesToDraw.append(notes[start % 12]);
        break;
    case ScaleType::Minor:
        formula = {2, 1, 2, 2, 1, 2};
        intervals = {"1", "2", "b3", "4", "5", "b6", "b7"};

        foreach (int i, formula) {
            notesToDraw.append(notes[start % 12]);
            start += i;
        }

        notesToDraw.append(notes[start % 12]);
        break;
    case ScaleType::PentatonicMajor:{
        QVector<int> majorFormula = {2, 2, 1, 2, 2, 2};
        intervals = {"1", "2", "3", "5", "6"};
        int majorStart = notes.indexOf(note);
        QVector<QString> majorScale = {};

        foreach (int i, majorFormula) {
            majorScale.append(notes[majorStart % 12]);
            majorStart += i;
        }

        majorScale.append(notes[majorStart % 12]);

        notesToDraw.append(majorScale[0]);
        notesToDraw.append(majorScale[1]);
        notesToDraw.append(majorScale[2]);
        notesToDraw.append(majorScale[4]);
        notesToDraw.append(majorScale[5]);
        break;
    }
    case ScaleType::PentatonicMinor:{
        int minorStart = notes.indexOf(note);
        intervals = {"1", "b3", "p4", "p5", "b7"};
        QVector<QString> minorScale = {};

        QVector<int> minorformula = {2, 1, 2, 2, 1, 2};

        foreach (int i, minorformula) {
            minorScale.append(notes[minorStart % 12]);
            minorStart += i;
        }

        minorScale.append(notes[minorStart % 12]);

        notesToDraw.append(minorScale[0]);
        notesToDraw.append(minorScale[2]);
        notesToDraw.append(minorScale[3]);
        notesToDraw.append(minorScale[4]);
        notesToDraw.append(minorScale[6]);
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

    this->repaint();
}

void GuitarWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter = QPainter(this);
    QRect geometry = this->geometry();

    const int FRETBOARD_PADDING = geometry.height() / STRING_COUNT;
    painter.setViewport(QRect(geometry.width() / FRET_COUNT, 5, geometry.width() - 10, geometry.height() - 10));

    painter.setRenderHint(QPainter::HighQualityAntialiasing);

    qDebug() << "GuitarWidget geometry: " << geometry;

    int fret_width = (geometry.width()) / (FRET_COUNT);
    int fret_height = (geometry.height() - FRETBOARD_PADDING) / (STRING_COUNT);

    painter.fillRect(this->rect(), Qt::white);
    painter.setPen(Qt::black);

    //Draw frets
    for(int i = 1; i < FRET_COUNT; i++) {
        if(i == 1) {
        auto pen = painter.pen();
        painter.fillRect(QRect(i* fret_width - 2, FRETBOARD_PADDING - 12, 4, ((STRING_COUNT - 1) * fret_height) + 24), Qt::black);
                /*
        painter.drawLine(QLine(
                     (i * fret_width),
                     FRETBOARD_PADDING,
                     (i * fret_width),
                     FRETBOARD_PADDING + ((STRING_COUNT - 1) * fret_height)));
                             */
        painter.setPen(pen);
        }
        else {
        painter.drawRect(QRect(i* fret_width - 2, FRETBOARD_PADDING - 12, 4, ((STRING_COUNT - 1) * fret_height) + 24));
        /*
        painter.drawLine(QLine(
                     (i * fret_width),
                     FRETBOARD_PADDING,
                     (i * fret_width),
                     FRETBOARD_PADDING + ((STRING_COUNT - 1) * fret_height)));
                     */
        }
    }

    //Draw strings
    for(int i = 0; i < STRING_COUNT; i++) {
        painter.drawLine(QLine(
                     fret_width,
                     FRETBOARD_PADDING + (i * fret_height),
                     ((FRET_COUNT - 1) * fret_width),
                     FRETBOARD_PADDING + (i * fret_height)));
    }

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
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2), fret_height * 6.7), fret_width / 5, fret_width / 5);/* QRect(i * fret_width - (fret_width / 2), fret_height * 6 + 15, 30, FRETBOARD_PADDING - (fret_height / 2)));*/
        }
        else if(i % 12 == 0 && i != 0) {
            painter.setBrush(QColor("#C0C0C0"));
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2) - 5, fret_height * 6.7), fret_width / 6, fret_width / 6);
            painter.drawEllipse(QPoint(i * fret_width + (fret_width / 2) + 5, fret_height * 6.7), fret_width / 6, fret_width / 6);
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
