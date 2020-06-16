#define LCD_ADDR 0x27

#define ONE_WIRE_BUS 9

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <OneWire.h>

#include <DS18B20.h>

LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

OneWire oneWire(ONE_WIRE_BUS);

DS18B20 sensor(&oneWire);

#define Button_Left 3

#define Button_Up 1

#define Button_Select 4

#define Button_Down 2

#define Button_Right 0

//——————————————-

#define Knob_Left 2

#define Knob_Up 3

#define Knob_Select 10

#define Knob_Down 11

#define Knob_Right 12

//——————————————-

#define ST_PRESSED 0b00000001        //кнопка нажата

#define ST_UNPRESSED 0b00000010 //кнопка отжата

#define ST_ERROR 0b00000100     //не удалось считать статус

#define ST_PRESSURE 0b00001000   //процесс нажатия кнопки

#define ST_UNPRESSURE 0b00010000 //процесс отжатия кнопки

#define ST_LOCKED 0b00100000        //кнопка недоступна

int periodButtons = 300;

int long nextCounterButton = 0;

int long nextBlinkPositionMenu = 0;

static unsigned char but_cnt[5] = {0};

unsigned char button_state[5];

unsigned int tim_cnt;

long nextMenuMillis = 0;

int intervalMenu = 50;

int intervalBlinkMenu = 500;

unsigned int currentMenuMillis = millis();


//==== MILLISTIMER MACRO ====
#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)
//===========================


void setup() {

  pinMode(Knob_Left, INPUT);

  pinMode(Knob_Up, INPUT);

  pinMode(Knob_Down, INPUT);

  pinMode(Knob_Right, INPUT);

  pinMode(Knob_Select, INPUT);

  nextCounterButton = millis() + periodButtons;
  
  nextMenuMillis = millis() + intervalMenu;

  nextBlinkPositionMenu = millis() + intervalBlinkMenu;

  lcd.init();

  lcd.backlight();

  sensor.begin();

  sensor.setResolution(12);

  sensor.requestTemperatures();
  
  Buttons_Ini();
}


void loop() {


//  EVERY_MS(10)
//  {
//    int long timer = millis();
//
//    lcd.setCursor(0, 3);
//
//    lcd.print("Timer=");
//
//    lcd.print(timer);
//
//    CheckButtons();
//  }
  
  EVERY_MS(2000)
  {
    float temperature;
    int n = 0;
        
        sensor.requestTemperatures();
        
        temperature = sensor.getTempC();

        lcd.setCursor(0, 2);

        lcd.print(temperature);
    }
  
    MenuProcess(); 

}
