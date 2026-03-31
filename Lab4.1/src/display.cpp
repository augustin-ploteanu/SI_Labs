#include "display.h"
#include <LiquidCrystal.h>

static LiquidCrystal lcd(12, 11, A0, A1, A2, A3);

static int serial_putchar(char c, FILE *) {
  if (c == '\n') Serial.write('\r');
  Serial.write(c);
  return 0;
}
static FILE serial_stdout;

static void serial_stdio_init(unsigned long baud) {
  Serial.begin(baud);
  fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
}

void display_init(void) {
  serial_stdio_init(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Actuator Ctrl");
  lcd.setCursor(0, 1);
  lcd.print("Ready...");

  printf("Binary Actuator Control ready\n");
  printf("Keys: 1/A=ON  0/B=OFF  *=Toggle\n");
  printf("Serial: 1=ON  0=OFF  T=Toggle\n");
}

void display_update(int8_t actuator_state) {
  // LCD line 0: actuator state
  lcd.setCursor(0, 0);
  lcd.print("State:  ");
  lcd.print(actuator_state ? "ON " : "OFF");
  lcd.print("      ");

  // LCD line 1: alert / status
  lcd.setCursor(0, 1);
  if (actuator_state) {
    lcd.print("Relay: ACTIVE   ");
  } else {
    lcd.print("Relay: INACTIVE ");
  }

  // Serial report
  printf("Actuator=%s  Relay=%s\n",
         actuator_state ? "ON" : "OFF",
         actuator_state ? "ACTIVE" : "INACTIVE");
}
