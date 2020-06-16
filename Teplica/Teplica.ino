unsigned char button_state[5];

int sensorVals[6];

float t;

//——————————————-

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

//——————————————-
#define LCD_ADDR 0x27

#define ONE_WIRE_BUS 9

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

#include <OneWire.h>

#include <DS18B20.h>

LiquidCrystal_I2C lcd(LCD_ADDR, 20, 4);

OneWire oneWire(ONE_WIRE_BUS);

DS18B20 sensor(&oneWire);

void UseDriver ()
{

  if (t<22)
  
  {
    
  digitalWrite(4, LOW);
  
  digitalWrite(5, HIGH);

  while (sensorVals[0]<800){

      sensorVals[0] = analogRead(A2);
    
    }
  
  }

  else if ((t>23)&&(t<25))
  
  {
    
  digitalWrite(4, LOW);
  
  digitalWrite(5, HIGH);
  
  }

  else if (t>25)
  
  {
    
  digitalWrite(5, LOW);
  
  digitalWrite(4, HIGH);
  
  }
  
}

class SensorRain
{
  int SensorRainPin;
  int updateInterval;
  unsigned long lastUpdate;

  public:
  SensorRain(int pin, int interval)
  {
    SensorRainPin= pin;
    
    pinMode (SensorRainPin, INPUT);

    updateInterval = interval;
    
    }

  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)
    {

//        digitalWrite(A1,HIGH);
        
        lastUpdate = millis();
        
        sensorVals[0] = analogRead(SensorRainPin);

        sensorVals[1] = analogRead(A6);

        float thermistor;
        
        thermistor =  10000/ ((float)1023 / sensorVals[1] - 1);
        
        thermistor /= 10000;                        // (R/Ro)
        
        thermistor = log(thermistor) / 3435;            // 1/B * ln(R/Ro)
        
        thermistor += (float)1.0 / (25 + 273.15);  // + (1/To)
        
        thermistor = (float)1.0 / thermistor - 273.15;    // инвертируем и конвертируем в градусы по Цельсию

        int n = 0;
        
        sensor.requestTemperatures();
        
        while (!sensor.isConversionComplete()) n++;
        
        t = sensor.getTempC();

        lcd.setCursor(0,2);

        lcd.print(sensorVals[0]);
      
        lcd.print("  ");

        lcd.setCursor(10,2);

        lcd.print(t);
      
        lcd.print("  ");

        lcd.setCursor(0,3);

        lcd.print(thermistor);
      
        lcd.print("  ");

        UseDriver ();
        
      }
//      else digitalWrite(A1,LOW);
    }
  };

void setup() {
  
  pinMode(Knob_Left, INPUT);
  
  pinMode(Knob_Up, INPUT);
  
  pinMode(Knob_Down, INPUT);
  
  pinMode(Knob_Right, INPUT);
  
  pinMode(Knob_Select, INPUT);

  pinMode(4, OUTPUT);

  pinMode(5, OUTPUT);

  pinMode(A6, INPUT);

  pinMode(A1, OUTPUT);

  TCCR1A = 0; // установить регистры в 0
    TCCR1B = 0; 

    OCR1A = 31248; // установка регистра совпадения
    TCCR1B |= (1 << WGM12); // включение в CTC режим

    // Установка битов CS10 и CS12 на коэффициент деления 1024
    TCCR1B |= (1 << CS10);
    TCCR1B |= (1 << CS12);

    TIMSK1 |= (1 << OCIE1A);

  sei();
  
  lcd.init();
  
  lcd.backlight();
  
  Buttons_Ini();

  sensor.begin();
  
  sensor.setResolution(12);
  
  sensor.requestTemperatures();
  
}

SensorRain rain1(2, 100);

ISR(TIMER1_COMPA_vect)
{
     readAllSensors();
}

void loop() {
  
//    GetAllValues ();

   // rain1.Update();

  //  readAllSensors();
    
    MenuProcess();  

}
