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

struct Point
{
    double x, y;
};

Point arr[] = {
    {0.2989, 105},
    {0.398, 95},
    {0.5386, 85},
    {0.7415, 75},
    {1.04, 65},
    {1.4881, 55},
    {2.1757, 45},
    {3.2564, 35},
    {5.0, 25},
    {7.8943, 15},
    {12.8515, 5},
};

int array_len() { return sizeof(arr) / sizeof(Point); }

double interpolate_simple(Point f[], int n, double xi)
{
    if (xi < f[0].x)
        return 999;
    for (size_t i = 0; i < n; i++)
    {
        if (xi == f[i].x)
            return f[i].y;
        if (xi < f[i + 1].x)
        {
            //B return (f[i].y + f[i + 1].y) / 2;
            double dx = xi - f[i].x;
            double Dx = f[i + 1].x - f[i].x;
            double Dy = f[i + 1].y - f[i].y;
            double dy = dx * Dy / Dx;
            return f[i].y + dy;
        }
    }
    return 0;
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
    // T displayVal(r);

    //* resistance -> temperature
    // https://www.aliexpress.com/item/1005004347451079.html?spm=a2g0o.cart.0.0.1d5d38da6yLzpw&mp=1
    double t = interpolate_simple(arr, array_len(), r);
    displayVal(t);

    delay(1000);
}
