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

#ifndef WMRROBOTCONNECTOR_H
#define WMRROBOTCONNECTOR_H

#include <QObject>
#include <QUdpSocket>

#include "wmrrobot.h"
#include "wmrsettings.h"

class WmrRobotConnector : public QObject
{
    Q_OBJECT
public:
    explicit WmrRobotConnector(WmrSettings* settings, WmrRobot* robot);
    bool connectRobot();

Q_SIGNALS:

public Q_SLOTS:

private:
    WmrRobot *robot_;
    const WmrSettings *settings_;

    WmrUdpConnection *movementCommandUdpConnection_;
    WmrUdpConnection *movementStatusUdpConnection_;
    WmrUdpConnection *sharpSensorsStatusUdpConnection_;
};

#endif // WMRROBOTCONNECTOR_H
