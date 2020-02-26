//Jacob Gorr Assignment 1

import java.lang.Math;
import java.util.*;

List<Point> posList = new ArrayList<Point>();
List<Vector> velList = new ArrayList<Vector>();
List<Point> starList = new ArrayList<Point>();
List<Float> lifeList = new ArrayList<Float>();
float dT = 0.1;//determines how

float eyeX = 250;//Camera variables
float eyeY = 250;
float eyeZ = 250/ tan(PI*30.0 / 180.0);
float cenX = 250;
float cenY = 250;
float cenZ = 0;
float x2=0;//keeps track of x position of ball
float y2=0;// keeps track of y position of ball
Point ball = new Point(0,0,0);
float radius = 15;

PShape ob;

//Class Declarations for points and vectors ----------------------------------------

class Vector{//I had trouble making a library so I just placed the class in the file
  float x = 0;
  float y = 0;
  float z = 0;
  
  Vector(float a, float b, float c){
   x=a;
   y=b;
   z=c;
  }
  float x(){
   return x; 
  }
  float y(){
   return y; 
  }
  float z(){
   return z; 
  }
  void setX(float n){
   x = n;
  }
  void setY(float n){
   y = n;
  }
  void setZ(float n){
   z = n;
  }
  Vector Add(Vector v){
    Vector n = new Vector(x+v.x(),y+v.y(),z+v.z());
    return n;
  }
  float Dot(Vector v){
   float scaler = x*v.x() + y*v.y() + z*v.z();
   return scaler;
  }
  float Mag(){
   float m = (float)sqrt(x*x + y*y + z*z);
   return m;
  }
  Vector Scale(float s){
   Vector sv = new Vector(x*s,y*s,z*s); 
   return sv;
  }
}

class Point{//I had trouble making a library so I just placed the class in the file
  float x = 0;
  float y = 0;
  float z = 0;
  
  Point(float a, float b, float c){
   x=a;
   y=b;
   z=c;
  }
  float x(){
   return x; 
  }
  float y(){
   return y; 
  }
  float z(){
   return z; 
  }
  void setX(float n){
   x = n;
  }
  void setY(float n){
   y = n;
  }
  void setZ(float n){
   z = n;
  }
  Vector Sub(Point p){
    Vector n = new Vector(x-p.x(),y-p.y(),z-p.z());
    return n;
  }
  Point Add(Vector v){
    Point p = new Point(x+v.x(),y+v.y(),z+v.z());
    return p;
  }
}


//End of Class Declartions-----------------------------------------------------------

void setup() {
  size(500,500, P3D);
  ob = loadShape("model3d1.obj");
  
  for(int i = 0; i <= 100; i ++){
    Point p = new Point(random(500),random(500),-10);
    starList.add(p);
  }
}

void generateParticles(float dT) {
  float genRate = 120;//240 gives 30fps and about 8000 particles
  float numParticles = dT*genRate;
  int radius = 3;
  numParticles = (int)numParticles;
  for(int i = 0; i < numParticles; i ++){
    double r = radius*Math.sqrt(random(2));
    float theta = 2*PI*random(1);
    float x = (float)r*sin(theta);
    float z = (float)r*cos(theta);
    Point p = new Point(300+x,200.0,z);
    Point p2 = new Point(300+x,200.0,z);
    posList.add(p);
    posList.add(p2);
    Vector v = new Vector(random(-6.05,-6.35),-10.0,random(-0.15,0.15));
    Vector v2 = new Vector(random(-4.05,4.35),-10.0,random(-0.15,0.15));
    velList.add(v);
    velList.add(v2);
    lifeList.add(0.0);
    lifeList.add(0.0);
  }
}

