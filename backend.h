#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTimer>
#include <QQmlApplicationEngine>
#include "sockethandler.h"
#include <QThread>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString domain MEMBER domain NOTIFY domainChanged)
    Q_PROPERTY(quint16 port MEMBER port NOTIFY portChanged)
    Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)

public:
    explicit Backend(QQmlApplicationEngine* newEngine, QObject *parent = nullptr);

public slots:
    void initSocket();
    void writeSocket(QString data);
    void initAndWriteSocket(QString data); // just a convenience function
    QString readSocket();
    void setPort(quint16 newPort);
    void setDomain(QString newDomain);
    void setName(QString newName);
    void closeSocket();
    bool isInitialised();
    void updateUI();
    bool sendPurchase(QString price, QString buyer, QString date, QString receiver);
    bool removePurchase(QString buyer, QString date, QString receiver);
    bool getBalance();
    bool getSummary();
    bool sendConsumer(QString consumer, QString date, QString hasEaten);
    bool getConsumer(QString consumer, QString date);

signals:
    void portChanged();
    void domainChanged();
    void dateChanged();
    void nameChanged();

private:
    QQmlApplicationEngine* engine;
    QObject* qmlRootObject;
    bool initialised;
    SocketHandler handle;
    quint16 port=39978;
    QString domain="palaven.de";
    QString name = "Max Mustermann";
};

#endif // BACKEND_H
