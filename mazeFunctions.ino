void mazeSolve(void)
{
    while (!status)
    {
        readLFSsensors();  
        switch (mode)
        {   
          case NO_LINE:  
            Stop();
            Reverse();
            recIntersection('B');
            break;
          
          case CONT_LINE: 
            runExtraInch();
            readLFSsensors();
            if (mode == FOLLOWING_LINE) {GoRight(); recIntersection('R');} 
            else if (mode == NO_LINE || mode == CONT_LINE) mazeEnd(); 
            break;
            
         case RIGHT_TURN: 
            GoRight();
            recIntersection('R');
            break;   
            
         case LEFT_TURN: 
            GoLeft(); 
            recIntersection('L');
            break;
   
         case T_INTERSECTION:
            GoRight();
            recIntersection('R');
            break;

         case RIGHT_T_INTERSECTION:
            GoRight();
            recIntersection('R');
            break;

         case LEFT_T_INTERSECTION:
            Forward();
            recIntersection('S');
            break;
                  
         case FOLLOWING_LINE: 
            Forward();
            break;      
        
         }
    }
    status = 0;
    pathIndex = 0;
    optimizing = 1;
}

//---------------------------------------------
void recIntersection(char direction)
{
  path[pathLength] = direction; // Store the intersection in the path variable.
  pathLength ++;
  simplifyPath(); // Simplify the learned path.
}

//----------------------------------------------
void mazeEnd(void)
{
  Stop();
  for(int i=0;i<pathLength;i++)
  
    Serial.print(path[i]);
 
  Serial.print("  pathLenght ==> ");
  Serial.println(pathLength);
  status = 1;
  mode = STOPPED;
  pathIndex = 0;
}

//------------------------------------------------------------------------------------------
// Path simplification.  The strategy is that whenever we encounter a
// sequence xBx, we can simplify it by cutting out the dead end.  For
// example, LBL -> S, because a single S bypasses the dead end
// represented by LBL.
void simplifyPath()
{
  // only simplify the path if the second-to-last turn was a 'B'
  if(pathLength < 3 || path[pathLength-2] != 'B')
    return;

  int totalAngle = 0;
  int i;
  for(i=1;i<=3;i++)
  {
    switch(path[pathLength-i])
    {
      case 'R':
        totalAngle += 90;
  break;
      case 'L':
  totalAngle += 270;
  break;
      case 'B':
  totalAngle += 180;
  break;
    }
  }

  // Get the angle as a number between 0 and 360 degrees.
  totalAngle = totalAngle % 360;

  // Replace all of those turns with a single one.
  switch(totalAngle)
  {
    case 0:
  path[pathLength - 3] = 'S';
  break;
    case 90:
  path[pathLength - 3] = 'R';
  break;
    case 180:
  path[pathLength - 3] = 'B';
  break;
    case 270:
  path[pathLength - 3] = 'L';
  break;
  }

  // The path is now two steps shorter.
  pathLength -= 2;
  
} 

//----------------------------------------------------------------------------------------------
void mazeOptimization (void)
{
  while (!status)
  {
    readLFSsensors();  
    switch (mode)
    {
      case FOLLOWING_LINE:
        Forward;
        break;    
      case CONT_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case LEFT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;
      case T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case LEFT_T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;
      case NO_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (path[pathIndex]); pathIndex++;}
        break;       
    }    
   }  
   status = 0;
   pathIndex = 0;
   allRunsDone++;
   optimizing = 0;
}

//-----------------------------------------------------
void mazeTurn (char dir) 
{
  switch(dir)
  {
    case 'L': // Turn Left
       GoLeft;      
       break;   
    
    case 'R': // Turn Right
       GoRight;     
       break;   
       
    case 'B': // Turn Back
       Reverse;     
       break;   
       
    case 'S': // Go Straight
       runExtraInch(); 
       break;
  }
}
//-----------------------------------------------------
void mazeReverse()
{
  for (int i = 0; i <= pathLength; i++)
  {
    reversedPath[i] = path[pathLength-i];
  }
  for (int i = 0; i <= pathLength; i++)
  {
    if (reversedPath[i] == 'R')
    reversedPath[i] = 'L';
    else if (reversedPath[i] == 'L')
    reversedPath[i] = 'R';
  }
}
//-----------------------------------------------------
void mazeOptimizationReversed (void)
{
  while (!status)
  {
    readLFSsensors();  
    switch (mode)
    {
      case FOLLOWING_LINE:
        Forward;
        break;    
      case CONT_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;  
      case LEFT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_TURN:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;
      case T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;  
      case LEFT_T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;  
      case RIGHT_T_INTERSECTION:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;
      case NO_LINE:
        if (pathIndex >= pathLength) mazeEnd (); 
        else {mazeTurn (reversedPath[pathIndex]); pathIndex++;}
        break;       
    }    
   }  
   status = 0;
   pathIndex = 0;
   allRunsDone++;
   reverseFinished = 1;
}
//-----------------------------------------------------

void setUpMazeSolver(void)
{
  pathLength = 0;
  mazeSolved = 0;
  allRunsDone = -1;
  reverseState = 0;
  optimizing = 0;
  solveState = 0;
  reverseFinished = 0;
}
//-----------------------------------------------------
