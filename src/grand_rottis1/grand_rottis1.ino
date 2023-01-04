#include <Servo.h>
#define servo_pin1 8
#define servo_pin2 9
#define servo_pin3 10
#define servo_speed 10
uint32_t servo_T = 0; // unsigned long int
byte pos=90, b=90;
Servo servo1;
Servo servo2;
Servo servo3;
int a = 0;

bool flag = 0;

void setup() {
    
    servo1.attach(servo_pin1);
    servo2.attach(servo_pin2);
    servo3.attach(servo_pin3);
    servo_T = millis();
      Serial.begin(9600);
      servo1.write(pos);
      servo2.write(pos);
      servo3.write(pos);
      delay(1000);
}
void loop() {

  
  while (Serial.available()==0);
  Serial.print("! ");
  int a = (Serial.parseInt());
  Serial.println(a);
  
  while (Serial.available()==0);
  Serial.print("? ");
  int b = (Serial.parseInt());
  Serial.println(b);
  b = constrain(b, 0, 180); // Ограничить число 0…180
  
  if (a == 1) {
    if ((b != pos)&&(millis() - servo_T >= servo_speed)) { // Прерывание для обработки перемещения сервы, если позиция отличается
      servo_T = millis();
      while (b != pos)
      if (b > pos){ // Если новая позиция больше текущей 
        pos++; // Повысить текущую на 1
      } else { // …иначе
        pos--; // Понизить на 1
      }
      pos = constrain(pos, 0, 180); // Ограничить число 0…180
      servo1.write(pos); // Перемесить серву на полученный угол
      Serial.print("Status: "); // Показать текущий угол оператору через порт
      Serial.println(pos);
      if (pos == b) Serial.println("Completed!"); // Если угол достиг цели – уведомить оператора
    }
  } else if (a == 2) {
    if ((b != pos)&&(millis() - servo_T >= servo_speed)) { // Прерывание для обработки перемещения сервы, если позиция отличается
      servo_T = millis();
      while (b != pos)
      if (b > pos){ // Если новая позиция больше текущей 
        pos++; // Повысить текущую на 1
      } else { // …иначе
        pos--; // Понизить на 1
      }
      pos = constrain(pos, 0, 180); // Ограничить число 0…180
      servo2.write(pos); // Перемесить серву на полученный угол
      Serial.print("Status: "); // Показать текущий угол оператору через порт
      Serial.println(pos);
      if (pos == b) Serial.println("Completed!"); // Если угол достиг цели – уведомить оператора
    }
  } else {
      if ((b != pos)&&(millis() - servo_T >= servo_speed)) { // Прерывание для обработки перемещения сервы, если позиция отличается
      servo_T = millis();
      while (b != pos)
      if (b > pos){ // Если новая позиция больше текущей 
        pos++; // Повысить текущую на 1
      } else { // …иначе
        pos--; // Понизить на 1
      }
      pos = constrain(pos, 0, 180); // Ограничить число 0…180
      servo3.write(pos); // Перемесить серву на полученный угол
      Serial.print("Status: "); // Показать текущий угол оператору через порт
      Serial.println(pos);
      if (pos == b) Serial.println("Completed!"); // Если угол достиг цели – уведомить оператора
    }
  }
}





