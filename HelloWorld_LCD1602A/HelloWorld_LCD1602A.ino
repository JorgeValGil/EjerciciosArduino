/*
Pantalla LCD1602A sin IIC/I2C
Tamaño LCD 16*2

VSS - GND
VDD - 5V
VO - Contraste de la pantalla, conectado con un potenciometro
RS - Selector de registro
RW - GND
E - Enable
D4 - BUS
D5 - BUS
D6 - BUS
D7 - BUS
A - 5V
K - GND
*/

#include <LiquidCrystal.h>

const int rs = 7, e = 8, d4 = 9, d5 = 10, d6 = 11, d7 = 12;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.write("Hello");
  lcd.setCursor(0,1);
  lcd.write("World");
}

void loop() {

}
