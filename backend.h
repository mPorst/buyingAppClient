#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include "sockethandler.h"

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString domain MEMBER domain NOTIFY domainChanged)
    Q_PROPERTY(quint16 port MEMBER port NOTIFY portChanged)

public:
    explicit Backend(QObject *parent = nullptr);

public slots:
    void initSocket();
    void writeSocket(QString data);
    void initAndWriteSocket(QString data); // just a convenience function
    QString readSocket();
    void setPort(quint16 newPort);
    void setDomain(QString newDomain);
    void closeSocket();
    bool isInitialised();

signals:
    void portChanged();
    void domainChanged();

private:
    bool initialised;
    SocketHandler handle;
    quint16 port=39978;
    QString domain="palaven.de";
};

#endif // BACKEND_H
