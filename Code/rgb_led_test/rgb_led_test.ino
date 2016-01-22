

/*
@Author: TONYLABS
@Date: 2012/11/03
@Function: Power RGB LED
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop()
{
  setColor(255, 0, 0);  // 红色
  delay(500);
  setColor(0, 255, 0);  // 绿色
  delay(500);
  setColor(0, 0, 255);  // 蓝色
  delay(500);
  setColor(255, 255, 0);  // 黄色
  delay(500);  
  setColor(255, 0, 255);  // 紫色
  delay(500);
  setColor(0, 255, 255);  // 浅绿色
  delay(500);
  setColor(255, 255, 0);  
  delay(50000);
  setColor(0, 0, 0); 
  delay(500);
}

void setColor(int red, int green, int blue)
{
  analogWrite(redPin, 255-red);
  analogWrite(greenPin, 255-green);
  analogWrite(bluePin, 255-blue);  
}

 
