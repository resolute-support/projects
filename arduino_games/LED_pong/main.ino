#include <Arduino.h>
// setup of the global variables 
int gameSpeed = 250; //lower is faster
int currentPin = 100;
bool start = false;
bool leftBounceBack = true;
bool rightBounceBack = true;
// int gameCounter = 0;
 
void setup() {
 // put your setup code here, to run once:
 Serial.begin(9600);
 // setting up output pins
 for (int i = 6; i < 14; i++)
 {
   pinMode(i,OUTPUT);
 }
 // setting up input pins
 pinMode(2,INPUT);
 pinMode(3,INPUT);
}
 
// this function makes sure that the players presses the button only on pin 13 or 7 to see if a shot can be returned. as well as adds a delay between LED flashes.
void delayCheck()
{
 int initualState2 = digitalRead(2);
 int initualState3 = digitalRead(3);
 bool allowRightBounceBack = false;
 bool allowLeftBounceBack = false;
 bool bounced = false;
 for (int i = 0; i <= gameSpeed; i++)
 {
   /* code */
   int currentState2 = digitalRead(2);
   int currentState3 = digitalRead(3);
   if(initualState2 != currentState2)
   {
     allowRightBounceBack = true;
   }
   if(initualState3 != currentState3)
   {
     allowLeftBounceBack = true;
   }
   if(allowLeftBounceBack == true or allowRightBounceBack == true)
   {
     rightBounceBack=false;
     leftBounceBack=false;
     if(currentPin == 13)
     {
       delay(1);
       rightBounceBack = true;
       leftBounceBack = false;
       bounced = true;
       i = gameSpeed+1;
     }
     if(currentPin == 7)
     {
       delay(1);
       leftBounceBack = true;
       rightBounceBack = false;
       bounced = true;
       i = gameSpeed+1;
     }
   }
   delay(1);
  
 }
 if(currentPin == 13 and bounced == false)
 {
   Serial.println("yes1");
   currentPin = 100;
   start = false;
 }
 if(currentPin == 7 and bounced == false)// and gameCounter != 1)
 {
   Serial.println("yes2");
   currentPin = 100;
   start = false;
 }
}
 
// cycles thru the LEDs in the direction the of the player the return shot
void ledCycle(int i)
{
 currentPin = i;
 digitalWrite(i, HIGH);
 delayCheck();
 digitalWrite(i,LOW);
}
// this is the mane loop that makes sure the game has started and that a new game can start. and that if the game has ended the game can start again.
void loop() {
 // put your main code here, to run repeatedly:
 if(digitalRead(2) == HIGH and digitalRead(3) == HIGH and start == false)
 {
  //  gameCounter=0;
   Serial.println("yes");
   rightBounceBack = true;
   leftBounceBack = true;
   start = true;
   delay(30);
   for (int i = 13; i >= 7; i--)
   {
     /* code */
     digitalWrite(i,HIGH);
   }
   delay(500);
   for (int i = 7; i < 14; i++)
   {
     /* code */
     digitalWrite(i,LOW);
   }
 }
 // if the game has started then this loop will make the game continue until someone has lost.
 if(start == true)
 {
  //  gameCounter++;
   if(leftBounceBack == true)
   {
     rightBounceBack = false;
     leftBounceBack = false;
     for (int i = 8; i < 14; i++)
     {
       /* code */
       ledCycle(i);
     }
   }     
   else if(rightBounceBack == true)
   {
     leftBounceBack = false;
     rightBounceBack = false;
     for (int i = 12; i > 6; i--)
     {
       /* code */
       ledCycle(i);
     }
   }
 }
}
