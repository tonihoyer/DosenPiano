#include "Arduino.h"
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
SoftwareSerial mySoftwareSerial(10, 11); // RX, TX
DFRobotDFPlayerMini myDFPlayer;
int taster = 7;
int tasterstatus = 0;
int count = 0; //für die Cola light Dose, zählt nach jeder Berührung hoch



void setup()
{
  mySoftwareSerial.begin(9600);
  myDFPlayer.volume(30);  //Lautstärke auf Maximum (30)
  pinMode(taster, INPUT); //Der Pin mit dem Taster (Pin 7) ist jetzt der Eingang
}

void loop()
{
  tasterstatus = digitalRead(taster); // Pin7 wird ausgelesen, tasterstatus bekommt den Wert "HIGH" für 5V oder "LOW" für 0V
  count++;
  if(tasterstatus == HIGH){
    myDFPlayer.play(1);  //Spielt die erste MP3-Datei ab
  } 
  tasterstatus = LOW;
}
