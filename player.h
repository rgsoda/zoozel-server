#ifndef PLAYER_H
#define PLAYER_H
#include <QtNetwork>

class player
{
public:
    player(QHostAddress *address, quint16 *port, QString *nick);
    QHostAddress hostAddress;
    quint16 hostPort;
    QString nick;
    bool isReady();
    void setReady(bool ready);
private:
    bool ready;
};

#endif // PLAYER_H
