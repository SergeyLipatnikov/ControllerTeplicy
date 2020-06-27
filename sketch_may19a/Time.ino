void printTimeData() {

  timehour = rtc.getHours();                   
  timemin = rtc.getMinutes();                       
  timesec = rtc.getSeconds();
  timeday = rtc.getDay();                       
  timemounth = rtc.getDate();                    
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
  
  if (timeday < 10)
  { 
    lcd.setCursor(10,3);
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
