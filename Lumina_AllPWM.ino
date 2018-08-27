#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

const int outPin1 = 7;
const int inPin1 = 4;
const int outPin2 = 6;
const int inPin2 = 2;

int pinVal1 = 0;
int lastPinVal1 = 1;
int pinVal2 = 0;
int lastPinVal2 = 1;

const int led1 = 3;
const int led2 = 9;
const int led3 = 10;
const int led4 = 11;
const int led5 = 5;

bool Normal = false;
bool Comm = false;

void setup() {
  Serial.begin(115200);

  pinMode (LED_BUILTIN, OUTPUT);
  pinMode (outPin1, OUTPUT);
  pinMode(inPin1, INPUT);
  pinMode (outPin2, OUTPUT);
  pinMode(inPin2, INPUT);

  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (led3, OUTPUT);
  pinMode (led4, OUTPUT);
  pinMode (led5, OUTPUT); 

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }

  //Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
   // Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  // power
 // Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;

//  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4 && measure.RangeMilliMeter < 800) {  // phase failures have incorrect data
//    Serial.println("Distance (mm): "); 
//    Serial.println(measure.RangeMilliMeter);
    outputOn();
  
    if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Normal = true;
//    Comm = false;
    Serial.write("a");
    }
  
//    if (measure.RangeStatus != 4 && pinVal1 == 1 && pinVal2 == 0) {
//    Normal = true;
//    Comm = true;
//    }
//    
//    if (measure.RangeStatus != 4 && pinVal2 == 1 && pinVal1 == 0) {
//    Normal = true;
//    Comm = true;
//    } 
    
//    Serial.println ("Normal = ");
//    Serial.println (Normal);
//    Serial.println ("Communicating = ");
//    Serial.println (Communicating);
     
   if (Normal == true && Comm == true) {
      Communicating();
    }
    
    else if (Normal == true) {
      NormalBehaviour();
    }

    
  } else {
    Off();
    outputOff();
    Serial.write("b");
  }

  input();
  delay(100);

}

// OUTPUT ON FUNCTION
void outputOn () {
  digitalWrite(outPin1, HIGH);
  digitalWrite(outPin2, HIGH);
}

// OUTPUT OFF FUNCTION
void outputOff() {
  digitalWrite(outPin1, LOW);
  digitalWrite(outPin2, LOW);
}

// INPUT FUNCTION
void input () {
  pinVal1 = digitalRead(inPin1);
  if (lastPinVal1 != pinVal1) {
    digitalWrite(LED_BUILTIN, pinVal1);
    Serial.print(pinVal1);
    lastPinVal1 = pinVal1;

    if (pinVal1 == 1) {
    Comm = true;
    } else {
    Comm = false;
    }
  }
  
//  pinVal2 = digitalRead(inPin2);
//  if (lastPinVal2 != pinVal2) {
//    digitalWrite(LED_BUILTIN, pinVal2);
//    Serial.print(pinVal2);
//    lastPinVal2 = pinVal2;
//
//    if (pinVal2 == 1) {
//    Comm = true;
//    } else {
//    Comm = false;
//    }
//  }
}

void NormalBehaviour() {
  // fade in from min to max in increments of 5 points:

  for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
    // sets the value (range from 0 to 255):
    analogWrite(led1, fadeValue);
    analogWrite(led2, fadeValue);
    analogWrite(led3, fadeValue);
    analogWrite(led4, fadeValue);
    analogWrite(led5, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(40);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
    // sets the value (range from 0 to 255):
    analogWrite(led1, fadeValue);
    analogWrite(led2, fadeValue);
    analogWrite(led3, fadeValue);
    analogWrite(led4, fadeValue);
    analogWrite(led5, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(40);
  }
}

void Communicating() {
    for (int fadeValueOne = 0 ; fadeValueOne <= 255; fadeValueOne += 20) {
    // sets the value (range from 0 to 255):

    analogWrite(led1, fadeValueOne);
    analogWrite(led2, fadeValueOne);
    analogWrite(led3, fadeValueOne);
    analogWrite(led4, fadeValueOne);
    analogWrite(led5, fadeValueOne);
    // wait for 30 milliseconds to see the dimming effect
    delay(20);
  }

  // fade out from max to min in increments of 5 points:
  for (int fadeValueOne = 255 ; fadeValueOne >= 0; fadeValueOne -= 20) {
    // sets the value (range from 0 to 255):

    analogWrite(led1, fadeValueOne);
    analogWrite(led2, fadeValueOne);
    analogWrite(led3, fadeValueOne);
    analogWrite(led4, fadeValueOne);
    analogWrite(led5, fadeValueOne);
    // wait for 30 milliseconds to see the dimming effect
    delay(20);
  }
}


void Off() {

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);
  delay(20);
}

