/*
  버튼을 통해 7세그먼트 값 증가 시키기
*/
#define BUTTON_NOT_PRESSED 1
#define BUTTON_PRESSED 0

int position_pin[] = {1,2,3,4};               //4자리 결정 핀
int segment_pin[] = {5,6,7,8,9,10,11,12};     //세그먼트 제어 핀
int button_pin = 13;                          //버튼 입력 핀
const int delayTime = 2;                      //일시정지 시간

//0 ~ 9를 표현하는 세그먼트 값
byte data[] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xE6};

void setup() {
  //4자리 결정 핀 출력용으로 설정
  for(int i = 0; i < 4; i++) {
     pinMode(position_pin[i], OUTPUT);
  }

  //세그먼트 제어 핀 출력용으로 설정
  for(int i = 0; i < 8; i++) {
    pinMode(segment_pin[i], OUTPUT);
  }

  // 버튼 풀업 저항 설정
  pinMode(button_pin, INPUT_PULLUP);
}

int button_state = BUTTON_NOT_PRESSED;
int number_count = 0;
void loop() {
    show_number(number_count);
    int button_read = digitalRead(button_pin);
    if (button_state != BUTTON_PRESSED) {
        if (button_read == BUTTON_PRESSED) {
            button_state = BUTTON_PRESSED;
            number_count = (number_count+1)%10000;
        }
    } else {
        if (button_read == BUTTON_NOT_PRESSED) {
            button_state = BUTTON_NOT_PRESSED;
        }
    }
}

void show_number(int number) {
    if (number > 9999) {
      return;
    }

    int dig1 = number / 1000;
    int dig2 = number / 100 - dig1*10;
    int dig3 = number / 10 - dig1*100 - dig2*10;
    int dig4 = number - dig1*1000 - dig2*100 - dig3*10;

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