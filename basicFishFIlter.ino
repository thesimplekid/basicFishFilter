int relayPin = 15;
int button = 5;//yellow
int switchPin = 4; //orange left most

int relayState = HIGH;
int buttonCurrent;

unsigned long buttonPushedMillis;
unsigned long relayTurnedOnAt;
unsigned long currentMillis;

unsigned long turnOffDelay = 1800000;

long timer = 0;
long debounce = 200;

boolean relaySwitch;
boolean switchPrev;

void setup() {
  pinMode(button, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(switchPin, INPUT);
}

void filterOff() {
  digitalWrite(relayPin, HIGH);
  relayState = true;
  // save when the LED turned on
  relayTurnedOnAt = currentMillis;
}

boolean switchOnOff() {
  boolean  switchState ;
  if (digitalRead(switchPin) == HIGH) {
    switchState = true;
  } else {
    switchState = false;
  }

  return switchState;
}

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
    }

    buttonCurrent = digitalRead(button);

    if (buttonCurrent == HIGH && millis() - timer > debounce) {
      buttonPushedMillis = currentMillis;
      filterOff();
    }
    
    if (relayState) {
      if ((unsigned long)(currentMillis - relayTurnedOnAt) >= turnOffDelay) {
        relayState = false;
        digitalWrite(relayPin, LOW);
      }
    }
  }
}
