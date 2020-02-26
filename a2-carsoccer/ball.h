/** CSci-4611 Assignment 2:  Car Soccer
 */

#ifndef BALL_H_
#define BALL_H_

#include <mingfx.h>

/// Small data structure for a ball
class Ball {
public:

    /// The constructor sets the radius and calls Reset() to start the ball at
    /// the center of the field
    Ball() : radius_(2.6) {
        Reset();
    }

    /// Nothing special needed in the constructor
    virtual ~Ball() {}


    void Reset() {
        position_ = Point3(0, radius_, 0);
        float x_ = float (rand() / float (RAND_MAX));
        float y_ = float (rand() / float (RAND_MAX));
        float z_ = float (rand() / float (RAND_MAX));
        if(int(x_*10)%2 == 0){
          x_ = -1*x_;
        }
        if(int(z_*10)%2 == 0){
          z_ = -1*z_;
        }
	      velocity_ = Vector3(x_/8, y_/8, z_/8);//starting ball velocity
    }

    float radius() { return radius_; }

    Point3 position() { return position_; }
    void set_position(const Point3 &p) { position_ = p; }
    Vector3 velocity() { return velocity_; }
    void set_velocity(const Vector3 &v) {velocity_ = v; }


private:
    // You will probably need to store some additional data here, e.g., velocity

    Point3 position_;
    float radius_;
    Vector3 velocity_;
};

#endif
