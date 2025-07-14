#include <Button.h>

Button count(8); // Button connected with GPIO 8 and GND of ESP32.
Button reset(9); // Button connected with GPIO 9 and GND of ESP32.

unsigned int value = 0;

void setOnPress() {
  // Invoke the callback functions to handle presses.
  count.onSinglePress([]() {
    value++;
    Serial.println("count.onSinglePress: " + String(value));
  });
  count.onDoublePress([]() {
    value += 5;
    Serial.println("count.onDoublePress: " + String(value));
  });
  count.onLongPress([]() {
    value += 10;
    Serial.println("count.onLongPress: " + String(value));
  });
  reset.onSinglePress([]() {
    value = 0;
    Serial.println("reset.onSinglePress: " + String(value));
  });
}

void setup() {
  Serial.begin(115200);
  count.begin(); // Invoke the begin function once for calibration.
  reset.begin(); // Invoke the begin function once for calibration.
  setOnPress();
}

void loop() {
  count.async(); // Invoke the async function inside the RTOS loop.
  reset.async(); // Invoke the async function inside the RTOS loop.
}