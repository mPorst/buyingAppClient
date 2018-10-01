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
    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit sentPurchase("Server sent \"" + answerFromServer +"\"\n");
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
    answerFromServer = readSocket();
    closeSocket();
    emit sentPurchase(answerFromServer);
    return answerFromServer;
}
QString CommunicationProtocol::removePurchase(QString buyer, QString date, QString receiver)
{
    writeSocket("remove purchase\n");
    QThread::msleep(50);

    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit removedPurchase("Server sent \"" + answerFromServer +"\"\n");
        return "Server error, did not send data";
    }

    QThread::msleep(50);
    writeSocket(buyer.append("\n"));
    QThread::msleep(50);
    writeSocket(date.append("\n"));
    QThread::msleep(50);
    writeSocket(receiver.append("\n"));
    answerFromServer = readSocket();
    closeSocket();
    emit removedPurchase(answerFromServer);
    return answerFromServer;
}

QString CommunicationProtocol::getBalance(QString buyer)
{
    writeSocket("get balance\n");
    QThread::msleep(50);

    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit gotBalance("Server sent \"" + answerFromServer +"\"\n");
        return "Server error, did not send data";
    }

    writeSocket(buyer.append("\n"));
    answerFromServer = readSocket();
    closeSocket();
    emit gotBalance(answerFromServer);
    return answerFromServer;
}

QString CommunicationProtocol::getSummary()
{
    writeSocket("get summary\n");
    QThread::msleep(50);
    QString serverResponse;

    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit gotSummary("Server sent \"" + answerFromServer +"\"\n");
        return "Server error, did not send data";
    }

    //for(int i=0; i<12; i++)
    QString answer;
    do
    {
        //if(!handle->waitForReadyRead(5000))
        //{
         //   qDebug() << "Breaking as waitForReadyRead was false";
          //  break;
        //}
        answer = readSocket();
        qDebug() << "Received message " << answer;
        if(!serverResponse.isEmpty() && answer == "Socket read error")
        {

        }
        else
        {
            serverResponse.append(answer);
        }
    }
    while(answer != "Socket read error");
    closeSocket();
    emit gotSummary(serverResponse);
    return serverResponse;
}

QString CommunicationProtocol::sendConsumer(QString consumer, QString date, QString hasEaten)
{
    writeSocket("send consumer\n");
    QThread::msleep(50);

    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit sentConsumer("Server sent \"" + answerFromServer +"\"\n");
        return "Server error, did not send data";
    }

    QThread::msleep(50);
    writeSocket(consumer.append("\n"));
    QThread::msleep(50);
    writeSocket(date.append("\n"));
    QThread::msleep(50);
    writeSocket(hasEaten.append("\n"));
    answerFromServer = readSocket();
    closeSocket();
    emit sentConsumer(answerFromServer);
    return answerFromServer;
}

QString CommunicationProtocol::getConsumer(QString consumer, QString date=QDate::currentDate().toString(Qt::ISODate))
{
    writeSocket("get consumer\n");
    QThread::msleep(50);

    QString answerFromServer = readSocket();

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit gotConsumer("Server sent \"" + answerFromServer +"\"\n");
        return "Can't reach server on regular UI update";
    }

    QThread::msleep(30);
    writeSocket(consumer.append("\n"));
    QThread::msleep(30);
    writeSocket(date.append("\n"));
    answerFromServer = readSocket();
    closeSocket();
    emit gotConsumer(answerFromServer);
    return answerFromServer;
}

void CommunicationProtocol::checkThread()
{
    qDebug() << __PRETTY_FUNCTION__
             << QThread::currentThread() ;
}

QString CommunicationProtocol::getEaters(QString date)
{
    writeSocket("get eaters\n");
    QThread::msleep(50);

    QString answerFromServer = readSocket();
    QString appendedAnswer;

    if(answerFromServer != "ack\n")
    {
        qDebug() << "Did not receive confirmation from server, received \"" << answerFromServer << "\" \n";
        closeSocket();
        emit gotEaters("Server sent \"" + answerFromServer +"\"\n");
        return "Server error, did not send data";
    }

    QThread::msleep(10);
    writeSocket(date.append("\n"));
    do
    {
        QThread::msleep(30);
        answerFromServer = readSocket();
        qDebug() << "Server answered" << answerFromServer;
        if(answerFromServer == "Socket read error" && !appendedAnswer.isEmpty())
        {
        }
        else
        {
            appendedAnswer.append(answerFromServer);
        }
    }
    while(answerFromServer != "Socket read error");
    closeSocket();
    emit gotEaters(appendedAnswer);
    return appendedAnswer;
}
