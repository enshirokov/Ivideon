#include "mytcpserver.h"
#include <QThread>


MyTcpServer::MyTcpServer(const Led* pLed, QObject *parent)
    : QTcpServer(parent),
      _pLed(pLed)
{

}

MyTcpServer::~MyTcpServer()
{
    // remove all threads and clients
    foreach(int i, _clients.keys()){
        QThread* thread = _clients[i]->thread();
        thread->quit();
        thread->wait();
        delete thread;

        _clients.remove(i);
    }
}

void MyTcpServer::incomingConnection(qintptr descriptor)
{
    // create new client with own thread

    QThread *thread = new QThread;

    ClientThread* client = new ClientThread(_pLed, descriptor);
    client->moveToThread(thread);

    connect(thread, &QThread::started, client, &ClientThread::run);
    connect(client, &ClientThread::disconnect, this, &MyTcpServer::removeThread);

    _clients[descriptor] = client;

    thread->start();
}

void MyTcpServer::removeThread(qintptr socketDescriptor)
{
    // remove client thread after disconnect

    _clients.remove(socketDescriptor);
}

