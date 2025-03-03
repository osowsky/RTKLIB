//---------------------------------------------------------------------------

#include <QColorDialog>
#include <QShowEvent>

#include "vmapdlg.h"
#include "plotmain.h"
#include "helper.h"

#include "ui_vmapdlg.h"


//---------------------------------------------------------------------------
VecMapDialog::VecMapDialog(Plot *_plot, QWidget *parent)
    : QDialog(parent), plot(_plot), ui(new Ui::VecMapDialog)
{
    ui->setupUi(this);

    rBLayer << ui->rBLayer1 << ui->rBLayer2 <<  ui->rBLayer3 << ui->rBLayer4 << ui->rBLayer5 << ui->rBLayer6 << ui->rBLayer7 << ui->rBLayer8 << ui->rBLayer9 << ui->rBLayer10 << ui->rBLayer11 << ui->rBLayer12;

    btnColor << ui->btnColor1 << ui->btnColor2 << ui->btnColor3 << ui->btnColor4 << ui->btnColor5 << ui->btnColor6 << ui->btnColor7 << ui->btnColor8 << ui->btnColor9 <<
        ui->btnColor10 << ui->btnColor11 << ui->btnColor12;

    btnColorf << ui->btnColor1F << ui->btnColor2F << ui->btnColor3F << ui->btnColor4F << ui->btnColor5F << ui->btnColor6F << ui->btnColor7F << ui->btnColor8F <<
        ui->btnColor9F << ui->btnColor10F << ui->btnColor11F << ui->btnColor12F;

    cBVisible << ui->cBVisible1 << ui->cBVisible2 << ui->cBVisible3 << ui->cBVisible4 << ui->cBVisible5 << ui->cBVisible6 << ui->cBVisible7 << ui->cBVisible8 <<
        ui->cBVisible9 << ui->cBVisible10 << ui->cBVisible11 << ui->cBVisible12;

    connect(ui->btnApply, &QPushButton::clicked, this, &VecMapDialog::saveClose);
    connect(ui->btnClose, &QPushButton::clicked, this, &VecMapDialog::reject);
    connect(ui->btnUp, &QPushButton::clicked, this, &VecMapDialog::moveUp);
    connect(ui->btnDown, &QPushButton::clicked, this, &VecMapDialog::moveDown);

    connect(ui->btnColor1, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor2, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor3, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor4, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor5, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor6, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor7, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor8, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor9, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor10, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor11, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor12, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor1F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor2F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor3F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor4F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor5F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor6F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor7F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor8F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor9F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor10F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor11F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
    connect(ui->btnColor12F, &QPushButton::clicked, this, &VecMapDialog::selectColor);
}
//---------------------------------------------------------------------------
void VecMapDialog::selectColor()
{
    int idx;
    QList<QPushButton*> btnColor;
    btnColor << btnColor << btnColorf;

    idx = btnColor.indexOf(static_cast<QPushButton*>(sender()));
    if (idx >= 0) {
        QColorDialog dialog(this);

        dialog.setCurrentColor(color[idx]);

        if (dialog.exec() != QDialog::Accepted) return;

        color[idx] = dialog.currentColor();
        btnColor[idx]->setStyleSheet(QString("QPushButton {background-color: %1;}").arg(color2String(color[idx])));
    }
}
//---------------------------------------------------------------------------
void VecMapDialog::moveUp()
{
    int layer;

    for (layer = 0; layer < MAXMAPLAYER; layer++)
        if (rBLayer[layer]->isChecked()) break;
    if (layer == MAXMAPLAYER - 1 || layer >= MAXMAPLAYER) return;

    QString name = rBLayer[layer - 1]->text();
    rBLayer[layer - 1]->setText(rBLayer[layer]->text());
    rBLayer[layer]->setText(name);

    bool flag = cBVisible[layer - 1]->isChecked();
    cBVisible[layer - 1]->setChecked(cBVisible[layer]->isChecked());
    cBVisible[layer]->setChecked(flag);

    gisd_t *data = gis_data[layer - 1];
    gis_data[layer - 1] = gis_data[layer];
    gis_data[layer] = data;

    QString lineColor = btnColor[layer - 1]->styleSheet();
    btnColor[layer - 1]->setStyleSheet(btnColor[layer]->styleSheet());
    btnColor[layer]->setStyleSheet(lineColor);

    QString fillColor = btnColorf[layer - 1]->styleSheet();
    btnColorf[layer - 1]->setStyleSheet(btnColorf[layer]->styleSheet());
    btnColorf[layer]->setStyleSheet(fillColor);

    rBLayer[layer - 1]->setChecked(true);
    rBLayer[layer]->setChecked(false);
}
//---------------------------------------------------------------------------
void VecMapDialog::moveDown()
{
    int layer;

    for (layer = 0; layer < MAXMAPLAYER; layer++)
        if (rBLayer[layer]->isChecked()) break;
    if (layer == MAXMAPLAYER - 1 || layer >= MAXMAPLAYER) return;

    QString name = rBLayer[layer + 1]->text();
    rBLayer[layer + 1]->setText(rBLayer[layer]->text());
    rBLayer[layer]->setText(name);

    bool flag = cBVisible[layer + 1]->isChecked();
    cBVisible[layer + 1]->setChecked(cBVisible[layer]->isChecked());
    cBVisible[layer]->setChecked(flag);

    gisd_t *data = gis_data[layer + 1];
    gis_data[layer + 1] = gis_data[layer];
    gis_data[layer] = data;

    QString lineColor = btnColor[layer + 1]->styleSheet();
    btnColor[layer + 1]->setStyleSheet(btnColor[layer]->styleSheet());
    btnColor[layer]->setStyleSheet(lineColor);

    QString fillColor = btnColorf[layer + 1]->styleSheet();
    btnColorf[layer + 1]->setStyleSheet(btnColorf[layer]->styleSheet());
    btnColorf[layer]->setStyleSheet(fillColor);

    rBLayer[layer + 1]->setChecked(true);
    rBLayer[layer]->setChecked(false);
}
//---------------------------------------------------------------------------
void VecMapDialog::showEvent(QShowEvent *event)
{
    if (event->spontaneous()) return;

    for (int i = 0; i < MAXMAPLAYER; i++) {
        rBLayer[i]->setText(plot->gis.name[i]);
        cBVisible[i]->setChecked(plot->gis.flag[i]);
        gis_data[i] = plot->gis.data[i];
    }
}
//---------------------------------------------------------------------------
void VecMapDialog::saveClose()
{
    for (int i = 0; i < MAXMAPLAYER; i++) {
        strncpy(plot->gis.name[i], qPrintable(rBLayer[i]->text()), 255);
        plot->gis.flag[i] = cBVisible[i]->isChecked();
        mapColor[i] = color[i];
        mapColor[i+12] = color[i+12];
        plot->gis.data[i] = gis_data[i];
    }

    accept();
}
//---------------------------------------------------------------------------
QColor VecMapDialog::getMapColor(int i)
{
    return mapColor[i];
}
//---------------------------------------------------------------------------
QColor VecMapDialog::getMapColorF(int i)
{
    return mapColor[i + 12];
}
//---------------------------------------------------------------------------
void VecMapDialog::loadOptions(QSettings &settings)
{
    mapColor[0] = settings.value("plot/mapcolor1", QColor(0xc0, 0xc0, 0xc0)).value<QColor>();
    mapColor[1] = settings.value("plot/mapcolor2", QColor(0xc0, 0xc0, 0xc0)).value<QColor>();
    mapColor[2] = settings.value("plot/mapcolor3", QColor(0xf0, 0xd0, 0xd0)).value<QColor>();
    mapColor[3] = settings.value("plot/mapcolor4", QColor(0xd0, 0xf0, 0xd0)).value<QColor>();
    mapColor[4] = settings.value("plot/mapcolor5", QColor(0xd0, 0xd0, 0xf0)).value<QColor>();
    mapColor[5] = settings.value("plot/mapcolor6", QColor(0xd0, 0xf0, 0xf0)).value<QColor>();
    mapColor[6] = settings.value("plot/mapcolor7", QColor(0xf8, 0xf8, 0xd0)).value<QColor>();
    mapColor[7] = settings.value("plot/mapcolor8", QColor(0xf0, 0xf0, 0xf0)).value<QColor>();
    mapColor[8] = settings.value("plot/mapcolor9", QColor(0xf0, 0xf0, 0xf0)).value<QColor>();
    mapColor[9] = settings.value("plot/mapcolor10", QColor(0xf0, 0xf0, 0xf0)).value<QColor>();
    mapColor[10] = settings.value("plot/mapcolor11", QColor(Qt::white)).value<QColor>();
    mapColor[11] = settings.value("plot/mapcolor12", QColor(Qt::white)).value<QColor>();
    mapColor[0] = settings.value("plot/mapcolorf1", QColor(Qt::white)).value<QColor>();
    mapColor[1] = settings.value("plot/mapcolorf2", QColor(Qt::white)).value<QColor>();
    mapColor[2] = settings.value("plot/mapcolorf3", QColor(Qt::white)).value<QColor>();
    mapColor[3] = settings.value("plot/mapcolorf4", QColor(Qt::white)).value<QColor>();
    mapColor[4] = settings.value("plot/mapcolorf5", QColor(Qt::white)).value<QColor>();
    mapColor[5] = settings.value("plot/mapcolorf6", QColor(Qt::white)).value<QColor>();
    mapColor[6] = settings.value("plot/mapcolorf7", QColor(Qt::white)).value<QColor>();
    mapColor[7] = settings.value("plot/mapcolorf8", QColor(Qt::white)).value<QColor>();
    mapColor[8] = settings.value("plot/mapcolorf9", QColor(Qt::white)).value<QColor>();
    mapColor[9] = settings.value("plot/mapcolorf10", QColor(Qt::white)).value<QColor>();
    mapColor[10] = settings.value("plot/mapcolorf11", QColor(Qt::white)).value<QColor>();
    mapColor[11] = settings.value("plot/mapcolorf12", QColor(Qt::white)).value<QColor>();

    for (int i = 0; i < MAXMAPLAYER; i++) {
        rBLayer[i]->setChecked(false);
        btnColor[i]->setStyleSheet(QString("QPushButton {background-color: %1;}").arg(color2String(mapColor[i])));
        btnColorf[i]->setStyleSheet(QString("QPushButton {background-color: %1;}").arg(color2String(mapColor[i])));
    }

}
//---------------------------------------------------------------------------
void VecMapDialog::saveOptions(QSettings &settings)
{
    settings.setValue("plot/mapcolor1", mapColor[0]);
    settings.setValue("plot/mapcolor2", mapColor[1]);
    settings.setValue("plot/mapcolor3", mapColor[2]);
    settings.setValue("plot/mapcolor4", mapColor[3]);
    settings.setValue("plot/mapcolor5", mapColor[4]);
    settings.setValue("plot/mapcolor6", mapColor[5]);
    settings.setValue("plot/mapcolor7", mapColor[6]);
    settings.setValue("plot/mapcolor8", mapColor[7]);
    settings.setValue("plot/mapcolor9", mapColor[8]);
    settings.setValue("plot/mapcolor10", mapColor[9]);
    settings.setValue("plot/mapcolor11", mapColor[10]);
    settings.setValue("plot/mapcolor12", mapColor[11]);
    settings.setValue("plot/mapcolorf1", mapColor[0]);
    settings.setValue("plot/mapcolorf2", mapColor[1]);
    settings.setValue("plot/mapcolorf3", mapColor[2]);
    settings.setValue("plot/mapcolorf4", mapColor[3]);
    settings.setValue("plot/mapcolorf5", mapColor[4]);
    settings.setValue("plot/mapcolorf6", mapColor[5]);
    settings.setValue("plot/mapcolorf7", mapColor[6]);
    settings.setValue("plot/mapcolorf8", mapColor[7]);
    settings.setValue("plot/mapcolorf9", mapColor[8]);
    settings.setValue("plot/mapcolorf10", mapColor[9]);
    settings.setValue("plot/mapcolorf11", mapColor[10]);
    settings.setValue("plot/mapcolorf12", mapColor[11]);
}
//---------------------------------------------------------------------------
