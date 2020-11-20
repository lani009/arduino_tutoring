#include <DHT11.h>

int thermometer_pin = 2;

DHT11 termo_sensor(thermometer_pin);

void setup() {
  Serial.begin(9600);
  int h = dht.readHumidity();
}
