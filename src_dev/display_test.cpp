#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306 allocation failed"));
        while (true)
            delay(100); // Don't proceed, loop forever
    }

    // // Show initial display buffer contents on the screen --
    // // the library initializes this with an Adafruit splash screen.
    // display.display();
    // delay(2000); // Pause for 2 seconds

    // // Clear the buffer
    // display.clearDisplay();

    // // Draw a single pixel in white
    // display.drawPixel(100, 10, SSD1306_WHITE);

    // // Show the display buffer on the screen. You MUST call display() after
    // // drawing commands to make them visible on screen!
    // display.display();
    // delay(2000);
    // display.clearDisplay();

    // display.drawLine(0, 0, 16 - 1, display.height() - 1, SSD1306_WHITE);
    // display.drawLine(0, 0, 32 - 1, display.height() - 1, SSD1306_WHITE);
    // display.drawLine(0, 0, 64 - 1, display.height() - 1, SSD1306_WHITE);
    // display.drawLine(0, 0, 128 - 1, display.height() - 1, SSD1306_WHITE);
    // display.display(); // Update screen with each newly-drawn line
    // delay(3000);
    display.clearDisplay();

    display.setTextSize(2);              // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);             // Start at top-left corner
    // display.cp437(true);                 // Use full 256 char 'Code Page 437' font
    display.write("Bojan... 123456.0");
    // display.println(3.141592);
    display.display();
}

void loop()
{
    delay(1000);
}
