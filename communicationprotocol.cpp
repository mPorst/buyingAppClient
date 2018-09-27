#include "communicationprotocol.h"

CommunicationProtocol::CommunicationProtocol(QThread* newMainThread)
{
    initialised = false;
    qDebug() << ">>>>>>>>>>>> Called constructor for CommunicationProtocol...";
    handle = new SocketHandler();
    mainThread = newMainThread;
    qDebug() << "Everything was set in constructor... ";
}

CommunicationProtocol::~CommunicationProtocol()
{

}

void CommunicationProtocol::setPort(quint16 inputPort)
{
    port = inputPort;
}

void CommunicationProtocol::setDomain(QString inputDomain)
{
    domain = inputDomain;
}

void CommunicationProtocol::initSocket()
{
    if(!handle->bindSocket(port))
    {
        qDebug() << "Could not bind socket!\n"; return;
    }
}

QString CommunicationProtocol::readSocket()
{
    return handle->readSocket();
}

void CommunicationProtocol::writeSocket(QString data)
{
    if(initialised == false)
    {
        qDebug() << "Before initSocket";
        initSocket();
        qDebug() << "After initSocket";
        handle->connectToHost(domain, port);
        qDebug() << "Attempted connection to " << domain << " on port " << port;
        initialised=true;
        qDebug() << "Initialised socket \n";
    }
    handle->writeSocket(data);
}

void CommunicationProtocol::closeSocket()
{
    initialised = false;
    handle->closeSocket();
}

QString CommunicationProtocol::sendPurchase(QString price, QString buyer, QString date, QString receiver)
{
    writeSocket("send purchase\n");
    QThread::msleep(50);

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        return "Server communication error"; // server didn't answer
    }

    QThread::msleep(50);
    writeSocket(buyer.append("\n"));
    QThread::msleep(50);
    writeSocket(date.append("\n"));
    QThread::msleep(50);
    writeSocket(price.append("\n"));
    QThread::msleep(50);
    writeSocket(receiver.append("\n"));
    QString answerFromServer = readSocket();
    closeSocket();
    emit sentPurchase(answerFromServer);
    return answerFromServer;
}
QString CommunicationProtocol::removePurchase(QString buyer, QString date, QString receiver)
{
    writeSocket("remove purchase\n");
    QThread::msleep(50);

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        return "Server error, did not send data";
    }

    QThread::msleep(50);
    writeSocket(buyer.append("\n"));
    QThread::msleep(50);
    writeSocket(date.append("\n"));
    QThread::msleep(50);
    writeSocket(receiver.append("\n"));
    QString answerFromServer = readSocket();
    closeSocket();
    emit removedPurchase(answerFromServer);
    return answerFromServer;
}

QString CommunicationProtocol::getBalance(QString buyer)
{
    writeSocket("get balance\n");
    QThread::msleep(50);

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        return "Server error, did not send data";
    }

    writeSocket(buyer.append("\n"));
    QString serverAnswer = readSocket();
    closeSocket();
    emit gotBalance(serverAnswer);
    return serverAnswer;
}

QString CommunicationProtocol::getSummary()
{
    writeSocket("get summary\n");
    QThread::msleep(50);
    QString serverResponse;

    QString mystr = readSocket();
    if(mystr != "ack\n")
    {
        qDebug() << "Entering != ack case, received " << mystr << " \n";
        closeSocket();
        return "Server error, did not send data";
    }

    for(int i=0; i<12; i++)
    {
        serverResponse.append(readSocket());
    }
    closeSocket();
    emit gotSummary(serverResponse);
    return serverResponse;
}

QString CommunicationProtocol::sendConsumer(QString consumer, QString date, QString hasEaten)
{
    writeSocket("send consumer\n");
    QThread::msleep(50);
    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        return "Server error, did not send data";
    }

    QThread::msleep(50);
    writeSocket(consumer.append("\n"));
    QThread::msleep(50);
    writeSocket(date.append("\n"));
    QThread::msleep(50);
    writeSocket(hasEaten.append("\n"));
    QString serverAnswer = readSocket();
    closeSocket();
    emit sentConsumer(serverAnswer);
    return serverAnswer;
}

QString CommunicationProtocol::getConsumer(QString consumer, QString date=QDate::currentDate().toString(Qt::ISODate))
{
    writeSocket("get consumer\n");
    QThread::msleep(50);

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        qDebug() << "Immediately before return \" cant reach server on regular UI update \" ";
        emit gotConsumer("Server communication error\n");
        return "Can't reach server on regular UI update";
    }

    QThread::msleep(30);
    writeSocket(consumer.append("\n"));
    QThread::msleep(30);
    writeSocket(date.append("\n"));
    QString answerFromServer = readSocket();
    closeSocket();
    emit gotConsumer(answerFromServer);
    return answerFromServer;
}

void CommunicationProtocol::checkThread()
{
    qDebug() << __PRETTY_FUNCTION__
             << QThread::currentThread() ;
}

