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
#include "KeyCodes.h"

String ditKey = "37";
String dahKey = "2D";

KeyboardKey periodKey(6, ditKey, "120", speedTyper);
KeyboardKey hyphonKey(A3, dahKey, "121", speedTyper);

void setup(void)
{
  bleSetup();
}

void loop(void)
{
  boolean shiftValue = false; //shiftKey.Check();
  speedTyper = 500;//analogRead(A2)/speedSense;

  periodKey.Press(shiftValue);
  hyphonKey.Press(shiftValue);
}
