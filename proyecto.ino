no
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  18
#define OLED_CLK   5
#define OLED_DC    27
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
}

void loop() {
  display.clearDisplay();
  display.setTextColor(WHITE);        // color del texto
  display.setTextSize(1);
  display.setCursor(0,1);             // Start at top-left corner
  display.println(String("Temperatura: ") + String("C"));
}
