
#include <SoftwareSerial.h>



// 定义蓝牙模块的RX和TX引脚

const int bluetooth_rx = 12;

const int bluetooth_tx = 13;



// 创建一个软件串口对象，用于与蓝牙模块通信

SoftwareSerial bluetooth(bluetooth_rx, bluetooth_tx);



void setup() {

  // 初始化硬件串口和蓝牙模块

  Serial.begin(9600);

  bluetooth.begin(9600);

}



void loop() {

  // 从蓝牙模块读取数据

  if (bluetooth.available()) {

    char c = bluetooth.read();

    Serial.print("Received: ");

    Serial.println(c);
  
  }

  // 将数据发送到蓝牙模块

  if (Serial.available()) {

    char c = Serial.read();

    bluetooth.write(c);

  }

}

