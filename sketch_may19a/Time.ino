void TimeData(){

DateTime now = rtc.now();           // получение даты - времени
   timehour = now.hour();          // Переменная для считывания времени (часы)
   timemin = now.minute();         // Переменная для считывания времени (минуты)
   timeday = now.date();           // Переменная для считывания времени (минуты)
  
   lcd.setCursor(14,0);                // Начинаем выводить данные на дисплей
   
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
  lcd.setCursor(17,0);
   
  if (timemin < 10)
  { 
    lcd.print("0");
    lcd.print(timemin);
  }
  else
  {
    lcd.print(timemin);
  }
}
