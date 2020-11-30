int relay_pin = 2;

void setup() {
    Serial.begin(9600);
    pinMode(relay_pin, OUTPUT);
}

bool i = false;
void loop() {
    if (i) {
        digitalWrite(relay_pin, HIGH);
        delay(2000);
        i = false;
    } else {
        digitalWrite(relay_pin, LOW);
        delay(2000);
        i = true;
    }
}