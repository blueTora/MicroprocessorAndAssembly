#include <Keypad.h>
#include <Adafruit_NeoPixel.h>

#define PIN 53

#define NUMPIXELS 256
const int X = 15;
const int Y = 15;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL1 60
#define DELAYVAL2 120
#define DELAYVAL3 110

int r = 0, g = 0, b = 25;

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

void setup() {  
  pixels.begin();

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

  keypad.addEventListener(keypadEvent);
}

const String animations = "123";
char anime = 'e';

void loop() {
  char k = keypad.getKey();
  
  pixels.clear();
  pixels.show();
  
  if (anime != 'e'){          
    switch(anime){
      case '1':
        anime = 'e';
        showName();
        break;
        
      case '2':
        anime = 'e';
        showWalkingMan();
        break;
        
      case '3':
        anime = 'e';
        showBalls();
        break;
    }
  }
}

void keypadEvent(KeypadEvent key){
  switch (keypad.getState()){
    case PRESSED:
      if (animations.indexOf(key) > -1)
          anime = key;
  }
}

void showBalls(){
  int time = 70;
  while(time > 0){
    pixels.clear();

    moveRedBall();
    moveGreenBall();
    moveBlueBall();
    
    pixels.show();
    delay(DELAYVAL1);
    time -= 1;
  }
}

void mapLEDXY(int x, int y, int RED, int  GREEN, int BLUE) {
  int RGBlocation = 0;

  if (y % 2 == 0) { //even column
    RGBlocation = x + y * 16;

  } else { //odd column
    RGBlocation =  x + y * 16;
  }

  pixels.setPixelColor(RGBlocation, RED * 10, GREEN * 10 ,BLUE * 10);
}

void moveBlueBall(){
    static bool negativeX = false, negativeY = false, next = false;
    static int i = 0, j = 0;
    
    mapLEDXY(0 + i,2 + j,0,0,25);mapLEDXY(1 + i,1 + j,0,0,25);mapLEDXY(1 + i,2 + j,0,0,25);mapLEDXY(1 + i,3 + j,0,0,25);mapLEDXY(2 + i,0 + j,0,0,25);mapLEDXY(2 + i,1 + j,0,0,25);mapLEDXY(2 + i,2 + j,0,0,25);mapLEDXY(2 + i,3 + j,0,0,25);mapLEDXY(2 + i,4 + j,0,0,25);mapLEDXY(3 + i,1 + j,0,0,25);mapLEDXY(3 + i,2 + j,0,0,25);mapLEDXY(3 + i,3 + j,0,0,25);mapLEDXY(4 + i,2 + j,0,0,25);                    

    if(4 + j >= Y)
      negativeY = true;
    else if(j <= 0)
      negativeY = false;

    if(4 + i >= X)
      negativeX = true;
    else if(i <= 0)
      negativeX = false;

    if(next){
      if(negativeX)
        i -= 1;
      else
        i++;

      next = false;
    } else
        next = true;

    if(negativeY)
      j -= 1;
    else
      j++;
}

void moveRedBall(){
    static bool negativeX = false, negativeY = false, next = false;
    static int i = 1, j = 0;
    
    mapLEDXY(9 + i,3 + j,25,0,0);mapLEDXY(10 + i,2 + j,25,0,0);mapLEDXY(10 + i,3 + j,25,0,0);mapLEDXY(10 + i,4 + j,25,0,0);mapLEDXY(11 + i,1 + j,25,0,0);mapLEDXY(11 + i,2 + j,25,0,0);mapLEDXY(11 + i,3 + j,25,0,0);mapLEDXY(11 + i,4 + j,25,0,0);mapLEDXY(11 + i,5 + j,25,0,0);mapLEDXY(12 + i,2 + j,25,0,0);mapLEDXY(12 + i,3 + j,25,0,0);mapLEDXY(12 + i,4 + j,25,0,0);mapLEDXY(13 + i,3 + j,25,0,0);                    

    if(5 + j >= Y)
      negativeY = true;
    else if(j + 1 <= 0)
      negativeY = false;

    if(13 + i >= X)
      negativeX = true;
    else if(i + 9 <= 0)
      negativeX = false;

    if(next){
      if(negativeY)
        j -= 1;
      else
        j++;

      next = false;
    } else
        next = true;

    if(negativeX)
      i -= 1;
    else
      i++;
}

