#include <Arduino.h>
#line 2 "d:\\git\\arduino_tutoring\\test.ino"
void setup();
#line 8 "d:\\git\\arduino_tutoring\\test.ino"
void loop();
#line 0 "d:\\git\\arduino_tutoring\\test.ino"
#line 1 "d:\\git\\arduino_tutoring\\test.c"

#line 1 "d:\\git\\arduino_tutoring\\test.ino"
int led = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(OUTPUT, led);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 255; i++)
  {
      analogWrite(led, i);
      Serial.println(i);
      delay(100);
  }
}
