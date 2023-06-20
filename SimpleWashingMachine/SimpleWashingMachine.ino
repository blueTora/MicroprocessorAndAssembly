#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DEVICE_ADDRESS 0b1010000

#define LED_Mode1 49
#define LED_Mode2 50
#define LED_Mode3 51
#define LED_Mode4 52

#define RS_PIN 13
#define EN_PIN 11
#define D4_PIN 6
#define D5_PIN 5
#define D6_PIN 4
#define D7_PIN 3

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

uint8_t data[24];
uint16_t menuItemAddresses[4];
int menuNum = 4;
boolean modeON = false;

void setup() {
  Wire.begin();
  Serial1.begin(9600);
  
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

  pinMode(LED_Mode1, OUTPUT);
  digitalWrite(LED_Mode1, LOW);
  pinMode(LED_Mode2, OUTPUT);
  digitalWrite(LED_Mode2, LOW);
  pinMode(LED_Mode3, OUTPUT);
  digitalWrite(LED_Mode3, LOW);
  pinMode(LED_Mode4, OUTPUT);
  digitalWrite(LED_Mode4, LOW);

  lcd.begin(20,4);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println("Select a Mode to");
  lcd.setCursor(0, 1);
  lcd.println("Start washing:");

  menuItemAddresses[0] = 0;
  menuItemAddresses[1] = 30;
  menuItemAddresses[2] = 60;
  menuItemAddresses[3] = 90;

  writeMenuItem("1. Pre wash             ", 24, menuItemAddresses[0]);
  delay(300);
  writeMenuItem("2. Wash with detergent  ", 24, menuItemAddresses[1]);
  delay(300);
  writeMenuItem("3. Wash with water      ", 24, menuItemAddresses[2]);
  delay(300);
  writeMenuItem("4. dry wash             ", 24, menuItemAddresses[3]);
  delay(300);
  
  menuScreen();
}

long startTime = 0;
int duration = 0;
int selectedMode = 0;

void loop() {
  char code = keypad.getKey();
    
  if(code != NO_KEY){
    if(!modeON){
      if(code == '1'){
        selectedMode = 1;
        digitalWrite(LED_Mode1, HIGH);
        getTime();
      } else if(code == '2'){
        selectedMode = 2;
        digitalWrite(LED_Mode2, HIGH);
        getTime();
      } else if(code == '3'){
        selectedMode = 3;
        digitalWrite(LED_Mode3, HIGH);
        getTime();
      } else if(code == '4'){
        selectedMode = 4;
        digitalWrite(LED_Mode4, HIGH);
        getTime();
      }
    } else if(code == '#') {
      holding();
    }
  }

  if(modeON){
    long milli = millis() - startTime;
      
      if(milli <= duration*1000){
        lcd.setCursor(0,1);
        lcd.print("The Washing Will be");
        lcd.setCursor(0,2);
        lcd.print("Finished in: ");
        lcd.setCursor(0,3);
        lcd.print("       ");
        lcd.print(duration - milli/1000);
        lcd.print("  sec");
        
      } else {
        delay(100);
        finished();
      }
  }
}

void getTime(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Enter washing Time ");
  lcd.setCursor(0,1);
  lcd.print("         ");

  char t[2];
  t[0] = keypad.waitForKey();
  lcd.print(t[0]);
  t[1] = keypad.waitForKey();
  lcd.print(t[1]);
  
  duration = atoi(t);
  Serial1.println(duration);
  delay(400);

  startMenu();
}

void holding(){
  duration -= (millis() - startTime)/1000;
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Washing is on HOLD!!");

  char c;
  do{
    c = keypad.waitForKey();
  }while(c != '#');
  delay(50);

  startTime = millis();
  lcd.clear();
}

void finished(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(" Washing Finished!!");
  lcd.setCursor(0,2);
  lcd.print("  enjoy your clean");
  lcd.setCursor(0,3);
  lcd.print("      clothes :)");

  digitalWrite(LED_Mode1, HIGH);
  digitalWrite(LED_Mode2, HIGH);
  digitalWrite(LED_Mode3, HIGH);
  digitalWrite(LED_Mode4, HIGH);
  
  char c;
  do{
    c = keypad.waitForKey();
  }while(c != '*');
  delay(50);

  digitalWrite(LED_Mode1, LOW);
  digitalWrite(LED_Mode2, LOW);
  digitalWrite(LED_Mode3, LOW);
  digitalWrite(LED_Mode4, LOW);

  modeON = false;
  menuScreen();
}

void menuScreen(){
  lcd.clear();
  lcd.setCursor(0,0);
  uint8_t readData[24];

  for(int i=0 ; i<menuNum ; i++){
    memset(readData, 0, 24);
    readMemory(menuItemAddresses[i], readData, 24);
    
    lcd.setCursor(0, i);
    for(int j=0 ; j<20 ; j++){
      lcd.print((char)readData[j]);
    }
    delay(100);
  }
}

void startMenu(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("do you want to start");
  lcd.setCursor(0,1);
  lcd.print("Washing?");
  lcd.setCursor(0,2);
  lcd.print("1. YES");
  lcd.setCursor(0,3);
  lcd.print("2. NO");

  char yn = keypad.waitForKey();
  delay(100);

  lcd.clear();
  lcd.setCursor(0,0);

  if(yn == '1'){
    lcd.print("WASHING STARTED!!");
    modeON = true;
    startTime = millis();
    
  } else if(yn == '2'){
    lcd.print("WASHING CANCELLED!!");
    lcd.setCursor(0,1);
    lcd.print("Going Back to menu");
    lcd.setCursor(0,2);
    lcd.print("        :(");

    digitalWrite(LED_Mode1, LOW);
    digitalWrite(LED_Mode2, LOW);
    digitalWrite(LED_Mode3, LOW);
    digitalWrite(LED_Mode4, LOW);
    
    delay(1500);
    menuScreen();
  }
}

void writeMenuItem(uint8_t* data, uint8_t n, uint16_t address){
  writeMemory(address, data, n);
  menuItemAddresses[menuNum] = address;
}

void writeMemory(uint16_t m_address, uint8_t* data, uint8_t n){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((m_address & 0xFF00) >> 8));
  Wire.write((uint8_t)(m_address & 0x00FF));

  for(int i=0 ; i<n ; i++)
    Wire.write(data[i]);
  
  Wire.endTransmission();
}

void readMemory(uint16_t m_address, uint8_t* data, uint8_t n){
  Wire.beginTransmission(DEVICE_ADDRESS);
  Wire.write((uint8_t)((m_address & 0xFF00) >> 8));
  Wire.write((uint8_t)(m_address & 0x00FF));
  Wire.endTransmission();

  Wire.requestFrom(DEVICE_ADDRESS, n);
  for(int i=0 ; i<n ; i++)
    data[i] = Wire.read();
}
