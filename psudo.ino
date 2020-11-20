#include <SimpleDHT.h>
#define BUTTON_NOT_PRESSED 1
#define BUTTON_PRESSED 0
#define ON 1
#define OFF 0

int position_pin[] = {1,2,3,4};               // 세그먼트 자리 결정 핀
int segment_pin[] = {5,6,7,8,9,10,11};        // 세그먼트 제어 핀
int relay_pin = A5;                           // analog A5 pin as digital output
int therm_up_pin = A0;                        // 온도 상승 버튼
int therm_down_pin = A1;                      // 온도 하강 버튼
int temp_pin = A3;                            // 온도 센서
const int delayTime = 2;                      // 세그먼트 프레임 간격
SimpleDHT11 dht11(temp_pin);

//0 ~ 9를 표현하는 세그먼트 값
byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

void setup() {
  //4자리 결정 핀 출력용으로 설정
  for(int i = 0; i < 4; i++) {
     pinMode(position_pin[i], OUTPUT);
  }

  //세그먼트 제어 핀 출력용으로 설정
  for(int i = 0; i < 7; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }

  // 버튼 풀업 저항 설정
  pinMode(therm_up_pin, INPUT_PULLUP);
  pinMode(therm_down_pin, INPUT_PULLUP);

  // analog A5 pin as relay signal digital pin
  pinMode(relay_pin, OUTPUT);

  // DHT 온습도 센서
}

int goal_therm_global = 0;
byte current_therm;
int therm_up_read, therm_down_read;

void loop() {
    therm_up_read = digitalRead(therm_up_pin);
    therm_down_read = digitalRead(therm_down_pin);
    dht11.read(&current_therm, NULL, NULL);
    int current_therm = digitalRead(temp_pin);

    // 현재온도 보여주기
    show_therm(current_therm, goal_therm_global);

    if (therm_up_read != BUTTON_PRESSED) {
        if (therm_up_pin == BUTTON_PRESSED) {
            therm_down_read = BUTTON_PRESSED;
            goal_therm_global++;
            digitalWrite(relay_pin, HIGH);
        }
    } else {
        if (therm_up_pin == BUTTON_NOT_PRESSED) {
            therm_up_read = BUTTON_NOT_PRESSED;
            digitalWrite(relay_pin, LOW);
        }
    }

    if (therm_down_read != BUTTON_PRESSED) {
        if (therm_down_pin == BUTTON_PRESSED) {
            therm_down_read = BUTTON_PRESSED;
            goal_therm_global--;
            digitalWrite(relay_pin, HIGH);
        }
    } else {
        if (therm_down_pin == BUTTON_NOT_PRESSED) {
            therm_down_read = BUTTON_NOT_PRESSED;
            digitalWrite(relay_pin, LOW);
        }
    }


}

void show_therm(int current_therm, int goal_therm) {
    int dig1 = current_therm / 10;
    int dig2 = current_therm - dig1 * 10;
    int dig3 = goal_therm / 10;
    int dig4 = goal_therm - dig3 * 10;

    show_led(1, dig1);
    delay(delayTime);
    show_led(2, dig2);
    delay(delayTime);
    show_led(3, dig3);
    delay(delayTime);
    show_led(4, dig4);
    delay(delayTime);
}

void show_led(int position, int number) {
  //4자리 중 원하는 자리 선택
  for(int i = 0; i < 4; i++) {
    if(i + 1 == position){
      digitalWrite(position_pin[i], LOW);
    } else {
      digitalWrite(position_pin[i], HIGH);
    }
  }

  //8개 세그먼트를 제어해서 원하는 숫자 출력
  for(int i = 0; i < 8; i++){
     int segment = (data[number] & (0x01 << i));
     if(segment == 0x01 << i){
       digitalWrite(segment_pin[7 - i], HIGH);
     } else {
       digitalWrite(segment_pin[7 - i], LOW);
     }
  }
}