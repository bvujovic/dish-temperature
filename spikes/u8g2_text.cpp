
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SSD1306_64X48_ER_1_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE); // EastRising 0.66" OLED breakout board, Uno: A4=SDA, A5=SCL, 5V powered

void setup()
{
    u8g2.begin();
}

void loop()
{
    u8g2.firstPage();
    do
    {
        // u8g2.drawHLine(0, 0, 10);
        // u8g2.drawHLine(1, 1, 10);
        // u8g2.drawHLine(12, 2, 5);
        // u8g2.drawHLine(0, 24, 5);
        // u8g2.drawHLine(0, 36, 5);
        // u8g2.drawHLine(0, 48, 5);

        u8g2.setFont(u8g2_font_ncenB10_tr);
        u8g2.drawStr(0, 15, "*Pera");
        u8g2.drawStr(0, 15+16, "* Mile");
        u8g2.drawStr(0, 15+32, "* Jole123");
    } while (u8g2.nextPage());
    // delay(1000);
}
