#ifndef WMRSHARPSENSORPROTOCOL_H
#define WMRSHARPSENSORPROTOCOL_H
#include <math.h>

class WmrIRReading {
public:
    WmrIRReading(float angle):
    angle_(angle) {
    }

    const void updateValue(const byte raw_range) {
        x_ = raw_range*cos(angle_*(M_PI/180));
        y_ = raw_range*sin(angle_*(M_PI/180));
    }

    const float getX() const { return x_; }
    const float getY() const { return y_; }

private:
    float angle_;
    float x_;
    float y_;
};


#endif // WMRSHARPSENSORPROTOCOL_H
