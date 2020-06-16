//void TestMotor() // Тестовая программа для проверки и настройки моторов открывания окон
//{
//  MotorTest = 1;
//  lcd.clear();                     // Очистка дисплея
//  lcd.backlight();                 // Подсветка дисплея
//  lcd.setCursor(0, 0);             // Вывод на дисплей неизменяемых символов:
//  lcd.print("Motors test");
//  lcd.setCursor(0, 1);
//  lcd.print("Motors select:");
//  lcd.setCursor(0, 2);
//  lcd.print("Motors status:");
//  lcd.setCursor(0, 3);
//  lcd.print("TO:");
//  lcd.setCursor(5, 3);
//  lcd.print("TC:");
//  lcd.setCursor(10, 3);
//  lcd.print("FO:");
//  lcd.setCursor(15, 3);
//  lcd.print("FC:");
//  delay(500);
//             
//  while ( MotorTest == 1)
//             
//  {
//    lcd.setCursor(15, 1);
//    lcd.print("OFF  ");
//    lcd.setCursor(15, 2);
//    lcd.print("STOP ");    
//    Kontsevik ();
//     
//    if ((digitalRead(Left) == 1) && (digitalRead(KontsTylOtkr) == 0))  // Нажата кнопка 1 и концевик открыт
//    {
//      lcd.setCursor(15, 1);
//      lcd.print("Tyl  ");
//      lcd.setCursor(15, 2);
//      lcd.print("Open ");
//     
//      Kontsevik ();
//
//      digitalWrite (MotorTyl_1, 0);
//
//      while ((digitalRead(Left) == 1) && (digitalRead(KontsTylOtkr) == 0))
//      {
//        Kontsevik ();
//        delay (100);
//      }
//
//      digitalWrite (MotorTyl_1, 1);
//    }
//     
//    if ((digitalRead(Esc) == 1) && (digitalRead(KontsTylZakr) == 0))  // Нажата кнопка 2 и концевик открыт
//    {
//      lcd.setCursor(15, 1);
//      lcd.print("Tyl  ");
//      lcd.setCursor(15, 2);
//      lcd.print("Close");
//     
//      Kontsevik ();
//
//      digitalWrite (MotorTyl_2, 0);
//
//      while ((digitalRead(Esc) == 1) && (digitalRead(KontsTylZakr) == 0))
//      {
//        Kontsevik ();
//        delay (100);
//      }
//
//      digitalWrite (MotorTyl_2, 1);
//    }
//
//    if ((digitalRead(Enter) == 1) && (digitalRead(KontsFasOtkr) == 0))  // Нажата кнопка 3 и концевик открыт
//    {
//      lcd.setCursor(15, 1);
//      lcd.print("Fasad");
//      lcd.setCursor(15, 2);
//      lcd.print("Open ");
//     
//      Kontsevik ();
//
//      digitalWrite (MotorFas_1, 0);
//
//      while ((digitalRead(Enter) == 1) && (digitalRead(KontsFasOtkr) == 0))
//      {
//        Kontsevik ();
//        delay (100);
//      }
//
//      digitalWrite (MotorFas_1, 1);
//    }
//
//    if ((digitalRead(Right) == 1) && (digitalRead(KontsFasZakr) == 0))  // Нажата кнопка 4 и концевик открыт
//    {
//      lcd.setCursor(15, 1);
//      lcd.print("Fasad");
//      lcd.setCursor(15, 2);
//      lcd.print("Close");
//     
//      Kontsevik ();
//
//      digitalWrite (MotorFas_2, 0);
//
//      while ((digitalRead(Right) == 1) && (digitalRead(KontsFasZakr) == 0))
//      {
//        Kontsevik ();
//        delay (100);
//      }
//
//      digitalWrite (MotorFas_2, 1);
//    }
//
//    if (digitalRead(Podsvetka) == 1)  // Нажата кнопка подсветки
//    {
//      delay (2000);
//      if (digitalRead(Podsvetka) == 1)  // Все еще нажата кнопка подсветки 
//      {
//        MotorTest = 0;
//        lcd.clear();                     // Очистка дисплея
//        delay(1000);
//        break;
//      }
//      break;
//    }
//  }
//  delay (500);
//}

int FuncOkon (int Action)       // Функция управления моторами
{
 if (Action == Otkryt) 
 {
  
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
     
 }
   
 if (Action == Zakryt) 
 { 
  
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  
 }

}

//void Kontsevik () // Для отображения положения концевиков
//{
//  lcd.setCursor(3, 3);
//  lcd.print(digitalRead(KontsTylOtkr));
//  lcd.setCursor(8, 3);
//  lcd.print(digitalRead(KontsTylZakr));
//  lcd.setCursor(13, 3);
//  lcd.print(digitalRead(KontsFasOtkr));
//  lcd.setCursor(18, 3);
//  lcd.print(digitalRead(KontsFasZakr));
//}


void DecisionAfterSensors () 
{
  
  if (Rain<=GoRain && TempVozd<= Parametr[10] && Svet>=darkness ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain<=GoRain && TempVozd<= Parametr[10] && Svet<=lighting ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain<=GoRain && TempVozd>= Parametr[9] && Svet<=lighting ) 
  {
    FuncOkon(Otkryt);
    
    }
    else if (Rain<=GoRain && TempVozd>= Parametr[9] && Svet>=darkness ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd<= Parametr[10] && Svet>=darkness ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd<= Parametr[10] && Svet<=lighting ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd>= Parametr[9] && Svet>=darkness ) 
  {
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd>= Parametr[9] && Svet<=lighting ) 
  {
    FuncOkon(Otkryt);
    
    }
//      else 
//      {
//        
//        FuncOkon(Otkryt);
//        }
 }
