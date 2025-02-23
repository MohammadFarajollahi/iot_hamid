
int element1 = 2;
int element2 = 3;
int tank1 = 4;
int tank2 = 5;
int tank3 = 6;
int tank4 = 7;
int tank5 = 8;
int light1 = 9;
int light2 = 10;
int fan1 = 11;
int fan2 = 12;
String sub1;
String inputData;
#include <ArduinoJson.h>
JsonDocument doc;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(element1, OUTPUT);
  pinMode(element2, OUTPUT);
  pinMode(tank1, OUTPUT);
  pinMode(tank2, OUTPUT);
  pinMode(tank3, OUTPUT);
  pinMode(tank4, OUTPUT);
  pinMode(tank5, OUTPUT);
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(fan2, OUTPUT);
  Serial.println("start...");
}

void loop() {
  uart2();
}
