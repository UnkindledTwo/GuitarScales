#include "guitarscales.h"
#include "ui_guitarscales.h"

GuitarScales::GuitarScales(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GuitarScales)
{
    ui->setupUi(this);
    gw = new GuitarWidget(this);

    ui->gridLayout->addWidget(gw);

    qDebug() << Globals.scaleNames;
    foreach (QString name, Globals.scaleNames) {
        ui->cbMode->addItem(name);
    }

    foreach(auto a, Globals.scaleIntervals) {
        qDebug() << a;
    }

    gw->noteColor = QColor(settings.value("noteColor", "#C0C0C0").toString());
    gw->highlightNoteColor = QColor(settings.value("highlightNoteColor", "#B19CD9").toString());
    //gw->setScale(settings.value("note", "A").toString(), settings.value("name", "Major").toString());
    ui->cbNote->setCurrentText(settings.value("note", "A").toString());
    ui->cbMode->setCurrentText(settings.value("name", "Major").toString());
    ui->cbScaleDegrees->setChecked(settings.value("showIntervals", false).toBool());
    on_bSet_clicked();
    gw->repaint();

    //QColor highlightNoteColor = QColor("#B19CD9");
    //QColor noteColor = QColor("#C0C0C0");
}

GuitarScales::~GuitarScales()
{
    settings.setValue("noteColor", gw->noteColor.name());
    settings.setValue("highlightNoteColor", gw->highlightNoteColor.name());

    settings.setValue("name", gw->scaleName);
    settings.setValue("note", gw->scaleNote);

    settings.setValue("showIntervals", ui->cbScaleDegrees->isChecked());

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

