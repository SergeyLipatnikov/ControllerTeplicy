extern unsigned int tim_cnt;//счетчик тиков таймера

static unsigned char i = 0;

char str2[5];


//———————————————————–

typedef enum {

  MENU_STATE_IDLE = 0,

  MENU_STATE_WAIT,

  MENU_STATE_MAIN,

} MENU_StateTypeDef;

typedef enum {

  MAIN_MENU_STATE_IDLE = 0,

  MAIN_MENU_STATE_WAIT,

  MAIN_MENU_STATE_MM1,

  MAIN_MENU_STATE_MM2,

  MAIN_MENU_STATE_MM3,

  MAIN_MENU_STATE_MM4,

  MAIN_MENU_STATE_MM5,

  MAIN_MENU_STATE_EXIT,

  MAIN_MENU_STATE_MM1_WAIT,

  MAIN_MENU_STATE_MM2_WAIT,

  MAIN_MENU_STATE_MM3_WAIT,

  MAIN_MENU_STATE_MM4_WAIT,

  MAIN_MENU_STATE_MM5_WAIT,

  MAIN_MENU_STATE_EXIT_WAIT

} MAIN_MENU_StateTypeDef;

//———————————————————–

char str1[6][11] =

{

  "MM_1 \0",

  "MM_2 \0",

  "MM_3 \0",

  "MM_4 \0",

  "MM_5 \0",

  "EXIT \0"

};

MENU_StateTypeDef menu_state = MENU_STATE_IDLE;

MAIN_MENU_StateTypeDef main_menu_state = MAIN_MENU_STATE_IDLE;



void MenuProcess(void)

{


  EVERY_MS(10)
  {
    int long timer = millis();

    lcd.setCursor(0, 3);

    lcd.print("Timer=");

    lcd.print(timer);

    CheckButtons();
  }

  switch (menu_state)

  {

    case MENU_STATE_IDLE: //старт программы

      menu_state = MENU_STATE_WAIT;

      lcd.clear();

      lcd.setCursor(0, 0);

      lcd.print("MENU");

      lcd.setCursor (0, 1);

      lcd.print("Press SELECT");

      break;

    case MENU_STATE_WAIT: //ждем запуска главного меню

      if (button_state[Button_Select]&ST_UNPRESSURE)

      {

        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        //обработка нажатия кнопки

        menu_state = MENU_STATE_MAIN;

      }

      break;

    case MENU_STATE_MAIN: //запуск главного меню

      main_menu_state = MAIN_MENU_STATE_IDLE;

      MainMenuProcess();

      break;

  }

}

//—————————————————–
//мигание пункта меню

void BlinkItem(unsigned char ind)

{
  int BlinkPositionMenu = millis();

    EVERY_MS(10)
  {
    int long timer = millis();

    lcd.setCursor(0, 3);

    lcd.print("Timer=");

    lcd.print(timer);

    CheckButtons();
  }

  if (ind < 3) lcd.setCursor(ind * 5, 0);

  else lcd.setCursor((ind - 3) * 5, 1);

  if (BlinkPositionMenu > nextBlinkPositionMenu)
  
  {

    
    
    lcd.print(str1[ind]);
  }

  else lcd.print(" ");

}

//—————————————————–


void MainMenuProcess(void)

