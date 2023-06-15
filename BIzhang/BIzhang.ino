int lh = 11;//马达 b为正，h为负
int lb = 10;
int rh = 9;
int rb = 5; 
int sin1 = 2;//灰度
int sin2 = 3;
int sin3 = 4;
int Echo = 12;
int Trig = 13;
void setup() {
Serial.begin(9600);
pinMode(11,OUTPUT);
pinMode(10,OUTPUT);
pinMode(9,OUTPUT); 
pinMode(5,OUTPUT);
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
}

void go()
{
  analogWrite(11,0);
  analogWrite(10,55);
  analogWrite(9,0);
  analogWrite(5,55);

 
               
}
void around(){        //自转
  
  analogWrite(11,75);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(5,75);

  
  }
void R()//左动
{
  analogWrite(11,55);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(5,85);    

}
void rt(int time)//左动
{
  analogWrite(11,55);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(5,85);    
delay(time*10);
}
void L()//右动
{
 analogWrite(11,0);
  analogWrite(10,85);
  analogWrite(9,55);
  analogWrite(5,0);  
}
void lt(int time)//右动
{
 analogWrite(11,0);
  analogWrite(10,85);
  analogWrite(9,55);
  analogWrite(5,0);  
  delay(time*10);
}
void Stop(int time)//停
{
 analogWrite(11,0);
  analogWrite(10,0);
  analogWrite(9,0);
  analogWrite(5,0);  
 delay(time*10);
}
void loop() {
char rsin1,rsin2,rsin3;
rsin1 = digitalRead(sin1);
rsin2 = digitalRead(sin2);
rsin3 = digitalRead(sin3);
Serial.println(digitalRead(sin3));

if(rsin1==0 && rsin2==1 &&rsin3==0)
{
  go();
  }
else

if(rsin1==0 && rsin2==0 &&rsin3==1){

R();

}
else

if(rsin1==1 && rsin2==0 &&rsin3==0) { 

L();
  
}
if(rsin1==0 && rsin2==1 &&rsin3==1){

  R();
Stop(10);
 rt(10);

}
if(rsin1==1 && rsin2==1 &&rsin3==0) { 

  L();
Stop(10);
lt(10);
}
/*if(rsin1==0 && rsin2==0 &&rsin3==0){
  
  around();
  
  }*