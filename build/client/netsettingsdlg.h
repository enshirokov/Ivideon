#ifndef NETSETTINGSDLG_H
#define NETSETTINGSDLG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>

class NetSettingsDlg : public QDialog
{
	Q_OBJECT
public:
    NetSettingsDlg(QString& remoteAddress, quint16& remotePort);
	~NetSettingsDlg();

signals:
    void netSettings(QString, quint16);

private slots:
	void acceptSlot();			// Ok
	void cancelSlot();			// Cancel


private:
    QLabel*				_labelRemote;

    QLineEdit*			_lineEditRemoteAddress;

    QSpinBox*			_spinBoxRemotePort;

	QPushButton*		_pushButtonConnect;
	QPushButton*		_pushButtonCancel;

    QString&			_remoteAddress;
    quint16&			_remotePort;
};

#endif // NETSETTINGSDLG_H