void moveGreenBall(){
    static bool negativeX = false, negativeY = false, next = false;
    static int i = 0, j = 0;
    
    mapLEDXY(6 + i,8 + j,0,25,0);mapLEDXY(7 + i,7 + j,0,25,0);mapLEDXY(7 + i,8 + j,0,25,0);mapLEDXY(7 + i,9 + j,0,25,0);mapLEDXY(8 + i,6 + j,0,25,0);mapLEDXY(8 + i,7 + j,0,25,0);mapLEDXY(8 + i,8 + j,0,25,0);mapLEDXY(8 + i,9 + j,0,25,0);mapLEDXY(8 + i,10 + j,0,25,0);mapLEDXY(9 + i,7 + j,0,25,0);mapLEDXY(9 + i,8 + j,0,25,0);mapLEDXY(9 + i,9 + j,0,25,0);mapLEDXY(10 + i,8 + j,0,25,0);                    

    if(10 + j >= Y)
      negativeY = true;
    else if(j + 6 <= 0)
      negativeY = false;

    if(10 + i >= X)
      negativeX = true;
    else if(i + 6 <= 0)
      negativeX = false;

    if(next){
      if(negativeX)
        i -= 1;
      else
        i++;

      next = false;
    } else
        next = true;

    if(negativeY)
      j -= 1;
    else
      j++;
}

void updateColors(){
  r += 5;
  g += 10;
  b++;

  if(r > 25)
    r = 0;
  if(g > 25)
    g = 0;
  if(b > 25)
    b = 0;
}

