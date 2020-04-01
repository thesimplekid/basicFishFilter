

int relay = 15;
int button = 5;
int switchPin = 4;
int warningLed = 2;

int ledState = HIGH;
int buttonCurrent;

unsigned long buttonPushedMillis;
unsigned long ledTurnedOnAt;
unsigned long currentMillis;

unsigned long turnOffDelay = 10000;
unsigned long warningTime = 5000;

long timeer = 0;
long debounce = 200;

boolean ledSwitch;
boolean switchPrev;

void setup() {
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(warningLed, OUTPUT);
}

void filterOff() {
  digitalWrite(relay, HIGH);
  ledState = true;
  // save when the LED turned on
  ledTurnedOnAt = currentMillis;
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
  ledSwitch = switchOnOff();

  if (!ledSwitch) {
    digitalWrite(relay, HIGH);
    switchPrev = true;
  } else {
    if (switchPrev) {
      digitalWrite(relay, LOW);
      switchPrev = false;
    }

    buttonCurrent = digitalRead(button);

    if (buttonCurrent == HIGH && millis() - timeer > debounce) {
      buttonPushedMillis = currentMillis;
      filterOff();
    }
    
    if (ledState) {
      if ((unsigned long)(currentMillis - ledTurnedOnAt) >= warningTime) {
        digitalWrite(warningLed, HIGH);
      }

      if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay) {
        ledState = false;
        digitalWrite(relay, LOW);
        digitalWrite(warningLed, LOW);
      }
    }
  }
}
