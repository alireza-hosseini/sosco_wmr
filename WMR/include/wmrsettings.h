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

#ifndef WMRSETTINGS_H
#define WMRSETTINGS_H

#include <QHostAddress>

class WmrSettings
{
public:
    explicit WmrSettings(QHostAddress robotIp, quint16 commandPort, quint16 statusPort, quint16 sharpSensorPort);

    QHostAddress robotIp() const;

    quint16 robotCommandPort() const;

    quint16 robotStatusPort() const;

    quint16 sharpSensorsPort() const;

Q_SIGNALS:

public Q_SLOTS:

private:
    const QHostAddress robotIp_;
    const quint16 robotCommandPort_;
    const quint16 robotStatusPort_;
    const quint16 sharpSensorsStatusPort_;

    //interface command 6001
    //manual command 6002
    //sensor gyro,sonar receive 5001
    //sensor sharp 5002
};

#endif // WMRSETTINGS_H
