int relayPin = 15;
int buttonPin = 5;
int switchPin = 4; 

int relayState = HIGH;
int buttonCurrent;

unsigned long relayTurnedOnAt;
unsigned long currentMillis;

unsigned long turnOffDelay = 1800000;

long timer = 0;
long debounce = 200;

boolean relaySwitch;
boolean switchPrev;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);
}//end setup


boolean switchOnOff() {
  boolean  switchState ;
  
  if (digitalRead(switchPin) == HIGH) {
    switchState = true;
  } else {
    switchState = false;
  }//end else

  return switchState;
}//end switchOnOff


void loop() {
  currentMillis = millis();
  relaySwitch = switchOnOff();

  if (!relaySwitch) {
    digitalWrite(relayPin, HIGH);
    switchPrev = true;
  } else {
    if (switchPrev) {
      digitalWrite(relayPin, LOW);
      switchPrev = false;
    }//end if

    buttonCurrent = digitalRead(buttonPin);

    if (buttonCurrent == HIGH && millis() - timer > debounce) {
      digitalWrite(relayPin, HIGH);
      relayState = true;
      relayTurnedOnAt = currentMillis;
    }//end if
    
    if (relayState) {
      if ((unsigned long)(currentMillis - relayTurnedOnAt) >= turnOffDelay) {
        relayState = false;
        digitalWrite(relayPin, LOW);
      }//end innerif
    }//end outer if
    
  }//end Else
}//end loop
