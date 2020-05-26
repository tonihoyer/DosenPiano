#include <CapacitiveSensor.h>
#include "pitches.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

#define COMMON_PIN      2    // The common 'send' pin for all keys
#define LAUTSPRECHER_PIN 8
#define NUM_OF_SAMPLES  10   // Higher number whens more delay but more consistent readings
#define CAP_THRESHOLD   300  // Capactive reading that triggers a note (adjust to fit your needs)
#define NUM_OF_KEYS     1    // Number of keys that are on the keyboard
#define CS(Y) CapacitiveSensor(2, Y)// This macro creates a capacitance "key" sensor object for each key on the piano keyboard:

SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;

int notes[]={ 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 93, 98, 104, 110, 117, 123, 131, 139,
              147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523,
              554, 587, 622, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865,
              1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978
            };

// Defines the pins that the keys are connected to:
CapacitiveSensor keys[] = {CS(3)};

const int buttonPin = 4;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

int buttonState = LOW;
int speakerState = 0;

void setup() { 
  mySoftwareSerial.begin(9600);
  Serial.begin(115200);
  
  // Turn off autocalibrate on all channels:
  for(int i=0; i<1; ++i) {
    keys[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
  }

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  
  myDFPlayer.volume(25);  //Set volume value. From 0 to 30
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    digitalWrite(ledPin, HIGH);
    speakerState = changeSpeaker();  
  }else{
    digitalWrite(ledPin, LOW);
  }
  
  if(keys[0].capacitiveSensor(NUM_OF_SAMPLES) > CAP_THRESHOLD) {
    if(speakerState == 0){
      tone(LAUTSPRECHER_PIN, notes[wert()], 200);
      delay(200);
    }else{
      myDFPlayer.play(wertSD());
      delay(1000);
    }
  }
  delay(200);
}

int changeSpeaker(){
  if(speakerState == 0){
    speakerState = 1;
  }else{
    speakerState = 0;
  }
  return speakerState;
}

int wert(){
  int zahl = random(0, 88);
  return zahl;
}

int wertSD(){
  int zahl = random(1, 28);
  return zahl;
}
