// Motor Variables
int Left_Motor =10;
int Rigth_Motor =9;

// Push buttons
int Start_Push = 3; 
int White_Push = 2; 
int Black_Push = 4; 

// Sensor Variables

int Right_IR;
int Mid_IR;
int Left_IR;

int Right_IR_W;
int Mid_IR_W;
int Left_IR_W;

int Right_IR_B; 
int Mid_IR_B;  
int Left_IR_B; 

int Left_T = Left_IR;
int Mid_T = Mid_IR;
int Right_T = Right_IR;

bool line_follow = false;

void setup() {
  Serial.begin(9600);

  pinMode(Left_Motor, OUTPUT);
  pinMode(Rigth_Motor, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(Start_Push, INPUT_PULLUP);
  pinMode(White_Push, INPUT_PULLUP);
  pinMode(Black_Push, INPUT_PULLUP);
  
  digitalWrite(Left_Motor, HIGH);
  digitalWrite(Rigth_Motor, HIGH);
  digitalWrite(13, LOW);

}

void loop() 
{

  Left_IR = analogRead(A2);
  Mid_IR = analogRead(A1);
  Right_IR = analogRead(A0);

  //print_sensor_values();
  //print_buttons();
  
  if (digitalRead(Black_Push) == LOW)
  {
    digitalWrite(13, HIGH);
    Left_IR_B = Left_IR;
    Mid_IR_B = Mid_IR;
    Right_IR_B = Right_IR;
    Serial.println("black");
    delay(1000);
    digitalWrite(13, LOW);
  }
  if (digitalRead(White_Push) == LOW)
  {
    digitalWrite(13, HIGH);
    Left_IR_W = Left_IR;
    Mid_IR_W = Mid_IR;
    Right_IR_W = Right_IR;
    Serial.println("white");
    delay(1000);
    digitalWrite(13, LOW);
  }
  if (digitalRead(Start_Push) == LOW)
  {
    digitalWrite(13, HIGH);
    Left_T = Left_IR_B-Left_IR_W/2;
    Mid_T = Mid_IR_B-Mid_IR_W/2;
    Right_T = Right_IR_B-Right_IR_W/2-50;
    Serial.println("Go");
    line_follow = true;
    delay(1000);
    digitalWrite(13, LOW);  
  }
  if (line_follow == true)
  {
    line_following();
  }
}

void print_buttons()
{
  Serial.print(digitalRead(White_Push));
  Serial.print(digitalRead(Black_Push));
  Serial.print(digitalRead(Start_Push));
  Serial.println("");
}

void print_sensor_values()
{
  
  Serial.print(Left_IR);
  Serial.print("\t");
  Serial.print(Mid_IR);
  Serial.print("\t");
  Serial.print(Right_IR);
  Serial.println("");
  
}

void line_following()
{
  if (Left_IR < Left_T and Mid_IR > Mid_T and Right_IR < Right_T) //F
  {
    Serial.println("F");
    forward();
  }
  else if (Left_IR > Left_T and Mid_IR < Mid_T and Right_IR < Right_T)//L
  {
    Serial.println("L");
    left();
  }
  else if (Left_IR < Left_T and Mid_IR < Mid_T and Right_IR > Right_T)//R
  {
    Serial.println("R");
    right();
  }
  else
  {
    Serial.println("...");
  }
}

void left()
{
  digitalWrite(Left_Motor, HIGH);
   digitalWrite(Rigth_Motor, LOW); 
}

void forward()
{
  digitalWrite(Left_Motor, LOW);
   digitalWrite(Rigth_Motor, LOW);
}

void right()
{
  digitalWrite(Left_Motor, LOW);
  digitalWrite(Rigth_Motor, HIGH);
}
