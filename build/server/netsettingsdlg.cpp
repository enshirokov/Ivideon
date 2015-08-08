#include "netsettingsdlg.h"
#include <qhostaddress.h>
#include <qmessagebox.h>
#include <QHBoxLayout>


NetSettingsDlg::NetSettingsDlg(QString& remoteAddress, quint16& remotePort)
    : _remoteAddress(remoteAddress),
    _remotePort(remotePort)
{
	
    _labelRemote = new QLabel("Remote address:");

	QString inputMask = "000.000.000.000; ";

    _lineEditRemoteAddress = new QLineEdit(_remoteAddress);
    _lineEditRemoteAddress->setInputMask(inputMask);

    quint16 minPort = 0;
	quint16 maxPort = 0xFFFF;
	
    _spinBoxRemotePort	= new QSpinBox;
    _spinBoxRemotePort->setMinimum(minPort);
    _spinBoxRemotePort->setMaximum(maxPort);
    _spinBoxRemotePort->setValue(_remotePort);


	_pushButtonConnect	= new QPushButton("OK");
	_pushButtonCancel	= new QPushButton("Cancel");

	connect(_pushButtonConnect, SIGNAL(clicked()), this, SLOT(acceptSlot()));
	connect(_pushButtonCancel, SIGNAL(clicked()), this, SLOT(cancelSlot()));

	QHBoxLayout* layoutH1 = new QHBoxLayout;
    layoutH1->addWidget(_lineEditRemoteAddress);
    layoutH1->addWidget(_spinBoxRemotePort);


    QHBoxLayout* layoutH2 = new QHBoxLayout;
    layoutH2->addWidget(_pushButtonConnect);
    layoutH2->addWidget(_pushButtonCancel);

	QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(_labelRemote, 0, 0);
	mainLayout->addLayout(layoutH1, 0, 1);
    mainLayout->addLayout(layoutH2, 2, 1);

	this->setLayout(mainLayout);
	this->setWindowTitle("Net settings");

}

NetSettingsDlg::~NetSettingsDlg()
{

}

void NetSettingsDlg::acceptSlot()
{
    QString remoteAddress = _lineEditRemoteAddress->text();

    if (QHostAddress(remoteAddress).protocol() == -1){
		//qDebug() << "Bad hubAddress" << endl;
		QMessageBox msg;
        msg.setText("Bad remote address!");
		msg.exec();
		return;
    }

    _remoteAddress = _lineEditRemoteAddress->text();
    _remotePort = (quint16)_spinBoxRemotePort->value();


	this->close();
}

void NetSettingsDlg::cancelSlot()
{
	this->close();
}

