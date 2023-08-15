
//car control default
//arrow up    1 forward      select 5 = stop
//arrow down  2 backward     X      6  = hard right
//arrow right 3 right        box    7 = hard left
//arrow left  4 left        start   8 = swtich from car to claw

//claw control
//arrow up    1 forward     select 5 = stop
//arrow down  2 backward    X      6  = right claw
//arrow right 3 right       box    7 = left claw
//arrow left  4 left        start  8 = swtich from claw to car
//                          circle 9 = middle claw
#include <Servo.h>
//#######################################################################
char t;
char ctrl;
char cl;

//const int check = 1;
int motor1pin1 =10; //right motor forward
int motor1pin2 =11; //right motor backward

int motor2pin1 =12; //left motor forward
int motor2pin2 =13; //left motor backward

//#######################################################################

int anglestep = 10;

int angleC =25;
int minangleC = 0;
int maxangleC =25;

Servo myservo;

//#######################################################################
//status
int carled;
int craneled;
int controlled;
//servo
int middleled;
int rightled;
int leftled;
int clawled;


//#######################################################################

void setup() {
  // put your setup code here, to run once:
  
pinMode(motor1pin1,OUTPUT);
pinMode(motor1pin2,OUTPUT);
pinMode(motor2pin1,OUTPUT);
pinMode(motor2pin2,OUTPUT);

myservo.attach(3);
Serial.begin(9600);
}
void loop(){
       myservo.write(90);
       Serial.println("welcome to car");
  if(Serial.available())
  {
    t =  Serial.read();
        Serial.println(t);}

   
   // change control
  if (t == '8')
  {
    
    Serial.println("JEDCONTROL");
    t = 'Z';
    control();
  }
  
 if (t == '5')
  {
    //STOP
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,LOW);
    
  }
  
  
 //car bluetooth
 if (t == '1') 
  {
    //forward
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin2,LOW);
   
  }

 if (t == '2')
  {
    //backward
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(motor2pin2,HIGH);
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor2pin1,LOW);
 
    
  }
  
  if (t == '3')
  {
    //turn right
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor2pin2,LOW);

  }

 if (t == '4')
  {
    //turn left
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,LOW);
 
  }

  
  if (t == '6')
  {
    //HARD RIGHT
    digitalWrite(motor1pin1,LOW);
    digitalWrite(motor1pin2,HIGH);
    digitalWrite(motor2pin1,HIGH);
    digitalWrite(motor2pin2,LOW);
    
  }
  
 if (t == '7')
  {
    //HARD LEFT
    digitalWrite(motor1pin1,HIGH);
    digitalWrite(motor1pin2,LOW);
    digitalWrite(motor2pin1,LOW);
    digitalWrite(motor2pin2,HIGH);
    
  }
 
   }


void control(){
  int checkk = 1;
   while(checkk==1) {
       if(Serial.available())
        {
          ctrl =  Serial.read();
          Serial.println(ctrl);
        }
        
         if (ctrl == '0')
        {
          Serial.println("controlling claw");
        }
        
        if (ctrl == '9')
        {
          Serial.println("controlling middle");
          middle();
        }
        
          checkk = 1;
    
        if (ctrl == '8')
        {
        checkk = 0;
        }ctrl = 'Z'; 
    }

}
void middle(){
  int minangle = 20;
  int maxangle = 160;
  int check = 1;
  int angle = 90;
        //middle   
       while(check == 1){
              if(Serial.available())
              {   cl = Serial.read();
                  Serial.println(cl);
               }
               
              if (cl == '3' && angle <= maxangle && angle > minangle )
              {     angle = angle - anglestep;
                   myservo.write(angle);
              }

               if (cl =='4' && angle < maxangle && angle >= minangle )
              { angle = angle + anglestep;
                myservo.write(angle);
              }

              check = 1;    
               if (cl == '8')
              {   Serial.println("claw to car");
                  ctrl = '8';
                  check = 0;
              }      

                if (cl =='5')
              {  
                check = 0;
              }
              
               if (cl == '6' || cl == '7' || cl == '9' || cl == '0')
               {  Serial.println("change claw");
                  ctrl = cl;
                  check = 0;
               }  cl = 'Z';  
        }
  }
