#include<SPI.h>                            
#define SS1 4
#define SS2 5               

uint8_t temp,light;
int sensor1Value,sensor2Value;

void setup (void)
{
  Serial.begin(9600);            
  
  pinMode(SS1,OUTPUT);           
  pinMode(SS2,OUTPUT); 
  digitalWrite(SS1,HIGH);
  digitalWrite(SS2,HIGH);
  SPI.begin();                   
  SPI.setClockDivider(SPI_CLOCK_DIV8);
}

void loop(void)
{
  char c;
  sensor1Value = analogRead(A0);
  light = map(sensor1Value, 0, 684, 0, 101);
  sensor2Value = analogRead(A1);
  temp = map(sensor2Value, 0, 1023, 0, 500); 
  digitalWrite(SS1, LOW); 
  delay(50);

//  const char * p = "Negar\r"
//  for (const char * p = "Hi\r" ; c = *p; p++)
// {
//   SPI.transfer (c);
//   Serial.print(c);
// } 
//  delay(600);
 
  SPI.transfer (light);
  digitalWrite(SS1, HIGH);
  delay(50);
  
  digitalWrite(SS2, LOW); 
  delay(50);
  

  Serial.println("master");                            
  Serial.println(temp);
  SPI.transfer(temp);

//  const char * p = "9722039\r";
//  for (const char * p = "Hello world\r" ; c = *p; p++)
//  {
//     SPI.transfer (c);
//     Serial.print(c);
//  }
  digitalWrite(SS2, HIGH);
  delay(50);
}
