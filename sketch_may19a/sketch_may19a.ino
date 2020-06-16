#define LCD_ADDR 0x27

#define ONE_WIRE_BUS 9

#define DHTLIB_OK 0

#define Button_Left 3

#define Button_Up 1

#define Button_Select 4

#define Button_Down 2

#define Button_Right 0

//——————————————-

#define Left 2

#define Up 3

#define Enter 10

#define Down 11

#define Right 12

//——————————————-

#define ST_PRESSED 0b00000001        //кнопка нажата

#define ST_UNPRESSED 0b00000010 //кнопка отжата

#define ST_ERROR 0b00000100     //не удалось считать статус

#define ST_PRESSURE 0b00001000   //процесс нажатия кнопки

#define ST_UNPRESSURE 0b00010000 //процесс отжатия кнопки

#define ST_LOCKED 0b00100000        //кнопка недоступна

unsigned char button_state[5];

static unsigned char but_cnt[5]={0};

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <OneWire.h>

#include <DS18B20.h>

#include <EEPROM.h>            // Библиотека памяти

#include "Sodaq_DS3231.h"

LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

OneWire oneWire(ONE_WIRE_BUS);

DS18B20 sensor(&oneWire);

int VlazhnVozd;                    // Переменная влажности воздуха
int TempVozd;                      // Переменная температуры воздуха
int VlazhPoch = 0;                 // влажность почвы
int chk;                           // Переменная проверки датчика температуры и влажности воздуха
byte i;                            // для датчика температуры почвы
byte DataVozd[12];                 // Данные для датчика температуры почвы
//byte AddrVozd[8] = {0x28, 0xFF, 0x63, 0xC1, 0x74, 0x16, 0x4, 0xF7};  // Адрес для датчика температуры почвы
byte AddrVozd[8] = {0x28, 0xFF, 0x32, 0xD1, 0x64, 0x15, 0x1, 0xB7};  // Адрес для датчика температуры почвы
int TempPochv;                     // Переменная температуры почвы
char weekDay[][4] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
int FlagNaborVoda = 0;             // Флажок, определяющий, что вода в этот час уже набиралась
int FlagPoliva = 0;                // Флажок, определяющий, что полив в этот час уже был
unsigned long Vremya = 0;          // Переменная для определения времени подсветки дисплея
int MotorTest = 0;                 // Переменная для включения теста моторов
int Konts;                         // переменная для определения концевика
int Sett = 0;                      // Включаем нумерацию настроечных параметров
int nz = 0;                        // Переменная отсчета задержек для меню.
int memread = 0;                   // Ключ для чтения данных из EEPROM
int KluchPauza = 0;                // Ключ для паузы
int NParam;                        // Переменная для выбора параметра по времени работы моторов
double izmer [20];                 // массив для получения данных с аналогового датчика температуры воздуха
double temp;                       // Временная переменная для сортировки данных с аналогового датчика температуры воздуха
double temperatura;                // Значение температуры с аналогового датчика температуры воздуха
int temperatura_out;               // округленное значение температуры аналогового датчика температуры воздуха
double Volt;                       // Напряжение на выходе (для настройки) с аналогового датчика температуры воздуха
int lightOut;                      // округленное значение относительной освещенности в %

int timehour;                      // Переменная для считывания времени (часы)
int timemin;                       // Переменная для считывания времени (минуты)
int timeday;                       // Переменная для считывания времени (дни)



int Rain;
int Svet;

byte Datasend[16];                  // Массив для отправки данных в ESP8266
//unsigned long Vremya_send_start = 0;     // Переменная для определения времени задержки отправки данных после включения
unsigned long Vremya_send = 0;     // Переменная для определения времени задержки отправки данных
int obogrVozd = 0;                 // Флаг включения подогрева воздуха 
int obogrPoch = 0;                 // Флаг включения подогрева почвы
int sensorType = 0;                // Флаг типа датчика температуры, по которому работает теплица
int flagLight = 0;                 // Флаг включения освещения
const int KolNactr = 20;           // Количество элементов массивов настроек
                                   // (количество настраиваемых параметров)

int Parametr[KolNactr];            // Массив для значений параметров настроек

