

int x = 0;
int PWM1motor1 = 2;
int PWM2motor1 = 3;
int LPWMmotor1 = 4;
int RPWMmotor1 = 5;

int PWM1motor2 = 6;
int PWM2motor2 = 7;
int LPWMmotor2 = 8;
int RPWMmotor2 = 9;

void setup ()
{
     Serial.begin(9600);

     pinMode(PWM1motor1, OUTPUT);
  pinMode(PWM2motor1, OUTPUT);
  pinMode(LPWMmotor1, OUTPUT);
  pinMode(RPWMmotor1, OUTPUT);
     
     pinMode(PWM1motor2, OUTPUT);
  pinMode(PWM2motor2, OUTPUT);
  pinMode(LPWMmotor2, OUTPUT);
  pinMode(RPWMmotor2, OUTPUT);
} 

void loop()
{
   
    if (Serial.available() > 0) 
    {
      x = Serial.read();
      Serial.println(x);
     if (x==8)
     {
        forward () ;
        
     }

     if (x==4)
     {
        right() ;
        
     }

     if (x==6)
     {
        left() ;
        
     }

     if (x==2)
     {
        back() ;
        
     }

     if (x==0)
     {
        stoop() ;
        
     }
        

    }


}

void forward()
{

  analogWrite(PWM1motor1, 50);
  analogWrite(PWM2motor1, 50);
  digitalWrite(LPWMmotor1, HIGH);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 50);
  analogWrite(PWM2motor2, 50);
  digitalWrite(LPWMmotor2, HIGH);
  digitalWrite(RPWMmotor2, LOW);


}

void back()
{

  analogWrite(PWM1motor1, 50);
  analogWrite(PWM2motor1, 50);
  digitalWrite(LPWMmotor1, LOW);
  digitalWrite(RPWMmotor1, HIGH);

  analogWrite(PWM1motor2, 50);
  analogWrite(PWM2motor2, 50);
  digitalWrite(LPWMmotor2, LOW);
  digitalWrite(RPWMmotor2, HIGH);

  
}

void right()
{

  analogWrite(PWM1motor1, 50);
  analogWrite(PWM2motor1, 50);
  digitalWrite(LPWMmotor1, HIGH);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 0);
  analogWrite(PWM2motor2, 0);
  digitalWrite(LPWMmotor2, LOW);
  digitalWrite(RPWMmotor2, LOW);


}

void left()
{

  analogWrite(PWM1motor1, 0);
  analogWrite(PWM2motor1, 0);
  digitalWrite(LPWMmotor1, LOW);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 50);
  analogWrite(PWM2motor2, 50);
  digitalWrite(LPWMmotor2, HIGH);
  digitalWrite(RPWMmotor2, LOW);


}
void stoop()
{

  analogWrite(PWM1motor1, 0);
  analogWrite(PWM2motor1, 0);
  digitalWrite(LPWMmotor1, LOW);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 0);
  analogWrite(PWM2motor2, 0);
  digitalWrite(LPWMmotor2, LOW);
  digitalWrite(RPWMmotor2, LOW);


}