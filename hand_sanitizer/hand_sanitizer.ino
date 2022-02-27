int pump = 8;

void setup() 
{
  Serial.begin(9600);
  pinMode(pump, OUTPUT);
  digitalWrite(pump, HIGH);
}

void loop() 
{
  if (digitalRead(5) == LOW)
  {
    sanitize();
  }
  delay(80);
}


void sanitize()
{
  Serial.println("pumping");
  digitalWrite(pump, LOW);
  delay(400);
  digitalWrite(pump, HIGH);
  Serial.println("pls remove hand");
  wait();
}

void wait()
{
  while (digitalRead(5) == LOW)
  {
    delay(1);
  }
}
