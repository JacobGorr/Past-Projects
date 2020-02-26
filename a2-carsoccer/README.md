# My solution to Assignment 2

Jacob Gorr

Design Descions 

I edited the ball.h reset function to randomly assign values

In car.h I added a speed member variable and set the starting angle to be -pi/2 to help align my car

In the joystick direction i made the left and right key presses change the direction the car is facing,
and have up and down act as the accelerator, with a min and max speed.
The joystick direction function is called to detect these key presses.

The major of my changes are in the update simulation.

I change the car's member variables first and check to make sure it doesnt leave the play bounds

After this i check for if the car is hitting the ball, and update the ball's values accordingly.
Lastly I check to see if the ball is bounds and change its velocity accordingly.

Most of my scaler values are selected by trail and error based on the feel.
