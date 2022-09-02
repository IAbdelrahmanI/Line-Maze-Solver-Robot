
void readLFSsensors()
{
  front = digitalRead(Front);
  right = digitalRead(Right);
  left = digitalRead(Left);

  
  if      (left == 1 && front == 1 && right == 1)  mode = CONT_LINE;
  else if (left == 0 && front == 0 && right == 1)  mode = RIGHT_TURN;
  else if (left == 1 && front == 0 && right == 0)  mode = LEFT_TURN;
  else if (left == 0 && front == 0 && right == 0)  mode = NO_LINE;
  else if (left == 0 && front == 1 && right == 0)  mode = FOLLOWING_LINE;
  else if (left == 1 && front == 0 && right == 1)  mode = T_INTERSECTION;
  else if (left == 0 && front == 1 && right == 1)  mode = RIGHT_T_INTERSECTION;
  else if (left == 1 && front == 1 && right == 0)  mode = LEFT_T_INTERSECTION;
  

    
}
