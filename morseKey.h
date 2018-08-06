int speedTyper = 300;
int speedSense = 3;
int debouncerTime = 200;

class KeyboardKey
{
    int keyPin;      // the number of the button pin
    String keyUppercase;
    String keyLowercase;
    int pressSpeed;
    int keyFirstPress = true;

    unsigned long lastDebounceTime = 0;
    unsigned long heldTime = 0;
    unsigned long debounceDelay = debouncerTime;

  public:
    KeyboardKey (int pin, String valueLower, String valueUpper, int ditdahTimer)
    {
      keyPin = pin;
      keyLowercase = valueLower;
      keyUppercase = valueUpper;
      pressSpeed = ditdahTimer;
      pinMode(keyPin, INPUT_PULLUP);
    }

    void Press(boolean isShiftPressed)
    {
      int keyState = digitalRead(keyPin);
      boolean shiftCheck = isShiftPressed;
      String keyValue;
      pressSpeed = speedTyper;

      if (isShiftPressed) {
        keyValue = keyUppercase;
      }
      else {
        keyValue = keyLowercase;
      }

      if (keyState == LOW) {
        if (millis() - lastDebounceTime > debounceDelay) {
          if (keyFirstPress == true) {
            ble.print("AT+BLEKEYBOARDCODE=00-00-");
            ble.print(keyValue);
            ble.println("-00-00");
            ble.println("AT+BLEKEYBOARDCODE=00-00");
            keyFirstPress = false;
            lastDebounceTime = millis();
          }
          while (digitalRead(keyPin) == LOW && millis() - lastDebounceTime > debounceDelay) {
            if (millis() - lastDebounceTime > pressSpeed) {
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


