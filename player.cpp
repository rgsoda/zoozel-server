#include "player.h"

player::player(QHostAddress *address, quint16 *port, QString *nick) : ready(false)
{
    this->hostAddress = *address;
    this->hostPort = *port;
    this->nick = *nick;
}

bool player::isReady() {
    return this->ready;
}

void player::setReady(bool ready) {
    this->ready = ready;
}
