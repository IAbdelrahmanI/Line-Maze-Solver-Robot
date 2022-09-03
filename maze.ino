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

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
//  checkPIDvalues();
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
  reverseButton = digitalRead(BUTTON_R);
  delay(25);

  
  if (forwardButton && !previousForward)
  solveState = !solveState;
  
  if (solveState && !mazeSolved)
  {mazeSolve();mazeSolved = 1;ledBlink(2); Serial.println("End First Pass"); } // First pass to solve the maze
  
  
  
  
  if (!solveState && mazeSolved && optimizing)
  {Serial.println("Starting 2nd Pass"); mazeOptimization(); //run the maze as fast as possible
  ledBlink(3);
  Serial.println("End 2nd Pass"); }

  if (reverseButton && !previousReverse)
  reverseState = !reverseState;

  if (reverseState && mazeSolved && !reverseFinished)
  mazeOptimizationReversed();
  
  mode = STOPPED;
  if (allRunsDone == 1)
  setUpMazeSolver();
}
