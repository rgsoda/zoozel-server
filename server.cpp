#include "server.h"
#include <QDebug>


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
        QByteArray responseDatagram;
        responseDatagram.append("ACK");
        qDebug() << "New player connected NICKNAME : " << nick << host << port;
        qint64 res = udpSocket.writeDatagram(responseDatagram,host,port);
        if(res!=-1) {
            qDebug() << "Login ACK sended to client" << host << port;
        }
        //register new player

    } else if (messageType == "POS_UPDATE") {

        //qDebug() << "Position update " << datagram.data();

    }

}
