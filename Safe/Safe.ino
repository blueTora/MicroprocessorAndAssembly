#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;

#define CLOSE_LED 21
#define OPEN_LED 17
#define BEEP 53

#define RS_PIN 12
#define EN_PIN 10
#define D4_PIN 5
#define D5_PIN 4
#define D6_PIN 3
#define D7_PIN 2

LiquidCrystal lcd(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={32, 33, 34, 35};
byte colPins[cols]={24, 23, 22};

Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);

char password[] = {'1','2','3','4'};
boolean doorOpen = false;
long openTime = 0;
const int closeTime = 5;
int currentPos = 0;
int pos=0;
boolean changePass = false;
char code;
 
void setup(){
  Serial.begin(9600);

  pinMode(CLOSE_LED, OUTPUT);
  digitalWrite(CLOSE_LED, HIGH);
  pinMode(OPEN_LED, OUTPUT);
  digitalWrite(OPEN_LED, LOW);
  pinMode(BEEP, OUTPUT);
  digitalWrite(BEEP, LOW);

  pinMode(32, OUTPUT);
  digitalWrite(32, HIGH);
  pinMode(33, OUTPUT);
  digitalWrite(33, HIGH);
  pinMode(34, OUTPUT);
  digitalWrite(34, HIGH);
  pinMode(35, OUTPUT);
  digitalWrite(35, HIGH);

  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  pinMode(24, INPUT_PULLUP);

  myservo.attach(46);
 
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);

  myservo.writeMicroseconds(1000);

  displayScreen();
}
 
void loop(){

  int l ;
  code = keypad.getKey();
    
  if(code != NO_KEY){
  
      if(code == '#'){
        changePass = true;
        code = NO_KEY;
        lcd.setCursor(0,0);
        lcd.println(" Enter old Pass ");
        
      } if(code == '*' && doorOpen){
          closeDoor();
          code = NO_KEY;
          
      } else if(!doorOpen && code != NO_KEY) {
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("PASSWORD:");
        lcd.setCursor(7,1);
        lcd.print(" ");
        lcd.setCursor(7,1);    
          
        for(l=0 ; l<=currentPos ; ++l){
          lcd.print("*");
        }

        
        if (code == password[currentPos]){
          ++currentPos;
          if(currentPos == 4){
            delay(800);
            
            if(changePass){
              changingPassword();
            } else {
              openDoor();
            }
            
            currentPos = 0;
          }
          
        } else {
          incorrectPass();
          currentPos = 0;
        }
        
      }
   }else if(doorOpen){
        
      long milli = millis() - openTime;
      
      if(milli <= closeTime*1000){
        lcd.setCursor(0,0);
        lcd.print("The Door Will be");
        lcd.setCursor(0,1);
        lcd.print("Closed in: ");
        lcd.print(closeTime - milli/1000);
        lcd.print(" sec");
        
      } else {
        closeDoor();
      }
   }
   
}
 
void incorrectPass()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("CODE INCORRECT!!");
  delay(2000);
  
  lcd.setCursor(0,0);
  lcd.print("    Try Again   ");
  delay(1000);
   
  displayScreen();
}

void changingPassword(){

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Enter New Pass: ");
  lcd.setCursor(0,1);
  lcd.print("      ");

  password[0] = keypad.waitForKey();
  lcd.print(password[0]);
  
  password[1] = keypad.waitForKey();
  lcd.print(password[1]);
  
  password[2] = keypad.waitForKey();
  lcd.print(password[2]);
  
  password[3] = keypad.waitForKey();
  lcd.print(password[3]);
  delay(800);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Password Changed");
  delay(2000);

  changePass = false;
  displayScreen();
}

void displayScreen(){
  lcd.setCursor(0,0);
  lcd.println(" Enter the Pass ");
}

void openDoor()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Access Granted ");
  delay(1500);
  lcd.clear();
  lcd.print("    WELCOME!!   ");
  delay(1000);
  buzzer();
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" The Safe Door  ");
  lcd.setCursor(0,1);
  lcd.print("     Opens      ");

  digitalWrite(CLOSE_LED, LOW);
  digitalWrite(OPEN_LED, HIGH);
  
  for (pos = 0; pos <= 180; pos += 1) {
    int deg = map(pos, 0, 180, 1000, 2000);
    myservo.writeMicroseconds(deg);
    delay(15);                       
  }

  doorOpen = true;
  openTime = millis();
}

void closeDoor()
{
  doorOpen = false;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" The Safe Door  ");
  lcd.setCursor(0,1);
  lcd.print("     Closes     ");

  buzzer();
  digitalWrite(CLOSE_LED, HIGH);
  digitalWrite(OPEN_LED, LOW);
  
  for (pos = 180; pos >= 0; pos -= 1) {
    int deg = map(pos, 0, 180, 1000, 2000);
    myservo.writeMicroseconds(deg);
    delay(15);                       
  }

  currentPos = 0;
  lcd.clear();
  displayScreen();
}

void buzzer(){
  tone(BEEP, 1000);
  delay(1000);
  noTone(BEEP);
}
