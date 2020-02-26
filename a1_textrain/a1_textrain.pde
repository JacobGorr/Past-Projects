/**
    CSci-4611 Assignment #1 Text Rain
    Jacob Gorr
**/

import processing.video.*;

// Global variables for handling video data and the input selection screen
String[] cameras;
Capture cam;
Movie mov;
PImage inputImage;
boolean inputMethodSelected = false;

boolean debugMode = false;
char[] rain = "abcdefghijklmnopqrstuvwxyz".toCharArray();//will have my poem or whatever
int[] xPos = new int[26];//will hold the x positions of all rain letters
int[] yPos = new int[26];//will hold all y positions of rain letters
int pos = 0;
float threshold = 80;//will hold value that text can't fall through

void setup() {
  size(1280, 720);  
  inputImage = createImage(width, height, RGB);
  PFont font;
  font = loadFont("JavaneseText-48.vlw");
  textFont(font,24); 
  for(int j = 0; j < xPos.length; j++){
    float r = random(15,width-15);
    float h = random(10,15);
    xPos[j] = int(r);
    yPos[j] = int(h);
  }
}

void draw() {
  // When the program first starts, draw a menu of different options for which camera to use for input
  // The input method is selected by pressing a key 0-9 on the keyboard
  if (!inputMethodSelected) {
    cameras = Capture.list();
    int y=40;
    text("O: Offline mode, test with TextRainInput.mov movie file instead of live camera feed.", 20, y);
    y += 40; 
    for (int i = 0; i < min(9,cameras.length); i++) {
      text(i+1 + ": " + cameras[i], 20, y);
      y += 40;
    }
    return;
  }

  // This part of the draw loop gets called after the input selection screen, during normal execution of the program.

  // STEP 1.  Load an image, either from a movie file or from a live camera feed. Store the result in the inputImage variable
  if ((cam != null) && (cam.available())) {
    cam.read();
    inputImage.copy(cam, 0,0,cam.width,cam.height, 0,0,inputImage.width,inputImage.height);
  }
  else if ((mov != null) && (mov.available())) {
    mov.read();
    inputImage.copy(mov, 0,0,mov.width,mov.height, 0,0,inputImage.width,inputImage.height);
  }
  
  // Fill in your code to implement the rest of TextRain here..
  int ms = millis();
  
  for(int i = 0; i <inputImage.pixels.length;i++){//goes through the image data and averages rgb to get grey value
    color c = inputImage.pixels[i];
    int g = int((red(c) + blue(c) + green(c))/3);
    if(debugMode){
      if(g<threshold){
       inputImage.pixels[i] = color(0,0,0); 
      }else{
       inputImage.pixels[i] = color(255,255,255); 
      }
    }else{
      inputImage.pixels[i] = color(g,g,g);
    }
    //inputImage.pixels[i] = color(g,g,g);
  }
  
 pushMatrix();
 //translate(inputImage.width,0);
 scale(-1,1);
 image(inputImage,-inputImage.width,0);

  // Tip: This code draws the current input image to the screen
  //set(0, 0, inputImage);
  //print(inputImage.pixels.length);
  
  popMatrix(); 
  //stroke(255,255,255);
  fill(0,0,0);
  //circle(width/2,pos,5);
  for(int i = 0; i < rain.length;i++){
    color a = inputImage.pixels[width-xPos[i]+yPos[i]*width];
    color p = inputImage.pixels[width-xPos[i]+(yPos[i])*width];
    float aVal = ((red(a) + blue(a) + green(a))/3);
    float pVal = ((red(p) + blue(p) + green(p))/3);
    if(aVal > threshold){
      if(yPos[i] + 3 >= height){
        xPos[i] = int(random(15,width-15));
        yPos[i]= 10;  
      }
      yPos[i] += 2; 
    }else if(aVal <= threshold){
      if(pVal <= threshold){
        yPos[i] = yPos[i] - 2; 
      }
      yPos[i] = yPos[i]; 
    }
    text(rain[i],xPos[i],yPos[i]); 
  }
  text("test text",width/2,pos);
  if(debugMode){
    text("Threshold: ",20,20);
    text(threshold,160,20);
  }
}

void keyPressed() {
  
  if (!inputMethodSelected) {
    // If we haven't yet selected the input method, then check for 0 to 9 keypresses to select from the input menu
    if ((key >= '0') && (key <= '9')) { 
      int input = key - '0';
      if (input == 0) {
        println("Offline mode selected.");
        mov = new Movie(this, "TextRainInput.mov");
        mov.loop();
        inputMethodSelected = true;
      }
      else if ((input >= 1) && (input <= 9)) {
        println("Camera " + input + " selected.");           
        // The camera can be initialized directly using an element from the array returned by list():
        cam = new Capture(this, cameras[input-1]);
        cam.start();
        inputMethodSelected = true;
      }
    }
    return;
  }

  // This part of the keyPressed routine gets called after the input selection screen during normal execution of the program
  // Fill in your code to handle keypresses here..
  
  if (key == CODED) {
    if (keyCode == UP) {
      if(threshold <255){
        threshold = threshold + 5;
      }
    }
    else if (keyCode == DOWN) {
      if(threshold >0){
        threshold = threshold - 5;
      }
    }
  }
  else if (key == ' ') {
    // space bar pressed
    debugMode = !debugMode;
  } 
  
}