String NameParametr[KolNactr] =
{
  "VremNabora",
  "ChasNabora",
  "VremPoliva",
  "ChasPoliva",
  "ChPoliva_2",
  "VrOtkrTyla",
  "VrZakrTyla",
  "VrOtkFasad",
  "VrZakFasad",
  "T_OtkrOkon",
  "T_ZakrOkon",
  "T_Pochv_on",
  "T_Poch_off",
  "T_Vozd_ on",
  "T_Vozd_off",
  "Light_on  ",
  "Light_off ",
  "ChLightOn ",
  "ChLightOff",
  "Exit      "
};



String NameClockSet[] =
{
  "year:       ",
  "month:      ",
  "date:       ",
  "day of week:",
  "hour:       ",
  "minute:     "
};

int const PositivMotor = 4;      // номер пина мотора открывания форточки тыла 1
int const NegativeMotor = 5;      // номер пина мотора открывания форточки тыла 2
//int const MotorFas_1 = 6;      // номер пина мотора открывания форточки фасада 1
//int const MotorFas_2 = 7;      // номер пина мотора открывания форточки фасада 2
//int const Left = 2;            // Кнопка настроек влево 
//int const Esc = 3;             // Кнопка настроек выход
//int const Enter = 10;          // Кнопка настроек ввод
//int const Right = 11;          // Кнопка настроек вправо
int const KontsTylOtkr = 22;   // номер пина концевого выключателя открывания форточки тыла
int const KontsTylZakr = 24;   // номер пина концевого выключателя закрывания форточки тыла
int const SensorVoda = 26;     // номер пина сенсора уровня воды в поливочном баке
int const KontsFasOtkr = 28;   // номер пина концевого выключателя открывания форточки фасада
int const KontsFasZakr = 30;   // номер пина концевого выключателя закрывания форточки фасада
int const OtklObogr = 32;      // номер пина ручного выключателя автоматического обогрева (теплого пола и обогревателя воздуха)
int const OtkrOkon = 34;       // номер пина ручного выключателя ОТКРЫТИЯ окон и отключения автоматического управления окнами
int const ZakrOkon = 36;       // номер пина ручного выключателя ЗАКРЫТИЯ окон и отключения автоматического управления окнами
int const KnopkaNabor = 38;    // номер пина для кнопки ручного набора воды в поливочный бак
int const KnopkaPoliv = 40;    // номер пина кнопки включения полива
int const Poliv_x2 = 42;       // номер пина переключателя полива (1 или 2 раза)
int const Podsvetka = 44;      // номер пина кнопки включения подсветки дисплея
int const ReleLight_1 = 46;    // номер пина реле №1 включения освещения
int const ReleNasos_2 = 48;    // номер пина реле №2 включения насоса
int const ReleTeplPol_3 = 50;  // номер пина реле №3 включения теплого пола
int const ReleObogr_4 = 52;    // номер пина реле №4 включения обогревателя воздуха
int const VlazhPochPin = 14;   // пин датчика влажности почвы
int const Temper_A = 13;        // Пин аналогового датчика температуры LM235Z    
const int datchikLight_1 = 12;  // аналоговые пины для поключения датчиков освещенности в зависимости от их количества
int Otkryt = true;
int Zakryt = false;
int GoRain = 400;
int OutRain = 600;
int lighting = 400;
int darkness = 550;



