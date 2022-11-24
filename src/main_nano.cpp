#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const byte pin = A2;

void setup()
{
    Serial.begin(9600);
    pinMode(pin, INPUT);

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
}

void displayVal(float x)
{
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(x);
    // T Serial.println(x);
    display.display();
}

void loop()
{
    int val = analogRead(pin);
    // T Serial.println(val);
    int valRev = 1023 - val;
    // T Serial.println(valRev);
    float v = valRev * (5.0 / 1023.0); // voltage
    // T Serial.println(v);

    // float r = v * 5.1 / (5.0 - v); // resistance (kOhm)
    float r = 5.1 * 1.0 / (5.0 / v - 1);
    // T Serial.println(r);
    displayVal(r);

    //* resistance -> temperature
    // https://www.aliexpress.com/item/1005004347451079.html?spm=a2g0o.cart.0.0.1d5d38da6yLzpw&mp=1

    delay(1000);
}
