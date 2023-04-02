#include <ESP8266WiFi.h>
#include <Servo.h>
uint32_t servo_T = 0; // unsigned long int
byte pos = 90, b = 90;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
int a = 0;
bool flag = 0;
int poss[5] = {90,90,90,90,90};
int poss_real[5] = {90,90,90,90,90};

const char* ssid = "TP-Link_770E_5G";
const char* password = "9263529760";
const char* host = "192.168.0.131";
int port = 12345;

int last_data = 0;
unsigned long int t_servo = 0;

WiFiClient client;

void setup() {

  Serial.begin(115200);
  servo_T = millis();
  Serial.println();
  servo1.attach(2);
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
}


void loop() {
  update_wifi();
  update_servo();
}

void update_wifi() {
  

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        int abc = line.toInt();
        if (last_data==0) last_data = abc;
        else {
          if (last_data>0 && last_data<6) {
            poss[last_data] = constrain(abc,0,180);
          }
        }
      }
      update_servo();
    }
  }
}

void update_servo() {
  if (millis()-t_servo>50) {
    for (int i = 0; i<5; i++) {
      if (poss[i]>poss_real[i]) poss_real[i]++;
      else if (poss[i]>poss_real[i]) poss_real[i]--;
    }
    t_servo = millis();
  }
  servo1.write(poss_real[0]);
  servo2.write(poss_real[1]);
}
