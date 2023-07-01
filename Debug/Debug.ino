#include <Servo.h>

int input1 = 3; // 定义uno的pin 5 向 input1 输出
int input2 = 11; // 定义uno的pin 6 向 input2 输出
int input3 = 5; // 定义uno的pin 9 向 input3 输出
int input4 = 6; // 定义uno的pin 10 向 input4 输出
// int servoPin = 11;   // 舵机引脚
Servo myServo;    // 创建一个 Servo 对象
int angle = 0;    // 初始角度
bool avodiMode = false;

void setup() {
  Serial.begin(9600);
  pinMode(input1,OUTPUT);
  pinMode(input2,OUTPUT);
  pinMode(input3,OUTPUT);
  pinMode(input4,OUTPUT);
  myServo.attach(9);    // 将 Servo 对象与数字引脚 9 关联
  // pinMode(servoPin,OUTPUT);
}

void loop() {
    // back();
    // delay(1000);
    // stop();
    // delay(1000);
    // forward();
    // delay(1000);

  if(avodiMode)
    {
      for (angle = 0; angle <= 180; angle += 1)
        {  // 逐渐增加角度
          myServo.write(angle);    // 设置舵机位置
          delay(15);               // 等待一段时间
        }
      for (angle = 180; angle >= 0; angle -= 1) 
      {  // 逐渐减小角度
      myServo.write(angle);    // 设置舵机位置
      delay(15);               // 等待一段时间
    }
      avodiMode = false;
    }
  else{
    back();
    delay(1000);
    stop();
    delay(1000);
    forward();
    delay(1000);
    stop();
    delay(1000);
    avodiMode = true;
  }
}

void forward() {
  analogWrite(input1,55);
  analogWrite(input2,0);
  analogWrite(input3,55);
  analogWrite(input4,0);
}
void back() {
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

///////////////////////////////////////////////////////////////////////////////////

// int input1 = 3;  // 模拟输出引脚
// int input2 = 9;  // 模拟输出引脚
// int input3 = 5;  // 模拟输出引脚
// int input4 = 6;  // 模拟输出引脚

// void setup() {
//   // 将引脚模式设置为输出
//   pinMode(input1, OUTPUT);
//   pinMode(input2, OUTPUT);
//   pinMode(input3, OUTPUT);
//   pinMode(input4, OUTPUT);
// }

// void loop() {
//   back();
//   delay(1000);
//   stop();
//   delay(1000);
//   forward();
//   delay(1000);
// }

// void forward() {
//   analogWrite(input1,0);
//   analogWrite(input2,55); 
//   analogWrite(input3,0);
//   analogWrite(input4,55); 
// }
// void back() {
//   analogWrite(input1,55);
//   analogWrite(input2,0);
//   analogWrite(input3,55);
//   analogWrite(input4,0); 
// }
// void stop() {
//   analogWrite(input1,0);
//   analogWrite(input2,0);
//   analogWrite(input3,0);
//   analogWrite(input4,0); 
// }


