#include <Arduino.h>
#include "pitches.h"
#include <Keypad.h>
#include "eyiran.h"
#include "marioMain.h"
#include "piratesOfTheCaribbean.h"
#include "underworld.h"
#include "ode.h"


const int TONE = 18;
const byte rows = 4;
const byte columns = 4;
char hexaKeys[rows][columns] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[rows] = {2, 1, 0, 3};    // Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[columns] = {4, 5, 6, 7}; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, rows, columns);


void setup(){
}


float f_scale;


void loop()
{
  char key = keypad.getKey();
  if (key)
  {
    if (key == '1')
      for (int i = 0; i < sizeof(eyiran_melody) / sizeof(int); i++)
      {
         f_scale = analogRead(A1) / 512.0;
        int noteDuration = 800 / eyiran_noteDurations[i];
        tone(TONE, (int)(eyiran_melody[i] * f_scale), noteDuration);
        delay((int)(noteDuration * 1.3));
      }
    else if (key == '2')
      for (int i = 0; i < sizeof(marioMain_melody) / sizeof(int); i++)
      {
        f_scale = analogRead(A1) / 512.0;
        int noteDuration = 800 / marioMain_noteDurations[i];
        tone(TONE, (int)(marioMain_melody[i] * f_scale), noteDuration);
        delay((int)(noteDuration * 1.3));
      }
    else if (key == '3')
      for (int i = 0; i < sizeof(pirates_melody) / sizeof(int); i++)
      {
        f_scale = analogRead(A1) / 512.0;
        int noteDuration = 800 / pirates_noteDurations[i];
        tone(TONE, (int)(pirates_melody[i] * f_scale), noteDuration);
        delay((int)(noteDuration * 1.3));
      }
    else if (key == '4')
      for (int i = 0; i < sizeof(underworld_melody) / sizeof(int); i++)
      {
        f_scale = analogRead(A1) / 512.0;
        int noteDuration = 800 / underworld_noteDurations[i];
        tone(TONE, (int)(underworld_melody[i] * f_scale), noteDuration);
        delay((int)(noteDuration * 1.3));
      }
    else if (key == '5')
      for (int i = 0; i < sizeof(ode_melody) / sizeof(int); i++)
      {
        f_scale = analogRead(A1) / 512.0;
        int noteDuration = 800 / ode_noteDurations[i];
        tone(TONE, (int)(ode_melody[i] * f_scale), noteDuration);
        delay((int)(noteDuration * 1.3));
      }
  }
}
