#include <Servo.h>

Servo myservo;

int count =0;
int pos;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  
  pinMode(3, OUTPUT); // Blue LED
  pinMode(5, OUTPUT); // Green LED
  pinMode(6, OUTPUT); // Red LED
  
  pinMode(2, OUTPUT); // Relay turn on the fan
  Serial.begin(9600);

  myservo.attach(9);  // door
  
  pinMode(10, INPUT); // outside 
  pinMode(12, INPUT); // inside

  pinMode(13, OUTPUT);// Testing reed switch
  
  pinMode(11, OUTPUT);// Buzzer

  myservo.write(180);
  pos=180;
}

// the loop function runs over and over again forever
void loop() {

  // -----------------Temp control code---------------------
  int tempSensor = analogRead(A0);
  //Serial.println(tempSensor);

  if(tempSensor<550){
    digitalWrite(2, HIGH);
  }
  else{
    digitalWrite(2, LOW);
  }
  //--------------------------------------------------------


  //+++++++++++++++++++++++++++++RGB Code+++++++++++++++++++
  if(count<10){
    digitalWrite(3, HIGH); // Blue LED
    digitalWrite(5, LOW);  // Green LED
    digitalWrite(6, LOW);  // Red LED
  }
  else if(count <20){
    digitalWrite(3, LOW); // Blue LED
    digitalWrite(5, HIGH);  // Green LED
    digitalWrite(6, LOW);  // Red LED
  }
  else if(count <30){
    digitalWrite(3, LOW); // Blue LED
    digitalWrite(5, LOW);  // Green LED
    digitalWrite(6, HIGH);  // Red LED
  }
  else if(count <40){
    digitalWrite(3, HIGH); // Blue LED
    digitalWrite(5, LOW);  // Green LED
    digitalWrite(6, HIGH);  // Red LED
  }
  else if(count< 50){
    count = 0;
  }

  count ++;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //#################Open Garage door######################

  
  if(digitalRead(10) && digitalRead(12)){// nothing outside and nothing inside = close door
    delay(200);
    if(digitalRead(10) && digitalRead(12))
    {
      goTo(180);
    }
   }
  else if(!digitalRead(10) && digitalRead(12)){// something outside and nothing inside = open door
    goTo(100);
  }
  else if(!digitalRead(10) && !digitalRead(12)){// something outside and something inside = open door
    goTo(100);
  }
  else if(digitalRead(10) && !digitalRead(12)){// nothing outside and something inside = open door
    goTo(100);
  }
  //#######################################################

  //&&&&&&&&&&&&&&&&&&&&&Security Systems&&&&&&&&&&&&&&&&&&
  if(digitalRead(7) == true){//door is open
    digitalWrite(13, LOW);
    tone(11,500 + count*10);
  }
  else{//door is closed
    digitalWrite(13, HIGH);
    noTone(11);
  }
  //&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
  
  delay(100);                       // wait for a second
  
}


void goTo(int state){ //open 100 degrees; close 180 degrees
  if(pos<state){
    while(pos<state){
      pos++;
      myservo.write(pos);
      delay(15);
    }
  }
  else{
    while(pos>state){
      pos--;
      myservo.write(pos);
      delay(15);
    }
  }

  Serial.print("inside: ");
  Serial.print(digitalRead(10));
  Serial.print("  outside: ");
  Serial.print(digitalRead(12));
  Serial.print("  heat: ");
  Serial.print(analogRead(A0));
  Serial.print("  alarm: ");
  Serial.println(digitalRead(7));
  
}
