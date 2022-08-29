String button_press() {
  delay(10);
  int reading = analogRead(A4);
  if (reading > 300 and reading < 443) {
    return "Bottom";
  }
  else if (reading > 443 and reading < 470) {
    return "Right";
  }
  else if (reading > 470 and reading < 505) {
    return "Mid";
  }
  else if (reading > 505 and reading < 552) {
    return "Left";
  }
  else if (reading > 552 and reading < 598) {
    return "Top right";
  }
  else if (reading > 598 and reading < 722) {
    return "Top";
  }
  else if (reading > 722 and reading < 1023) {
    return "Top left";
  }
  if (reading < 300) {
    return "None";
  }
}

void setup()
{
  pinMode(A4, INPUT);
  Serial.begin(9600);
}

void loop()
{
  Serial.print(analogRead(A6));
  Serial.print("  -   ");
  Serial.print(analogRead(A4));
  Serial.print("  -   ");
  Serial.println(button_press());
}