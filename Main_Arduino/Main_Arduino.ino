#include <SoftwareSerial.h>
#include <Servo.h>

const int bluetooth_rx = 2; //定义蓝牙串口引脚
const int bluetooth_tx = 4; 

Servo myServo;    // 创建一个 Servo 对象
SoftwareSerial bluetooth(bluetooth_rx, bluetooth_tx);  // 设置软串口，连接蓝牙模块
int trigPin = 13;                // 超声波模块的Trig引脚
int echoPin = 12;                // 超声波模块的Echo引脚
int analog1 = 5; // 定义uno的pin 9 向 analog3 输出
int analog2 = 6; // 定义uno的pin 10 向 analog4 输出
int analog3 = 3; // 定义uno的pin 5 向 analog1 输出
int analog4 = 11; // 定义uno的pin 6 向 analog2 输出
int servoPin = 9;   // 舵机引脚
bool avoidMode = false;         // 是否启用避障模式
int angle = 0;    // 初始角度

void setup() {
  Serial.begin(9600);         // 硬件串口，波特率为9600
  bluetooth.begin(9600);        // 蓝牙模块使用软串口，波特率为9600
  pinMode(servoPin,OUTPUT);
  pinMode(trigPin, OUTPUT);    // 配置超声波模块的Trig引脚为输出模式
  pinMode(echoPin, INPUT);     // 配置超声波模块的Echo引脚为输入模式
  pinMode(analog1,OUTPUT);
  pinMode(analog2,OUTPUT);
  pinMode(analog3,OUTPUT);
  pinMode(analog4,OUTPUT);
  myServo.attach(9);
}

void loop() {
  if (bluetooth.available()) {   // 如果接收到蓝牙数据
    char cmd = bluetooth.read(); // 读取蓝牙数据
    Serial.print("Received: ");
    Serial.println(cmd);
    switch (cmd) {              // 根据接收到的命令进行处理
      case 'F':                // 前进
        forward();
        break;
      case 'B':                // 后退
        backward();
        break;
      case 'L':                // 左转
        leftward();
        break;
      case 'R':                // 右转
        rightward();
        break;
      case 's':                // 停止
        stop();
        break;  
      case 'A':                // 切换避障模式
        avoidMode = true;  // 打开避障模式开关状态
        Serial.print("Mode: ");
        Serial.println(avoidMode);
        break;
      case 'a':                // 切换避障模式
        avoidMode = false;  // 反转避障模式开关状态，实现切换功能
        stop();
        Serial.print("Mode: ");
        Serial.println(avoidMode);
        break;
      default:                 // 未知命令
        stop();
        break;
    }
  }
  if (avoidMode) {              // 如果处于避障模式
    int distance = detectObstacle();  // 检测距离
    Serial.println(distance);
    if (distance < 15) {        // 如果距离小于5cm
      stop(); 
      delay(1000);                  
      int L_distance,R_distance;
      steer(L_distance,R_distance);                  // 使用舵机转向
      if (L_distance > 15 && R_distance > 15){
        if (L_distance > R_distance){
                leftward();
                delay(375);
              }
        else{
          rightward();
          delay(375);
        }
      }
      else{
        leftward();
        delay(1000);
      }
    } 
    else {                    // 否则正常运行
      forward();
    }
  }
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
void rightward() {
  analogWrite(analog1,0);
  analogWrite(analog2,55);
  analogWrite(analog3,55);
  analogWrite(analog4,0);
}
void leftward() {
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

void steer(int& value1, int& value2) {
  for (angle = 90; angle <= 180; angle += 1){  // 逐渐增加角度
  myServo.write(angle);    // 设置舵机位置
  delay(15);               // 等待一段时间
  if (angle == 180){
  value1 = detectObstacle();
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
