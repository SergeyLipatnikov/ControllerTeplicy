void printTimeData() {

  timehour = rtc.getHours();                   
  timemin = rtc.getMinutes();                       
  timesec = rtc.getSeconds();
  timeday = rtc.getDate();                       
  timemounth = rtc.getMonth();                    
  timeyear = rtc.getYear();

  PrintTime();

  PrintData();

}

void PrintTime() {

  lcd.setCursor(0,3);
  
    if (timehour < 10)
  { 
    lcd.print("0");
    lcd.print(timehour);
  }
  else
  {
   lcd.print(timehour);
  }
      
  lcd.print(":"); 
   
  if (timemin < 10)
  { 
    lcd.print("0");
    lcd.print(timemin);
  }
  else
  {
    lcd.print(timemin);
  }

  lcd.print(":");

  if (timesec < 10)
  { 
    lcd.print("0");
    lcd.print(timesec);
  }
  else
  {
    lcd.print(timesec);
  }
  
  }

 void PrintData() {
  
  lcd.setCursor(10,3);
  
  if (timeday < 10)
  { 
    
    lcd.print("0");
    lcd.print(timeday);
  }
  else
  {
   lcd.print(timeday);
  }
      
  lcd.print("/"); 
   
  if (timemounth < 10)
  { 
    lcd.print("0");
    lcd.print(timemounth);
  }
  else
  {
    lcd.print(timemounth);
  }

  lcd.print("/");

//  if (timeyar < 10)
//  { 
//    lcd.print("0");
//    lcd.print(timesec);
//  }
//  else
//  {
    lcd.print(timeyear);
//  }
  }




void Timeset () // Функция настройки часов

