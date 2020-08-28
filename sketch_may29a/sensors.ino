void DatchikVozd () // Функция получения данных с датчика температуры и влажности воздуха
{
  
  sensor.requestTemperatures();
  TempVozd = sensor.getTempC();    // Считываем данные с датчика температуры и влажности воздуха
  TempVozdBme280 = bme.readTemperature();
  HumVozdBme280 = bme.readHumidity();
  HumVozdBme280 = constrain(HumVozdBme280, 0, 99);
    
  if (TempVozd==85)  // Если цифровой датчик температуры завис, используем данные с резервного аналогового
  {
    lcd.setCursor(6, 0);            // Выводим на дисплей, что работаем на резервном аналоговом датчике
    lcd.print("!!");
//    TempVozd = temperatura_out;      // переключаемся на работу от резервного аналогового датчика температуры воздуха
//    sensorType = 1;                  // ставим флаг работы от аналогового датчика
//    lcd.setCursor(17, 1);            // Выводим на дисплей, что работаем на резервном аналоговом датчике
//    lcd.print("A");
  }
  else
  {
//    lcd.setCursor(6,0);   
//    PrintTemperatureDs18b20();
    sensorType = 0;                  // Ставим флаг, что работаем от цифрового датчика температуры воздуха
//    lcd.setCursor(17, 1);            // Выводим на дисплей, что работаем на цифровом датчике
//    lcd.print("D");
//    DisplayDataStatusSensors ();
  }

//  lcd.setCursor(17,2);
//  PrintHumidity();
//
//  delay (1500);
//
//  lcd.setCursor(6,0);
//  PrintTemperatureBme280 ();












  
  
}

void PrintTemperatureDs18b20() {
  
  if (TempVozd < 10)
  { 
    lcd.print("0");
    lcd.print(TempVozd);
  }
  else
  {
   lcd.print(TempVozd);
  }
}


void PrintTemperatureBme280 () {
  
  if ( TempVozdBme280 < 10)
  { 
    lcd.print("0");
    lcd.print( TempVozdBme280);
  }
  else
  {
   lcd.print(TempVozdBme280);
  }
}

void PrintHumidity() {
  
  if (HumVozdBme280 < 10)
  { 
    lcd.print("0");
    lcd.print(HumVozdBme280);
  }
  else
  {
   lcd.print(HumVozdBme280);
  }
}

void DatchikDozd ()
{

   Rain = analogRead(6);

  
 }


void DatchikSveta ()
 {

    Svet = analogRead(3);  
 
 }

 
