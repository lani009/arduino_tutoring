#include <SimpleDHT.h>

const int relay_pin = 2;
const int moter_pin = 3;
const int temp_sensor_pin = 4;
const int dirt_sensor_pin = 5;

SimpleDHT11 dht11(temp_sensor_pin);

const int a_temp = 26;  // 최적 온도 -> 자라나기 적당한 온도

void setup() {
    pinMode(relay_pin, OUTPUT);
    pinMode(moter_pin, OUTPUT);
}


unsigned long motor_started_time;   // 모터가 작동 시작이 된 시간
unsigned long last_water_time = 0;  // 마지막으로 물을 준 시간

bool is_motor_stated = false;       // 모터가 시작이 되었는가?

/* 
 * 1. 온도가 낮을 때 마다 릴레이를 켜줘야 함.
 * 1.1. 온도가 낮을 때 어떻게 온도 조절을 할 것인가??
 * 
 * 2. 토양 수분이 낮을 때 마다 모터를 켜줘야함.
 * 2.2. 토양 수분이 낮다는건 어떻게 측정하는가??
 */
void loop() {
    byte current_temp;
    dht11.read(&current_temp, NULL, NULL);

    if (current_temp < 24) {
        // 릴레이 작동
        digitalWrite(relay_pin, HIGH);
    } else if (current_temp > 26) {
        // 릴레이 off
        digitalWrite(relay_pin, LOW);
    }

    // int dirt_value = analogRead(dirt_sensor_pin);   // 토양 습도를 센서로 부터 받아옴

    // if (is_motor_stated) {
    //     if (millis() - motor_started_time > 10000) {
    //         digitalWrite(moter_pin, LOW);
    //         is_motor_stated = false;
    //     }
    // } else {
    //     if (dirt_value < 50%) {
    //         digitalWrite(moter_pin, HIGH);
    //         motor_started_time = millis();
    //         is_motor_stated = true;
    //     }
    // }

    /* 현재시간 - 마지막에 물을 준 시간
     * = 물을 주지 않았던 시간
     * 물을 주지 않았던 시간 == 1일(하루) -> 물을 준다.
     */

    // 하루에 한번씩 물을 주게 해줄 수 있다. 물을 줄 때는 10초 동안 물을 줌.
    if (is_motor_stated) {
        // 모터가 시작됨 -> 물을 주고 있다

        if (millis() - motor_started_time > 10000) {
            digitalWrite(moter_pin, LOW);
            is_motor_stated = false;
            last_water_time = millis();
        }
    } else {
        // 모터 꺼짐

        if (millis() - last_water_time > 43200000) {
            digitalWrite(moter_pin, HIGH);
            motor_started_time = millis();
            is_motor_stated = true;
        }
    }

}