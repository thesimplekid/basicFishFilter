
int led = 4;
int button = 5;



int ledState = HIGH;
int buttonCurrent;
int buttonPrev = LOW;

long timeer = 0;
long debounce = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  

}

void loop() {
  // put your main code here, to run repeatedly:

  buttonCurrent = digitalRead(button);

  if (buttonCurrent == HIGH && buttonPrev == LOW && millis() - timeer > debounce){
    
    Serial.print(ledState);
    if (ledState == HIGH){
      ledState = LOW;
      Serial.print("low");
    }else{
      ledState = HIGH;
      Serial.print("HIGH");
    }
    timeer = millis();
  }

  digitalWrite(led, ledState);
  //Serial.print("Here");
  //Serial.print(buttonCurrent);
  buttonPrev = buttonCurrent;
  

}
