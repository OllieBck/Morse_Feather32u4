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

String ditKey = "37";
String dahKey = "2D";
String enterKey = "28";
String GUI = "E3";

int debounceTime = 100;

int ditSound = 880;
int dahSound = 500;

int ditSoundDuration = 400;
int dahSoundDuration = 450;

int speedTyper = 300;
int speedSense = 3;

KeyboardKey shortKey(6, ditKey, debounceTime, 11, ditSound, ditSoundDuration);
KeyboardKey longKey(5, dahKey, debounceTime, 11, dahSound, dahSoundDuration);
AccessKey accessButton(10, enterKey, 100);

void setup(void)
{
  bleSetup();
}

void loop(void)
{
  boolean shiftValue = accessButton.Check();
  accessButton.Press();
  
  //speedTyper = analogRead(A2)/speedSense;

  shortKey.Press(shiftValue, speedTyper);
  longKey.Press(shiftValue, speedTyper);
  
}
