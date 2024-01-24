
#include <Keypad.h>
#include "pitches.h"

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {37, 35, 33, 31}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {29, 27, 25, 23}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//setup pins for other components
const int piezodig = 5;
const int motors = A3;
const int rgbRED = A7;
const int rgbGREEN = A8;

//new function to cleah up the void loop 
void dealCards(){
analogWrite(rgbRED, 200);//turn on red light
delay(1000);


  char customKey = customKeypad.getKey();
customKey = customKey*600;//multiply the number of cards by .6s, the time it takes to deal one card
analogWrite(motors, 200);//spin the wheels
delay(customKey);//spin the wheels for the percise amount of time needed
analogWrite(motors, 0);

analogWrite(rgbRED, 0);// red light off
analogWrite(rgbGREEN, HIGH);// green light on 
    tone(piezodig, 128, 2000); //speaker sound
    customKey = 0;//reset
}


void setup(){

  Serial.begin(9600);

pinMode(rgbRED, OUTPUT);
pinMode(rgbGREEN, OUTPUT);
pinMode(motors, OUTPUT);
}

void loop(){

Serial.println(customKey);


  if (customKey>0){
    dealCards();
  }
}