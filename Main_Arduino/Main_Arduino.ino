#include <SoftwareSerial.h>
#include <Servo.h>

const int bluetooth_rx = 12; //定义蓝牙串口引脚
const int bluetooth_tx = 13;

SoftwareSerial bluetooth(bluetooth_rx, bluetooth_tx);  // 设置软串口，连接蓝牙模块
int trigPin = 4;                // 超声波模块的Trig引脚
int echoPin = 3;                // 超声波模块的Echo引脚
Servo steering;                 // 舵机对象
int input1 = 5; // 定义uno的pin 5 向 input1 输出
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 9; // 定义uno的pin 9 向 input3 输出
int input4 = 10; // 定义uno的pin 10 向 input4 输出
bool avoidMode = false;         // 是否启用避障模式

void setup() {
  Serial.begin(9600);         // 硬件串口，波特率为9600
  bluetooth.begin(9600);        // 蓝牙模块使用软串口，波特率为9600
  pinMode(trigPin, OUTPUT);    // 配置超声波模块的Trig引脚为输出模式
  pinMode(echoPin, INPUT);     // 配置超声波模块的Echo引脚为输入模式
  steering.attach(11);          // 连接舵机控制引脚
pinMode(input1,OUTPUT);
pinMode(input2,OUTPUT);
pinMode(input3,OUTPUT);
pinMode(input4,OUTPUT);
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
        avoidMode = !avoidMode;  // 打开避障模式开关状态
        break;
      case 'a':                // 切换避障模式
        avoidMode = !avoidMode;  // 反转避障模式开关状态，实现切换功能
        break;
      default:                 // 未知命令
        stop();
        break;
    }
  }
  if (avoidMode) {              // 如果处于避障模式
    int distance = detectObstacle();  // 检测距离
    if (distance < 5) {        // 如果距离小于5cm
      stop();                   // 停止
      steer();                  // 使用舵机转向
      rightward();
      delay(500);
    } else {                    // 否则正常运行
      forward();
    }
  }
}

int detectObstacle() {
  digitalWrite(trigPin, LOW);     // 准备发射超声波信号
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);    // 发射超声波信号
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  int duration = pulseIn(echoPin, HIGH);  // 计算超声波信号往返时间
  return duration / 58;           // 计算距离（单位：厘米）
}

void forward() {
  analogWrite(input1,55);
  analogWrite(input2,0);
  analogWrite(input3,0);
  analogWrite(input4,55);
}

void backward() {
  analogWrite(input1,0);
  analogWrite(input2,55);
  analogWrite(input3,55);
  analogWrite(input4,0);
}

void leftward() {
  analogWrite(input1,55);
  analogWrite(input2,0);
  analogWrite(input3,55);
  analogWrite(input4,0);
}

void rightward() {
  analogWrite(input1,0);
  analogWrite(input2,55);
  analogWrite(input3,0);
  analogWrite(input4,55);
}

void stop() {
  analogWrite(input1,0);
  analogWrite(input2,0);
  analogWrite(input3,0);
  analogWrite(input4,0);
}

void steer() {
  steering.write(90);  // 转向舵机至中间位置
  delay(1000);         // 延时1秒等待舵机运动完成
  steering.write(0);   // 转向舵机至左侧极限位置
  delay(1000);         // 延时1秒等待舵机运动完成
  steering.write(155); // 转向舵机至右侧极限位置
  delay(1000);         // 延时1秒等待舵机运动完成
  steering.write(90);  // 转向舵机至中间位置
}