{

  while (1)

  {

      EVERY_MS(10)
  {
    int long timer = millis();

    lcd.setCursor(0, 3);

    lcd.print("Timer=");

    lcd.print(timer);

    CheckButtons();
  }

    switch (main_menu_state)

    {

      case MAIN_MENU_STATE_IDLE: //старт главного меню

        lcd.setCursor(0, 0);

        for (i = 0; i < 3; i++)

        {

          lcd.print(str1[i]);

        }

        lcd.setCursor(0, 1);

        for (i = 0; i < 3; i++)

        {

          lcd.print(str1[i + 3]);

        }

        ResetButtonState(Button_Select, ST_LOCKED);

        main_menu_state = MAIN_MENU_STATE_WAIT;

        break;

      case MAIN_MENU_STATE_WAIT: //Ожидаем выбора меню

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM1_WAIT;

        }

        break;

      case MAIN_MENU_STATE_MM1_WAIT: //ожидание выбора 1 пункта

        BlinkItem(0);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM2_WAIT;

          lcd.setCursor(0, 0);

          lcd.print(str1[0]); //зажжем 1 пункт, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_EXIT_WAIT;

          lcd.setCursor(0, 0);

          lcd.print(str1[0]); //зажжем 1 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша вниз

        if (button_state[Button_Down]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Down, ST_LOCKED);

          ResetButtonState(Button_Down, ST_UNPRESSURE);

          SetButtonState(Button_Down, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Down, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM4_WAIT;

          lcd.setCursor(0, 0);

          lcd.print(str1[0]); //зажжем 1 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM1;

          lcd.setCursor(0, 0);

          lcd.print(str1[0]); //зажжем 1 пункт, а то вдруг он в потухшем состоянии

        }
        break;

      case MAIN_MENU_STATE_MM2_WAIT: //ожидание выбора 2 пункта

        BlinkItem(1);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM3_WAIT;

          lcd.setCursor(5, 0);

          lcd.print(str1[1]); //зажжем 2 пункт, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM1_WAIT;

          lcd.setCursor(5, 0);

          lcd.print(str1[1]); //зажжем 2 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша вниз

        if (button_state[Button_Down]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Down, ST_LOCKED);

          ResetButtonState(Button_Down, ST_UNPRESSURE);

          SetButtonState(Button_Down, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Down, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM5_WAIT;

          lcd.setCursor(5, 0);

          lcd.print(str1[1]); //зажжем 2 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM2;

          lcd.setCursor(5, 0);

          lcd.print(str1[1]); //зажжем 2 пункт, а то вдруг он в потухшем состоянии

        }

        break;

      case MAIN_MENU_STATE_MM3_WAIT: //ожидание выбора 3 пункта

        BlinkItem(2);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM4_WAIT;

          lcd.setCursor(10, 0);

          lcd.print(str1[2]); //зажжем 3 пункт, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM2_WAIT;

          lcd.setCursor(10, 0);

          lcd.print(str1[2]); //зажжем 3 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша вниз

        if (button_state[Button_Down]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Down, ST_LOCKED);

          ResetButtonState(Button_Down, ST_UNPRESSURE);

          SetButtonState(Button_Down, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Down, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_EXIT_WAIT;

          lcd.setCursor(10, 0);

          lcd.print(str1[2]); //зажжем 3 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM3;

          lcd.setCursor(10, 0);

          lcd.print(str1[2]); //зажжем 3 пункт, а то вдруг он в потухшем состоянии

        }

        break;

      case MAIN_MENU_STATE_MM4_WAIT: //ожидание выбора 4 пункта

        BlinkItem(3);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM5_WAIT;

          lcd.setCursor(0, 1);

          lcd.print(str1[3]); //зажжем 4 пункт, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM3_WAIT;

          lcd.setCursor(0, 1);

          lcd.print(str1[3]); //зажжем 4 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша вверх

        if (button_state[Button_Up]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Up, ST_LOCKED);

          ResetButtonState(Button_Up, ST_UNPRESSURE);

          SetButtonState(Button_Up, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Up, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM1_WAIT;

          lcd.setCursor(0, 1);

          lcd.print(str1[3]); //зажжем 4 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM4;

          lcd.setCursor(0, 1);

          lcd.print(str1[3]); //зажжем 4 пункт, а то вдруг он в потухшем состоянии

        }

        break;

      case MAIN_MENU_STATE_MM5_WAIT: //ожидание выбора 5 пункта

        BlinkItem(4);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_EXIT_WAIT;

          lcd.setCursor(5, 1);

          lcd.print(str1[4]); //зажжем 5 пункт, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM4_WAIT;

          lcd.setCursor(5, 1);

          lcd.print(str1[4]); //зажжем 5 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша вверх

        if (button_state[Button_Up]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Up, ST_LOCKED);

          ResetButtonState(Button_Up, ST_UNPRESSURE);

          SetButtonState(Button_Up, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Up, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM2_WAIT;

          lcd.setCursor(5, 1);

          lcd.print(str1[4]); //зажжем 5 пункт, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM5;

          lcd.setCursor(5, 1);

          lcd.print(str1[4]); //зажжем 5 пункт, а то вдруг он в потухшем состоянии

        }

        break;

      case MAIN_MENU_STATE_EXIT_WAIT: //ожидание выбора пункта EXIT

        BlinkItem(5);

        //правая клавиша

        if (button_state[Button_Right]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Right, ST_LOCKED);

          ResetButtonState(Button_Right, ST_UNPRESSURE);

          SetButtonState(Button_Right, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Right, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM1_WAIT;

          lcd.setCursor(10, 1);

          lcd.print(str1[5]); //зажжем пункт EXIT, а то вдруг он в потухшем состоянии

        }

        //левая клавиша

        if (button_state[Button_Left]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Left, ST_LOCKED);

          ResetButtonState(Button_Left, ST_UNPRESSURE);

          SetButtonState(Button_Left, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Left, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM5_WAIT;

          lcd.setCursor(10, 1);

          lcd.print(str1[5]); //зажжем пункт EXIT, а то вдруг он в потухшем состоянии

        }

        //клавиша вверх

        if (button_state[Button_Up]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Up, ST_LOCKED);

          ResetButtonState(Button_Up, ST_UNPRESSURE);

          SetButtonState(Button_Up, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Up, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_MM3_WAIT;

          lcd.setCursor(10, 1);

          lcd.print(str1[5]); //зажжем пункт EXIT, а то вдруг он в потухшем состоянии

        }

        //клавиша SELECT

        if (button_state[Button_Select]&ST_UNPRESSURE)

        {

          SetButtonState(Button_Select, ST_LOCKED);

          ResetButtonState(Button_Select, ST_UNPRESSURE);

          SetButtonState(Button_Select, ST_PRESSURE);

          //обработка нажатия кнопки

          ResetButtonState(Button_Select, ST_LOCKED);

          main_menu_state = MAIN_MENU_STATE_EXIT;

          lcd.setCursor(10, 1);

          lcd.print(str1[5]); //зажжем пункт EXIT, а то вдруг он в потухшем состоянии

        }

        break;

      case MAIN_MENU_STATE_MM1:

        main_menu_state = MAIN_MENU_STATE_IDLE;

        MainMenuItemProcess(1);

        lcd.clear();

        break;

      case MAIN_MENU_STATE_MM2:

        main_menu_state = MAIN_MENU_STATE_IDLE;

        MainMenuItemProcess(2);

        lcd.clear();

        break;

      case MAIN_MENU_STATE_MM3:

        main_menu_state = MAIN_MENU_STATE_IDLE;

        MainMenuItemProcess(3);

        lcd.clear();

        break;

      case MAIN_MENU_STATE_MM4:

        main_menu_state = MAIN_MENU_STATE_IDLE;

        MainMenuItemProcess(4);

        lcd.clear();

        break;

      case MAIN_MENU_STATE_MM5:

        main_menu_state = MAIN_MENU_STATE_IDLE;

        MainMenuItemProcess(5);

        lcd.clear();

        break;

      case MAIN_MENU_STATE_EXIT: //выбор пункта EXIT

        menu_state = MENU_STATE_IDLE;

        return;

        break;

    }

  }

}

