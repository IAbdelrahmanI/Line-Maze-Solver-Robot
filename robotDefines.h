int mode = 0;

# define STOPPED 0
# define FOLLOWING_LINE 1
# define NO_LINE 2
# define CONT_LINE 3
# define RIGHT_TURN 5
# define LEFT_TURN 6
# define T_INTERSECTION 7
# define LEFT_T_INTERSECTION 8
# define RIGHT_T_INTERSECTION 9
# define BUTTON_F 10
# define BUTTON_R 11
# define IN1 13
# define IN2 14
# define IN3 15
# define IN4 16
# define ENA 17
# define ENB 18

bool forwardButton = 0;
bool reverseButton = 0;
bool previousForward = forwardButton;
bool previousReverse= reverseButton;
bool solveState = 0;
bool reverseState = 0;
bool mazeSolved = 0;
bool optimizing = 0;
bool reverseFinished = 0;

const int power = 250;
const int iniMotorPower = 250;
const int adj = 0;
float adjTurn = 8;
int extraInch = 200;
int adjGoAndTurn = 800;

const int ledPin = 13;
const int buttonPin = 9;

// LFSensor
const byte Front = 10;
const byte Right = 11;
const byte Left = 12;


bool front = 0;
bool right = 0;
bool left = 0;



// PID controller
float Kp=50;
float Ki=0;
float Kd=0;

float error=0, P=0, I=0, D=0, PIDvalue=0;
float previousError=0, previousI=0;

//-------------------------------------------------
//Specific Maze Phase 2 (optimization) definitions and variables 

unsigned char dir; 

// The path variable will store the path that the robot has taken:
//  'L' for left
//  'R' for right
//  'S' for straight (going straight through an intersection)
//  'B' for back (U-turn)

char path[100] = "";
char reversedPath[100] = "";
unsigned int pathLength = 0; // the length of the path
int pathIndex = 0;
bool status = 0; // solving = 0; reach end = 1
short allRunsDone = -1;
