#include <QtCore/QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QStringList cmdline_args = QCoreApplication::arguments();
    QString host;
    QString port;

    if(cmdline_args.length() != 3) {
        qDebug("Usage :");
        qDebug("program host port");
        return 0;
    } else {
        host = cmdline_args[1];
        port = cmdline_args[2];
    }

    server *s = new server(host,port.toUInt());

    return a.exec();
}
