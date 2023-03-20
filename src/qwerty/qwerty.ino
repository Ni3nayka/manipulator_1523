#include <Servo.h>
#define servo_pin1 3
#define servo_pin2 4
#define servo_pin3 5
#define servo_pin4 6
#define servo_pin5 7
#define servo_speed 10
#define PIN_TRIG 11
#define PIN_ECHO 10
uint32_t servo_T = 0; // unsigned long int
byte pos = 90, b = 90;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
long duration, cm;
int a = 0;
bool flag = 0;

int poss[5] = {90,90,90,90,90};

#define led_pin 12
#define magnit_pin 13

#define PC 0

void setup() {
  Serial.begin (9600);
  pinMode(led_pin,OUTPUT);
  pinMode(magnit_pin,OUTPUT);
  //Определяем вводы и выводы
  servo1.attach(servo_pin1);
  servo2.attach(servo_pin2);
  servo3.attach(servo_pin3);
  servo4.attach(servo_pin4);
  servo5.attach(servo_pin5);
  servo_T = millis();
  servo1.write(pos);
  servo2.write(pos);
  servo3.write(pos);
  servo4.write(pos);
  servo5.write(pos);
  delay(1000);
}
void loop() {


  while (Serial.available() == 0);
  Serial.print("! ");
  int a = (Serial.parseInt());
  Serial.println(a);

  while (Serial.available() == 0);
  Serial.print("? ");
  int b = (Serial.parseInt());
  Serial.println(b);
  b = constrain(b, 0, 181); // Ограничить число 0…180

  if (PC == 1) {
    while (Serial.available() == 0);
    Serial.print("?&");
    Serial.parseInt();
  }

  if (a>0 && a<6) run_servo(a,b);
  else if (a==6) {
    pinMode(PIN_TRIG, OUTPUT);
    digitalWrite(PIN_TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(PIN_TRIG, HIGH);

    delayMicroseconds(10);
    digitalWrite(PIN_TRIG, LOW);
    pinMode(PIN_ECHO, INPUT);
    duration = pulseIn(PIN_ECHO, HIGH);
    cm = (duration / 2) / 29.1;
    Serial.print("Distance to object: ");
    Serial.print(cm);
    Serial.println(" cm.");
    delay(250);
  }
  else if (a==7) {
    b = constrain(b,0,1);
    digitalWrite(led_pin,b);
  }
  else if (a==8) {
    b = constrain(b,0,1);
    digitalWrite(magnit_pin,b);
  }
}

void run_servo(int n, int angle) {
  if ((angle != poss[n-1]) && (millis() - servo_T >= servo_speed)) { // Прерывание для обработки перемещения сервы, если позиция отличается
      servo_T = millis();
      while (angle != poss[n-1]) {
        if (angle > poss[n-1]) { // Если новая позиция больше текущей
          poss[n-1]++; // Повысить текущую на 1
        } else { // …иначе
          poss[n-1]--; // Понизить на 1
        }
        poss[n-1] = constrain(poss[n-1], 0, 181); // Ограничить число 0…180

        if (n==1) servo1.write(poss[n-1]);
        if (n==2) servo2.write(poss[n-1]);
        if (n==3) servo3.write(poss[n-1]);
        if (n==4) servo4.write(poss[n-1]);
        if (n==5) servo5.write(poss[n-1]);

        
        delay(15);
      }
      Serial.print("Status: "); // Показать текущий угол оператору через порт
      Serial.println(poss[n-1]);
      if (poss[n-1] == angle) Serial.println("Completed!"); // Если угол достиг цели – уведомить оператора
    }
}
