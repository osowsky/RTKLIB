//---------------------------------------------------------------------------
#ifndef ftpoptdlgH
#define ftpoptdlgH
//---------------------------------------------------------------------------
#include <QDialog>

#define MAXHIST		10

namespace Ui {
class FtpOptDialog;
}

class KeyDialog;
class QComboBox;

//---------------------------------------------------------------------------
class FtpOptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FtpOptDialog(QWidget *parent, int options = 0);

    int getOptions() {return options;}
    void setOptions(int option); // 0(default): FTP options; 1: HTTP options
    QString getPath();
    void setPath(const QString&);

protected slots:
    void saveClose();
    void showKeyDialog();

private:
    void addHistory(QComboBox *list, QString *hist);
    void updateEnable();

    KeyDialog *keyDlg;
    int options;
    QString history[MAXHIST], MountpointHistory[MAXHIST];

    Ui::FtpOptDialog *ui;

};
//---------------------------------------------------------------------------
#endif
