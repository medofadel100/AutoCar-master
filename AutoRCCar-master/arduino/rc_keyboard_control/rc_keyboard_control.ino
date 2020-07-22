

// motor Driver 1
int PWM1motor1=2;
int PWM2motor1=3;
int LPWMmotor1=22;
int RPWMmotor1=23;


// motor Driver 2
int PWM1motor2=4;
int PWM2motor2=5;
int LPWMmotor2=24;
int RPWMmotor2=25;


// motor Driver 3
int PWM1motor3=6;
int PWM2motor3=7;
int LPWMmotor3=26;
int RPWMmotor3=27;



// motor Driver 4
int PWM1motor4=8;
int PWM2motor4=9;
int LPWMmotor4=28;
int RPWMmotor4=29;

//UltraSonic pin
const int trigPinr = 22; // Trigger Pin Of Right Ultrasonic Sesnor
const int echoPinr = 23; // Echo Pin Of Right Ultrasonic Sesnor
const int trigPinl = 24; // Trigger Pin Of Lift Ultrasonic Sesnor
const int echoPinl = 25; // Echo Pin Of Lift Ultrasonic Sesnor
const int trigPinf1 = 26; // Trigger Pin Of Lift Front Ultrasonic Sesnor
const int echoPinf1 = 27; // Echo Pin Of Lift Front Ultrasonic Sesnor
const int trigPinf2 = 28; // Trigger Pin OfFr ont Ultrasonic Sesnor
const int echoPinf2 = 29; // Echo Pin Of Front Ultrasonic Sesnor
const int trigPinf3 = 30; // Trigger Pin Of Right Front Ultrasonic Sesnor
const int echoPinf3 = 31; // Echo Pin Of Right Right  Ultrasonic Sesnor
const int trigPinb1 = 32; // Trigger Pin Of Right Back Ultrasonic Sesnor
const int echoPinb1 = 34; // Echo Pin Of Right Back Ultrasonic Sesnor
const int trigPinb2 = 35; // Trigger Pin Of Back Ultrasonic Sesnor
const int echoPinb2 = 36; // Echo Pin Of Back Ultrasonic Sesnor
const int trigPinb3 = 37; // Trigger Pin Of Lift Back Ultrasonic Sesnor
const int echoPinb3 = 38; // Echo Pin Of Lift Back Ultrasonic Sesnor

//UltraSonic variables
long durationr; // variables to Calculate the distance
float distancer;
long durationl; // variables to Calculate the distance
float distancel;
long durationf1; // variables to Calculate the distance
float distancef1;
long durationf2; // variables to Calculate the distance
float distancef2;
long durationf3; // variables to Calculate the distance
float distancef3;
long durationb1; // variables to Calculate the distance
float distanceb1;
long durationb2; // variables to Calculate the distance
float distanceb2;
long durationb3; // variables to Calculate the distance
float distanceb3;



void setup()
{
 Serial.begin(9600);

 pinMode(trigPinr, OUTPUT);
 pinMode(echoPinr, INPUT);
 pinMode(trigPinl, OUTPUT);
 pinMode(echoPinl, INPUT);
 pinMode(trigPinf1, OUTPUT);
 pinMode(echoPinf1, INPUT);
 pinMode(trigPinf2, OUTPUT);
 pinMode(echoPinf2, INPUT);
 pinMode(trigPinf3, OUTPUT);
 pinMode(echoPinf3, INPUT);
 pinMode(trigPinb1, OUTPUT);
 pinMode(echoPinb1, INPUT);
 pinMode(trigPinb2, OUTPUT);
 pinMode(echoPinb2, INPUT);
 pinMode(trigPinb3, OUTPUT);
 pinMode(echoPinb3, INPUT);

 pinMode(PWM1motor1, OUTPUT);
 pinMode(PWM2motor1, OUTPUT);
 pinMode(LPWMmotor1, OUTPUT);
 pinMode(RPWMmotor1, OUTPUT);

 pinMode(PWM1motor2, OUTPUT);
 pinMode(PWM2motor2, OUTPUT);
 pinMode(LPWMmotor2, OUTPUT);
 pinMode(RPWMmotor2, OUTPUT);

 pinMode(PWM1motor3, OUTPUT);
 pinMode(PWM2motor3, OUTPUT);
 pinMode(LPWMmotor3, OUTPUT);
 pinMode(RPWMmotor3, OUTPUT);

 pinMode(PWM1motor4, OUTPUT);
 pinMode(PWM2motor4, OUTPUT);
 pinMode(LPWMmotor4, OUTPUT);
 pinMode(RPWMmotor4, OUTPUT);


 
 pinMode(10, OUTPUT);
 pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
}
void loop()
{
 ultrar();
 ultraf();
 ultral();

  if( distancef<20 ) // Sharp Back Turn if the distance is less than 50cm
 {
 
 Serial.println("Stop");
 STOP();
 delay(500);
 Serial.println("back"); 
  BACK();
 
 delay(3000);
Serial.println("LEFT"); 
 LEFT();

 delay(2000);
 }


else if(distancef>50) // Move Forward if distance is greater than 65cm
 {
  
 Serial.println("Forward");
  FORWORD();
  
  
 }
 
 else if(distancef<50) // Move back and turn if distance is less than 60cm
 {
 Serial.println("Object Detect");

   if( distancel<30  ) // Sharp Right Turn if the distance is less than 50cm
     {
     
     Serial.println("Right");
      RIGHT();
      delay(1000);
      
     }

   else if(  distancer<30) // Sharp Left Turn if the distance is less than 50cm
     {
     
     Serial.println("left");
      LEFT();
      delay(1000);
      
     }
    else
    {
      RIGHT();
      delay(1000);
    }
 
 }
 

 else if( distancel<20 && distancef<20 && distancer<20) // Sharp Back Turn if the distance is less than 50cm
 {
 
 Serial.println("Stop");
 STOP();
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
 delay(500);
 Serial.println("back"); 
  BACK();
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);
 delay(2000);
Serial.println("Right"); 
 RIGHT();
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
 delay(1500);
 }

}


