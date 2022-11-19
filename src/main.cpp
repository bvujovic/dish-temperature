#include <Arduino.h>

const byte pinTermistor = A0;

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3C /// 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(128, 32, &Wire, -1);

void setup()
{
  // T Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      delay(100);
  }
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
}

void displayVal(int x)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(x);
  display.display();
}

void loop()
{
  int val = analogRead(pinTermistor);
  // T Serial.println(val);
  displayVal(val);
  delay(1000);
}