void setup() {

//         """НАЗНАЧЕНИЕ ПИНОВ"""

pinMode (PositivMotor, OUTPUT);    // пин мотора открывания форточки тыла 1 - выход
pinMode (NegativeMotor, OUTPUT);    // пин мотора открывания форточки тыла 2 - выход
pinMode (6, OUTPUT);    // пин мотора открывания форточки фасада 1 - выход
pinMode (7, OUTPUT);    // пин мотора открывания форточки фасада 2 - выход
pinMode (Left, INPUT);           // Кнопка настроек влево 
pinMode (Up, INPUT);            // Кнопка настроек вверх
pinMode (Enter, INPUT);          // Кнопка настроек ввод
pinMode (Right, INPUT);          // Кнопка настроек вправо
pinMode (Down, INPUT);           // Кнопка настроек вниз    
//pinMode (KontsTylOtkr, INPUT);   // пин концевого выключателя открывания форточки тыла - вход
//pinMode (KontsTylZakr, INPUT);   // пин концевого выключателя закрывания форточки тыла - вход
//pinMode (SensorVoda, INPUT);     // пин сенсора уровня воды в поливочном баке - вход
//pinMode (KontsFasOtkr, INPUT);   // пин концевого выключателя открывания форточки фасада - вход
//pinMode (KontsFasZakr, INPUT);   // пин концевого выключателя закрывания форточки фасада - вход
//pinMode (OtklObogr, INPUT);      // пин ручного выключателя автоматического обогрева (теплого пола и обогревателя воздуха) - вход
//pinMode (OtkrOkon, INPUT);       // пин ручного выключателя ОТКРЫТИЯ окон и отключения автоматического управления окнами - вход
//pinMode (ZakrOkon, INPUT);       // пин ручного выключателя ЗАКРЫТИЯ окон и отключения автоматического управления окнами - вход
//pinMode (KnopkaNabor, INPUT);    // пин для кнопки ручного набора воды в поливочный бак - вход
//pinMode (KnopkaPoliv, INPUT);    // пин кнопки включения полива - вход
//pinMode (Poliv_x2, INPUT);       // пин переключателя полива (1 или 2 раза) - вход
//pinMode (Podsvetka, INPUT);      // пин кнопки включения подсветки дисплея - вход
//pinMode (ReleLight_1, OUTPUT);   // пин реле №1 освещение выход
//pinMode (ReleNasos_2, OUTPUT);   // пин реле №2 включения насоса - выход
//pinMode (ReleTeplPol_3, OUTPUT); // пин реле №3 включения теплого пола - выход
//pinMode (ReleObogr_4, OUTPUT);   // пин реле №4 включения обогревателя воздуха - выход
//
//digitalWrite (ReleLight_1,1);    // Освещение отключено
//digitalWrite (ReleNasos_2,1);    // Насос отключен
//digitalWrite (ReleTeplPol_3,1);  // Подогрев почвы отключен
//digitalWrite (ReleObogr_4,1);    // Обогреватель воздуха отключен
////digitalWrite (MotorTyl_1, 1);    // Пины управления моторами отключены
////digitalWrite (MotorTyl_2, 1);    
//digitalWrite (MotorFas_1, 1); 
//digitalWrite (MotorFas_2, 1);


 //      """ДИСПЛЕЙ""" 
 
  lcd.init();                  // Инициализация дисплея
  lcd.backlight();             // Подсветка дисплея
  
  //  данные самодельных символов для дисплея:
  
byte lcd_ch[8] = {0x00,0x00,0x11,0x11,0x0F,0x01,0x01,0x00};
byte lcd_z[8] = {0x00,0x00,0x0E,0x11,0x06,0x11,0x0E,0x00}; 
byte lcd_d[8] = {0x00,0x00,0x06,0x0A,0x0A,0x0A,0x1F,0x00};
byte lcd_v[8] = {0x00,0x00,0x1E,0x11,0x1E,0x11,0x1E,0x00}; 
byte lcd_gradus[8] = {0x00,0x10,0x06,0x09,0x08,0x09,0x06,0x00};
byte lcd_l[8] = {0x00,0x00,0x07,0x09,0x09,0x09,0x19,0x00};
byte lcd_g[8] = {0x00,0x00,0x15,0x15,0x0E,0x15,0x15,0x00};
byte lcd_p[8] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x11,0x00};


  //  Создание самодельных символов для дисплея

lcd.createChar(0, lcd_ch);      // буква ч
lcd.createChar(1, lcd_z);       // буква з
lcd.createChar(2, lcd_d);       // буква д
lcd.createChar(3, lcd_v);       // буква в
lcd.createChar(4, lcd_gradus);  // градус
lcd.createChar(5, lcd_l);       // буква л
lcd.createChar(6, lcd_g);       // буква ж
lcd.createChar(7, lcd_p);       // буква п


  rtc.begin(); 
  
  sensor.begin();

  sensor.setResolution(12);

  sensor.requestTemperatures();

  Buttons_Ini();

}