void updateParticals() {
  for(int i = 0; i <posList.size(); i++) {
    //Point newP = new Point();
    posList.set(i,posList.get(i).Add(velList.get(i).Scale(dT)));

    if(posList.get(i).y() > 400){//if the particles area at the bottom of the screen, change direction
      posList.get(i).setY(400.0);
      velList.get(i).setY(velList.get(i).y*(-0.4));//(i, velList.get(i).Scale(-0.4));//may be an error here
    }
    Vector d = posList.get(i).Sub(ball);
    float dist = d.Mag();
    if(dist < radius){//if a particle is inside of the sphere
      Vector normal = d;
      normal = normal.Scale(1/normal.Mag());//normalize normal
      posList.get(i).Add(normal.Scale(-1/3));
      
      normal = normal.Scale(velList.get(i).Dot(normal));
      normal = normal.Scale(-2);
      Vector result = velList.get(i).Add(normal);
      velList.set(i,result);
    }
  }
}

void updateVelocity() {
  for(int i = 0; i < velList.size(); i++){
    velList.get(i).setY(velList.get(i).y()+(2*dT));//velList.get(i+1)+2*dT)
  }
}

void updateLifeList() {
  //int dT = 1;
  for(int i = 0; i < lifeList.size();i++) {
    if(lifeList.get(i) > 45){
      posList.remove(i);
      velList.remove(i);
      lifeList.remove(i); 
    }else{
    lifeList.set(i,(lifeList.get(i) + dT));
    }
  }
}

void mouseDragged(){
  ball.setX(pmouseX);//x2 = pmouseX;
  ball.setY(pmouseY);//y2 = pmouseY;
}

void drawScene(){
  background(70,70,70);
  stroke(180,180,180);
  fill(90,90,90);
  beginShape();
  vertex(-50,600,-5);
  vertex(-50,400,-5);
  vertex(600,400,-5);
  vertex(600,600,-5);
  endShape(CLOSE);
  fill(100,100,100);
  camera(eyeX, eyeY, eyeZ, cenX, cenY, cenZ, 0, 1, 0);
  
  shape(ob,305,400,200,-200);
  
  for(int i = 0; i < starList.size(); i++) {
    Point p = starList.get(i);
    point(p.x(),p.y(),p.z());
  }
  circle(100,100,40);
  fill(70,70,70);
  circle(104,104,30);
  
  fill(255,255,255);
  
  translate(ball.x(),ball.y(),0);
  noStroke();
  sphere(radius);
  translate(-ball.x(),-ball.y(),0);
  
  strokeWeight(3);
  stroke(0,61,102);
  //stroke(255,61,102);
  for(int i = 0; i<posList.size(); i++){
    Point p = posList.get(i);
    point(p.x(),p.y(),p.z());
  }
}


void draw() {
  
  float startFrame = millis();
  generateParticles(dT);
  updateParticals();
  updateVelocity();
  updateLifeList();
  
  float endPhysics = millis();
  
  drawScene();
  
  float endFrame = millis();
  
  String runtimeReport = "Frame: "+str(endFrame-startFrame)+"ms,"+
        " Physics: "+ str(endPhysics-startFrame)+"ms,"+
        " FPS: "+ str(round(frameRate)) +"\n";
  surface.setTitle(runtimeReport);
  
  if (keyPressed) {
    if(key == ' '){
      eyeY -= 5;
      cenY -= 5;
    }else if(key == 'w'){
      eyeZ -= 5;
      cenZ -= 5;
    }else if(key == 'a'){
      eyeX -= 5;
      cenX -= 5;
    }else if(key == 's'){
      eyeZ += 5;
      cenZ += 5;
    }else if(key == 'd'){
      eyeX += 5;
      cenX += 5;
    }else if(key == 'r'){//reset to default camera position
      eyeX = 250;
      eyeY = 250;
      eyeZ = 250/ tan(PI*30.0 / 180.0);
      cenX = 250;
      cenY = 250;
      cenZ = 0;
    }
    if(key == CODED){
      if(keyCode == UP){
        cenY -= 10;
      }else if(keyCode == DOWN){
        cenY += 10;
      }else if(keyCode == LEFT){
        cenX -= 10;
      }else if(keyCode == RIGHT){//moves quickly at first, but slows down how fast it turns
        cenX += 10;
      }else if(keyCode == SHIFT){
      eyeY += 5;
      cenY += 5;
      }
    }  
  } 

  //text(posList.size()/3,50,450);  
}
