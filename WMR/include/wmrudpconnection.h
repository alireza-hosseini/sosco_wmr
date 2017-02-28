/*
    SOSCO, Wheeled Mobile Robot(WMR)
    Copyright (C) 2016  Alireza Hosseini

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef WMRUDPCONNECTION_H
#define WMRUDPCONNECTION_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

enum WmrConnectionDirection {
    TX,
    RX
};

class WmrUdpConnection : public QObject
{
    Q_OBJECT
public:
    explicit WmrUdpConnection(QHostAddress hostAddress, quint16 port, WmrConnectionDirection direction);
    void openConnection();
    void send(QByteArray byteArray);
    QByteArray readDatagram();

    ~WmrUdpConnection();

Q_SIGNALS:
    void dataReceived(QByteArray);

private Q_SLOTS:
    void onReadyRead();

private:
    QUdpSocket  *udpSocket_;
    QHostAddress hostAddress_;
    quint16      port_;
    WmrConnectionDirection direction_;
};

#endif // WMRUDPCONNECTION_H
