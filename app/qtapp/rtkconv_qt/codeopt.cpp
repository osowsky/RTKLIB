//---------------------------------------------------------------------------
#include <QShowEvent>
#include <QDebug>

#include "rtklib.h"
#include "convopt.h"
#include "codeopt.h"
//---------------------------------------------------------------------------
CodeOptDialog::CodeOptDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    
    connect(buttonBox, &QDialogButtonBox::accepted, this, &CodeOptDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &CodeOptDialog::reject);
    connect(btnSetAll, &QPushButton::clicked, this, &CodeOptDialog::setUnsetAll);
}
//---------------------------------------------------------------------------
void CodeOptDialog::setCodeMask(int i, const QString &mask)
{
    if (i == 0) { // GPS
        G01->setChecked(mask[0] == '1');
        G02->setChecked(mask[1] == '1');
        G03->setChecked(mask[2] == '1');
        G04->setChecked(mask[3] == '1');
        G05->setChecked(mask[4] == '1');
        G06->setChecked(mask[5] == '1');
        G07->setChecked(mask[6] == '1');
        G08->setChecked(mask[7] == '1');
        G14->setChecked(mask[13] == '1');
        G15->setChecked(mask[14] == '1');
        G16->setChecked(mask[15] == '1');
        G17->setChecked(mask[16] == '1');
        G18->setChecked(mask[17] == '1');
        G19->setChecked(mask[18] == '1');
        G20->setChecked(mask[19] == '1');
        G21->setChecked(mask[20] == '1');
        G22->setChecked(mask[21] == '1');
        G23->setChecked(mask[22] == '1');
        G24->setChecked(mask[23] == '1');
        G25->setChecked(mask[24] == '1');
        G26->setChecked(mask[25] == '1');
    } else if (i == 1) { // GLONASS
        R01->setChecked(mask[0] == '1');
        R02->setChecked(mask[1] == '1');
        R14->setChecked(mask[13] == '1');
        R19->setChecked(mask[18] == '1');
        R30->setChecked(mask[29] == '1');
        R31->setChecked(mask[30] == '1');
        R33->setChecked(mask[32] == '1');
        R44->setChecked(mask[43] == '1');
        R45->setChecked(mask[44] == '1');
        R46->setChecked(mask[45] == '1');
        R66->setChecked(mask[65] == '1');
        R67->setChecked(mask[66] == '1');
        R68->setChecked(mask[67] == '1');
    } else if (i == 2) { // Galileo
        E01->setChecked(mask[0] == '1');
        E10->setChecked(mask[9] == '1');
        E11->setChecked(mask[10] == '1');
        E12->setChecked(mask[11] == '1');
        E13->setChecked(mask[12] == '1');
        E24->setChecked(mask[23] == '1');
        E25->setChecked(mask[24] == '1');
        E26->setChecked(mask[25] == '1');
        E27->setChecked(mask[26] == '1');
        E28->setChecked(mask[27] == '1');
        E29->setChecked(mask[28] == '1');
        E30->setChecked(mask[29] == '1');
        E31->setChecked(mask[30] == '1');
        E32->setChecked(mask[31] == '1');
        E33->setChecked(mask[32] == '1');
        E34->setChecked(mask[33] == '1');
        E37->setChecked(mask[36] == '1');
        E38->setChecked(mask[37] == '1');
        E39->setChecked(mask[38] == '1');
    } else if (i==3) { // QZSS
        J01->setChecked(mask[0] == '1');
        J07->setChecked(mask[6] == '1');
        J08->setChecked(mask[7] == '1');
        J12->setChecked(mask[11] == '1');
        J13->setChecked(mask[12] == '1');
        J16->setChecked(mask[15] == '1');
        J17->setChecked(mask[16] == '1');
        J18->setChecked(mask[17] == '1');
        J24->setChecked(mask[23] == '1');
        J25->setChecked(mask[24] == '1');
        J26->setChecked(mask[25] == '1');
        J33->setChecked(mask[32] == '1');
        J34->setChecked(mask[33] == '1');
        J35->setChecked(mask[34] == '1');
        J36->setChecked(mask[35] == '1');
        J57->setChecked(mask[56] == '1');
        J58->setChecked(mask[57] == '1');
        J59->setChecked(mask[58] == '1');
        J60->setChecked(mask[59] == '1');
    } else if (i == 4){ // SBAS
        S01->setChecked(mask[0] == '1');
        S24->setChecked(mask[23] == '1');
        S25->setChecked(mask[24] == '1');
        S26->setChecked(mask[25] == '1');
    } else if (i == 5) { //BDS
        C02->setChecked(mask[1] == '1');
        C06->setChecked(mask[5] == '1');
        C10->setChecked(mask[9] == '1');
        C12->setChecked(mask[11] == '1');
        C18->setChecked(mask[17] == '1');
        C26->setChecked(mask[25] == '1');
        C27->setChecked(mask[26] == '1');
        C28->setChecked(mask[27] == '1');
        C29->setChecked(mask[28] == '1');
        C30->setChecked(mask[29] == '1');
        C33->setChecked(mask[32] == '1');
        C39->setChecked(mask[38] == '1');
        C40->setChecked(mask[39] == '1');
        C41->setChecked(mask[40] == '1');
        C42->setChecked(mask[41] == '1');
        C43->setChecked(mask[42] == '1');
        C56->setChecked(mask[55] == '1');
        C57->setChecked(mask[56] == '1');
        C58->setChecked(mask[57] == '1');
        C61->setChecked(mask[60] == '1');
        C62->setChecked(mask[61] == '1');
        C63->setChecked(mask[62] == '1');
        C64->setChecked(mask[63] == '1');
        C65->setChecked(mask[64] == '1');
    } else if (i == 6) { // NavIC
        I26->setChecked(mask[25] == '1');
        I49->setChecked(mask[48] == '1');
        I50->setChecked(mask[49] == '1');
        I51->setChecked(mask[50] == '1');
        I52->setChecked(mask[51] == '1');
        I53->setChecked(mask[52] == '1');
        I54->setChecked(mask[53] == '1');
        I55->setChecked(mask[54] == '1');
    }
}
//---------------------------------------------------------------------------
QString CodeOptDialog::getCodeMask(int i)
{
    QString mask;

    mask.fill('0', MAXCODE);

    if (i == 0) { // GPS
        if (G01->isChecked()) mask[0] = '1';
        if (G02->isChecked()) mask[1] = '1';
        if (G03->isChecked()) mask[2] = '1';
        if (G04->isChecked()) mask[3] = '1';
        if (G05->isChecked()) mask[4] = '1';
        if (G06->isChecked()) mask[5] = '1';
        if (G07->isChecked()) mask[6] = '1';
        if (G08->isChecked()) mask[7] = '1';
        if (G14->isChecked()) mask[13] = '1';
        if (G15->isChecked()) mask[14] = '1';
        if (G16->isChecked()) mask[15] = '1';
        if (G17->isChecked()) mask[16] = '1';
        if (G18->isChecked()) mask[17] = '1';
        if (G19->isChecked()) mask[18] = '1';
        if (G20->isChecked()) mask[19] = '1';
        if (G21->isChecked()) mask[20] = '1';
        if (G22->isChecked()) mask[21] = '1';
        if (G23->isChecked()) mask[22] = '1';
        if (G24->isChecked()) mask[23] = '1';
        if (G25->isChecked()) mask[24] = '1';
        if (G26->isChecked()) mask[25] = '1';
    } else if (i == 1) { // GLONASS
        if (R01->isChecked()) mask[0] = '1';
        if (R02->isChecked()) mask[1] = '1';
        if (R14->isChecked()) mask[13] = '1';
        if (R19->isChecked()) mask[18] = '1';
        if (R30->isChecked()) mask[29] = '1';
        if (R31->isChecked()) mask[30] = '1';
        if (R33->isChecked()) mask[32] = '1';
        if (R44->isChecked()) mask[43] = '1';
        if (R45->isChecked()) mask[44] = '1';
        if (R46->isChecked()) mask[45] = '1';
        if (R66->isChecked()) mask[65] = '1';
        if (R67->isChecked()) mask[66] = '1';
        if (R68->isChecked()) mask[67] = '1';
    } else if (i == 2) { // Galileo
        if (E01->isChecked()) mask[0] = '1';
        if (E10->isChecked()) mask[9] = '1';
        if (E11->isChecked()) mask[10] = '1';
        if (E12->isChecked()) mask[11] = '1';
        if (E13->isChecked()) mask[12] = '1';
        if (E24->isChecked()) mask[23] = '1';
        if (E25->isChecked()) mask[24] = '1';
        if (E26->isChecked()) mask[25] = '1';
        if (E27->isChecked()) mask[26] = '1';
        if (E28->isChecked()) mask[27] = '1';
        if (E29->isChecked()) mask[28] = '1';
        if (E30->isChecked()) mask[29] = '1';
        if (E31->isChecked()) mask[30] = '1';
        if (E32->isChecked()) mask[31] = '1';
        if (E33->isChecked()) mask[32] = '1';
        if (E34->isChecked()) mask[33] = '1';
        if (E37->isChecked()) mask[36] = '1';
        if (E38->isChecked()) mask[37] = '1';
        if (E39->isChecked()) mask[38] = '1';
    } else if (i == 3) { // QZSS
        if (J01->isChecked()) mask[0] = '1';
        if (J07->isChecked()) mask[6] = '1';
        if (J08->isChecked()) mask[7] = '1';
        if (J13->isChecked()) mask[12] = '1';
        if (J12->isChecked()) mask[11] = '1';
        if (J16->isChecked()) mask[15] = '1';
        if (J17->isChecked()) mask[16] = '1';
        if (J18->isChecked()) mask[17] = '1';
        if (J24->isChecked()) mask[23] = '1';
        if (J25->isChecked()) mask[24] = '1';
        if (J26->isChecked()) mask[25] = '1';
        if (J33->isChecked()) mask[32] = '1';
        if (J34->isChecked()) mask[33] = '1';
        if (J35->isChecked()) mask[34] = '1';
        if (J36->isChecked()) mask[35] = '1';
        if (J57->isChecked()) mask[56] = '1';
        if (J58->isChecked()) mask[57] = '1';
        if (J59->isChecked()) mask[58] = '1';
        if (J60->isChecked()) mask[59] = '1';
    } else if (i == 4) { // SBAS
        if (S01->isChecked()) mask[0] = '1';
        if (S24->isChecked()) mask[23] = '1';
        if (S25->isChecked()) mask[24] = '1';
        if (S26->isChecked()) mask[25] = '1';
    } else if (i == 5) { // BDS
        if (C02->isChecked()) mask[1] = '1';
        if (C06->isChecked()) mask[5] = '1';
        if (C10->isChecked()) mask[9] = '1';
        if (C12->isChecked()) mask[11] = '1';
        if (C18->isChecked()) mask[17] = '1';
        if (C26->isChecked()) mask[25] = '1';
        if (C27->isChecked()) mask[26] = '1';
        if (C28->isChecked()) mask[27] = '1';
        if (C29->isChecked()) mask[28] = '1';
        if (C30->isChecked()) mask[29] = '1';
        if (C33->isChecked()) mask[32] = '1';
        if (C39->isChecked()) mask[38] = '1';
        if (C40->isChecked()) mask[39] = '1';
        if (C41->isChecked()) mask[40] = '1';
        if (C42->isChecked()) mask[41] = '1';
        if (C43->isChecked()) mask[42] = '1';
        if (C56->isChecked()) mask[55] = '1';
        if (C57->isChecked()) mask[56] = '1';
        if (C58->isChecked()) mask[57] = '1';
        if (C61->isChecked()) mask[60] = '1';
        if (C62->isChecked()) mask[61] = '1';
        if (C63->isChecked()) mask[62] = '1';
        if (C64->isChecked()) mask[63] = '1';
        if (C65->isChecked()) mask[64] = '1';
    } else if (i == 6) { // NavIC
        if (I26->isChecked()) mask[25] = '1';
        if (I49->isChecked()) mask[48] = '1';
        if (I50->isChecked()) mask[49] = '1';
        if (I51->isChecked()) mask[50] = '1';
        if (I52->isChecked()) mask[51] = '1';
        if (I53->isChecked()) mask[52] = '1';
        if (I54->isChecked()) mask[53] = '1';
        if (I55->isChecked()) mask[54] = '1';
    }

    return mask;
}
//---------------------------------------------------------------------------
void CodeOptDialog::setUnsetAll()
{
    bool set = (btnSetAll->text() == tr("&Set All"));

    G01->setChecked(set);
    G02->setChecked(set);
    G03->setChecked(set);
    G04->setChecked(set);
    G05->setChecked(set);
    G06->setChecked(set);
    G07->setChecked(set);
    G08->setChecked(set);
    G14->setChecked(set);
    G15->setChecked(set);
    G16->setChecked(set);
    G17->setChecked(set);
    G18->setChecked(set);
    G19->setChecked(set);
    G20->setChecked(set);
    G21->setChecked(set);
    G22->setChecked(set);
    G23->setChecked(set);
    G24->setChecked(set);
    G25->setChecked(set);
    G26->setChecked(set);
    R01->setChecked(set);
    R02->setChecked(set);
    R14->setChecked(set);
    R19->setChecked(set);
    R44->setChecked(set);
    R45->setChecked(set);
    R46->setChecked(set);
    R66->setChecked(set);
    R67->setChecked(set);
    R68->setChecked(set);
    R30->setChecked(set);
    R31->setChecked(set);
    R33->setChecked(set);
    E01->setChecked(set);
    E10->setChecked(set);
    E11->setChecked(set);
    E12->setChecked(set);
    E13->setChecked(set);
    E24->setChecked(set);
    E25->setChecked(set);
    E26->setChecked(set);
    E27->setChecked(set);
    E28->setChecked(set);
    E29->setChecked(set);
    E30->setChecked(set);
    E31->setChecked(set);
    E32->setChecked(set);
    E33->setChecked(set);
    E34->setChecked(set);
    E37->setChecked(set);
    E38->setChecked(set);
    E39->setChecked(set);
    J01->setChecked(set);
    J07->setChecked(set);
    J08->setChecked(set);
    J12->setChecked(set);
    J13->setChecked(set);
    J16->setChecked(set);
    J17->setChecked(set);
    J18->setChecked(set);
    J24->setChecked(set);
    J25->setChecked(set);
    J26->setChecked(set);
    J33->setChecked(set);
    J34->setChecked(set);
    J35->setChecked(set);
    J36->setChecked(set);
    J57->setChecked(set);
    J58->setChecked(set);
    J59->setChecked(set);
    J60->setChecked(set);
    C02->setChecked(set);
    C06->setChecked(set);
    C10->setChecked(set);
    C12->setChecked(set);
    C18->setChecked(set);
    C26->setChecked(set);
    C27->setChecked(set);
    C28->setChecked(set);
    C29->setChecked(set);
    C30->setChecked(set);
    C33->setChecked(set);
    C39->setChecked(set);
    C40->setChecked(set);
    C41->setChecked(set);
    C42->setChecked(set);
    C43->setChecked(set);
    C56->setChecked(set);
    C57->setChecked(set);
    C58->setChecked(set);
    C61->setChecked(set);
    C62->setChecked(set);
    C63->setChecked(set);
    C64->setChecked(set);
    C65->setChecked(set);
    I26->setChecked(set);
    I49->setChecked(set);
    I50->setChecked(set);
    I51->setChecked(set);
    I52->setChecked(set);
    I53->setChecked(set);
    I54->setChecked(set);
    I55->setChecked(set);
    S01->setChecked(set);
    S24->setChecked(set);
    S25->setChecked(set);
    S26->setChecked(set);

    btnSetAll->setText(btnSetAll->text() == tr("&Set All") ? tr("Un&set All") : tr("&Set All"));
}
//---------------------------------------------------------------------------
void CodeOptDialog::setNavSystem(int navSystem)
{
    this->navSystem = navSystem;
    updateEnable();
}
//---------------------------------------------------------------------------
void CodeOptDialog::setFrequencyType(int frequencyType)
{
    this->frequencyType = frequencyType;
    updateEnable();
}
//---------------------------------------------------------------------------
void CodeOptDialog::updateEnable()
{
    G01->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G02->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G03->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G04->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G05->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G06->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G07->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G08->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L1));
    G14->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G15->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G16->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G17->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G18->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G19->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G20->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G21->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G22->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G23->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L2));
    G24->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L3));
    G25->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L3));
    G26->setEnabled((navSystem & SYS_GPS) && (frequencyType & FREQTYPE_L3));
    R01->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L1));
    R02->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L1));
    R14->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L2));
    R19->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L2));
    R44->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L3));
    R45->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L3));
    R46->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L3));
    R66->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L1));
    R67->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L1));
    R68->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L1));
    R30->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L2));
    R31->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L2));
    R33->setEnabled((navSystem & SYS_GLO) && (frequencyType & FREQTYPE_L2));
    E01->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L1));
    E10->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L1));
    E11->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L1));
    E12->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L1));
    E13->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L1));
    E24->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L3));
    E25->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L3));
    E26->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L3));
    E27->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L2));
    E28->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L2));
    E29->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L2));
    E30->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L4));
    E31->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L4));
    E32->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L4));
    E33->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L4));
    E34->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L4));
    E37->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L5));
    E38->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L5));
    E39->setEnabled((navSystem & SYS_GAL) && (frequencyType & FREQTYPE_L5));
    J01->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L1));
    J07->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L1));
    J08->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L1));
    J13->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L1));
    J12->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L1));
    J16->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L2));
    J17->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L2));
    J18->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L2));
    J24->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J25->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J26->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J57->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J58->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J59->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L3));
    J60->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L4));
    J34->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L4));
    J35->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L4));
    J36->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L4));
    J33->setEnabled((navSystem & SYS_QZS) && (frequencyType & FREQTYPE_L4));
    C02->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C06->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C10->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C12->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C18->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C26->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L3));
    C27->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C28->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C29->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C30->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L4));
    C33->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L4));
    C39->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L5));
    C40->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C41->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C42->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L4));
    C43->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L4));
    I49->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L1));
    C56->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L1));
    C57->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L3));
    C58->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L3));
    C61->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C62->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C63->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L2));
    C64->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L5));
    C65->setEnabled((navSystem & SYS_CMP) && (frequencyType & FREQTYPE_L5));
    I50->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L1));
    I51->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L1));
    I26->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L1));
    I52->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L2));
    I53->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L2));
    I54->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L2));
    I55->setEnabled((navSystem & SYS_IRN) && (frequencyType & FREQTYPE_L3));
    S01->setEnabled((navSystem & SYS_SBS) && (frequencyType & FREQTYPE_L1));
    S24->setEnabled((navSystem & SYS_SBS) && (frequencyType & FREQTYPE_L3));
    S25->setEnabled((navSystem & SYS_SBS) && (frequencyType & FREQTYPE_L3));
    S26->setEnabled((navSystem & SYS_SBS) && (frequencyType & FREQTYPE_L3));
}
//---------------------------------------------------------------------------
