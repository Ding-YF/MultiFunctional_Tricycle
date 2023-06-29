#include <Servo.h>

Servo myServo; 
int input1 = 5; // 定义uno的pin 5 向 input1 输出
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 3; // 定义uno的pin 9 向 input3 输出
int input4 = 0; // 定义uno的pin 10 向 input4 输出

void setup() {
  myServo.attach(7);          // 连接舵机控制引脚
  myServo.write(30);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
}

void loop() {
  forward();
}

void forward() {
  analogWrite(input1,55);
  analogWrite(input2,0);
  analogWrite(input3,0);
  analogWrite(input4,55);
}
void back() {
  analogWrite(input1,0);
  analogWrite(input2,55);
  analogWrite(input3,55);
  analogWrite(input4,0);
}



