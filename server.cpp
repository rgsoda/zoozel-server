#include <QDebug>
#include "server.h"
#include "player.h"

server::server(QString host, quint16 p)
{

    udpSocket.bind(QHostAddress(host),p);
    connect(&udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    qDebug() << "Server started ::: " << udpSocket.localAddress() << udpSocket.localPort();

}

void server::processPendingDatagrams() {
    QByteArray datagram;
    QHostAddress host;
    quint16 port;

    do {
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size(),&host,&port);

    } while (udpSocket.hasPendingDatagrams());

    QDataStream in(&datagram, QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_1);

    QString messageType;
    in >> messageType;

    if(messageType == "NEW_PLAYER") {

        QString nick;
        in >> nick;
        qDebug() << "New player connected NICKNAME : " << nick << host << port;

        sendPlayerList(host,port);
        player *p = new player(&host,&port,&nick);
        registerPlayer(p);


    } else if (messageType == "POS_UPDATE") {

        foreach(player *player,this->players) {

            if((player->hostPort != port)) {
                if(player->isReady()) {
                    qint64 res = udpSocket.writeDatagram(datagram,player->hostAddress,player->hostPort);
                    if(res!=-1) {
                        //qDebug() << player->nick << " informed about "  << nick << " move ";
                    }
                }
            }

        }

    } else if (messageType == "PLAYER_READY") {

        QString nick;
        in >> nick;
        qDebug() << nick << " is Ready ";
        player *p = getPlayer(nick);
        if(p!=0) {
            p->setReady(true);
        }
    }

}


void server::registerPlayer(player *p) {
    if(this->players.size() > 0 ) {
        foreach(player *player,this->players) {

            QByteArray datagram;
            QDataStream in(&datagram, QIODevice::ReadWrite);
            in.setVersion(QDataStream::Qt_4_1);
            in << QString("PLAYER_CONNECTED") << p->nick;
            qint64 res = udpSocket.writeDatagram(datagram,player->hostAddress,player->hostPort);
            if(res!=-1) {
                qDebug() << player->nick << " informed about new player" <<  p->nick;
            }

        }
    }
    this->players.append(p);
}

void server::sendPlayerList(QHostAddress host, quint16 port) {
    QByteArray datagram;
    QList<QString> pNames;
    foreach(player *player,this->players) {
        pNames.append(player->nick);
    }

        QDataStream in(&datagram, QIODevice::ReadWrite);
        in.setVersion(QDataStream::Qt_4_1);
        in << QString("PLAYER_LIST") << pNames;
        qint64 res = udpSocket.writeDatagram(datagram,host,port);
        if(res!=-1) {
            qDebug() << "Player list "<< pNames <<"sended to client" << host << port;
        }

}

player *server::getPlayer(QString nick) {
    foreach(player *player,this->players) {
        if (player->nick == nick) return player;
    }
    return 0;
}
