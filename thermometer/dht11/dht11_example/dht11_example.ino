#include <SimpleDHT.h>

SimpleDHT11 dht(2);

void setup() {
    Serial.begin(9600);
}

void loop() {
    byte temp;  // 온도
    byte humid; // 습도

    dht.read(&temp, &humid, NULL);  // temp 변수에는 온도가 들어가고, humid 변수에는 습도가 들어간다.

    Serial.print("온도: ");
    Serial.print((int)temp);
    Serial.print(" 습도: ");
    Serial.print((int)humid);
    Serial.println();

    delay(1500);
}
