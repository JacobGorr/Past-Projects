/** CSci-4611 Assignment 2:  Car Soccer
 */

#include "car_soccer.h"
#include "config.h"
#include "math.h"


CarSoccer::CarSoccer() : GraphicsApp(1024,768, "Car Soccer") {
    // Define a search path for finding data files (images and shaders)
    searchPath_.push_back(".");
    searchPath_.push_back("./data");
    searchPath_.push_back(DATA_DIR_INSTALL);
    searchPath_.push_back(DATA_DIR_BUILD);
}

CarSoccer::~CarSoccer() {
}


Vector2 CarSoccer::joystick_direction() {
    Vector2 dir;
    if (IsKeyDown(GLFW_KEY_LEFT)){
        dir[0]--;
        car_.set_angle(car_.angle()- 0.005 );
    }
    if (IsKeyDown(GLFW_KEY_RIGHT)){
        dir[0]++;
        car_.set_angle(car_.angle()+ 0.005 );
    }
    if (IsKeyDown(GLFW_KEY_UP)){
        dir[1]++;
        if(car_.speed()<0.1){//max speed
          car_.set_speed(car_.speed() + 0.0001);
        }
    }
    if (IsKeyDown(GLFW_KEY_DOWN)){
        dir[1]--;
        if(car_.speed()>-0.1){
          car_.set_speed(car_.speed() - 0.0001);
        }
    }
    if (!IsKeyDown(GLFW_KEY_UP) && !IsKeyDown(GLFW_KEY_DOWN)){
      //if niether the accelartion or brake is pressed, slow down car
      if(car_.speed() > 0 ){
        car_.set_speed(car_.speed() - 0.0001);
      }else if(car_.speed() < 0){
        car_.set_speed(car_.speed() + 0.0001);
      }
    }

    return dir;
}


void CarSoccer::OnSpecialKeyDown(int key, int scancode, int modifiers) {
    if (key == GLFW_KEY_SPACE) {
        // Here's where you could call some form of launch_ball();
        //ball_.set_position(Point3(0,2.6,0));//reset position to center
        //ball_.set_velocity(ball_.velocity()+Vector3(0,1,0));
        ball_.Reset();
    }
}


void CarSoccer::UpdateSimulation(double timeStep) {
    // Here's where you shound do your "simulation", updating the positions of the
    // car and ball as needed and checking for collisions.  Filling this routine
    // in is the main part of the assignment.

    Vector2 carD = joystick_direction().ToUnit()*0.15;//calling this updates speed
    Vector3 car3d = Vector3(cos(car_.angle()),0,sin(car_.angle()))*car_.speed();
    //car_.set_angle( atan(carD[1]/carD[0]));//radians causes flashing car
    car_.set_position( car_.position()+ car3d );
    Point3 carPos = car_.position();

    if(carPos.x() >= 38.4){//wall detection for car
      car_.set_position(Point3(38.4,carPos.y(),carPos.z()));
    }else if(carPos.x() <= -38.4){
      car_.set_position(Point3(-38.4,carPos.y(),carPos.z()));
    }else if(carPos.z() >= 48.4){
      car_.set_position(Point3(carPos.x(),carPos.y(),48.4));
    }else if(carPos.z() <= -48.4){
      car_.set_position(Point3(carPos.x(),carPos.y(),-48.4));
    }//car can drive out of corners stright for every,




    ball_.set_position(ball_.position() + ball_.velocity());
    Point3 pos = ball_.position();
    Vector3 direction = pos-carPos;
    if((direction).Length() < car_.collision_radius()+ball_.radius()){
      ball_.set_position(pos+direction.ToUnit()*1.3);//resets ball to center on hit with car
      Vector3 result = ball_.velocity()-2*(ball_.velocity().Dot(direction.ToUnit()))*direction.ToUnit();
      ball_.set_velocity(result);
    }

    Vector3 vel = ball_.velocity();

    //Height hitbox detection
    if(pos.y() > 2 && pos.y()<35){
      ball_.set_velocity(ball_.velocity() + Vector3(0,-0.05,0)*timeStep);//gravity
    }else if(pos.y() <= 2.6){//if the ball hits the ground, bounce up
      ball_.set_position(Point3(pos.x(),2.6,pos.z()));
      ball_.set_velocity(Vector3(vel.x(),vel.y()*-0.8,vel.z()));
    }else if(pos.y() >= 35){//if the ball hits the ceiling
      ball_.set_velocity(Vector3(vel.x(),vel.y()*-1,vel.z()));
    }
    //Wall hitbox detection
    if(abs(pos.x()) >= 37.4 ){
      ball_.set_velocity(Vector3(vel[0]*-0.8,vel[1],vel[2]));//real basic, too basic
      ball_.set_position(ball_.position() + ball_.velocity());
    } else if( abs(pos.z()) >= 47.4){
      ball_.set_velocity(Vector3(vel[0],vel[1],vel[2]*-0.8));//real basic, too basic
      ball_.set_position(ball_.position() + ball_.velocity());
    }

}


