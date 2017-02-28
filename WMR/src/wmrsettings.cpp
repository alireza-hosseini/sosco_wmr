#include "include/wmrsettings.h"

WmrSettings::WmrSettings(QHostAddress robotIp, quint16 commandPort, quint16 statusPort, quint16 sharpSensorPort):
    robotIp_(robotIp),
    robotCommandPort_(commandPort),
    robotStatusPort_(statusPort),
    sharpSensorsStatusPort_(sharpSensorPort)
{

}
QHostAddress WmrSettings::robotIp() const
{
    return robotIp_;
}
quint16 WmrSettings::robotCommandPort() const
{
    return robotCommandPort_;
}
quint16 WmrSettings::robotStatusPort() const
{
    return robotStatusPort_;
}

quint16 WmrSettings::sharpSensorsPort() const {
    return sharpSensorsStatusPort_;
}

