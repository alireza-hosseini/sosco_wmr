#include "include/wmrrobot.h"
#include <math.h>

WmrRobot::WmrRobot(QObject *parent) :
    QObject(parent) {
    for(int i=0;i<IR_SENSORS_NUM;i++) {
        ir_sensors_.append(WmrIRReading(i*33));
    }
}

WmrRobot::~WmrRobot()
{
    delete wmrUdpCommandConnection_;
    delete wmrUdpStatusConnection_;
    delete wmrUdpSharpSensorConnection_;
}

WmrUdpConnection *WmrRobot::wmrUdpCommandConnection() const
{
    Q_ASSERT(wmrUdpCommandConnection_!=NULL);
    return wmrUdpCommandConnection_;
}

void WmrRobot::setWmrUdpCommandConnection(WmrUdpConnection *wmrUdpCommandConnection)
{
    wmrUdpCommandConnection_ = wmrUdpCommandConnection;
}
WmrUdpConnection *WmrRobot::wmrUdpStatusConnection() const
{
    return wmrUdpStatusConnection_;
}

void WmrRobot::setWmrUdpStatusConnection(WmrUdpConnection *wmrUdpStatusConnection)
{
    wmrUdpStatusConnection_ = wmrUdpStatusConnection;
}

WmrUdpConnection *WmrRobot::wmrUdpSharpSensorConnection() const
{
    return wmrUdpSharpSensorConnection_;
}

void WmrRobot::setWmrUdpSharpSensorConnection(WmrUdpConnection *wmrUdpStatusConnection)
{
    wmrUdpSharpSensorConnection_ = wmrUdpStatusConnection;
    connect(wmrUdpSharpSensorConnection_,SIGNAL(dataReceived(QByteArray)),this,SLOT(onSharpSensorStatusReceived(QByteArray)));
}

void WmrRobot::readStatus()
{
    QByteArray byteArray = wmrUdpStatusConnection()->readDatagram();
    WmrMovementStatus status;
    if(status.deserialize(byteArray)) {
        //qDebug()<<status.odometryDeltaX_<<""<<status.odometryDeltaY_<<" "<<status.odometryDeltaTheta_;

        currentPose_.setX(currentPose_.getX()+(status.odometryDeltaX_*cos(currentPose_.getTheta())-status.odometryDeltaY_*sin(currentPose_.getTheta())));
        currentPose_.setY(currentPose_.getY()+(status.odometryDeltaY_*sin(currentPose_.getTheta())+status.odometryDeltaY_*cos(currentPose_.getTheta())));
        currentPose_.setTetha((currentPose_.getTheta()+status.odometryDeltaTheta_));

        encoderPulseLeft_ = status.leftMotorEncoderPulse_;
        encoderPulseRight_ = status.rightMotorEncoderPulse_;

        encoderRPosPrev += status.rightMotorEncoderPulse_;
        encodetLPosPrev += status.leftMotorEncoderPulse_;

        velocityLeft_ = status.leftMotorVelocity_;
        velocityRight_ = status.rightMotorVelocity_;

        linearVelocity_ = (velocityLeft_ + velocityRight_)/2.0;
        rotationalVelocity_ = (velocityLeft_ - velocityRight_)/robot_length_;
    }
}

void WmrRobot::readSharp() {
    QByteArray byteArray = wmrUdpSharpSensorConnection()->readDatagram();
    QDataStream ds(&byteArray,QIODevice::ReadWrite);
    for(int i=0;i<IR_SENSORS_NUM;i++) {
        byte value;
        ds>>value;
        ir_sensors_[i].updateValue(value);
    }
}

void WmrRobot::setLinearVel(double linear_vel)
{
    wmrMovementCommand_.linearVelocty = -1*linear_vel;
    wmrUdpCommandConnection()->send(wmrMovementCommand_.serialize());
}

void WmrRobot::setRotVel(double rotational_vel)
{
    wmrMovementCommand_.angularVelocity = -1*rotational_vel;
    wmrUdpCommandConnection()->send(wmrMovementCommand_.serialize());
}

float WmrRobot::getX()
{
    return currentPose_.getX();
}

float WmrRobot::getY()
{
    return currentPose_.getY();
}

float WmrRobot::getTheta()
{
    return currentPose_.getTheta();
}

WmrPose WmrRobot::getPose()
{
    return currentPose_;
}

float WmrRobot::getLinearVel()
{
    return linearVelocity_;
}

float WmrRobot::getRotationalVel()
{
    return rotationalVelocity_;
}

unsigned int WmrRobot::getLeftMotorEncoderPulse()
{
    return encoderPulseLeft_;
}

unsigned int WmrRobot::getRightMotorEncoderPulse()
{
    return encoderPulseRight_;
}

float WmrRobot::getLeftMotorVelocity()
{
    return velocityLeft_;
}

float WmrRobot::getRightMotorVelocity()
{
    return velocityRight_;
}

WmrIRReading WmrRobot::getIRProximity(int index)
{
    if( index > (IR_SENSORS_NUM-1) ){
        return 0;
    }
    return ir_sensors_[index];
}

void WmrRobot::onMovementStatusReceived(QByteArray byteArray)
{

    WmrMovementStatus status;
    if(status.deserialize(byteArray)) {
        currentPose_.setX((currentPose_.getX()+status.odometryDeltaX_*status.odometryDeltaTheta_));
        currentPose_.setY((currentPose_.getY()+status.odometryDeltaY_*status.odometryDeltaTheta_));
        currentPose_.setTetha((currentPose_.getTheta()+status.odometryDeltaTheta_));

        encoderPulseLeft_ = status.leftMotorEncoderPulse_;
        encoderPulseRight_ = status.rightMotorEncoderPulse_;
        velocityLeft_ = status.leftMotorVelocity_;
        velocityRight_ = status.rightMotorVelocity_;

    }
}

void WmrRobot::onSharpSensorStatusReceived(QByteArray byteArray)
{
    QDataStream ds(&byteArray,QIODevice::ReadWrite);
    for(int i=0;i<IR_SENSORS_NUM;i++) {
        byte value;
        ds>>value;
        ir_sensors_[i].updateValue(value);
    }
}






