/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 6

int power = 150;

int trigPin = 2;    // TRIG pin
int echoPin = 3;    // ECHO pin

float duration_us;
float distance_cm;
char data;

// We wish you a merry Christmas

int wish_melody[] = {
  NOTE_B3,
  NOTE_F4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4,
  NOTE_D4, NOTE_D4, NOTE_D4,
  NOTE_G4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_F4,
  NOTE_E4, NOTE_E4, NOTE_E4,
  NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4,
  NOTE_F4, NOTE_D4, NOTE_B3, NOTE_B3,
  NOTE_D4, NOTE_G4, NOTE_E4,
  NOTE_F4
};

int wish_tempo[] = {
  4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 4,
  4, 8, 8, 8, 8,
  4, 4, 8, 8,
  4, 4, 4,
  2
};

void setup()
{

  Serial.begin(9600);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop()
{
  check_bluetooth();
  //ultrasonic();
  //line();
}

void check_bluetooth()
{
  if (Serial.available() > 0 )
  {
    data = Serial.read();
    Serial.println(data);
  }
  if (data == 'F')
  {
    straight();
  }
  else if (data == 'S')
  {
    still();
  }
  else if (data == 'R')
  {
    Right();
  }
  else if (data == 'L')
  {
    Left();
  }
  else if (data == 'X')
  {
    line();
  }
  else if (data == 'U')
  {
    ultrasonic();
  }
  else if (data == 'B')
  {
    back();
  }
  else if (data == '0')
  {
    noTone(6);
    noTone(7);
  }
  else if (data == '1')
  {
    tone(6, 31);
    tone(7, 31);
  }
  else if (data == '2')
  {
    tone(6, 41);
    tone(7, 41);
  }
  else if (data == '3')
  {
    tone(6, 62);
    tone(7, 62);
  }
  else if (data == '4')
  {
    tone(6, 87);
    tone(7, 87);
  }
  else if (data == '5')
  {
    tone(6, 100);
    tone(7, 100);
  }
  else if (data == '6')
  {
    tone(6, 131);
    tone(7, 131);
  }
  else if (data == '7')
  {
    tone(6, 196);
    tone(7, 196);
  }
  else if (data == '8')
  {
    tone(6, 294);
    tone(7, 294);
  }
  else if (data == '9')
  {
    tone(6, 440);
    tone(7, 440);
  }
  else if (data == '10')
  {
    tone(6, 659);
    tone(7, 659);
  }
  else if (data == '11')
  {
    tone(6, 988);
    tone(7, 988);
  }
  else if (data == '12')
  {
    tone(6, 1397);
    tone(7, 1397);
  }
  else if (data == '13')
  {
    tone(6, 2093);
    tone(7, 2093);
  }
  else if (data == '14')
  {
    tone(6, 3136);
    tone(7, 3136);
  }
  else if (data == '15')
  {
    tone(6, 4699);
    tone(7, 4699);
  } 
}



void ultrasonic()
{
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration_us = pulseIn(echoPin, HIGH);
  int distance_cm = 0.017 * duration_us;

  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  delay(50);

  if (distance_cm > 8 and distance_cm < 500 and distance_cm != 0)
  {
    straight();
  }
  else if (distance_cm <= 8 and distance_cm < 500 and distance_cm != 0)
  {
    new_route();
  }
}

void line()
{
  int left = digitalRead(4);
  int right = digitalRead(5);


  if (left == 0 and right == 0)
  {
    straight();
  }

  else if (left == 0 and right == 1)
  {
    line_right();
  }

  else if (left == 1 and right == 0)
  {
    line_left();
  }
}

void Left()

{
  digitalWrite(8,LOW);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10,power);
}

void back()
{
  digitalWrite(8,LOW);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10, power);  
}

void straight()
{
  digitalWrite(8,HIGH);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10,power);
}

void Right()
{
  digitalWrite(8,HIGH);
  analogWrite(9,138);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10,power);
}

void still()
{
  digitalWrite(8,HIGH);
  analogWrite(9,0);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10,0);
  noTone(6);
  noTone(7);
}

void new_route()
{
  still();
  delay(400);

  back();
  delay(400);

  Left();
  delay(400);
}

void line_left()
{
  digitalWrite(8,LOW);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10, 60);
}

void line_right()
{
  digitalWrite(8,HIGH);
  analogWrite(9, 60);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10,power);
}