void ultrar()
{
 digitalWrite(trigPinr, LOW); // Sending and Detecting the Ultrasonic Signal
 delayMicroseconds(2);
 digitalWrite(trigPinr, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinr, LOW);
 durationr = pulseIn(echoPinr, HIGH); // Calulating the timme taken by the ultrasonic wave to reflect back
 distancer = 0.034*(durationr/2); // Calulating the distance betweek thee robbot and the obstacle.
}
void ultraf()
{
 digitalWrite(trigPinf, LOW); // Sending and Detecting the Ultrasonic Signal
 delayMicroseconds(2);
digitalWrite(trigPinf, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinf, LOW);
 durationf = pulseIn(echoPinf, HIGH); // Calulating the timme taken by the ultrasonic wave to reflectback
 distancef = 0.034*(durationf/2); // Calulating the distance betweek thee robbot and the obstacle.
}
void ultral()
{
 digitalWrite(trigPinl, LOW); // Sending and Detecting the Ultrasonic Signal
 delayMicroseconds(2);
 digitalWrite(trigPinl, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPinl, LOW);
 durationl = pulseIn(echoPinl, HIGH); // Calulating the timme taken by the ultrasonic wave to reflect back
 distancel = 0.034*(durationl/2); // Calulating the distance betweek thee robbot and the obstacle.
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

   analogWrite(PWM1motor3, 200);
   analogWrite(PWM2motor3, 200);
   digitalWrite(LPWMmotor3, HIGH);
   digitalWrite(RPWMmotor3, LOW);

   analogWrite(PWM1motor4, 200);
   analogWrite(PWM2motor4, 200);
   digitalWrite(LPWMmotor4, HIGH);
   digitalWrite(RPWMmotor4, LOW);
 
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

   analogWrite(PWM1motor3, 200);
   analogWrite(PWM2motor3, 200);
   digitalWrite(LPWMmotor3, LOW);
   digitalWrite(RPWMmotor3, HIGH);

   analogWrite(PWM1motor4, 200);
   analogWrite(PWM2motor4, 200);
   digitalWrite(LPWMmotor4, LOW);
   digitalWrite(RPWMmotor4, HIGH);
 
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

   analogWrite(PWM1motor3, 200);
   analogWrite(PWM2motor3, 200);
   digitalWrite(LPWMmotor3, HIGH);
   digitalWrite(RPWMmotor3, LOW);

   analogWrite(PWM1motor4, 0);
   analogWrite(PWM2motor4, 0);
   digitalWrite(LPWMmotor4, LOW);
   digitalWrite(RPWMmotor4, LOW);
 
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

   analogWrite(PWM1motor3, 0);
   analogWrite(PWM2motor3, 0);
   digitalWrite(LPWMmotor3, LOW);
   digitalWrite(RPWMmotor3, LOW);

   analogWrite(PWM1motor4, 200);
   analogWrite(PWM2motor4, 200);
   digitalWrite(LPWMmotor4, HIGH);
   digitalWrite(RPWMmotor4, LOW);
 
}

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

   analogWrite(PWM1motor3, 0);
   analogWrite(PWM2motor3, 0);
   digitalWrite(LPWMmotor3, LOW);
   digitalWrite(RPWMmotor3, LOW);

   analogWrite(PWM1motor4, 0);
   analogWrite(PWM2motor4, 0);
   digitalWrite(LPWMmotor4, LOW);
   digitalWrite(RPWMmotor4, LOW);
   
}