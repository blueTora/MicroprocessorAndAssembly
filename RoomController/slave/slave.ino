#include <LiquidCrystal.h>
#include<SPI.h>

LiquidCrystal lcd(13,12, 8, 9, 10, 11);

volatile boolean received;
volatile byte Slavereceived,Slavesend;
volatile byte indx;
char buff[50];
void setup()
{
  Serial.begin(9600);
  Serial.println("sssssss");
  lcd.begin(16, 2);           
  pinMode(MISO,OUTPUT);                    
  digitalWrite(MISO,LOW);
  
  
  SPCR |= _BV(SPE); 
  SPCR |= _BV(SPIE);
  indx = 0;
  received = false;

  SPI.attachInterrupt();                 
  
}

ISR (SPI_STC_vect)                   
{
  byte c= SPDR;
   
// if (indx < sizeof buff) {
//   buff [indx++] = c; 
//   if (c == '\r'){
//    received = true;
//    indx = 0;
//   }
// }
    Slavereceived = SPDR;
    received = true;
}

void loop()
{ if(received)                           
   {
      Serial.println(Slavereceived);
      lcd.clear();  
//      lcd.print(buff); 
      lcd.print(Slavereceived);
   }        
}
