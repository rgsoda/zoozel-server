#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>

class server : public QObject
{
    Q_OBJECT
public:
    server(QString host, quint16 port);


private slots:
    void processPendingDatagrams();
private:
    QUdpSocket udpSocket;
};

#endif // SERVER_H
