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

    qDebug() << Globals.scaleNames;
    foreach (QString name, Globals.scaleNames) {
        ui->cbMode->addItem(name);
    }

    foreach(auto a, Globals.scaleIntervals) {
        qDebug() << a;
    }
}

GuitarScales::~GuitarScales()
{
    delete ui;
}

void GuitarScales::on_bSet_clicked()
{
    QString note;

    ui->lScaleName->setText(ui->cbNote->currentText() + " " + ui->cbMode->currentText());

    note = ui->cbNote->currentText();
    gw->setScale(note, ui->cbMode->currentText());
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

