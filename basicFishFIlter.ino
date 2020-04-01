
int led = 15;
int button = 5;
int switchPin = 4;

unsigned long buttonPushedMillis;
unsigned long ledTurnedOnAt;
unsigned long turnOffDelay = 5000;
unsigned long currentMillis;

int ledState = HIGH;
int buttonCurrent;

long timeer = 0;
long debounce = 200;

boolean ledSwitch;
boolean switchPrev;

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  pinMode(switchPin, INPUT);
}

void filterOff(){
      digitalWrite(led, HIGH);
     ledState = true;
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
}

boolean switchOnOff(){
    boolean  switchState ;
    if(digitalRead(switchPin) == HIGH){
      switchState = true;
  }else{
    switchState = false;
  }

  return switchState;
}

void loop() { 
  currentMillis = millis();
  ledSwitch = switchOnOff();
  
  if (!ledSwitch){
    digitalWrite(led, HIGH);
    switchPrev = true;
  }else{
    if (switchPrev){
       digitalWrite(led, LOW);
       switchPrev = false;
    }

  buttonCurrent = digitalRead(button);

  if (buttonCurrent == HIGH && millis() - timeer > debounce){
    buttonPushedMillis = currentMillis;
    filterOff();
  }

  if (ledState) {
   if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay) {
     ledState = false;
     digitalWrite(led, LOW);
   }
 }
  }
}