void CarSoccer::InitOpenGL() {
    // Set up the camera in a good position to see the entire field
    projMatrix_ = Matrix4::Perspective(60, aspect_ratio(), 1, 1000);
    modelMatrix_ = Matrix4::LookAt(Point3(0,60,70), Point3(0,0,10), Vector3(0,1,0));

    // Set a background color for the screen
    glClearColor(0.8,0.8,0.8, 1);

    // Load some image files we'll use
    fieldTex_.InitFromFile(Platform::FindFile("pitch.png", searchPath_));
    crowdTex_.InitFromFile(Platform::FindFile("crowd.png", searchPath_));

    //ball_.set_velocity(Vector3(0,0,0));
}


void CarSoccer::DrawUsingOpenGL() {
    // Draw the crowd as a fullscreen background image
    quickShapes_.DrawFullscreenTexture(Color(1,1,1), crowdTex_);

    // Draw the field with the field texture on it.
    Color col(16.0/255.0, 46.0/255.0, 9.0/255.0);
    Matrix4 M = Matrix4::Translation(Vector3(0,-0.201,0)) * Matrix4::Scale(Vector3(50, 1, 60));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, col);
    M = Matrix4::Translation(Vector3(0,-0.2,0)) * Matrix4::Scale(Vector3(40, 1, 50));
    quickShapes_.DrawSquare(modelMatrix_ * M, viewMatrix_, projMatrix_, Color(1,1,1), fieldTex_);

    // Draw the car
    Color carcol(0.8, 0.2, 0.2);
    Matrix4 Mcar =
        Matrix4::Translation(car_.position() - Point3(0,0,0)) *
        Matrix4::RotationY(-1*car_.angle()) *
        Matrix4::Scale(car_.size()) *
        Matrix4::Scale(Vector3(0.5,0.5,0.5));
    quickShapes_.DrawCube(modelMatrix_ * Mcar, viewMatrix_, projMatrix_, carcol);


    // Draw the ball
    Color ballcol(1,1,1);
    Matrix4 Mball =
        Matrix4::Translation(ball_.position() - Point3(0,0,0)) *
        Matrix4::Scale(Vector3(ball_.radius(), ball_.radius(), ball_.radius()));
    quickShapes_.DrawSphere(modelMatrix_ * Mball, viewMatrix_, projMatrix_, ballcol);


    // Draw the ball's shadow -- this is a bit of a hack, scaling Y by zero
    // flattens the sphere into a pancake, which we then draw just a bit
    // above the ground plane.
    Color shadowcol(0.2,0.4,0.15);
    Matrix4 Mshadow =
        Matrix4::Translation(Vector3(ball_.position()[0], -0.1, ball_.position()[2])) *
        Matrix4::Scale(Vector3(ball_.radius(), 0, ball_.radius())) *
        Matrix4::RotationX(90);
    quickShapes_.DrawSphere(modelMatrix_ * Mshadow, viewMatrix_, projMatrix_, shadowcol);


    // You should add drawing the goals and the boundary of the playing area
    // using quickShapes_.DrawLines()
    std::vector<Point3> blueGoal;//loop contains points for blue goal
    blueGoal.push_back(Point3( -10.0, 0.0, -50.0));
    blueGoal.push_back(Point3( -10.0, 10.0, -50.0));
    blueGoal.push_back(Point3( 10.0, 10.0,  -50.0));
    blueGoal.push_back(Point3( 10.0, 0.0,  -50.0));
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_,Color(0,0,1),blueGoal,
                            quickShapes_.LinesType::LINE_LOOP, 0.23);//larger size cause further
                                                                    //camera

    std::vector<Point3> OrangeGoal;//loop contains points for orange goal
    OrangeGoal.push_back(Point3( -10.0, 0.0, 50.0));
    OrangeGoal.push_back(Point3( -10.0, 10.0, 50.0));
    OrangeGoal.push_back(Point3( 10.0, 10.0,  50.0));
    OrangeGoal.push_back(Point3( 10.0, 0.0,  50.0));
    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_,Color(1,0.5,0),OrangeGoal,
                            quickShapes_.LinesType::LINE_LOOP, 0.2);
    ;
    std::vector<Point3> boundaries;//loop contains points for orange goal
    boundaries.push_back(Point3( -40.0, 0.0, 50.0));
    boundaries.push_back(Point3( -40.0, 35.0, 50.0));
    boundaries.push_back(Point3( 40.0, 35.0,  50.0));
    boundaries.push_back(Point3( 40.0, 0.0,  50.0));
    boundaries.push_back(Point3( 40.0, 0.0,  -50.0));
    boundaries.push_back(Point3( 40.0, 35.0,  -50.0));
    boundaries.push_back(Point3( -40.0, 35.0, -50.0));
    boundaries.push_back(Point3( -40.0, 0.0, -50.0));
    boundaries.push_back(Point3( -40.0, 35.0, -50.0));
    boundaries.push_back(Point3( -40.0, 35.0, 50.0));
    boundaries.push_back(Point3( 40.0, 35.0, 50.0));
    boundaries.push_back(Point3( 40.0, 35.0, -50.0));



    quickShapes_.DrawLines(modelMatrix_, viewMatrix_, projMatrix_,Color(1,1,1),boundaries,
                            quickShapes_.LinesType::LINES, 0.15);


}
