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

#ifndef WMRMOVEMENTPROTOCOL_H
#define WMRMOVEMENTPROTOCOL_H

#include "BasicUtils.h"
#include <QDataStream>
#include "stdint.h"
#include <QDebug>

struct WmrMovementCommand {
protected:
    byte mode_ = 0x04;
public:
    float linearVelocty;
    float angularVelocity;

    QByteArray serialize() {
        QByteArray byteArray;
        QDataStream stream(&byteArray,QIODevice::WriteOnly);
        stream.setByteOrder(QDataStream::LittleEndian);
        stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
       stream<<mode_<<linearVelocty<<angularVelocity;
       return byteArray;
    }
};

#pragma pack(push)
#pragma pack(1)
struct WmrMovementStatus {
    uint16_t rightMotorEndSpeed_;
    uint16_t leftMotorEndSpeed_;
    byte     rightMotorDirection_;
    byte     leftMotorDirection_;
    uint16_t rightMotorEncoderPulse_;
    uint16_t leftMotorEncoderPulse_;
    float    odometryDeltaTheta_ = 0.0;
    float    odometryDeltaX_ = 0.0;
    float    odometryDeltaY_ = 0.0;
    float    rightMotorVelocity_ = 0;
    float    leftMotorVelocity_ = 0;

    bool deserialize(const QByteArray &byteArray) {
        if(byteArray.size() != sizeof(WmrMovementStatus)) {
            qWarning()<<"WmrMovementStatus: Deserialization failed, status is curropted."<<byteArray.size()<<" "<<sizeof(WmrMovementStatus);
            return false;
        }
        *this = *(WmrMovementStatus*)byteArray.data();
        return true;
    }
};
#pragma pack(pop)
#endif // WMRMOVEMENTPROTOCOL_H
