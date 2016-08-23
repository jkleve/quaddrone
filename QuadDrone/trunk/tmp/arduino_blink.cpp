
#include <Arduino.h>

int A_LED = 27;
int B_LED = 26;
int C_LED = 25;

void setup() {
  // put your setup code here, to run once:
  pinMode(A_LED,OUTPUT);
  pinMode(B_LED,OUTPUT);
  pinMode(C_LED,OUTPUT);
  
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(A_LED,HIGH);
  delay(250);
  digitalWrite(B_LED,HIGH);
  delay(250);
  digitalWrite(C_LED,HIGH);
  delay(250);
  digitalWrite(A_LED,LOW);
  delay(250);
  digitalWrite(B_LED,LOW);
  delay(250);
  digitalWrite(C_LED,LOW);
}