

// motor Driver 1
int PWM1motor1 = 2;
int PWM2motor1 = 3;
int LPWMmotor1 = 4;
int RPWMmotor1 = 5;

// motor Driver 2
int PWM1motor2 = 6;
int PWM2motor2 = 7;
int LPWMmotor2 = 8;
int RPWMmotor2 = 8;





void setup()
{


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
    FORWORD();
    delay(2000);
    BACK();
    delay(2000);
    RIGHT();
    delay(2000);
    LEFT();
    delay(2000);
    STOP();
    delay(2000);

}



void FORWORD()
{

  analogWrite(PWM1motor1, 100);
  analogWrite(PWM2motor1, 100);
  digitalWrite(LPWMmotor1, HIGH);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 100);
  analogWrite(PWM2motor2, 100);
  digitalWrite(LPWMmotor2, HIGH);
  digitalWrite(RPWMmotor2, LOW);


}

void BACK()
{

  analogWrite(PWM1motor1, 200);
  analogWrite(PWM2motor1, 200);
  digitalWrite(LPWMmotor1, LOW);
  digitalWrite(RPWMmotor1, HIGH);

  analogWrite(PWM1motor2, 200);
  analogWrite(PWM2motor2, 200);
  digitalWrite(LPWMmotor2, LOW);
  digitalWrite(RPWMmotor2, HIGH);

  
}

void RIGHT()
{

  analogWrite(PWM1motor1, 200);
  analogWrite(PWM2motor1, 200);
  digitalWrite(LPWMmotor1, HIGH);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 0);
  analogWrite(PWM2motor2, 0);
  digitalWrite(LPWMmotor2, LOW);
  digitalWrite(RPWMmotor2, LOW);


}

void LEFT()
{

  analogWrite(PWM1motor1, 0);
  analogWrite(PWM2motor1, 0);
  digitalWrite(LPWMmotor1, LOW);
  digitalWrite(RPWMmotor1, LOW);

  analogWrite(PWM1motor2, 200);
  analogWrite(PWM2motor2, 200);
  digitalWrite(LPWMmotor2, HIGH);
  digitalWrite(RPWMmotor2, LOW);



void STOP()
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