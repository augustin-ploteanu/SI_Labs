#include <Arduino.h>
#include <LiquidCrystal.h>
#include <stdio.h>
#include "config.h"
#include "lcd.h"

/*LCD instance (4-bit mode, pins from config)*/
static LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*stdout → LCD  (printf writes to the display)*/
static int lcd_col = 0;
static int lcd_row = 0;

static int lcd_putchar(char c, FILE *stream) {
    (void)stream;
    switch (c) {
        case '\f':
            lcd.clear();
            lcd_col = lcd_row = 0;
            break;
        case '\n':
            lcd_row = (lcd_row + 1) % 2;
            lcd_col = 0;
            lcd.setCursor(lcd_col, lcd_row);
            break;
        case '\r':
            lcd_col = 0;
            lcd.setCursor(lcd_col, lcd_row);
            break;
        default:
            if (lcd_col < 16) {
                lcd.write((uint8_t)c);
                lcd_col++;
            }
            break;
    }
    return 0;
}

static FILE lcd_stream;

static int serial_putchar(char c, FILE *stream) {
    (void)stream;
    Serial.write((uint8_t)c);
    return 0;
}

static FILE serial_stream;

void lcd_init(void) {
    lcd.begin(16, 2);
    Serial.begin(9600);

    fdev_setup_stream(&lcd_stream, lcd_putchar, NULL, _FDEV_SETUP_WRITE);
    stdout = &lcd_stream;

    fdev_setup_stream(&serial_stream, serial_putchar, NULL, _FDEV_SETUP_WRITE);
    stderr = &serial_stream;
}
