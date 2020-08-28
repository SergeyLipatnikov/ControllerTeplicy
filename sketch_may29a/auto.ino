
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
GoRain = Parametr[2];
OutRain = Parametr[3];
lighting = Parametr[4];
darkness = Parametr[5];
tempOpen = Parametr[0];
tempClose = Parametr[1];
  
  if (Rain<=GoRain && TempVozd<= tempClose && Svet>=darkness ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain<=GoRain && TempVozd<= tempClose && Svet<=lighting ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain<=GoRain && TempVozd>= tempOpen && Svet<=lighting ) 
  {
    DecisionSensors = 1;
    
    FuncOkon(Otkryt);
    
    }
    else if (Rain<=GoRain && TempVozd>= tempOpen && Svet>=darkness ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd<= tempClose && Svet>=darkness ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd<= tempClose && Svet<=lighting ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd>= tempOpen && Svet>=darkness ) 
  {
    DecisionSensors = 0;
    
    FuncOkon(Zakryt);
    
    }
    else if (Rain>=OutRain && TempVozd>= tempOpen && Svet<=lighting ) 
  {
    DecisionSensors = 1;
    
    FuncOkon(Otkryt);
    
    }
 }

// void DisplayDataStatusSensors () {
//
//  if (Rain <= GoRain) {
//
//    lcd.setCursor(5, 1);
//    lcd.print("Yes");
////    lcd.print (Rain);
//    
//    }
//    else {
//      
//    lcd.setCursor(5, 1);
//    lcd.print("No ");
////    lcd.print (Rain);  
//      }
//
//  if (Svet <= lighting) {
//    
//    lcd.setCursor(15, 1);
//    lcd.print("Light");
//    
//    }
//    else {
//      
//    lcd.setCursor(15, 1);
//    lcd.print("Dark ");
//      
//      }
//
//    lcd.setCursor(15,0);
//    DoorStatusDisplay ();
//  }

void DoorStatusDisplay () {

  
  if (StatusDoor == 0){
    
    lcd.print("Clos");
    
    }
    else {
      
    lcd.print("Open");
      
      }
  
  }

void ChangeStatusDoorOpen () {

  ActiveStatusDoor = true;
  
  if (button_state[Button_Right]&ST_UNPRESSURE) // Если кнопка вправо нажата, увеличиваем значение параметра
        {
          
        SetButtonState(Button_Right, ST_LOCKED);

        ResetButtonState(Button_Right, ST_UNPRESSURE);

        SetButtonState(Button_Right, ST_PRESSURE);

        ResetButtonState(Button_Right, ST_LOCKED);
          
        StatusDoor = !StatusDoor;

        ChangeStatus = StatusDoor;

        lcd.setCursor(12,0);
        
        DoorStatusDisplay ();
          
        }
      
      
      
        if (button_state[Button_Left]&ST_UNPRESSURE)  // То же для кнопки влево
        {
          
        SetButtonState(Button_Left, ST_LOCKED);

        ResetButtonState(Button_Left, ST_UNPRESSURE);

        SetButtonState(Button_Left, ST_PRESSURE);

        ResetButtonState(Button_Left, ST_LOCKED);

        StatusDoor = !StatusDoor;

        ChangeStatus = StatusDoor;

        lcd.setCursor(12,0);

        DoorStatusDisplay ();

        ActiveStatusDoor = 0;
        
        }
        
  }

 void AutomaticsDoorOpenFunction () {

    if (StatusDoor == 1) {

        FuncOkon(Otkryt);

    }

    else {
      
     FuncOkon(Zakryt); 
      
      }

  

//    if (ActiveStatusDoor ==  ChangeStatus) {
//      
//      if (DecisionSensors == 1) {
//
//        FuncOkon(Otkryt);
//
//        lcd.setCursor(10, 2);
//    lcd.print("Open");
//
////        Parametr[8] = 1;
////
////        StatusDoor = 1;
//
////        ActiveStatusDoor = 1;
////        
////        ChangeStatus = 1;
//        
//        }
//        
//       else {
//
//        FuncOkon(Zakryt);
//
//        lcd.setCursor(10, 2);
//    lcd.print("Close");
//
////        Parametr[8] = 0;
////
////         StatusDoor = 0;
//
////        ActiveStatusDoor = 0;
////        
////        ChangeStatus = 0;      
//        
//        }
//        
//      }
//
//    else {
//      
//      if (ChangeStatus == 1) {
//        
//        FuncOkon(Otkryt);
//
//        lcd.setCursor(10, 2);
//    lcd.print("Open");
//
////        Parametr[8] = 1;
////
////         StatusDoor = 1;
//
////        ActiveStatusDoor = 1;
////        
////        ChangeStatus = 1;
//        
//        }
//
//       else {
//        
//        FuncOkon(Zakryt);
//
//        lcd.setCursor(10, 2);
//        lcd.print("Close");
//
////        Parametr[8] = 0;
////
////        StatusDoor = 0;
//
////        ActiveStatusDoor = 0;
////        
////        ChangeStatus = 0;    
//        
//        }
//      
//      }
      
  
  }
