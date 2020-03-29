
int led = 4;
int button = 5;

unsigned long buttonPushedMillis;
unsigned long ledTurnedOnAt;
unsigned long turnOffDelay = 5000;
unsigned long currentMillis;

int ledState = HIGH;
int buttonCurrent;

long timeer = 0;
long debounce = 200;

void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
}

void filterOff(){
      digitalWrite(led, HIGH);
     ledState = true;
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
}

void loop() {
  currentMillis = millis();

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
