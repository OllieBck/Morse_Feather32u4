class KeyboardKey {
    int keyPin;      // the number of the button pin
    String modifierValue;
    String keyValue;
    int pressSpeed;
    int debounceDelay;

    int keyFirstPress = true;

    unsigned long lastDebounceTime = 0;
    unsigned long heldTime = 0;


  public:
    KeyboardKey (int pin, String letterValue, int debouncerTime)
    {
      keyPin = pin;
      keyValue = letterValue;
      debounceDelay = debouncerTime;
      pinMode(keyPin, INPUT_PULLUP);
    }

    void Press(boolean isShiftPressed, int ditdahTimer)
    {
      int keyState = digitalRead(keyPin);
      boolean shiftCheck = isShiftPressed;
      pressSpeed = ditdahTimer;

      if (isShiftPressed) {
        modifierValue = "02";
      }
      else {
        modifierValue = "00";
      }

      if (keyState == LOW) {
        if (millis() - lastDebounceTime > debounceDelay) {
          if (keyFirstPress == true) {
            ble.print("AT+BLEKEYBOARDCODE=");
            ble.print(modifierValue);
            ble.print("-00-");
            ble.print(keyValue);
            ble.println("-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            keyFirstPress = false;
            lastDebounceTime = millis();
          }
          while (digitalRead(keyPin) == LOW && millis() - lastDebounceTime > debounceDelay) {
            if (millis() - lastDebounceTime > pressSpeed) {
              ble.print("AT+BLEKEYBOARDCODE=");
              ble.print(modifierValue);
              ble.print("-00-");
              ble.print(keyValue);
              ble.println("-00-00");
              ble.println("AT+BLEKEYBOARDCODE=00-00");
              lastDebounceTime = millis();
            }
          }
          lastDebounceTime = millis();
        }
      }
      else {
        keyFirstPress = true;
      }
    }
};

/****************************************************************************************************/

class ModifierKey
{
    // Class Member Variables
    // These are initialized at startup
    int keyPin;      // the number of the button pin

    // These maintain the current state
    int change = 0;
    int state = 0;

    boolean modifierState = false;

  public:
    ModifierKey (int pin)
    {
      keyPin = pin;
      pinMode(keyPin, INPUT_PULLUP);
    }

    boolean Check()
    {
      int keyState = digitalRead(keyPin);

      if (keyState)
      {
        state = 0;
      }

      else {
        state = 1;
      }

      if (state != change) {
        if (state == LOW) {
          digitalWrite(LED_BUILTIN, HIGH);
          modifierState = !modifierState;
          delay(5);
        }
        else {
          digitalWrite(LED_BUILTIN, LOW);
        }
      }
      change = state;
      return modifierState;
    }
};

/****************************************************************************************************/

class AccessKey {
    int keyPin;      // the number of the button pin
    String keyValue;
    int debounceDelay;

    unsigned long lastDebounceTime = 0;
    unsigned long heldTime = 0;

  public:
    AccessKey (int pin, String letterValue, int debouncerTime)
    {
      keyPin = pin;
      keyValue = letterValue;
      debounceDelay = debouncerTime;
      pinMode(keyPin, INPUT_PULLUP);
    }

    void Press()
    {
      int keyState = digitalRead(keyPin);

      if (keyState == LOW) {
        if (millis() - lastDebounceTime > debounceDelay) {
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            lastDebounceTime = millis();
          }
          lastDebounceTime = millis();
        }
    }
};
