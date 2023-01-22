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
    gw->ignoredIntervals.clear();
    gw->setScale(note, ui->cbMode->currentText());

    foreach (QCheckBox* w, intervalBoxes) {
        ui->hlIntervals->removeWidget(w);
        intervalBoxes.removeAll(w);
        w->deleteLater();
    }
    foreach (QString interval, gw->intervals) {
        QCheckBox *intervalBox = new QCheckBox(this);
        intervalBox->setText(interval);
        intervalBox->setChecked(true);
        connect(intervalBox, &QCheckBox::toggled, this, &GuitarScales::intervalBoxChecked);
        intervalBoxes.append(intervalBox);
        ui->hlIntervals->addWidget(intervalBox);
    }
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

void GuitarScales::intervalBoxChecked(bool state)
{
    QCheckBox* object = (QCheckBox*)sender();
    qDebug() << object->text() << state;
    if (state == false) gw->ignoredIntervals.append(object->text());
    else if (state == true) gw->ignoredIntervals.remove(gw->ignoredIntervals.indexOf(object->text()), 1);
    gw->refresh();
}

