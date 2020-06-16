void DatchikVozd () // Функция получения данных с датчика температуры и влажности воздуха
{
  
  //Serial.println("void DatchikVozd");
  sensor.requestTemperatures();
  chk = sensor.getTempC();    // Считываем данные с датчика температуры и влажности воздуха

//  if (chk <99)
//  {
//    DHTLIB_OK = 0;
//    }
  
    switch (chk)                  // Проверка данных на ошибки. Если они есть, присваиваем значения 99.
    
       {
        case DHTLIB_OK:
        break;
        default: TempVozd = 97; 
                 VlazhnVozd = 99;
        break;
       }
    
   if (TempVozd != 99)           // Если с данными все в порядке, присваиваем переменным значения.
   
       {
        //VlazhnVozd = DHT.humidity,1;
        TempVozd = sensor.getTempC();
        //Serial.println(VlazhnVozd);
        //Serial.println("   void DatchikVozd   ");
        //Serial.println(TempVozd);
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
