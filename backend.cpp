#include "backend.h"
#include "sockethandler.h"

Backend::Backend(QObject *parent) : QObject(parent)
{
}

void Backend::initSocket()
{
    if(!handle.bindSocket(port)) // binding is only required server-side
    {
        qDebug() << "Could not bind socket!\n"; return;
    }
}

void Backend::writeSocket(QString data)
{
    handle.connectToHost(domain, port);
    qDebug() << "bind socket to: " << domain << " and " << port << '\n';
    handle.writeSocket(data);
    qDebug() << "Wrote data: " << data << '\n';
}

QString Backend::readSocket()
{
    return handle.readSocket();
}

void Backend::initAndWriteSocket(QString data)
{
    if(isInitialised() == false)
        initSocket(); initialised=true; qDebug() << "Just some testing \n";
    writeSocket(data);
}

void Backend::closeSocket()
{
    handle.closeSocket();
}

void Backend::setPort(quint16 newPort)
{
    port = newPort;
}

void Backend::setDomain(QString newDomain)
{
    domain = newDomain;
}

bool Backend::isInitialised()
{
    return initialised;
}

/*
void Backend::setUserName(const QString &userName)
{
    if (userName == m_userName)
        return;

    m_userName = userName;
    emit userNameChanged();
}
*/
