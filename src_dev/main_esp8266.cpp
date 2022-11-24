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
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    while (true)
      delay(100);
  }
  display.clearDisplay();
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.cp437(true);

  // for(int16_t i=0; i<16; i++) {
  //   if(i == '\n') display.write(' ');
  //   else          display.write(i);
  // }
  // display.write("45");
  // display.write(248); // display.write(9);
  // display.write('C');
  // display.display();
  // delay(15000);
}

void displayVal(float x)
{
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(x);
  Serial.println(x);
  display.display();
}

void loop()
{
  int val = analogRead(pinTermistor);
  // T Serial.println(val);
  float v = val * (3.315 / 1023.0); // voltage
  // 3.3 : v = 5k+r : r
  // r = v*5k / (3.2-v)
  float r = v * 5.100 / (3.315 - v); // resistance (kOhm)
  // float r = v * 5.1 / (5.0 - v);
  // float r = 5.1 * 1.0 / (5.0/v - 1);

  //* ESP8266 neprecizno meri otpor tj. napon. Levo su prave, a desno izmerene vrednosti u kOhm.
  // 10     12.2
  // 5.1    5.9
  // 2      2.3
  // 1      1.19
  // 320    0.48
  // 222.5  0.36

  displayVal(r);
  delay(1000);
}
