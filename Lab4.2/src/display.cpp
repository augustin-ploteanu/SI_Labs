#include "display.h"
#include "actuator.h"
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

  printf("Actuator Control System\n");
  printf("Keypad: A=ON B=OFF *=Toggle\n");
  printf("Speed:  0-9,#=Set C=Clr D=Stop\n");
  printf("Serial: A/B/T  S<num> X=Stop\n");
}

void display_update(int8_t binary_state, uint8_t motor_speed) {
  char line[17];

  // LCD line 0: binary actuator
  snprintf(line, sizeof(line), "Relay: %-9s",
           binary_state ? "ON" : "OFF");
  lcd.setCursor(0, 0);
  lcd.print(line);

  // LCD line 1: analog actuator
  if (motor_speed == 100) {
    snprintf(line, sizeof(line), "Spd:%3d%% LIMIT!", motor_speed);
  } else {
    snprintf(line, sizeof(line), "Spd:%3d%%        ", motor_speed);
  }
  lcd.setCursor(0, 1);
  lcd.print(line);

  // Serial report
  printf("Binary=%s Relay=%s Speed=%d%%",
         binary_state ? "ON" : "OFF",
         binary_state ? "ACTIVE" : "INACTIVE",
         motor_speed);
  if (motor_speed == 100) printf(" [LIMIT]");
  printf("\n");
}

void display_task(void) {
  display_update(actuator_get_state(), actuator_get_speed());
}
