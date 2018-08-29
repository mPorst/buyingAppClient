#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostInfo>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QIODevice> // for errorStr()
#include <QObject>

#define DEBUG


class SocketHandler : public QObject
{
    Q_OBJECT

public:
    SocketHandler();
    bool bindSocket(quint16 port);
    void connectToHost(QString hostname, quint16 port);
    bool writeSocket(QString message);
    QString readSocket();
    void closeSocket();

private:
    QTcpSocket socket;
    QHostAddress myAddress;
    QHostAddress serverAddress;
    bool m_connected = false;
};

#endif // SOCKETHANDLER_H
