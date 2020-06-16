void Nastroyka() // Функция выбора меню на дисплее
  {
    ResetButtonState(Button_Select, ST_LOCKED);
    
    lcd.backlight();             // Подсветка дисплея
    lcd.clear();                 // Очистка дисплея
    while (nz < 5)               // Цикл ожидания, выполняется 1 раз при входе
    {
      delay (200);
      ++nz;
    }
    int Kluch_5 = 1;
    int menu = 0;

    while (Kluch_5 = 1)
    {        
      lcd.setCursor(0, 0);
      lcd.print("Set parametr");
      lcd.setCursor(0, 1);
      lcd.print("Set clock");
      lcd.setCursor(0, 2);
      lcd.print("EXIT");
      lcd.setCursor(0, 3);
      lcd.print("Testmot.-butt.on top");
      
      switch (menu){

        case 0:
        
        lcd.setCursor(15, 0);
        lcd.print("<");
        lcd.setCursor(15, 2);
        lcd.print(" ");
        lcd.setCursor(15, 1);
        lcd.print(" ");
        break;
        
        case 1:

        lcd.setCursor(15, 2);
        lcd.print(" ");
        lcd.setCursor(15, 1);
        lcd.print("<");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        break;
        
        case 2:
        
        lcd.setCursor(15, 2);
        lcd.print("<");
        lcd.setCursor(15, 1);
        lcd.print(" ");
        lcd.setCursor(15, 0);
        lcd.print(" ");
        break;
      }

      if (button_state[Button_Down]&ST_UNPRESSURE)           // Если кнопка вниз нажата
      {
        SetButtonState(Button_Down, ST_LOCKED);

        ResetButtonState(Button_Down, ST_UNPRESSURE);

        SetButtonState(Button_Down, ST_PRESSURE);

        ResetButtonState(Button_Down, ST_LOCKED);

        ++menu;
      }

      if (button_state[Button_Up]&ST_UNPRESSURE)           // Если кнопка ввверх нажата
      {
        SetButtonState(Button_Up, ST_LOCKED);

        ResetButtonState(Button_Up, ST_UNPRESSURE);

        SetButtonState(Button_Up, ST_PRESSURE);

        ResetButtonState(Button_Up, ST_LOCKED);
     
        --menu;
      }

      if (menu < 0) {

        menu = 2;
        
        }

       if (menu > 2) {

        menu = 0;
        
        }

      if (button_state[Button_Select]&ST_UNPRESSURE)           // Если кнопка ввода нажата
      {
        
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);

        if (menu == 2)
        {
//          Timeset ();
        lcd.clear();                     // Очистка дисплея
        Kluch_5 = 0;
        nz = 0;
        memread = 0;
        break;
        }

        else
        {
          Nastr_Parametr ();
        }
      }

//      if (digitalRead(Podsvetka) == 1)
//      {
//        TestMotor();
//      }
    }
  }

   void Nastr_Parametr ()          // Функция настройки параметров с кнопок и сохранения их в EEPROM
{

  lcd.clear();                 // Очистка дисплея
 
  int Kluch = 1;               // Задаем значение, не позволяющее покинуть функцию без команды
  int nastr = 0;               // Включаем нумерацию настроечных параметров
  int nastr_d = nastr+1;
  int nz = 0;                   // Счетчик для циклов ожидания, выполняющихся 1 раз

  while (Kluch = 1)            // Цикл выбора параметра
  {

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
        
      ++nastr;                   // увеличиваем
      
    }

    if (button_state[Button_Up]&ST_UNPRESSURE)
    {
        SetButtonState(Button_Up, ST_LOCKED);

        ResetButtonState(Button_Up, ST_UNPRESSURE);

        SetButtonState(Button_Up, ST_PRESSURE);

        ResetButtonState(Button_Up, ST_LOCKED);
      
      --nastr;                   // уменьшаем
     
    }

    if (nastr < 0)               // Ограничиваем выбор настроек заданным их количеством
    {
      nastr = KolNactr - 1;
      
    }

    if (nastr > KolNactr - 1)
    {
      nastr = 0;
    }

    nastr_d = nastr+1;

    if (nastr == KolNactr - 1)
    {
      nastr_d = 0;
    }

    lcd.setCursor(0, 0);               // Вывод на экран названия настройки
    
    lcd.print(NameParametr[nastr]);    // в соответствии с ее номером в массиве названий

    lcd.setCursor(10, 0);

    lcd.print("<");

    lcd.setCursor(0, 1);

    lcd.print(NameParametr[nastr_d]);

    lcd.setCursor(12, 0);

    if (Parametr[nastr] < 10)      // Прописываем пустое место перед единицами
    {      
      lcd.print("  ");
    }
    
    if (Parametr[nastr] >= 10 && Parametr[nastr] < 100)  // Пустое место перед десятками
    {
      lcd.print(" ");
    }

    lcd.print(Parametr[nastr]);  // выводим значение сохраненного параметра

    lcd.setCursor(12, 1);
   
    if (Parametr[nastr_d] < 10)      // Прописываем пустое место перед единицами
    {
      lcd.print("  ");
    }

    if (Parametr[nastr_d] >= 10 && Parametr[nastr_d] < 100)  // Пустое место перед десятками
    {
      lcd.print(" ");
    }

    lcd.print(Parametr[nastr_d]);

    if (nastr == KolNactr - 1){
      
    if (button_state[Button_Select]&ST_UNPRESSURE)        // Если нажата кнопка выхода из режима выбора настроек
    {
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);
      
      lcd.clear();                      // Очистка дисплея
      Kluch = 0;
      nz = 0;
      break;
    }

    }
    
    if (button_state[Button_Select]&ST_UNPRESSURE)       // Если нажата кнопка выбора настроечного параметра
    {
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);
      
      int Kluch_2 = 1;                 // Задаем значение, не позволяющее покинуть цикл без команды
      nz = 0;                           // Обнуляем счетчик цикла ожидания
      lcd.setCursor(10, 0);
      lcd.print(" ");
      lcd.setCursor(15, 0);
      lcd.print("<");

      while (Kluch_2 == 1)             // Цикл выбора значения параметра
      {
                
        
        lcd.setCursor(12, 0);

        if (Parametr[nastr] < 10)      // Прописываем пустое место перед единицами
        {
          lcd.print("  ");
        }

        if (Parametr[nastr] >= 10 && Parametr[nastr] < 100)  // Пустое место перед десятками
        {
          lcd.print(" ");
        }

        lcd.print(Parametr[nastr]);  // выводим значение сохраненного параметра

        while (nz < 5)                // Цикл ожидания, выполняется 1 раз
        {
          delay (100);
          ++nz;
        }

        delay (100);                 // Ожидание, отвечает за скорость смены значений

        if (button_state[Button_Right]&ST_UNPRESSURE) // Если кнопка вправо нажата, увеличиваем значение параметра
        {
          
        SetButtonState(Button_Right, ST_LOCKED);

        ResetButtonState(Button_Right, ST_UNPRESSURE);

        SetButtonState(Button_Right, ST_PRESSURE);

        ResetButtonState(Button_Right, ST_LOCKED);
          
          ++Parametr[nastr];
        }

        if (button_state[Button_Left]&ST_UNPRESSURE)  // То же для кнопки влево
        {
          
        SetButtonState(Button_Left, ST_LOCKED);

        ResetButtonState(Button_Left, ST_UNPRESSURE);

        SetButtonState(Button_Left, ST_PRESSURE);

        ResetButtonState(Button_Left, ST_LOCKED);
          
          --Parametr[nastr];
        }

        if (Parametr[nastr] < 1)     // Задаем границы для значений параметров, в том числе
        {                            // обусловленные возможностями ячейки памяти (256)
          Parametr[nastr] = 250;
        }

        if (Parametr[nastr] > 250)
        {
          Parametr[nastr] = 1;
        }

        if (button_state[Button_Select]&ST_UNPRESSURE)  // Если в этом режиме нажата кнопка Ввод,
        {                             // сохраняем значение параметра в EEPROM
        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        ResetButtonState(Button_Select, ST_LOCKED);
          
          EEPROM.write(nastr, Parametr[nastr]);
          lcd.setCursor(15, 0);
          lcd.print("+");
          delay (500);
          lcd.setCursor(15, 0);
          lcd.print(" ");             // Стираем значок
          Kluch_2 = 0;
          nz = 0;
          memread = 0;
          continue;
        }

        if (button_state[Button_Up]&ST_UNPRESSURE)   // Если нажата кнопка выхода, выходим в предыдущее меню
        {                             // выбора номера параметра,
        SetButtonState(Button_Up, ST_LOCKED);

        ResetButtonState(Button_Up, ST_UNPRESSURE);

        SetButtonState(Button_Up, ST_PRESSURE);

        ResetButtonState(Button_Up, ST_LOCKED);
          
          lcd.setCursor(15, 0);
          lcd.print(" ");             // попутно стирая на дисплее значок
          Kluch_2 = 0;
          nz = 0;
          continue;
        }
      }
    }
    delay (200);
  }
}
