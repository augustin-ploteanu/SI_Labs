#ifndef CONFIG_H
#define CONFIG_H

/*Pin Definitions*/
#define NTC_PIN         A0
#define POT_PIN         A1
#define DHT_PIN         8

#define LCD_RS          2
#define LCD_EN          3
#define LCD_D4          4
#define LCD_D5          5
#define LCD_D6          6
#define LCD_D7          7

#define LED_NTC_PIN     12
#define LED_DHT_PIN     13

/*NTC Parameters*/
#define NTC_NOMINAL_R    10000.0
#define NTC_NOMINAL_TEMP 25.0
#define NTC_BETA         3950.0
#define NTC_SERIES_R     10000.0

/*Threshold / Hysteresis*/
#define DEFAULT_THRESHOLD    25.0
#define DEFAULT_HYSTERESIS    1.0

/*Analog Conditioning*/
#define SATURATION_MIN      -40.0
#define SATURATION_MAX       80.0
#define MEDIAN_WINDOW         5
#define AVG_ALPHA             0.2f

/*Timing*/
#define SENSOR_INTERVAL_MS    50
#define DHT_INTERVAL_MS      500
#define DISPLAY_INTERVAL_MS  500

/*Potentiometer Mapping*/
#define POT_TEMP_MIN    15.0
#define POT_TEMP_MAX    45.0

#endif
