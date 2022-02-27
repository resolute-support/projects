int button = 10;
int sensor = A0;
int pump = 8;


void setup()
{
  //Serial.begin(9600);
  pinMode(pump, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop()
{
  int buttonPressed = digitalRead(button);
  int moisture = analogRead(sensor);
  
  if(buttonPressed==0 or moisture < 250)
  {
    pump_off();
  }
  else if (buttonPressed==1 or moisture < 250)
  {
    pump_on();
  }

  //Serial.println(moisture);
  //Serial.println(buttonPressed);
  //Serial.println("");
}


void pump_off()
{
  digitalWrite(pump, LOW);
}

void pump_on()
{
  digitalWrite(pump, HIGH);
}