void showName() {
  
  pixels.clear();
  mapLEDXY(4,0,r,g,b);mapLEDXY(4,1,r,g,b);mapLEDXY(9,0,r,g,b);mapLEDXY(10,0,r,g,b);mapLEDXY(10,1,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,0,r,g,b);mapLEDXY(4,1,r,g,b);mapLEDXY(4,2,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(7,0,r,g,b);mapLEDXY(8,0,r,g,b);mapLEDXY(8,1,r,g,b);mapLEDXY(9,1,r,g,b);mapLEDXY(9,2,r,g,b);mapLEDXY(10,0,r,g,b);mapLEDXY(10,1,r,g,b);mapLEDXY(10,2,r,g,b);mapLEDXY(10,3,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,0,r,g,b);mapLEDXY(4,1,r,g,b);mapLEDXY(4,2,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,4,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(6,0,r,g,b);mapLEDXY(6,1,r,g,b);mapLEDXY(7,1,r,g,b);mapLEDXY(7,2,r,g,b);mapLEDXY(8,2,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(9,3,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(10,0,r,g,b);mapLEDXY(10,1,r,g,b);mapLEDXY(10,2,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);
  
  pixels.clear();
  mapLEDXY(4,0,r,g,b);mapLEDXY(4,1,r,g,b);mapLEDXY(4,2,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,4,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(6,1,r,g,b);mapLEDXY(6,2,r,g,b);mapLEDXY(7,2,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,4,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(9,5,r,g,b);mapLEDXY(10,0,r,g,b);mapLEDXY(10,1,r,g,b);mapLEDXY(10,2,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,1,r,g,b);mapLEDXY(4,2,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,4,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(6,2,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,4,r,g,b);mapLEDXY(8,4,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(9,5,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(10,1,r,g,b);mapLEDXY(10,2,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(10,7,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,2,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,4,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,4,r,g,b);mapLEDXY(7,4,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(10,2,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,3,r,g,b);mapLEDXY(4,4,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(6,4,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,6,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);mapLEDXY(10,9,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(6,6,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,8,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,10,r,g,b);mapLEDXY(10,11,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(4,13,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(6,8,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,10,r,g,b);mapLEDXY(10,11,r,g,b);mapLEDXY(10,12,r,g,b);mapLEDXY(10,13,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(4,13,r,g,b);mapLEDXY(4,14,r,g,b);mapLEDXY(4,15,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,10,r,g,b);mapLEDXY(10,11,r,g,b);mapLEDXY(10,12,r,g,b);mapLEDXY(10,13,r,g,b);mapLEDXY(10,14,r,g,b);mapLEDXY(10,15,r,g,b);mapLEDXY(15,9,r,g,b);mapLEDXY(15,10,r,g,b);mapLEDXY(15,11,r,g,b);mapLEDXY(15,12,r,g,b);mapLEDXY(15,13,r,g,b);mapLEDXY(15,14,r,g,b);mapLEDXY(15,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(3,9,r,g,b);mapLEDXY(3,10,r,g,b);mapLEDXY(3,11,r,g,b);mapLEDXY(3,12,r,g,b);mapLEDXY(3,13,r,g,b);mapLEDXY(3,14,r,g,b);mapLEDXY(3,15,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(8,14,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(14,9,r,g,b);mapLEDXY(14,10,r,g,b);mapLEDXY(14,11,r,g,b);mapLEDXY(14,12,r,g,b);mapLEDXY(14,13,r,g,b);mapLEDXY(14,14,r,g,b);mapLEDXY(14,15,r,g,b);mapLEDXY(15,9,r,g,b);mapLEDXY(15,12,r,g,b);mapLEDXY(15,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(2,9,r,g,b);mapLEDXY(2,10,r,g,b);mapLEDXY(2,11,r,g,b);mapLEDXY(2,12,r,g,b);mapLEDXY(2,13,r,g,b);mapLEDXY(2,14,r,g,b);mapLEDXY(2,15,r,g,b);mapLEDXY(3,9,r,g,b);mapLEDXY(3,10,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(7,14,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(8,14,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(13,9,r,g,b);mapLEDXY(13,10,r,g,b);mapLEDXY(13,11,r,g,b);mapLEDXY(13,12,r,g,b);mapLEDXY(13,13,r,g,b);mapLEDXY(13,14,r,g,b);mapLEDXY(13,15,r,g,b);mapLEDXY(14,9,r,g,b);mapLEDXY(14,12,r,g,b);mapLEDXY(14,15,r,g,b);mapLEDXY(15,9,r,g,b);mapLEDXY(15,12,r,g,b);mapLEDXY(15,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,9,r,g,b);mapLEDXY(0,10,r,g,b);mapLEDXY(0,11,r,g,b);mapLEDXY(0,12,r,g,b);mapLEDXY(0,13,r,g,b);mapLEDXY(0,14,r,g,b);mapLEDXY(0,15,r,g,b);mapLEDXY(1,9,r,g,b);mapLEDXY(1,10,r,g,b);mapLEDXY(2,10,r,g,b);mapLEDXY(2,11,r,g,b);mapLEDXY(3,11,r,g,b);mapLEDXY(3,12,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(4,13,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(6,14,r,g,b);mapLEDXY(6,15,r,g,b);mapLEDXY(11,9,r,g,b);mapLEDXY(11,10,r,g,b);mapLEDXY(11,11,r,g,b);mapLEDXY(11,12,r,g,b);mapLEDXY(11,13,r,g,b);mapLEDXY(11,14,r,g,b);mapLEDXY(11,15,r,g,b);mapLEDXY(12,9,r,g,b);mapLEDXY(12,12,r,g,b);mapLEDXY(12,15,r,g,b);mapLEDXY(13,9,r,g,b);mapLEDXY(13,12,r,g,b);mapLEDXY(13,15,r,g,b);mapLEDXY(14,9,r,g,b);mapLEDXY(14,12,r,g,b);mapLEDXY(14,15,r,g,b);mapLEDXY(15,9,r,g,b);mapLEDXY(15,12,r,g,b);mapLEDXY(15,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,10,r,g,b);mapLEDXY(0,11,r,g,b);mapLEDXY(1,11,r,g,b);mapLEDXY(1,12,r,g,b);mapLEDXY(2,12,r,g,b);mapLEDXY(2,13,r,g,b);mapLEDXY(3,13,r,g,b);mapLEDXY(3,14,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(4,13,r,g,b);mapLEDXY(4,14,r,g,b);mapLEDXY(4,15,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,12,r,g,b);mapLEDXY(10,15,r,g,b);mapLEDXY(11,9,r,g,b);mapLEDXY(11,12,r,g,b);mapLEDXY(11,15,r,g,b);mapLEDXY(12,9,r,g,b);mapLEDXY(12,12,r,g,b);mapLEDXY(12,15,r,g,b);mapLEDXY(13,9,r,g,b);mapLEDXY(13,12,r,g,b);mapLEDXY(13,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,12,r,g,b);mapLEDXY(0,13,r,g,b);mapLEDXY(1,13,r,g,b);mapLEDXY(1,14,r,g,b);mapLEDXY(2,9,r,g,b);mapLEDXY(2,10,r,g,b);mapLEDXY(2,11,r,g,b);mapLEDXY(2,12,r,g,b);mapLEDXY(2,13,r,g,b);mapLEDXY(2,14,r,g,b);mapLEDXY(2,15,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(7,14,r,g,b);mapLEDXY(7,15,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,12,r,g,b);mapLEDXY(10,15,r,g,b);mapLEDXY(11,9,r,g,b);mapLEDXY(11,12,r,g,b);mapLEDXY(11,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,9,r,g,b);mapLEDXY(0,10,r,g,b);mapLEDXY(0,11,r,g,b);mapLEDXY(0,12,r,g,b);mapLEDXY(0,13,r,g,b);mapLEDXY(0,14,r,g,b);mapLEDXY(0,15,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(6,15,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(7,15,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(6,15,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(7,15,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,13,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,15,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,8,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,8,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(9,5,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(10,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,13,r,g,b);mapLEDXY(4,14,r,g,b);mapLEDXY(4,15,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,6,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,6,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(9,3,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,13,r,g,b);mapLEDXY(10,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,11,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(4,13,r,g,b);mapLEDXY(4,14,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,1,r,g,b);mapLEDXY(6,4,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,15,r,g,b);mapLEDXY(7,1,r,g,b);mapLEDXY(7,4,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(8,1,r,g,b);mapLEDXY(8,4,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(9,1,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,11,r,g,b);mapLEDXY(10,13,r,g,b);mapLEDXY(10,14,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(4,11,r,g,b);mapLEDXY(4,12,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(6,2,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(7,2,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,14,r,g,b);mapLEDXY(8,2,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,14,r,g,b);mapLEDXY(9,2,r,g,b);mapLEDXY(9,5,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,11,r,g,b);mapLEDXY(10,12,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(6,0,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(7,0,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(8,0,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(9,0,r,g,b);mapLEDXY(9,3,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(10,10,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(4,5,r,g,b);mapLEDXY(4,6,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(6,1,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(7,1,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(8,1,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(9,1,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);mapLEDXY(14,4,r,g,b);mapLEDXY(14,5,r,g,b);mapLEDXY(14,6,r,g,b);mapLEDXY(14,7,r,g,b);mapLEDXY(14,8,r,g,b);mapLEDXY(14,9,r,g,b);mapLEDXY(15,3,r,g,b);mapLEDXY(15,6,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(2,5,r,g,b);mapLEDXY(2,6,r,g,b);mapLEDXY(2,7,r,g,b);mapLEDXY(2,8,r,g,b);mapLEDXY(3,4,r,g,b);mapLEDXY(3,9,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,9,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(7,4,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(12,4,r,g,b);mapLEDXY(12,5,r,g,b);mapLEDXY(12,6,r,g,b);mapLEDXY(12,7,r,g,b);mapLEDXY(12,8,r,g,b);mapLEDXY(12,9,r,g,b);mapLEDXY(13,3,r,g,b);mapLEDXY(13,6,r,g,b);mapLEDXY(14,3,r,g,b);mapLEDXY(14,6,r,g,b);mapLEDXY(15,3,r,g,b);mapLEDXY(15,6,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,5,r,g,b);mapLEDXY(0,6,r,g,b);mapLEDXY(0,7,r,g,b);mapLEDXY(0,8,r,g,b);mapLEDXY(1,4,r,g,b);mapLEDXY(1,9,r,g,b);mapLEDXY(2,3,r,g,b);mapLEDXY(2,9,r,g,b);mapLEDXY(3,3,r,g,b);mapLEDXY(3,10,r,g,b);mapLEDXY(4,3,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,10,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,8,r,g,b);mapLEDXY(10,4,r,g,b);mapLEDXY(10,5,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(10,7,r,g,b);mapLEDXY(10,8,r,g,b);mapLEDXY(10,9,r,g,b);mapLEDXY(11,3,r,g,b);mapLEDXY(11,6,r,g,b);mapLEDXY(12,3,r,g,b);mapLEDXY(12,6,r,g,b);mapLEDXY(13,3,r,g,b);mapLEDXY(13,6,r,g,b);mapLEDXY(14,4,r,g,b);mapLEDXY(14,5,r,g,b);mapLEDXY(14,6,r,g,b);mapLEDXY(14,7,r,g,b);mapLEDXY(14,8,r,g,b);mapLEDXY(14,9,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,3,r,g,b);mapLEDXY(0,9,r,g,b);mapLEDXY(1,3,r,g,b);mapLEDXY(1,10,r,g,b);mapLEDXY(2,3,r,g,b);mapLEDXY(2,7,r,g,b);mapLEDXY(2,10,r,g,b);mapLEDXY(3,4,r,g,b);mapLEDXY(3,7,r,g,b);mapLEDXY(3,9,r,g,b);mapLEDXY(4,5,r,g,b);mapLEDXY(4,7,r,g,b);mapLEDXY(4,8,r,g,b);mapLEDXY(8,4,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(9,3,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(10,3,r,g,b);mapLEDXY(10,6,r,g,b);mapLEDXY(11,3,r,g,b);mapLEDXY(11,6,r,g,b);mapLEDXY(12,4,r,g,b);mapLEDXY(12,5,r,g,b);mapLEDXY(12,6,r,g,b);mapLEDXY(12,7,r,g,b);mapLEDXY(12,8,r,g,b);mapLEDXY(12,9,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,3,r,g,b);mapLEDXY(0,7,r,g,b);mapLEDXY(0,10,r,g,b);mapLEDXY(1,4,r,g,b);mapLEDXY(1,7,r,g,b);mapLEDXY(1,9,r,g,b);mapLEDXY(2,5,r,g,b);mapLEDXY(2,7,r,g,b);mapLEDXY(2,8,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,6,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,6,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(9,5,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,9,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(0,7,r,g,b);mapLEDXY(0,9,r,g,b);mapLEDXY(0,10,r,g,b);mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,8,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,8,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(9,0,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,7,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(10,1,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(6,0,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(7,0,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(8,1,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(9,2,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,9,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(10,3,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,0,r,g,b);mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,2,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(7,2,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(8,0,r,g,b);mapLEDXY(8,1,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(9,4,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(9,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,5,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,1,r,g,b);mapLEDXY(5,2,r,g,b);mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,1,r,g,b);mapLEDXY(6,4,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(6,14,r,g,b);mapLEDXY(7,1,r,g,b);mapLEDXY(7,4,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(7,14,r,g,b);mapLEDXY(8,2,r,g,b);mapLEDXY(8,3,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,14,r,g,b);mapLEDXY(9,6,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(9,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,7,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,3,r,g,b);mapLEDXY(5,4,r,g,b);mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,3,r,g,b);mapLEDXY(6,6,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(7,3,r,g,b);mapLEDXY(7,6,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(8,4,r,g,b);mapLEDXY(8,5,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(9,8,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(9,15,r,g,b);mapLEDXY(10,9,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,5,r,g,b);mapLEDXY(5,6,r,g,b);mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(6,5,r,g,b);mapLEDXY(6,8,r,g,b);mapLEDXY(6,15,r,g,b);mapLEDXY(7,5,r,g,b);mapLEDXY(7,8,r,g,b);mapLEDXY(7,15,r,g,b);mapLEDXY(8,6,r,g,b);mapLEDXY(8,7,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,15,r,g,b);mapLEDXY(9,10,r,g,b);mapLEDXY(10,11,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,7,r,g,b);mapLEDXY(5,8,r,g,b);mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(6,7,r,g,b);mapLEDXY(6,10,r,g,b);mapLEDXY(7,7,r,g,b);mapLEDXY(7,10,r,g,b);mapLEDXY(8,8,r,g,b);mapLEDXY(8,9,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(9,12,r,g,b);mapLEDXY(10,13,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,9,r,g,b);mapLEDXY(5,10,r,g,b);mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,9,r,g,b);mapLEDXY(6,12,r,g,b);mapLEDXY(7,9,r,g,b);mapLEDXY(7,12,r,g,b);mapLEDXY(8,10,r,g,b);mapLEDXY(8,11,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(9,14,r,g,b);mapLEDXY(10,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,11,r,g,b);mapLEDXY(5,12,r,g,b);mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,11,r,g,b);mapLEDXY(6,14,r,g,b);mapLEDXY(7,11,r,g,b);mapLEDXY(7,14,r,g,b);mapLEDXY(8,12,r,g,b);mapLEDXY(8,13,r,g,b);mapLEDXY(8,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
  mapLEDXY(5,13,r,g,b);mapLEDXY(5,14,r,g,b);mapLEDXY(5,15,r,g,b);mapLEDXY(6,13,r,g,b);mapLEDXY(7,13,r,g,b);mapLEDXY(8,14,r,g,b);mapLEDXY(8,15,r,g,b);                    
  updateColors();
  pixels.show();
  delay(DELAYVAL2);

  pixels.clear();
}

void showWalkingMan() {
  pixels.clear();
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);
  
  pixels.clear();
  mapLEDXY(0,8,5,5,25);mapLEDXY(0,13,5,5,25);mapLEDXY(1,9,5,5,25);mapLEDXY(1,14,5,5,25);                                        
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(0,4,5,5,25);mapLEDXY(0,5,5,5,25);mapLEDXY(0,7,5,5,25);mapLEDXY(0,12,5,5,25);mapLEDXY(1,8,5,5,25);mapLEDXY(1,13,5,5,25);mapLEDXY(2,9,5,5,25);mapLEDXY(2,14,5,5,25);                                        
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(0,4,5,5,25);mapLEDXY(0,5,5,5,25);mapLEDXY(0,7,5,5,25);mapLEDXY(0,12,5,5,25);mapLEDXY(1,8,5,5,25);mapLEDXY(1,9,5,5,25);mapLEDXY(1,13,5,5,25);mapLEDXY(1,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(0,4,5,5,25);mapLEDXY(0,5,5,5,25);mapLEDXY(0,6,5,5,25);mapLEDXY(0,7,5,5,25);mapLEDXY(0,8,5,5,25);mapLEDXY(0,9,5,5,25);mapLEDXY(0,10,5,5,25);mapLEDXY(0,11,5,5,25);mapLEDXY(1,4,5,5,25);mapLEDXY(1,5,5,5,25);mapLEDXY(1,7,5,5,25);mapLEDXY(1,8,5,5,25);mapLEDXY(1,9,5,5,25);mapLEDXY(1,12,5,5,25);mapLEDXY(1,13,5,5,25);mapLEDXY(1,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(0,4,5,5,25);mapLEDXY(0,5,5,5,25);mapLEDXY(0,7,5,5,25);mapLEDXY(0,12,5,5,25);mapLEDXY(1,4,5,5,25);mapLEDXY(1,5,5,5,25);mapLEDXY(1,6,5,5,25);mapLEDXY(1,7,5,5,25);mapLEDXY(1,8,5,5,25);mapLEDXY(1,9,5,5,25);mapLEDXY(1,10,5,5,25);mapLEDXY(1,11,5,5,25);mapLEDXY(2,4,5,5,25);mapLEDXY(2,5,5,5,25);mapLEDXY(2,7,5,5,25);mapLEDXY(2,12,5,5,25);mapLEDXY(3,8,5,5,25);mapLEDXY(3,9,5,5,25);mapLEDXY(3,13,5,5,25);mapLEDXY(3,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(0,8,5,5,25);mapLEDXY(0,13,5,5,25);mapLEDXY(1,4,5,5,25);mapLEDXY(1,5,5,5,25);mapLEDXY(1,7,5,5,25);mapLEDXY(1,12,5,5,25);mapLEDXY(2,4,5,5,25);mapLEDXY(2,5,5,5,25);mapLEDXY(2,6,5,5,25);mapLEDXY(2,7,5,5,25);mapLEDXY(2,8,5,5,25);mapLEDXY(2,9,5,5,25);mapLEDXY(2,10,5,5,25);mapLEDXY(2,11,5,5,25);mapLEDXY(3,4,5,5,25);mapLEDXY(3,5,5,5,25);mapLEDXY(3,7,5,5,25);mapLEDXY(3,12,5,5,25);mapLEDXY(4,8,5,5,25);mapLEDXY(4,13,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(1,8,5,5,25);mapLEDXY(1,9,5,5,25);mapLEDXY(1,13,5,5,25);mapLEDXY(1,14,5,5,25);mapLEDXY(2,4,5,5,25);mapLEDXY(2,5,5,5,25);mapLEDXY(2,7,5,5,25);mapLEDXY(2,12,5,5,25);mapLEDXY(3,4,5,5,25);mapLEDXY(3,5,5,5,25);mapLEDXY(3,6,5,5,25);mapLEDXY(3,7,5,5,25);mapLEDXY(3,8,5,5,25);mapLEDXY(3,9,5,5,25);mapLEDXY(3,10,5,5,25);mapLEDXY(3,11,5,5,25);mapLEDXY(4,4,5,5,25);mapLEDXY(4,5,5,5,25);mapLEDXY(4,7,5,5,25);mapLEDXY(4,12,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(5,14,5,5,25);                   
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(3,4,5,5,25);mapLEDXY(3,5,5,5,25);mapLEDXY(3,7,5,5,25);mapLEDXY(3,8,5,5,25);mapLEDXY(3,9,5,5,25);mapLEDXY(3,12,5,5,25);mapLEDXY(3,13,5,5,25);mapLEDXY(3,14,5,5,25);mapLEDXY(4,4,5,5,25);mapLEDXY(4,5,5,5,25);mapLEDXY(4,6,5,5,25);mapLEDXY(4,7,5,5,25);mapLEDXY(4,8,5,5,25);mapLEDXY(4,9,5,5,25);mapLEDXY(4,10,5,5,25);mapLEDXY(4,11,5,5,25);mapLEDXY(5,4,5,5,25);mapLEDXY(5,5,5,5,25);mapLEDXY(5,7,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,12,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(5,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(4,4,5,5,25);mapLEDXY(4,5,5,5,25);mapLEDXY(5,4,5,5,25);mapLEDXY(5,5,5,5,25);mapLEDXY(5,6,5,5,25);mapLEDXY(5,7,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,10,5,5,25);mapLEDXY(5,11,5,5,25);mapLEDXY(5,12,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(5,14,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(5,4,5,5,25);mapLEDXY(5,5,5,5,25);mapLEDXY(5,7,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,12,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(5,14,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,6,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,8,5,5,25);mapLEDXY(6,9,5,5,25);mapLEDXY(6,10,5,5,25);mapLEDXY(6,11,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,12,5,5,25);mapLEDXY(7,13,5,5,25);mapLEDXY(7,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(5,8,5,5,25);mapLEDXY(5,9,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(5,14,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,9,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(9,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

// hand shaking - start
  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,6,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,6,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,5,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,6,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);
// hand shaking - end

// hand shaking - start
  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,6,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,6,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,5,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,6,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);

  pixels.clear();
  mapLEDXY(4,9,5,5,25);mapLEDXY(4,14,5,5,25);mapLEDXY(5,8,5,5,25);mapLEDXY(5,13,5,5,25);mapLEDXY(6,4,5,5,25);mapLEDXY(6,5,5,5,25);mapLEDXY(6,7,5,5,25);mapLEDXY(6,12,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,6,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,8,5,5,25);mapLEDXY(7,9,5,5,25);mapLEDXY(7,10,5,5,25);mapLEDXY(7,11,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,13,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3/2);
// hand shaking - end

  pixels.clear();
  mapLEDXY(6,8,5,5,25);mapLEDXY(6,9,5,5,25);mapLEDXY(6,13,5,5,25);mapLEDXY(6,14,5,5,25);mapLEDXY(7,4,5,5,25);mapLEDXY(7,5,5,5,25);mapLEDXY(7,7,5,5,25);mapLEDXY(7,12,5,5,25);mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,6,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,8,5,5,25);mapLEDXY(8,9,5,5,25);mapLEDXY(8,10,5,5,25);mapLEDXY(8,11,5,5,25);mapLEDXY(9,4,5,5,25);mapLEDXY(9,5,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,12,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,13,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(8,4,5,5,25);mapLEDXY(8,5,5,5,25);mapLEDXY(8,7,5,5,25);mapLEDXY(8,8,5,5,25);mapLEDXY(8,9,5,5,25);mapLEDXY(8,12,5,5,25);mapLEDXY(8,13,5,5,25);mapLEDXY(8,14,5,5,25);mapLEDXY(9,4,5,5,25);mapLEDXY(9,5,5,5,25);mapLEDXY(9,6,5,5,25);mapLEDXY(9,7,5,5,25);mapLEDXY(9,8,5,5,25);mapLEDXY(9,9,5,5,25);mapLEDXY(9,10,5,5,25);mapLEDXY(9,11,5,5,25);mapLEDXY(10,4,5,5,25);mapLEDXY(10,5,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,12,5,5,25);mapLEDXY(10,13,5,5,25);mapLEDXY(10,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(9,4,5,5,25);mapLEDXY(9,5,5,5,25);mapLEDXY(10,4,5,5,25);mapLEDXY(10,5,5,5,25);mapLEDXY(10,6,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,10,5,5,25);mapLEDXY(10,11,5,5,25);mapLEDXY(10,12,5,5,25);mapLEDXY(10,13,5,5,25);mapLEDXY(10,14,5,5,25);mapLEDXY(11,4,5,5,25);mapLEDXY(11,5,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(10,4,5,5,25);mapLEDXY(10,5,5,5,25);mapLEDXY(10,7,5,5,25);mapLEDXY(10,8,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,12,5,5,25);mapLEDXY(10,13,5,5,25);mapLEDXY(10,14,5,5,25);mapLEDXY(11,4,5,5,25);mapLEDXY(11,5,5,5,25);mapLEDXY(11,6,5,5,25);mapLEDXY(11,7,5,5,25);mapLEDXY(11,8,5,5,25);mapLEDXY(11,9,5,5,25);mapLEDXY(11,10,5,5,25);mapLEDXY(11,11,5,5,25);mapLEDXY(12,4,5,5,25);mapLEDXY(12,5,5,5,25);mapLEDXY(12,7,5,5,25);mapLEDXY(12,8,5,5,25);mapLEDXY(12,9,5,5,25);mapLEDXY(12,12,5,5,25);mapLEDXY(12,13,5,5,25);mapLEDXY(12,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(10,8,5,5,25);mapLEDXY(10,9,5,5,25);mapLEDXY(10,13,5,5,25);mapLEDXY(10,14,5,5,25);mapLEDXY(11,4,5,5,25);mapLEDXY(11,5,5,5,25);mapLEDXY(11,7,5,5,25);mapLEDXY(11,12,5,5,25);mapLEDXY(12,4,5,5,25);mapLEDXY(12,5,5,5,25);mapLEDXY(12,6,5,5,25);mapLEDXY(12,7,5,5,25);mapLEDXY(12,8,5,5,25);mapLEDXY(12,9,5,5,25);mapLEDXY(12,10,5,5,25);mapLEDXY(12,11,5,5,25);mapLEDXY(13,4,5,5,25);mapLEDXY(13,5,5,5,25);mapLEDXY(13,7,5,5,25);mapLEDXY(13,12,5,5,25);mapLEDXY(14,8,5,5,25);mapLEDXY(14,9,5,5,25);mapLEDXY(14,13,5,5,25);mapLEDXY(14,14,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(10,9,5,5,25);mapLEDXY(10,14,5,5,25);mapLEDXY(11,8,5,5,25);mapLEDXY(11,13,5,5,25);mapLEDXY(12,4,5,5,25);mapLEDXY(12,5,5,5,25);mapLEDXY(12,7,5,5,25);mapLEDXY(12,12,5,5,25);mapLEDXY(13,4,5,5,25);mapLEDXY(13,5,5,5,25);mapLEDXY(13,6,5,5,25);mapLEDXY(13,7,5,5,25);mapLEDXY(13,8,5,5,25);mapLEDXY(13,9,5,5,25);mapLEDXY(13,10,5,5,25);mapLEDXY(13,11,5,5,25);mapLEDXY(14,4,5,5,25);mapLEDXY(14,5,5,5,25);mapLEDXY(14,7,5,5,25);mapLEDXY(14,12,5,5,25);mapLEDXY(15,8,5,5,25);mapLEDXY(15,13,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(12,8,5,5,25);mapLEDXY(12,9,5,5,25);mapLEDXY(12,13,5,5,25);mapLEDXY(12,14,5,5,25);mapLEDXY(13,4,5,5,25);mapLEDXY(13,5,5,5,25);mapLEDXY(13,7,5,5,25);mapLEDXY(13,12,5,5,25);mapLEDXY(14,4,5,5,25);mapLEDXY(14,5,5,5,25);mapLEDXY(14,6,5,5,25);mapLEDXY(14,7,5,5,25);mapLEDXY(14,8,5,5,25);mapLEDXY(14,9,5,5,25);mapLEDXY(14,10,5,5,25);mapLEDXY(14,11,5,5,25);mapLEDXY(15,4,5,5,25);mapLEDXY(15,5,5,5,25);mapLEDXY(15,7,5,5,25);mapLEDXY(15,12,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);

  pixels.clear();
  mapLEDXY(14,4,5,5,25);mapLEDXY(14,5,5,5,25);mapLEDXY(14,7,5,5,25);mapLEDXY(14,8,5,5,25);mapLEDXY(14,9,5,5,25);mapLEDXY(14,12,5,5,25);mapLEDXY(14,13,5,5,25);mapLEDXY(14,14,5,5,25);mapLEDXY(15,4,5,5,25);mapLEDXY(15,5,5,5,25);mapLEDXY(15,6,5,5,25);mapLEDXY(15,7,5,5,25);mapLEDXY(15,8,5,5,25);mapLEDXY(15,9,5,5,25);mapLEDXY(15,10,5,5,25);mapLEDXY(15,11,5,5,25);                    
  drawBackGround();
  pixels.show();
  delay(DELAYVAL3);
}

void drawBackGround(){
  mapLEDXY(0,15,0,25,0);mapLEDXY(1,15,0,25,0);mapLEDXY(2,15,0,25,0);mapLEDXY(3,15,0,25,0);mapLEDXY(4,15,0,25,0);mapLEDXY(5,15,0,25,0);mapLEDXY(6,15,0,25,0);mapLEDXY(7,15,0,25,0);mapLEDXY(8,15,0,25,0);mapLEDXY(9,15,0,25,0);mapLEDXY(10,15,0,25,0);mapLEDXY(11,15,0,25,0);mapLEDXY(12,15,0,25,0);mapLEDXY(13,15,0,25,0);mapLEDXY(14,15,0,25,0);mapLEDXY(15,15,0,25,0);                    
  mapLEDXY(11,0,25,25,0);mapLEDXY(12,0,25,25,0);mapLEDXY(12,1,25,25,0);mapLEDXY(13,0,25,25,0);mapLEDXY(13,1,25,25,0);mapLEDXY(13,2,25,25,0);mapLEDXY(14,0,25,25,0);mapLEDXY(14,1,25,25,0);mapLEDXY(15,0,25,25,0);                                        
}
