#include <DHT22.h>
#define DHT22_PIN A0
DHT22 myDHT22(DHT22_PIN);
int digit1 = 8; //*_:__
int digit2 = 9; //_*:__
int digit3 = 10; //__:*_
int digit4 = 11; //__:_*
int digitDD = 12;//__*__

int segA = 0; //Display pin 14
int segB = 1; //Display pin 16
int segC = 2; //Display pin 13
int segD = 3; //Display pin 3
int segE = 4; //Display pin 5
int segF = 5; //Display pin 11
int segG = 6; //Display pin 15
int segDD = 7; //Display pin 15

void setup() {
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segDD, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(digitDD, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  DHT22_ERROR_t errorCode;
  errorCode = myDHT22.readData();
  long  startTime = millis();
  


  long  sec1 =  (startTime / (1000)) % 60;
  long  hou1 = (startTime / (360000));
  long timer1 = startTime % 6000;
  if (timer1 <= 2000) {
    char buf[9];
    sprintf(buf, "%02ld%02ld", hou1, sec1); 
    displayNumber(buf );
    digitalWrite(digitDD, HIGH);
  } else if (timer1 > 2000 && timer1 <= 4000) {
    digitalWrite(digitDD, LOW);displayNumber(String(myDHT22.getTemperatureCInt(),DEC) +"c");
  } else {
    displayNumber(String(myDHT22.getHumidityInt(),DEC) +"H");
  }
}

void displayNumber(String toDisplay) {

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH

  long beginTime = millis();

  for (int digit = 4 ; digit > 0 ; digit--) {

    //Turn on a digit for a short amount of time
    switch (digit) {
      case 1:
        digitalWrite(digit1, DIGIT_ON);
        break;
      case 2:
        digitalWrite(digit2, DIGIT_ON);
        break;
      case 3:
        digitalWrite(digit3, DIGIT_ON);
        break;
      case 4:
        digitalWrite(digit4, DIGIT_ON);
        break;
    }


    char stringOne =  toDisplay.charAt(digit - 1);
    lightNumber(stringOne);
    //toDisplay /= 10;

    //Turn off all segments
    lightNumber('#');

    //Turn off all digits
    digitalWrite(digit1, DIGIT_OFF);
    digitalWrite(digit2, DIGIT_OFF);
    digitalWrite(digit3, DIGIT_OFF);
    digitalWrite(digit4, DIGIT_OFF);
  }

  //while( (millis() - beginTime) < 10) ;
  //Wait for 20ms to pass before we paint the display again
}

//Given a number, turns on those segments
//If number == 10, then turn off number
void lightNumber(char CharToDisplay) {

#define SEGMENT_ON  HIGH
#define SEGMENT_OFF LOW

  switch (CharToDisplay) {

    case '0':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case '1':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case '2':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '3':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '4':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '5':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '6':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '7':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case '8':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '9':
      digitalWrite(segA, SEGMENT_ON);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case '#':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_OFF);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_OFF);
      break;

    case 'H':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_ON);
      digitalWrite(segC, SEGMENT_ON);
      digitalWrite(segD, SEGMENT_OFF);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_ON);
      digitalWrite(segG, SEGMENT_ON);
      break;

    case 'c':
      digitalWrite(segA, SEGMENT_OFF);
      digitalWrite(segB, SEGMENT_OFF);
      digitalWrite(segC, SEGMENT_OFF);
      digitalWrite(segD, SEGMENT_ON);
      digitalWrite(segE, SEGMENT_ON);
      digitalWrite(segF, SEGMENT_OFF);
      digitalWrite(segG, SEGMENT_ON);
      break;
  }
}

