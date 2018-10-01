#ifndef COMMUNICATIONPROTOCOL_H
#define COMMUNICATIONPROTOCOL_H

#include <QObject>
#include "sockethandler.h"
#include <QThread>
#include <QDate>

class CommunicationProtocol : public QObject
{
    Q_OBJECT
public:
    CommunicationProtocol(QThread* newMainThread);
    virtual ~CommunicationProtocol();

public slots:
    // socket operations
    void initSocket();
    void writeSocket(QString data);
    QString readSocket();
    void closeSocket();

    //bool connect();
    QString sendPurchase(QString price, QString buyer, QString date, QString receiver);
    QString removePurchase(QString buyer, QString date, QString receiver);
    QString getBalance(QString name);
    QString getSummary();
    QString sendConsumer(QString consumer, QString date, QString hasEaten);
    QString getConsumer(QString consumer, QString date);
    QString getEaters(QString date);
    //QString getConsumer();

    // getters/setters
    void setPort(quint16 port);
    void setDomain(QString domain);

    void checkThread();

signals:
    void gotConsumer(QString msg);
    void sentPurchase(QString msg);
    void removedPurchase(QString msg);
    void sentConsumer(QString msg);
    void gotSummary(QString msg);
    void commsError(QString msg);
    void gotBalance(QString msg);
    void gotEaters(QString msg);

private:
    SocketHandler* handle;
    quint16 port;
    QString domain;
    bool initialised;
    QThread* mainThread;
};

#endif // COMMUNICATIONPROTOCOL_H
