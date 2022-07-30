#ifndef COLORPICKERDIALOG_H
#define COLORPICKERDIALOG_H

#include <QDialog>
#include <QColorDialog>

#include "guitarwidget.h"

namespace Ui {
class ColorPickerDialog;
}

class ColorPickerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ColorPickerDialog(QWidget *parent = nullptr, QColor noteColor = QColor("#C0C0C0"), QColor highlightNoteColor = QColor("#B19CD9"));
    ~ColorPickerDialog();

    void setNoteColor(QColor a) {
        m_noteColor = a;
    }
    QColor noteColor() {
        return m_noteColor;
    }
    void setHighlightNoteColor(QColor a) {
        m_hightlightNoteColor = a;
    }
    QColor highlightNoteColor() {
        return m_hightlightNoteColor;
    }

private slots:
    void on_bNoteColor_clicked();

    void on_bHighlightNoteColor_clicked();

private:
    Ui::ColorPickerDialog *ui;

    QColor m_noteColor;
    QColor m_hightlightNoteColor;
};

#endif // COLORPICKERDIALOG_H