//—————————————————–

void MainMenuItemProcess(unsigned char ind) {

  lcd.clear();

  lcd.setCursor(0, 0);

  lcd.print("ITEM ");

  sprintf(str2, "%d", ind);

  lcd.print(str2);

  lcd.print(" Press");

  lcd.setCursor(0, 1);

  lcd.print("SELECT from exit");

  //здесь будут функции, вызываемые пунктами меню

  switch (ind)

  {

    case 1:

      //функция-обработчик 1 пункта меню

      break;

    case 2:

      //функция-обработчик 2 пункта меню

      break;

    case 3:

      //функция-обработчик 3 пункта меню

      break;

    case 4:

      //функция-обработчик 4 пункта меню

      break;

    case 5:

      //функция-обработчик 5 пункта меню

      break;

  }

  while (1)

  {

      EVERY_MS(10)
  {
    int long timer = millis();

    lcd.setCursor(0, 3);

    lcd.print("Timer=");

    lcd.print(timer);

    CheckButtons();
  }

    if (button_state[Button_Select]&ST_UNPRESSURE)

    {

//      if (currentMenuMillis >= nextMenuMillis) {
//
//        nextMenuMillis = currentMenuMillis + intervalMenu;

        lcd.clear();

        SetButtonState(Button_Select, ST_LOCKED);

        ResetButtonState(Button_Select, ST_UNPRESSURE);

        SetButtonState(Button_Select, ST_PRESSURE);

        //обработка нажатия кнопки

 //     }

      ResetButtonState(Button_Select, ST_LOCKED);

      return;

    }

    //    delay(50);

  }

}

//—————————————————–
