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

#ifndef WMRROBOT_H
#define WMRROBOT_H

#include <QObject>
#include "wmrudpconnection.h"
#include "WmrMovementProtocol.h"
#include "WmrSharpSensorProtocol.h"
#include "WmrPose.h"

#define WMR_ROBOT_LENGTH 0.55
#define IR_SENSORS_NUM 16

class WmrRobot : public QObject
{
    Q_OBJECT
public:
    explicit WmrRobot(QObject *parent = 0);
    ~WmrRobot();

    WmrUdpConnection *wmrUdpCommandConnection() const;
    void setWmrUdpCommandConnection(WmrUdpConnection *wmrUdpCommandConnection);

    WmrUdpConnection *wmrUdpStatusConnection() const;
    void setWmrUdpStatusConnection(WmrUdpConnection *wmrUdpStatusConnection);

    WmrUdpConnection *wmrUdpSharpSensorConnection() const;
    void setWmrUdpSharpSensorConnection(WmrUdpConnection *wmrUdpStatusConnection);

    void setRobotLength(float length) { robot_length_ = length; }

    void readStatus();
    void readSharp();

    void stop(void);

    void setLinearVel(double linear_vel);
    void setRotVel(double rotational_vel);
    float getX();
    float getY();
    float getTheta();
    WmrPose getPose();

    float getLinearVel();
    float getRotationalVel();

    unsigned int getLeftMotorEncoderPulse();
    unsigned int getRightMotorEncoderPulse();

    float getLeftMotorVelocity();
    float getRightMotorVelocity();

    QList<WmrIRReading> getIRProximities(){ return ir_sensors_; }
    WmrIRReading getIRProximity(int index);

Q_SIGNALS:

private Q_SLOTS:
    void onMovementStatusReceived(QByteArray byteArray);
    void onSharpSensorStatusReceived(QByteArray byteArray);

private:

    float robot_length_ = WMR_ROBOT_LENGTH;

    WmrUdpConnection *wmrUdpCommandConnection_ = NULL;
    WmrUdpConnection *wmrUdpStatusConnection_ = NULL;
    WmrUdpConnection *wmrUdpSharpSensorConnection_ = NULL;

    WmrMovementCommand wmrMovementCommand_;
    QThread *statusThread;
    WmrPose currentPose_;

    unsigned int encoderPulseRight_ = 0;
    unsigned int encoderPulseLeft_ = 0;

    int encoderRPosPrev = 0;
    int encodetLPosPrev = 0;

    float velocityRight_ = 0;
    float velocityLeft_ = 0;

    float linearVelocity_ = 0;
    float rotationalVelocity_ = 0;

    QList<WmrIRReading> ir_sensors_;
};

#endif // WMRROBOT_H
