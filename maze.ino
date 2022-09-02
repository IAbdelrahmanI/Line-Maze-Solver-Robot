#include "robotDefines.h"




//---------------------------------------------
void setup() 
{
  
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // line follow sensors
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(Front, INPUT);

  pinMode(BUTTON_F, INPUT_PULLUP);
  pinMode(BUTTON_R, INPUT_PULLUP);
  
  checkPIDvalues();
  mode = STOPPED;
  status = 0; // 1st pass
}

void loop() 
{
  ledBlink(1);
  
  readLFSsensors(); 
  previousForward = forwardButton;
  previousReverse= reverseButton;
  forwardButton = digitalRead(BUTTON_F);
  delay(25);
  reverseButton = digitalRead(BUTTIN_R);
  delay(25);

  
  if (forwardButton && !previousForward)
  solveState = !solveState;
  
  if (solveState)
  {mazeSolve();mazeSolved = 1;} // First pass to solve the maze
  ledBlink(2);
  Serial.println("End First Pass"); 
  
  
  Serial.println("Starting 2nd Pass"); 
  pathIndex = 0;
  status = 0;
  if (!solveState && mazeSolved)
  mazeOptimization(); //run the maze as fast as possible
  ledBlink(3);
  Serial.println("End 2nd Pass"); 

  if (reverseButton && !previousReverse)
  reverseState = !reverseState;

  if (reverseState && mazeSolved)
  mazeOptimizationReversed();
  
  mode = STOPPED;
  status = 0; // 1st pass
  pathIndex = 0;
  pathLength = 0;
}
