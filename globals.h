#ifndef GLOBALS_H
#define GLOBALS_H

#include <QVector>

struct global {
    QVector<QString> scaleNames;
    QVector<QVector<QString>> scaleIntervals;
};

extern struct global Globals;

#endif // GLOBALS_H
