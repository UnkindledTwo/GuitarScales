#ifndef GUITARSCALES_H
#define GUITARSCALES_H

#include <QMainWindow>
#include "colorpickerdialog.h"
#include "guitarwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GuitarScales; }
QT_END_NAMESPACE

class GuitarScales : public QMainWindow
{
    Q_OBJECT

public:
    GuitarScales(QWidget *parent = nullptr);
    ~GuitarScales();

private slots:
    void on_bSet_clicked();

    void on_cbScaleDegrees_stateChanged(int arg1);

    void on_cbNote_currentIndexChanged(int index);

    void on_cbMode_currentIndexChanged(int index);

    void on_actionSet_Colors_triggered();

private:
    Ui::GuitarScales *ui;

    GuitarWidget *gw;
};
#endif // GUITARSCALES_H
