#include "runner.h"

runner::runner(QObject *parent)
    : QObject{parent}
{
    connect(&socket , &QUdpSocket::readyRead , this , &runner::readyRead);
}

void runner::readyRead()
{
    while(socket.hasPendingDatagrams()){
        QNetworkDatagram datagram = socket.receiveDatagram();
        qInfo()<<"Read:" << datagram.data();
        qInfo() << "from :" << datagram.senderAddress() << ":" << datagram.senderPort();

        int senderPort = datagram.senderPort();

        QString message = "Received";
        QByteArray data = message.toLatin1();
        QNetworkDatagram datagramAck(data , QHostAddress::Broadcast , senderPort);
        //qInfo()<<"send : " << data;
        socket.writeDatagram(datagramAck);

        clientports.insert(senderPort);

        foreach(int clientPort , clientports){
            QByteArray data = datagram.data();
            QNetworkDatagram datagram(data , QHostAddress::Broadcast , clientPort);
            //qInfo()<<"send : " << data;
            socket.writeDatagram(datagram);
        }

    }
}

void runner::start()
{
    if(!socket.bind(port)){
        qInfo()<<socket.errorString();
        return;
    }
    qInfo()<<"started UDP on :" << socket.localAddress() <<":"<< socket.localPort();
}
