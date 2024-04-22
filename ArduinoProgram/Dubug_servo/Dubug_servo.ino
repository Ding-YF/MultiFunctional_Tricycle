#include <Servo.h>

Servo myServo;    // 创建一个 Servo 对象
int angle = 0;    // 初始角度

void setup() {
  myServo.attach(11);    // 将 Servo 对象与数字引脚 9 关联
}

void loop() {
  // myServo.write(0); 
  for (angle = 0; angle <= 180; angle += 1) {  // 逐渐增加角度
    myServo.write(angle);    // 设置舵机位置
    delay(15);               // 等待一段时间
  }

  for (angle = 180; angle >= 0; angle -= 1) {  // 逐渐减小角度
    myServo.write(angle);    // 设置舵机位置
    delay(15);               // 等待一段时间
  }
}
