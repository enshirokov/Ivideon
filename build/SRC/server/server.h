#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>
#include <QMap>
#include <QLabel>
#include <QAction>
#include <QMenu>
#include <QMenuBar>

#include "led.h"
#include "netsettingsdlg.h"
#include "mytcpserver.h"

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private slots:
    void quit();   // quit application
    void showConnectDlg();   // show net settings dialog

private:
    void createActions();   // create action for menu
    void createMenu();   // create main menu

private:
    MyTcpServer* _server;   // server for user connections
    Led* _led;   // led

    QLabel* _label;   // "LED"
    QAction* _quitAct;   // quit action
    QAction* _connectionAct;   // connection action
    QMenu* _fileMenu;   // menu "File"
    QMenu* _connectionMenu;   // menu "Connection"

    NetSettingsDlg* _dialog;   // net settings dialog
    QString _address;   // remote address
    quint16 _port;   // remote port

};

#endif // SERVER_H
