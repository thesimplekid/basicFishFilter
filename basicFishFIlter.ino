
int led = 4;
int button = 5;

unsigned long buttonPushedMillis;
unsigned long ledTurnedOnAt;
unsigned long turnOffDelay = 5000;
unsigned long currentMillis;
//unsigned long turnOnDelay = 0;

//boolean ledReady = false;


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

void filterOff(){
  //if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay){
      digitalWrite(led, HIGH);
     // setup our next "state"
     ledState = true;
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
     // wait for next button press
//     ledReady = false;
}

void loop() {
  // put your main code here, to run repeatedly:
  currentMillis = millis();

  buttonCurrent = digitalRead(button);

  if (buttonCurrent == HIGH){
    buttonPushedMillis = currentMillis;
    //ledReady = true;
    filterOff();
  }
/*
  if (ledReady){
    //if ((unsigned long)(currentMillis - buttonPushedMillis) >= turnOnDelay){
      digitalWrite(led, HIGH);
     // setup our next "state"
     ledState = true;
     // save when the LED turned on
     ledTurnedOnAt = currentMillis;
     // wait for next button press
     ledReady = false;
   // }
  }
*/
  if (ledState) {
   // okay, led on, check for now long
   if ((unsigned long)(currentMillis - ledTurnedOnAt) >= turnOffDelay) {
     ledState = false;
     digitalWrite(led, LOW);
   }
 }
/*
  if (buttonCurrent == HIGH && buttonPrev == LOW && millis() - timeer > debounce){
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
  */

}
