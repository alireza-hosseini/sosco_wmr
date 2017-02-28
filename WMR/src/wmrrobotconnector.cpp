#include "include/wmrrobotconnector.h"
#include "include/wmrudpconnection.h"


WmrRobotConnector::WmrRobotConnector(WmrSettings *settings, WmrRobot *robot):
    settings_(settings),robot_(robot)
{
    Q_ASSERT(robot!=NULL);
    Q_ASSERT(settings!=NULL);
}

bool WmrRobotConnector::connectRobot()
{
    movementCommandUdpConnection_ = new WmrUdpConnection(settings_->robotIp(),settings_->robotCommandPort(),TX);
    robot_->setWmrUdpCommandConnection(movementCommandUdpConnection_);
    movementStatusUdpConnection_ = new WmrUdpConnection(settings_->robotIp(),settings_->robotStatusPort(),RX);
    robot_->setWmrUdpStatusConnection(movementStatusUdpConnection_);

    sharpSensorsStatusUdpConnection_ = new WmrUdpConnection(settings_->robotIp(), settings_->sharpSensorsPort(),RX);
    robot_->setWmrUdpSharpSensorConnection(sharpSensorsStatusUdpConnection_);

    movementCommandUdpConnection_->openConnection();
    movementStatusUdpConnection_->openConnection();
    sharpSensorsStatusUdpConnection_->openConnection();
}
