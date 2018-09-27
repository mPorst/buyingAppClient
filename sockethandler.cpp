#include "sockethandler.h"

SocketHandler::SocketHandler()
{
    int tempCounter = 0;
    qDebug() << "DEBUG in sockethandler constructor ";
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses())
    {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            tempCounter += 1;
            myAddress = address;
            qDebug() << "The address to bind is " << myAddress;
        }
    }

    //QObject::connect(this, &SocketHandler::connectedChanged, this, &SocketHandler::setConnected);
}

bool SocketHandler::bindSocket(quint16 port)
{
    if(socket.bind(serverAddress, port))
        return true;
    qDebug()<< "Could not bind socket: " << socket.error();
    return false;
}

void SocketHandler::connectToHost(QString hostname, quint16 port)
{
    socket.connectToHost(hostname, port);
    m_connected = true;
}

bool SocketHandler::writeSocket(QString message)
{
    if(m_connected == false)
        return false;
    if(!socket.waitForConnected(5000))
        return false;
    if(socket.write(message.toStdString().c_str(), message.size()) < 1)
        return false;
    return true;
}

QString SocketHandler::readSocket()
{
    char data[2048];
    socket.waitForReadyRead(1000);
    if(socket.readLine(&data[0], 2048) < 1)
    {
       return "Socket read error";
    }
    return data;
}

void SocketHandler::closeSocket()
{
    socket.disconnectFromHost();
}
