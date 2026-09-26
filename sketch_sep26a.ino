const int LED_PIN = 7;

int current_period = 100;
int current_duty = 0;


// 주기 설정
void set_period(int period) {
  current_period = period;
}


// duty 설정
void set_duty(int duty) {
  current_duty = duty;
}


// PWM 한 주기 실행
void write_pwm_cycle() {

  int on_time = (long)current_period * current_duty / 100;
  int off_time = current_period - on_time;

  // 5V → 저항 → LED → GPIO7
  // LOW = ON, HIGH = OFF
  if (on_time > 0) {
    digitalWrite(LED_PIN, LOW);
    delayMicroseconds(on_time);
  }

  if (off_time > 0) {
    digitalWrite(LED_PIN, HIGH);
    delayMicroseconds(off_time);
  }
}


void setup() {
  pinMode(LED_PIN, OUTPUT);

  // 10ms  : 10000
  // 1ms   : 1000
  // 0.1ms : 100
  set_period(100);
}


void loop() {

  // 밝기 0 → 100
  for (int duty = 0; duty <= 100; duty++) {

    set_duty(duty);

    // 한 단계당 약 5ms
    unsigned long start = micros();

    while (micros() - start < 5000) {
      write_pwm_cycle();
    }
  }


  // 밝기 100 → 0
  for (int duty = 100; duty >= 0; duty--) {

    set_duty(duty);

    // 한 단계당 약 5ms
    unsigned long start = micros();

    while (micros() - start < 5000) {
      write_pwm_cycle();
    }
  }
}
