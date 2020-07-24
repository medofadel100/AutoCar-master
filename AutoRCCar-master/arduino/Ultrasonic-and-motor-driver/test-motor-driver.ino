int x;

int IN1=2;            //D0 input 1 for motor 1  
int IN2=3 ;           //D1  input 2 for motor 1
int IN3=4;           //D2   input 1 for motor 2
int IN4=5;          //D3    input 2 for motor 2

void setup ()
{
     Serial.begin(9600);

     pinMode(IN1, OUTPUT);
     pinMode(IN2, OUTPUT);
     pinMode(IN3, OUTPUT);
     pinMode(IN4, OUTPUT);
} 

void loop()
{
    x = Serial.read();
    if (Serial.available() > 0) 
    {
     if (x==8)
     {
        forward () ;
     }

     if (x==6)
     {
        right() ;
     }

     if (x==4)
     {
        left() ;
     }

     if (x==8)
     {
        back() ;
     }

     if (x==0)
     {
        stoop() ;
     }
        

    }


}

void forward ()
{
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,HIGH);
  digitalWrite (IN4,LOW);

  
}

  //robot Move Right function
  void right()
{
  digitalWrite (IN1,HIGH);
  digitalWrite (IN2,LOW);
  digitalWrite (IN3,LOW);
  digitalWrite (IN4,LOW);
  
}

  //robot Move Left function
  void left()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
  
}

  //robot move back function
  void back()
{ 
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
}

  //robot Stop function
  void stoop()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  
  
}
