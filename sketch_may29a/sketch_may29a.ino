#define LCD_ADDR 0x27
#include <microWire.h>
#include <microLiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

#include <microDS3231.h>
MicroDS3231 rtc;





void setup() {

  
  lcd.init();                  // Инициализация дисплея
  lcd.backlight();             // Подсветка дисплея
  

}

void loop() {
  lcd.setCursor(0, 0);
  lcd.print(rtc.getHours());
  lcd.setCursor(2, 0);
  lcd.print(":");

  lcd.setCursor(5,2);
  lcd.print("Hello world");
  delay(500);

}

void printTime() {
  lcd.setCursor(0, 0);
  lcd.print(rtc.getHours());
  lcd.setCursor(2, 0);
  lcd.print(":");
  lcd.setCursor(0, 3);
  lcd.print(rtc.getMinutes());
  lcd.setCursor(0, 5);
  lcd.print(":");
  lcd.setCursor(0, 6);
  lcd.print(rtc.getSeconds());
  lcd.setCursor(0, 8);
  lcd.print(" ");
  lcd.setCursor(1, 0);
  lcd.print(rtc.getDay());
  lcd.setCursor(1, 2);
  lcd.print("/");
  lcd.setCursor(1, 3);
  lcd.print(rtc.getMonth());
  lcd.setCursor(1, 5);
  lcd.print("/");
  lcd.setCursor(1, 6);
  lcd.print(rtc.getYear());
  lcd.setCursor(1, 10);
  lcd.print(" ");

  lcd.setCursor(2, 10);
  lcd.print("Hello world");
}
