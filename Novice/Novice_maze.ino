int power = 150;

int trigPin = 2;    // TRIG pin 
int echoPin = 3;    // ECHO pin

float duration_us;
float distance_cm;
char data;


void setup() 
{
  delay(2000);
  
  Serial.begin(9600);
  pinMode(5, INPUT);
  pinMode(4, INPUT); 
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A1, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  int LS = digitalRead(4);
  int RS = digitalRead(5);

  Serial.print("Left:");
  Serial.print(LS);
  Serial.print("     ");
  Serial.print("right:");
  Serial.print(RS);
  Serial.println("");


  if (LS == 0 and RS == 1)
  {
    straight();
  }
  else if (LS == 0 and RS == 0)
  {
    Right();
  }
  else if (LS == 1 and RS == 1)
  {
    Left();
  }
}

void straight()

{
  digitalWrite(8,LOW);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10,power);
}

void back() 
{
  digitalWrite(8,HIGH);
  analogWrite(9,138);
  
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10,power);
}

void Left() 
{
  digitalWrite(8,HIGH);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,LOW);
  analogWrite(10,power);
}

void Right() 
{
  digitalWrite(8,LOW);
  analogWrite(9,power);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10, power);
}

void still() 
{
  digitalWrite(8,HIGH);
  analogWrite(9,0);
  pinMode(A1, OUTPUT);
  digitalWrite(A1,HIGH);
  analogWrite(10,0);
}
