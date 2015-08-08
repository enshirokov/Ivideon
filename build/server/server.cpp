#include "server.h"

#include <QThread>
#include <QHBoxLayout>

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    _address("127.0.0.1"),
    _port(33333)
{
    _led = new Led;
    _label = new QLabel("LED:");

    _server = new MyTcpServer(_led, this);

    QHBoxLayout* layout = new QHBoxLayout;
    layout->addWidget(_label);
    layout->addWidget(_led);

    QWidget *window = new QWidget();
    window->setLayout(layout);

    setCentralWidget(window);
    createMenu();

}

Server::~Server()
{
    _server->close();
    delete _server;
}

void Server::createActions()
{
    _quitAct = new QAction(QIcon(":/images/images/open.png"), tr("&Quit"), this);
    _quitAct->setStatusTip(tr("Quit"));
    connect(_quitAct, &QAction::triggered, this, &Server::quit);

    _connectionAct = new QAction(QIcon(":/images/images/open.png"), tr("&Connection"), this);
    _connectionAct->setStatusTip(tr("Connection"));
    connect(_connectionAct, &QAction::triggered, this, &Server::showConnectDlg);
}

void Server::createMenu()
{
    createActions();

    this->menuBar()->setNativeMenuBar(false);
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_quitAct);

    _connectionMenu = menuBar()->addMenu(tr("&Connection"));
    _connectionMenu->addAction(_connectionAct);

}

void Server::quit()
{
    this->close();
}

void Server::showConnectDlg()
{
    _dialog = new NetSettingsDlg(_address, _port);
    _dialog->exec();

    if (!_server->listen(QHostAddress(_address), _port)) {
        qDebug() <<  QObject::tr("Unable to start the server: %1.").arg(_server->errorString());
    } else {
        qDebug() << "Server started";
    }

    delete _dialog;
}


