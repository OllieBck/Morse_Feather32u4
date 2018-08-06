class KeyboardKey {
    int keyPin;      // the number of the button pin
    String modifierValue;
    String keyValue;
    String letterValue;
    String altLetterValue;
    int pressSpeed;
    int debounceDelay;
    int freq;
    int sndLength;
    int sndPin;

    bool keyFirstPress = true;

    unsigned long lastDebounceTime = 0;

  public:
    KeyboardKey (int pin, String primaryKeyValue, String secondaryKeyValue, int debouncerTime, int speakerPin, int freqValue, int sndDuration)
    {
      keyPin = pin;
      letterValue = primaryKeyValue;
      altLetterValue = secondaryKeyValue;
      keyValue = letterValue;
      debounceDelay = debouncerTime;
      freq = freqValue;
      sndLength = sndDuration;
      sndPin = speakerPin;
      pinMode(keyPin, INPUT_PULLUP);
    }

    void Press(boolean isShiftPressed, int ditdahTimer)
    {
      int keyState = digitalRead(keyPin);
      bool shiftCheck = isShiftPressed;
      pressSpeed = ditdahTimer;

      if (isShiftPressed) {
        keyValue = altLetterValue;
      }
      else {
        keyValue = letterValue;
      }

      if (keyState == LOW) {
        if (millis() - lastDebounceTime > debounceDelay) {
          if (keyFirstPress == true) {
            int playLength = sndLength - pressSpeed;
            tone(sndPin, freq, playLength / 2);
            ble.print("AT+BLEKEYBOARDCODE=00-00-");
            ble.print(keyValue);
            ble.println("-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            keyFirstPress = false;
            lastDebounceTime = millis();
          }
          while (digitalRead(keyPin) == LOW && millis() - lastDebounceTime > debounceDelay) {
            if (millis() - lastDebounceTime > pressSpeed) {
              int playLength = sndLength - pressSpeed;
              tone(sndPin, freq, playLength / 2);
              ble.print("AT+BLEKEYBOARDCODE=00-00-");
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

class ModifierKey {
    // Class Member Variables
    // These are initialized at startup
    int keyPin;      // the number of the button pin

    int debounceDelay;

    unsigned long lastDebounceTime = 0;

    // These maintain the current state
    bool lastButtonState = HIGH;
    bool buttonState;

    bool modifierState = false;

  public:
    ModifierKey (int pin, int debouncerLength)
    {
      keyPin = pin;
      debounceDelay = debouncerLength;
      pinMode(keyPin, INPUT_PULLUP);
    }

    boolean Check()
    {
      int keyState = digitalRead(keyPin);

      if (keyState != lastButtonState) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (keyState != buttonState) {
          buttonState = keyState;

          if (buttonState == LOW) {
            modifierState = !modifierState;
          }
        }
      }
      lastButtonState = keyState;
      return modifierState;
    }
};

/****************************************************************************************************/

class AccessKey {
    int keyPin;      // the number of the button pin
    String keyValue;
    int debounceDelay;

    unsigned long lastDebounceTime = 0;

    bool lastButtonState = HIGH;
    bool buttonState;

    bool modifierState = false;

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

    boolean Check()
    {
      int keyState = digitalRead(keyPin);

      if (keyState != lastButtonState) {
        lastDebounceTime = millis();
      }

      if ((millis() - lastDebounceTime) > debounceDelay) {
        if (keyState != buttonState) {
          buttonState = keyState;

          if (buttonState == LOW) {
            modifierState = !modifierState;
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            ble.println("AT+BLEKEYBOARDCODE=E3-00-28-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
          }
        }
      }
      lastButtonState = keyState;
      return modifierState;
    }
};
