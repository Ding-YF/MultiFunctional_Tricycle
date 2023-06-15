//LingShun Lab
 
int input1 = 5; // 定义uno的pin 5 向 input1 输出 
int input2 = 6; // 定义uno的pin 6 向 input2 输出
int input3 = 9; // 定义uno的pin 9 向 input3 输出
int input4 = 10; // 定义uno的pin 10 向 input4 输出
 
 
 
void setup() {
Serial.begin (9600);
//初始化各IO,模式为OUTPUT 输出模式
pinMode(input1,OUTPUT);
pinMode(input2,OUTPUT);
pinMode(input3,OUTPUT); 
pinMode(input4,OUTPUT);
 
}

void go(int time)
{
  analogWrite(input1,55);
  analogWrite(input2,0);
  analogWrite(input3,0);
  analogWrite(input4,55);
  delay(time*100);            
}
void stop(int time)//停
{
  analogWrite(input1,0);
  analogWrite(input2,0);
  analogWrite(input3,0);
  analogWrite(input4,0);
  delay(time*100);  
}
void back(int time)
{
  analogWrite(input1,0);
  analogWrite(input2,55);
  analogWrite(input3,55);
  analogWrite(input4,0);
  delay(time*100);            
}
 
void loop() {
  go(10); 
  stop(5); 
  back(10); 
}