void loop() {

    if (KluchPauza == 0)  // Пауза перед запуском программы 
  {
    //Serial.println("pause");
    delay (3000);
    KluchPauza = 1;
  }
    
  if (memread == 0)  // Оди раз считываем данные настроек из памяти и выводим неизменяемые символы на дисплей
  {
    //Serial.println("memread");
    for (int i = 0; i < KolNactr; ++i)     // Цикл считывания данных из EEPROM
    {
      Parametr[i] = EEPROM.read(i);
    }
    memread = 1;

    // Выводим на дисплей неизменяемые символы.
    lcd.setCursor(0, 0);
    lcd.print("Bo");
    lcd.write(byte(1));
    lcd.write(byte(2));
    lcd.print("yx:");

    lcd.setCursor(0, 1);
    lcd.print("t=");
    lcd.setCursor(4, 1);
    lcd.write(byte(4));
    lcd.setCursor(6, 1);
    lcd.write(byte(3));
    lcd.write(byte(5));
    lcd.print("a");
    lcd.write(byte(6));
    lcd.print(".=");
    lcd.setCursor(15, 1);
    lcd.print("%");

    lcd.setCursor(0, 2);
    lcd.write(byte(7));
    lcd.print("o");
    lcd.write(byte(0));
    lcd.write(byte(3));
    lcd.print("a:");
    lcd.setCursor(13, 2);
    lcd.write(byte(7));
    lcd.print("o");
    lcd.write(byte(2));
    lcd.print(":");

    lcd.setCursor(0, 3);
    lcd.print("t=");
    lcd.setCursor(4, 3);
    lcd.write(byte(4));
    lcd.setCursor(6, 3);
    lcd.write(byte(3));
    lcd.write(byte(5));
    lcd.print("a");
    lcd.write(byte(6));
    lcd.print(".=");
    lcd.setCursor(15, 3);
    lcd.print("%");
    lcd.setCursor(17, 3);
    lcd.print("L");    
  }

  if (button_state[Button_Select]&ST_UNPRESSURE)           // Если кнопка ввода нажата
  {
    SetButtonState(Button_Select, ST_LOCKED);

    ResetButtonState(Button_Select, ST_UNPRESSURE);

    SetButtonState(Button_Select, ST_PRESSURE);

//    ResetButtonState(Button_Select, ST_LOCKED);
        
    Nastroyka();                        // Переходим в меню настройки
  }

  DatchikVozd (); // Работаем с цифровым датчиком температуры и влажности воздуха
  DatchikDozd ();
  DatchikSveta ();

  if (TempVozd==99)  // Если цифровой датчик температуры завис, используем данные с резервного аналогового
  {
    lcd.setCursor(2, 1);            // Выводим на дисплей, что работаем на резервном аналоговом датчике
    lcd.print("!!");
    TempVozd = temperatura_out;      // переключаемся на работу от резервного аналогового датчика температуры воздуха
    sensorType = 1;                  // ставим флаг работы от аналогового датчика
    lcd.setCursor(17, 1);            // Выводим на дисплей, что работаем на резервном аналоговом датчике
    lcd.print("A");
  }
  else
  {
    lcd.setCursor(2,1);   
    lcd.print(TempVozd);
    sensorType = 0;                  // Ставим флаг, что работаем от цифрового датчика температуры воздуха
    lcd.setCursor(17, 1);            // Выводим на дисплей, что работаем на цифровом датчике
    lcd.print("D");
    lcd.setCursor(13, 0);
    lcd.print(Rain);
    lcd.setCursor(17, 0);
    lcd.print(Svet);
  }

     if ( (millis() - Vremya) > 30000 || millis() < Vremya)

      {
       lcd.noBacklight();             // Подсветка дисплея отключается    
      } 

   if ( digitalRead(Podsvetka) == 1)

      {
       lcd.backlight();              // Подсветка дисплея
       Vremya = millis();
      }  

      lcd.setCursor(10,0);              // установка курсора
      lcd.print("A");
      
    DecisionAfterSensors ();
//    TimeData();

    delay(3000);
}
