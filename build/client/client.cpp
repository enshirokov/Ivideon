#include "client.h"
#include <QHostAddress>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>


Client::Client(QWidget *parent) :
    QMainWindow(parent),
    _state(false),
    _address("127.0.0.1"),
    _port(33333)
{
    createCentralWidget();
    createMenu();

}

Client::~Client()
{

}

void Client::createCentralWidget()
{
     _led = new Led;

    _thread = new QThread;
    _connectionThread = new ConnectionThread(_led, _address, _port);
    _connectionThread->moveToThread(_thread);

    connect(_thread, &QThread::started, _connectionThread, &ConnectionThread::run);
    connect(_connectionThread, &ConnectionThread::error, this, &Client::handleError);
    connect(_connectionThread, &ConnectionThread::succsess, this, &Client::handleSuccess);
    connect(this, &Client::connectToHost, _connectionThread, &ConnectionThread::connectToHost);

    _group = createColorGroup();
    _group->setEnabled(false);

    QHBoxLayout* layout1 = new QHBoxLayout;
    layout1->addWidget(_group);
    layout1->addWidget(_led);

    _pbState = new QPushButton(LED_ON);
    _pbState->setEnabled(false);
    connect(_pbState, &QPushButton::clicked, this, &Client::buttonState);

    _sbRate = new QSpinBox();
    _sbRate->setMinimum(0);
    _sbRate->setMaximum(5);
    _sbRate->setEnabled(false);
    connect(_sbRate, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), _connectionThread, &ConnectionThread::sendSetRate, Qt::QueuedConnection);

    _labelRate = new QLabel("Rate: ");

    QHBoxLayout* layout2 = new QHBoxLayout;
    layout2->addWidget(_labelRate);
    layout2->addWidget(_sbRate);
    layout2->addWidget(_pbState);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layout1);
    mainLayout->addLayout(layout2);

    QWidget *window = new QWidget();
    window->setLayout(mainLayout);

    setCentralWidget(window);

    _thread->start();
}

void Client::slotConnected()
{
    qDebug() << "slot Connected";

}

void Client::buttonState()
{
    if(_state){
        if(_connectionThread->isConnected()){
        _pbState->setText(LED_ON);
        _state = false;
        _connectionThread->sendSetStateOff();
        }
    }
    else {
         if(_connectionThread->isConnected()){
            _pbState->setText(LED_OFF);
            _state = true;
            _connectionThread->sendSetRate(_sbRate->value());
            _connectionThread->sendSetStateOn();
        }
    }
}

QGroupBox* Client::createColorGroup()
{
    QGroupBox* groupBox = new QGroupBox(tr("Color"));

    _rbColorRed = new QRadioButton(tr("&Red"));
    connect(_rbColorRed, &QRadioButton::toggled, _connectionThread, &ConnectionThread::sendSetColorRed);
    _rbColorGreen = new QRadioButton(tr("&Green"));
    connect(_rbColorGreen, &QRadioButton::toggled, _connectionThread, &ConnectionThread::sendSetColorGreen);
    _rbColorBlue = new QRadioButton(tr("&Blue"));
    connect(_rbColorBlue, &QRadioButton::toggled, _connectionThread, &ConnectionThread::sendSetColorBlue);

    _rbColorRed->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(_rbColorRed);
    layout->addWidget(_rbColorGreen);
    layout->addWidget(_rbColorBlue);
    groupBox->setLayout(layout);

    return groupBox;

}

void Client::createActions()
{
    _quitAct = new QAction(QIcon(":/images/images/open.png"), tr("&Quit"), this);
    _quitAct->setStatusTip(tr("Quit"));
    connect(_quitAct, &QAction::triggered, this, &Client::quit);

    _connectionAct = new QAction(QIcon(":/images/images/open.png"), tr("&Connection"), this);
    _connectionAct->setStatusTip(tr("Connection"));
    connect(_connectionAct, &QAction::triggered, this, &Client::showConnectDlg);
}

void Client::createMenu()
{
    createActions();

    this->menuBar()->setNativeMenuBar(false);
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_quitAct);

    _connectionMenu = menuBar()->addMenu(tr("&Connection"));
    _connectionMenu->addAction(_connectionAct);

}

void Client::quit()
{
    this->close();
}

void Client::showConnectDlg()
{
    _dialog = new NetSettingsDlg(_address, _port);
    _dialog->exec();

    emit connectToHost(_address, _port);

    delete _dialog;
}

void Client::handleError(QString error)
{
    QMessageBox message;
    message.setText(error);
    message.exec();
}

void Client::handleSuccess()
{
    _group->setEnabled(true);
    _sbRate->setEnabled(true);
    _pbState->setEnabled(true);
}




