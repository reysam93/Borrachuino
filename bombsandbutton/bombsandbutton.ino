// named constants for the switch and motor pins
const int switchPin = 2; // the number of the switch pin
const int motorMezcla =  9; // the number of the motor pin
const int motorAlcohol =  10; // the number of the motor pin


int switchState = 0;  // variable for reading the switch's status

void setup() {
  // initialize the motor pin as an output:
  pinMode(motorMezcla, OUTPUT);
  pinMode(motorAlcohol, OUTPUT);
  // initialize the switch pin as an input:
  pinMode(switchPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the state of the switch value:
  switchState = digitalRead(switchPin);

  // check if the switch is pressed.
  if (switchState == HIGH) {
    // turn motor on:
    Serial.println("PULSADO");
    digitalWrite(motorMezcla, HIGH);
    digitalWrite(motorAlcohol, HIGH);
    delay(4000);
    
  } else {
    // turn motor off:
    digitalWrite(motorMezcla, LOW);
    digitalWrite(motorAlcohol, LOW);
  }
}

