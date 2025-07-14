#include <Button.h>

Button count(8);
Button reset(9);

unsigned int value = 0;

void setOnPress() {
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
  count.begin();
  reset.begin();
  setOnPress();
}

void loop() {
  count.async();
  reset.async();
}