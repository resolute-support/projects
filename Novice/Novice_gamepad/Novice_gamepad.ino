String button;

// the setup routine runs once when you press reset:
void setup() {
  pinMode(A4,INPUT);
  pinMode(A6,INPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  int sensorValue = analogRead(A6);
  float voltage = sensorValue * (100.0 / 1023.0);
  Serial.print(sensorValue);
  Serial.print("-------");
  if (analogRead(A4) == 235) {
    button = "none";
  }
  if (analogRead(A4) == 660) {
    button = "top";
  }
  if (analogRead(A4) == 432) {
    button = "bottom";
  }
  if (analogRead(A4) == 456) {
    button = "right";
  }
  if (analogRead(A4) == 526) {
    button = "left";
  }
  if (analogRead(A4) == 486) {
    button = "center";
  }
  if (analogRead(A4) == 580) {
    button = "top-right";
  }
  if (analogRead(A4) == 788) {
    button = "top-left";
  }
  Serial.println(button);
}