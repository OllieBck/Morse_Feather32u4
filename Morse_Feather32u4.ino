/*********************************************************************
  This is an example for our nRF51822 based Bluefruit LE modules

  Pick one up today in the adafruit shop!

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  MIT license, check LICENSE for more information
  All text above, and the splash screen below must be included in
  any redistribution
*********************************************************************/

#include"bleSetup.h"
#include "morseKey.h"

int ditPin = 6;
int dahPin = 5;
int buzzerPin = 11;

String ditKey = "37";
String dahKey = "2D";
String altDitKey = "44";
String altDahKey = "45";

int debounceTime = 100;

int ditSound = 880;
int dahSound = 500;

int ditSoundDuration = 400;
int dahSoundDuration = 450;

int speedTyper = 300;
int speedSense = 3;

int accessPin = 10;
String enterKey = "28";

KeyboardKey shortKey(ditPin, ditKey, altDitKey, debounceTime, buzzerPin, ditSound, ditSoundDuration);
KeyboardKey longKey(dahPin, dahKey, altDahKey, debounceTime, buzzerPin, dahSound, dahSoundDuration);
AccessKey accessButton(accessPin, enterKey, debounceTime);

//ModifierKey accessButton(accessPin, debounceTime);

void setup(void)
{
  bleSetup();
}

void loop(void)
{
   
  bool shiftValue = accessButton.Check();

  //speedTyper = analogRead(A2)/speedSense;

  shortKey.Press(shiftValue, speedTyper);
  longKey.Press(shiftValue, speedTyper);

}
