#include "clientthread.h"

ClientThread::ClientThread(const Led* pLed,qintptr socketDescriptor, QObject *parent)
    : QObject(parent),
      _pLed(pLed),
      _socketDescriptor(socketDescriptor),
      _socket(NULL),
      _handler(NULL)
{

}

ClientThread::~ClientThread()
{
    if(_socket != NULL){
        _socket->close();
        delete _socket;
    }

    if(_handler != NULL){
        delete _handler;
    }
}

void ClientThread::run()
{
    _socket = new QTcpSocket;
    _socket->setSocketDescriptor(_socketDescriptor);

    connect(_socket, &QTcpSocket::readyRead, this, &ClientThread::readMessage);
    connect(_socket, &QTcpSocket::disconnected, this, &ClientThread::disconnected);

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

    connect(_handler, &CommandHandler::message, this, &ClientThread::writeMessage);
    connect(this, &ClientThread::command, _handler, &CommandHandler::handleCommand);

    connect(_pLed, &Led::resultStateOn, _handler, &CommandHandler::messageResultStateOn);
    connect(_pLed, &Led::resultStateOff, _handler, &CommandHandler::messageResultStateOff);
    connect(_pLed, &Led::resultColorRed, _handler, &CommandHandler::messageResultColorRed);
    connect(_pLed, &Led::resultColorGreen, _handler, &CommandHandler::messageResultColorGreen);
    connect(_pLed, &Led::resultColorBlue, _handler, &CommandHandler::messageResultColorBlue);
    connect(_pLed, &Led::resultRate, _handler, &CommandHandler::messageResultRate);
    connect(_pLed, &Led::resultOk, _handler, &CommandHandler::messageResultOk);

}

void ClientThread::readMessage()
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

void ClientThread::writeMessage(QString message)
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

void ClientThread::disconnected()
{
    emit disconnect(_socketDescriptor);
}

