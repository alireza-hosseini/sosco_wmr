#ifndef WMRPOSE_H
#define WMRPOSE_H

class WmrPose {
    float x = 0;
    float y = 0;
    float tetha = 0;

public:

    const float getTheta() const {
        return tetha;
    }

    void setTetha(float tetha){
        this->tetha =  tetha;
    }

    const float getX() const {
        return x;
    }

    void setX(float x){
        this->x =  x;
    }

    const float getY() const {
        return y;
    }

    void setY(float y){
        this->y =  y;
    }


};

#endif // WMRPOSE_H
