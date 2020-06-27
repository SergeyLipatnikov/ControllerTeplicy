
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
 }

 void DisplayDataStatusSensors () {

  if (Rain <= GoRain) {

    lcd.setCursor(5, 1);
    lcd.print("Yes");
//    lcd.print (Rain);
    
    }
    else {
      
    lcd.setCursor(5, 1);
    lcd.print("No ");
//    lcd.print (Rain);  
      }

  if (Svet <= lighting) {
    
    lcd.setCursor(15, 1);
    lcd.print("Light");
    
    }
    else {
      
    lcd.setCursor(15, 1);
    lcd.print("Dark ");
      
      }  
  }
