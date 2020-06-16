//class SensorRain
//{
//  int SensorRainPin;
//  int updateInterval;
//  unsigned long lastUpdate;
//
//  public:
//  SensorRain(int pin, int interval)
//  {
//    SensorRainPin= pin;
//    
//    pinMode (SensorRainPin, INPUT);
//
//    updateInterval = interval;
//    
//    }
//
//  void Update()
//  {
//    if((millis() - lastUpdate) > updateInterval)
//    {
//      lastUpdate = millis();
//      
//      sensorVals[0] = analogRead(SensorRainPin);
//
//        lcd.setCursor(0,2);
//
//        lcd.print(sensorVals[0]);
//      
//        lcd.print("  ");
//        
//      }
//    }
//  };


void GetAllValues ()
{
  
  sensorVals[0] = analogRead(A2);

  lcd.setCursor(0,2);

  lcd.print(sensorVals[0]);

  lcd.print("  ");
 
  delay(5000);
  
}

//void UseDriver ()
//{
//
//  if (sensorVals[0]<500)
//  
//  {
//    
//  digitalWrite(4, LOW);
//  
//  digitalWrite(5, HIGH);
//
//  while (sensorVals[0]<800){
//
//      sensorVals[0] = analogRead(A2);
//    
//    }
//  
//  }
//
//  else if ((sensorVals[0]>500)&&(sensorVals[0]<800))
//  
//  {
//    
//  digitalWrite(4, LOW);
//  
//  digitalWrite(5, HIGH);
//  
//  }
//
//  else if (sensorVals[0]>800)
//  
//  {
//    
//  digitalWrite(5, LOW);
//  
//  digitalWrite(4, HIGH);
//  
//  }
//  
//}

int sensorTimer,sensorMode;
int period;


void readAllSensors() {
  if (millis() - sensorTimer >= period) {
    sensorTimer = millis();
    switch (sensorMode) {
      case 0:   // вкл питание
        sensorMode = 1;
        period = 500;
        digitalWrite(A1, 1);
        break;
      case 1:   // измеряем
        sensorMode = 2;
        period = 200;
//        getAllData();
        rain1.Update();
        break;
      case 2:   // выключаем
        sensorMode = 0;
        period = 500;
        digitalWrite(A1, 0);
        break;
    }
  }
}
