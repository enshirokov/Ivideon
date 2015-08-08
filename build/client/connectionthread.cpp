#include "connectionthread.h"

ConnectionThread::ConnectionThread(const Led* pLed, const QString& address, quint16 port, QObject *parent)
    : QObject(parent),
      _pLed(pLed),
      _address(address),
      _port(port),
      _socket(NULL),
      _handler(NULL)

{

}

ConnectionThread::~ConnectionThread()
{
    if(_socket != NULL){
        _socket->close();
        delete _socket;
    }
    if(_handler != NULL){
        delete _handler;
    }
}

void ConnectionThread::run()
{
    _socket = new QTcpSocket;
    connect(_socket, &QTcpSocket::readyRead, this, &ConnectionThread::readMessage);
    connect(_socket, static_cast<void (QTcpSocket::*)(QAbstractSocket::SocketError)>(&QAbstractSocket::error), this, &ConnectionThread::failConnection);
    connect(_socket, &QTcpSocket::connected, this, &ConnectionThread::successConnection);

    _handler = new CommandHandler;

    connect(_handler, &CommandHandler::setLedStateOn, _pLed, &Led::setLedStateOn);
    connect(_handler, &CommandHandler::setLedStateOff, _pLed, &Led::setLedStateOff);
    connect(_handler, &CommandHandler::setLedColorRed, _pLed, &Led::setLedColorRed);
    connect(_handler, &CommandHandler::setLedColorBlue, _pLed, &Led::setLedColorBlue);
    connect(_handler, &CommandHandler::setLedColorGreen, _pLed, &Led::setLedColorGreen);
    connect(_handler, &CommandHandler::setLedRate, _pLed, &Led::setLedRate);

    connect(_handler, &CommandHandler::getLedState, _pLed, &Led::getLedState);
    connect(_handler, &CommandHandler::getLedColor, _pLed, &Led::getLedColor);
    connect(_handler, &CommandHandler::getLedRate, _pLed, &Led::getLedRate);

    connect(_handler, &CommandHandler::message, this, &ConnectionThread::writeMessage);
    connect(this, &ConnectionThread::command, _handler, &CommandHandler::handleCommand);
    connect(_handler, &CommandHandler::ok, this, &ConnectionThread::getAllParams);

    connect(_pLed, &Led::resultStateOn, _handler, &CommandHandler::messageResultStateOn);
    connect(_pLed, &Led::resultStateOff, _handler, &CommandHandler::messageResultStateOff);
    connect(_pLed, &Led::resultColorRed, _handler, &CommandHandler::messageResultColorRed);
    connect(_pLed, &Led::resultColorGreen, _handler, &CommandHandler::messageResultColorGreen);
    connect(_pLed, &Led::resultColorBlue, _handler, &CommandHandler::messageResultColorBlue);
    connect(_pLed, &Led::resultRate, _handler, &CommandHandler::messageResultRate);
    connect(_pLed, &Led::resultOk, _handler, &CommandHandler::messageResultOk);


 }

void ConnectionThread::connectToHost(const QString& address, quint16 port)
{
    _mutex.lock();
    _address = address;
    _port = port;

    _socket->connectToHost(_address, _port);

    _mutex.unlock();
}

void ConnectionThread::readMessage()
{
    QByteArray message = _socket->readAll();
    QTextStream in(&message, QIODevice::ReadOnly);

    while(!in.atEnd()){
    QString line = in.readLine();

    if(_handler != NULL)
        emit command(line);

    }

    _socket->flush();

}

void ConnectionThread::writeMessage(QString message)
{
    qDebug() << "writeMessage(): " << message;

    if(_socket->state() == QAbstractSocket::ConnectedState){
        //_socket->flush();
        _socket->write(message.toStdString().data());
        //_socket->waitForBytesWritten();

    }
    else
        qDebug() << "socket not connected";
}

void ConnectionThread::getAllParams()
{
    _handler->messageGetState();
    _handler->messageGetColor();
    _handler->messageGetRate();
}

void ConnectionThread::failConnection(QAbstractSocket::SocketError err)
{
    emit error(_socket->errorString());
}

void ConnectionThread::successConnection()
{
    emit succsess();
}

bool ConnectionThread::isConnected()
{
    if(_socket != NULL)
        return _socket->isValid();

    return false;
}

void ConnectionThread::sendSetStateOn()
{
    _handler->messageSetStateOn();
}

void ConnectionThread::sendSetStateOff()
{
    _handler->messageSetStateOff();
}

void ConnectionThread::sendSetColorRed()
{
    _handler->messageSetColorRed();
}

void ConnectionThread::sendSetColorGreen()
{
    _handler->messageSetColorGreen();
}

void ConnectionThread::sendSetColorBlue()
{
    _handler->messageSetColorBlue();
}

void ConnectionThread::sendSetRate(int rate)
{
    _handler->messageSetRate(rate);
}

void ConnectionThread::sendGetState()
{
    _handler->messageGetState();
}

void ConnectionThread::sendGetColor()
{
    _handler->messageGetColor();
}

void ConnectionThread::sendGetRate()
{
    _handler->messageGetRate();
}

