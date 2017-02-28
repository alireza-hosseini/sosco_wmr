#include "include/wmrudpconnection.h"
#include "include/WmrMovementProtocol.h"


WmrUdpConnection::WmrUdpConnection(QHostAddress hostAddress, quint16 port, WmrConnectionDirection direction):
    hostAddress_(hostAddress),port_(port),direction_(direction)
{
    udpSocket_ = new QUdpSocket();
}

void WmrUdpConnection::openConnection()
{
    qDebug()<<"Openning connection to port: "+QString::number(port_)+" host address: "+hostAddress_.toString();
    udpSocket_->bind(port_);
    if(direction_ == RX) {

                connect(udpSocket_,SIGNAL(readyRead()),this,SLOT(onReadyRead()));
    }
}

void WmrUdpConnection::send(QByteArray byteArray)
{
    udpSocket_->writeDatagram(byteArray,hostAddress_,port_);
}

QByteArray WmrUdpConnection::readDatagram()
{
    if(!udpSocket_->waitForReadyRead(100))
    {
        qDebug()<<"waiting for status timed out!";
        return QByteArray();
    }
    while (udpSocket_->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket_->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);

        return datagram;
    }
    return QByteArray();

}

WmrUdpConnection::~WmrUdpConnection()
{
    qDebug()<<"Destructing WmrUdpConnection";
    delete udpSocket_;
}


void WmrUdpConnection::onReadyRead()
{
    if (udpSocket_->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket_->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udpSocket_->readDatagram(datagram.data(), datagram.size(),
                                 &sender, &senderPort);
        emit dataReceived(datagram);
    }
}
