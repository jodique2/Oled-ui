#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

unsigned long lastBlinkTime = 0;
unsigned long lastTimeOffSet = 0;
int offsetX = 0;
int offsetY = 0;
int targetOffsetX = 0;
int targetOffsetY = 0;

int centered_x = 34;
int centered_y = 20;
unsigned int blinkInterval = random(2500,4000);/*it is unsigned so that the error disapears*/

void setup() {
  // Blink LED to show Arduino is alive
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // LED ON
  delay(500);
  digitalWrite(13, LOW);  // LED OFF

  // Kick I2C lines to wake up stubborn OLED
  pinMode(A4, OUTPUT); // SDA
  pinMode(A5, OUTPUT); // SCL
  digitalWrite(A4, HIGH);
  digitalWrite(A5, HIGH);
  delay(10);

  Wire.begin();
  delay(200); // Let devices settle

  Serial.begin(9600);
  delay(100);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

/*drawEyes will draw the eyes on the given x and y position*/
void drawEyes(int x, int y) {
  display.clearDisplay();
  display.fillRoundRect(x, y, 20, 30, 5, SSD1306_WHITE);
  display.fillRoundRect(x+40, y, 20, 30, 5, SSD1306_WHITE);
  display.display();
  delay(30);
}
/*drawBlink will blink once*/
void drawBlink(int x, int y){
  display.clearDisplay();
  display.fillRoundRect(x,y+12,20,6,2,SSD1306_WHITE); /*the y+12 is because the greater the y, the lower in the screen you are*/
  display.fillRoundRect(x+40,y+12,20,6,2,SSD1306_WHITE); /*the x+40 is to compensate the size of the other eye and a space between the eyes*/
  display.display();
  delay(50);
}
/*drawBlinkTwice will blink twice in a row*/
void drawBlinkTwice(int x, int y){
  drawBlink(x,y);
  drawEyes(x,y);
  drawBlink(x,y);
}
/*a random number between 1-3 is generated and is less likely to blinkTwice then once, because only blinksTwice when a == 3*/
void getRandomBlink(int x, int y){
  int a = random(1,4);
  if(a == 3){
    drawBlinkTwice(x,y);
  }
  else{
    drawBlink(x,y);
  }
}

void loop() {
  if (millis() - lastTimeOffSet >= 2000){ /*the offset is only created with a 1 second interval*/
    lastTimeOffSet = millis();
    targetOffsetX = random(-3, 4);
    targetOffsetY = random(-2, 3);
  }

  /*targetOffSet ensures that the transition is smooth, so that it looks like it is loking around/daydreaming */
  if (offsetX < targetOffsetX) offsetX++;
  else if (offsetX > targetOffsetX) offsetX--;

  if (offsetY < targetOffsetY) offsetY++;
  else if (offsetY > targetOffsetY) offsetY--;


  drawEyes(centered_x + offsetX, centered_y + offsetY);

  if(millis() - lastBlinkTime >= blinkInterval){
    blinkInterval=random(2500,4000); /*a diferent blink interval, will bring more variety*/
    lastBlinkTime = millis();
    getRandomBlink(centered_x,centered_y);
  }
  delay(30);
}