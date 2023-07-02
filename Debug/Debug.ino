#include <Servo.h>

int analog1 = 3; // 定义uno的pin 5 向 analog1 输出
int analog2 = 11; // 定义uno的pin 6 向 analog2 输出
int analog3 = 5; // 定义uno的pin 9 向 analog3 输出
int analog4 = 6; // 定义uno的pin 10 向 analog4 输出
int trigPin = 13;                // 超声波模块的Trig引脚
int echoPin = 12;                // 超声波模块的Echo引脚

// int servoPin = 11;   // 舵机引脚
Servo myServo;    // 创建一个 Servo 对象
int angle = 0;    // 初始角度
bool avoidMode = true;         // 是否启用避障模式

void setup() {
  Serial.begin(9600);
  pinMode(analog1,OUTPUT);
  pinMode(analog2,OUTPUT);
  pinMode(analog3,OUTPUT);
  pinMode(analog4,OUTPUT);
  myServo.attach(9);    // 将 Servo 对象与数字引脚 9 关联
  pinMode(trigPin, OUTPUT);    // 配置超声波模块的Trig引脚为输出模式
  pinMode(echoPin, INPUT);     // 配置超声波模块的Echo引脚为输入模式
  // pinMode(servoPin,OUTPUT);
}

void loop() {
  rightward();
  delay(375);
  stop();
  delay(3000);
}

void forward() {
  analogWrite(analog1,0);
  analogWrite(analog2,55);
  analogWrite(analog3,0);
  analogWrite(analog4,55);
}
void backward() {
  analogWrite(analog1,55);
  analogWrite(analog2,0);
  analogWrite(analog3,55);
  analogWrite(analog4,0);
  
}
void leftward() {
  analogWrite(analog1,0);
  analogWrite(analog2,55);
  analogWrite(analog3,55);
  analogWrite(analog4,0);
}
void rightward() {
  analogWrite(analog1,55);
  analogWrite(analog2,0);
  analogWrite(analog3,0);
  analogWrite(analog4,55);
}

void stop() {
  analogWrite(analog1,0);
  analogWrite(analog2,0);
  analogWrite(analog3,0);
  analogWrite(analog4,0);
}

int detectObstacle() {
  long duration, distance;
  digitalWrite(trigPin, LOW);     // 准备发射超声波信号
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);    // 发射超声波信号
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // 计算超声波信号往返时间
  distance = duration * 0.034 / 2;
  return distance;         // 计算距离（单位：厘米）
}

void steer(int& value1, int& value2) {
  for (angle = 90; angle <= 180; angle += 1){  // 逐渐增加角度
  myServo.write(angle);    // 设置舵机位置
  delay(15);               // 等待一段时间
  if (angle == 180){
  value1 = detectObstacle();
  Serial.print("distance");
  Serial.println(value1);
  }
  }
  myServo.write(90); 
  delay(1000);
  for (angle = 90; angle >= 0; angle -= 1) {  // 逐渐减小角度
  myServo.write(angle);    // 设置舵机位置
  delay(15);             // 等待一段时间
  if (angle == 0){
  value2 = detectObstacle();
  }
  }
  myServo.write(90); 
  delay(1000);
}

