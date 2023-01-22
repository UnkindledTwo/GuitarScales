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
    this->scaleName = name;
    this->scaleNote = note;

    m_name = name;
    m_note = note;
    notesToDraw.clear();

    QVector<int> formula = {};

    qDebug() << name;
    qDebug() << Globals.scaleNames.indexOf(name);

    intervals = Globals.scaleIntervals[Globals.scaleNames.indexOf(name)];
    foreach (QString i, ignoredIntervals) {
        if (intervals.indexOf(i) > -1) {
            intervals.remove(intervals.indexOf(i), 1);
        }
    }
    foreach (QString interval, intervals) {
        qDebug() << interval;
        /*if(ignoredIntervals.indexOf(interval) > -1) {
            notesToDraw.append("ignore");
        }*/
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
    this->repaint();
}

void GuitarWidget::refresh()
{
    setScale(m_note, m_name);
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
        if(i == 0 && ignoredIntervals.indexOf("1") < 0) {
            painter.setBrush(highlightNoteColor);
        }
        else {
            painter.setBrush(noteColor);
        }
        QColor bColor = painter.brush().color();
        QColor bColorInv = QColor::fromRgb(255 - bColor.red(), 255 - bColor.green(), 255 - bColor.blue());
        painter.setPen(bColorInv);
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
