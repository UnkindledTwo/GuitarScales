#include "guitarscales.h"
#include "ui_guitarscales.h"

GuitarScales::GuitarScales(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GuitarScales)
{
    ui->setupUi(this);
    gw = new GuitarWidget(this);

    ui->gridLayout->addWidget(gw);

    on_bSet_clicked();
}

GuitarScales::~GuitarScales()
{
    delete ui;
}

void GuitarScales::on_bSet_clicked()
{
    ScaleType type;
    QString note;

    ui->lScaleName->setText(ui->cbNote->currentText() + " " + ui->cbMode->currentText());

    QString strType = ui->cbMode->currentText();
    if(strType == "Major") type = ScaleType::Major;
    else if(strType == "Minor") type = ScaleType::Minor;
    else if(strType == "Pentatonic Major") type = ScaleType::PentatonicMajor;
    else if(strType == "Pentatonic Minor") type = ScaleType::PentatonicMinor;
    else if(strType == "Chromatic") type = ScaleType::Chromatic;

    note = ui->cbNote->currentText();

    gw->setScale(note, type);
}

void GuitarScales::on_cbScaleDegrees_stateChanged(int arg1)
{
    gw->showIntervals = ui->cbScaleDegrees->isChecked();
    gw->repaint();
}


void GuitarScales::on_cbNote_currentIndexChanged(int index)
{
    on_bSet_clicked();
}


void GuitarScales::on_cbMode_currentIndexChanged(int index)
{
    on_bSet_clicked();
}


void GuitarScales::on_actionSet_Colors_triggered()
{
    ColorPickerDialog *cpd = new ColorPickerDialog(this, gw->noteColor, gw->highlightNoteColor);
    if(cpd->exec()) {
        gw->noteColor = cpd->noteColor();
        gw->highlightNoteColor = cpd->highlightNoteColor();

        gw->repaint();
    }
}

