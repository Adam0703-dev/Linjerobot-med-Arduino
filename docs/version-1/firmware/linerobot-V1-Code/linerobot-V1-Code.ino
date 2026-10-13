#include "arduino_secrets.h"

long duration; 
int distance;  

const int trigPin = 7; 
const int echoPin = 6; 
const int motorDirection1 = 8; 
const int motorDirection2 = 9; 
const int motorSpeed1 = 10; 
const int motorDirection3 = 12; 
const int motorDirection4 = 13; 
const int motorSpeed2 = 11; 

void setup() { 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  
  pinMode(motorDirection1, OUTPUT); 
  pinMode(motorDirection2, OUTPUT); 
  pinMode(motorDirection3, OUTPUT); 
  pinMode(motorDirection4, OUTPUT); 
  
  pinMode(motorSpeed1, OUTPUT); 
  pinMode(motorSpeed2, OUTPUT); 
  
  Serial.begin(115200); 
    } 

void loop() {  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  
  digitalWrite(trigPin, HIGH);  
  delayMicroseconds(10); 
  digitalWrite(trigPin, HIGH); 
  
  duration = pulseIn(echoPin, HIGH); 
  
  distance = duration * 0.034 / 2; 
  
  if (distance > 20) { 
    digitalWrite(motorDirection1, LOW); 
    digitalWrite(motorDirection2, HIGH); 
    analogWrite(motorSpeed1, 100); 
    
    digitalWrite(motorDirection3, LOW); 
    digitalWrite(motorDirection4, HIGH); 
    analogWrite(motorSpeed2, 100) 
      // KÃ¶r Fram
      } 
  
  else if (distance < 20) { 
    digitalWrite(motorDirection1, HIGH); 
    digitalWrite(motorDirection2, LOW); 
    analogWrite(motorSpeed1, 100); 
    
    digitalWrite(motorDirection3, HIGH); 
    digitalWrite(motorDirection4, LOW); 
    analogWrite(motorSpeed2, 100); 
    delay(1500);
    // Backa 
    
    digitalWrite(motorDirection1, HIGH); 
    digitalWrite(motorDirection2, LOW); 
    analogWrite(motorSpeed1, 100); 
   
    digitalWrite(motorDirection3, LOW); 
    digitalWrite(motorDirection4, HIGH);
    analogWrite(motorSpeed2, 100); 
    delay(750); 
    //Vridning
  } 
} 

 