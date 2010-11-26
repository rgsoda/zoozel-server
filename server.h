#ifndef SERVER_H
#define SERVER_H
#include <QtNetwork>
#include "player.h"

class server : public QObject
{
    Q_OBJECT
public:
    server(QString host, quint16 port);

private slots:
    void processPendingDatagrams();

private:
    QUdpSocket udpSocket;
    QList<player*> players;
    void registerPlayer(player *p);
    void sendPlayerList(QHostAddress host, quint16 port);
    player *getPlayer(QString nick);
};

#endif // SERVER_H
