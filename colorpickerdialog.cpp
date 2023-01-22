#include "colorpickerdialog.h"
#include "ui_colorpickerdialog.h"

ColorPickerDialog::ColorPickerDialog(QWidget *parent, QColor noteColor, QColor highlightNoteColor) :
    QDialog(parent),
    ui(new Ui::ColorPickerDialog)
{
    setNoteColor(noteColor);
    setHighlightNoteColor(highlightNoteColor);
    ui->setupUi(this);
}

ColorPickerDialog::~ColorPickerDialog()
{
    delete ui;
}

void ColorPickerDialog::on_bNoteColor_clicked()
{
    QColor c = QColorDialog::getColor(noteColor(), this, "Select Note Color");
    if(c.isValid()) {
        setNoteColor(c);
    }
}


void ColorPickerDialog::on_bHighlightNoteColor_clicked()
{
    QColor c = QColorDialog::getColor(highlightNoteColor(), this, "Select Highlight Note Color");
    if(c.isValid()) {
        setHighlightNoteColor(c);
    }
}

