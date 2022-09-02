
void Stop()
{
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

//--------------------------------------------- 
void Forward()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);
}

//---------------------------------------------
void Reverse()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);

  delay(500); //We will test the delay for 180 degree turn
}
//------------------------------------------------
void runExtraInch(void)
{
  Forward();
  delay(extraInch);
  Stop();
}
//---------------------------------------------------
void GoRight()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 100);
  
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 100);

  delay(500); //We will test the delay for 90 degree turn

  Forward();
}
//---------------------------------------------------
void GoLeft()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);
  
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100);

  delay(500); //We will test the delay for 90 degree turn

  Forward();
}
//---------------------------------------------------
