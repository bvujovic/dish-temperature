
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

uint8_t m = 24;

void loop()
{
    char m_str[3];
    strcpy(m_str, u8x8_u8toa(m, 2)); /* convert m to a string with two digits */
    u8g2.firstPage();
    u8g2.setFont(u8g2_font_logisoso24_tn);
    do
    {
        u8g2.drawStr(0, 40, "08");
        u8g2.drawStr(29, 40, ":");
        u8g2.drawStr(35, 40, m_str);
    } while (u8g2.nextPage());
    delay(1000);
    m++;
    if (m == 60)
        m = 0;
}