{
  int Setyear = rtc.getYear();
  int Setmonth = rtc.getMonth();
  int Setdate = rtc.getDate();
  int SetdayOfWeek = rtc.getDay();
  int Sethour = rtc.getHours();
  int Setmin = rtc.getMinutes();
  int Setsec = rtc.getSeconds();

  lcd.clear();                 // Очистка дисплея
  int Kluch_3 = 1;               // Задаем значение, не позволяющее покинуть функцию без команды

  while (Kluch_3 == 1)            // Цикл выбора параметра
  {
    lcd.setCursor(0, 0);
    lcd.print("Clock setting:");
    while (nz < 5)              // Цикл ожидания, выполняется 1 раз при входе
    {
      delay (100);
      ++nz;
    }

    delay (100);               // Ожидание - выполняется каждый раз

    if (button_state[Button_Down]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
    {

      SetButtonState(Button_Down, ST_LOCKED);

      ResetButtonState(Button_Down, ST_UNPRESSURE);

      SetButtonState(Button_Down, ST_PRESSURE);

      ResetButtonState(Button_Down, ST_LOCKED);
      
      ++Sett;                   // увеличиваем
    }

    if (button_state[Button_Up]&ST_UNPRESSURE)
    {
      SetButtonState(Button_Up, ST_LOCKED);

      ResetButtonState(Button_Up, ST_UNPRESSURE);

      SetButtonState(Button_Up, ST_PRESSURE);

      ResetButtonState(Button_Up, ST_LOCKED);
      
      --Sett;                   // уменьшаем
    }

    if (Sett < 0)               // Ограничиваем выбор настроек заданным их количеством
    {
      Sett = 7;
    }

    if (Sett > 7)
    {
      Sett = 0;
    }

    lcd.setCursor(0, 1);               // Вывод на экран названия настройки
    
    lcd.print(NameClockSet[Sett]);     // в соответствии с ее номером в массиве названий

   if (Sett == 7)

    {             
    
    if (button_state[Button_Select]&ST_UNPRESSURE)        // Если нажата кнопка выхода из режима выбора настроек
    {
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);
        
          lcd.clear();                      // Очистка дисплея
          Kluch_3 = 0;
          memread = 0;
          break;
        }
    }
    
    if (button_state[Button_Select]&ST_UNPRESSURE)       // Если нажата кнопка выбора настроечного параметра
    {
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);
        
      int Kluch_4 = 1;                 // Задаем значение, не позволяющее покинуть цикл без команды
      
      nz = 0;                           // Обнуляем счетчик цикла ожидания

      while (Kluch_4 == 1)             // Цикл выбора значения параметра
      {
        lcd.setCursor(12, 1);

        delay (100);                 // Ожидание, отвечает за скорость смены значений

        if (Sett == 0)
        {
          lcd.print(Setyear);
          
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Setyear;
            
            if (Setyear > 2040)
            {
              
              Setyear = 2016;
              
            }
            
          }
          
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Setyear;
            
            if (Setyear < 2016)
            
            {
              
              Setyear = 2040;
              
            }
            
          }
          
        }

        if (Sett == 1)
        {
          lcd.print("  ");
          if (Setmonth < 10)
          {
            lcd.print("0");
          }
          lcd.print(Setmonth);
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Setmonth;
            
            if (Setmonth > 12)
            {
              Setmonth = 1;
            }
          }
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Setmonth;
            
            if (Setmonth < 1)
            {
              Setmonth = 12;
            }
          }
        }

        if (Sett == 2)
        {
          lcd.print("  ");
          if (Setdate < 10)
          {
            lcd.print("0");
          }
          lcd.print(Setdate);
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Setdate;
            
            if (Setdate > 31)
            {
              Setdate = 1;
            }
          }
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Setdate;
            
            if (Setdate < 1)
            {
              Setdate = 31;
            }
          }
        }

        if (Sett == 3)
        {
          lcd.print(" ");
          
          lcd.print(weekDay[SetdayOfWeek]);
          
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++SetdayOfWeek;
            
            if (SetdayOfWeek > 6)
            {
              SetdayOfWeek = 0;
            }
          }
          
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --SetdayOfWeek;
            
            if (SetdayOfWeek < 0)
            {
              SetdayOfWeek = 6;
            }
          }
        }

        if (Sett == 4)
        {
          lcd.print("  ");
          if (Sethour < 10)
          {
            lcd.print("0");
          }
          lcd.print(Sethour);
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Sethour;
            
            if (Sethour > 23)
            {
              Sethour = 0;
            }
          }
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Sethour;
            
            if (Sethour < 0)
            {
              Sethour = 23;
            }
          }
        }

        if (Sett == 5)
        {
          lcd.print("  ");
          if (Setmin < 10)
          {
            lcd.print("0");
          }
          lcd.print(Setmin);
          
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Setmin;
            
            if (Setmin > 59)
            {
              Setmin = 0;
            }
          }
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Setmin;
            
            if (Setmin < 0)
            {
              Setmin = 59;
            }
          }
        }

        if (Sett == 6)
        {
          lcd.print("  ");
          if (Setsec < 10)
          {
            lcd.print("0");
          }
          lcd.print(Setsec);
          
          if (button_state[Button_Right]&ST_UNPRESSURE) // Изменяем значение номера выбираемого параметра:
          {
      
            SetButtonState(Button_Right, ST_LOCKED);
      
            ResetButtonState(Button_Right, ST_UNPRESSURE);
      
            SetButtonState(Button_Right, ST_PRESSURE);
      
            ResetButtonState(Button_Right, ST_LOCKED);
            
            ++Setsec;
            
            if (Setsec > 59)
            {
              Setsec = 0;
            }
          }
          if (button_state[Button_Left]&ST_UNPRESSURE)
          
          {
            
            SetButtonState(Button_Left, ST_LOCKED);
      
            ResetButtonState(Button_Left, ST_UNPRESSURE);
      
            SetButtonState(Button_Left, ST_PRESSURE);
      
            ResetButtonState(Button_Left, ST_LOCKED);
            
            --Setsec;
            
            if (Setsec < 0)
            {
              Setsec = 59;
            }
          }
        }

        while (nz < 5)                // Цикл ожидания, выполняется 1 раз
        {
          delay (100);
          ++nz;
        }

        delay (100);                 // Ожидание, отвечает за скорость смены значений

        if (button_state[Button_Select]&ST_UNPRESSURE)       // Если нажата кнопка выбора настроечного параметра
          {
              SetButtonState(Button_Select, ST_LOCKED);
      
              ResetButtonState(Button_Select, ST_UNPRESSURE);
      
              SetButtonState(Button_Select, ST_PRESSURE);
      
              ResetButtonState(Button_Select, ST_LOCKED); // Производим установку часов

              rtc.setTime(Setsec, Setmin, Sethour, Setdate, Setmonth, Setyear); // устанвока времени вручную
              
              lcd.setCursor(11, 1);
              
              lcd.print("+");             // и выводим значок +, подтверждение сохранения

              lcd.setCursor(12, 1);
              
              lcd.print("    ");      // попутно стирая на дисплее значение.
              
              Kluch_4 = 0;
              
              nz = 0;
              
              continue;
        }
      }
    }
    delay (200);
  }
}
