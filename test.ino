int led = 0;
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