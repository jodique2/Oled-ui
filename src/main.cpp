#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String input = "";

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2); // Increased text size
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.display();
}

void loop() {
  if (Serial.available() > 0) {
    input = Serial.readStringUntil('\n'); // Waits until Enter is pressed

    display.clearDisplay();             // Clear previous text
    display.setCursor(0, 0);            // Reset cursor
    display.setTextSize(2);             // Bigger text size
    display.setTextColor(SSD1306_WHITE);
    display.println(input);            // Print input to display
    display.display();                 // Update screen

    Serial.print("Updated display with: ");
    Serial.println(input);
  }
}
