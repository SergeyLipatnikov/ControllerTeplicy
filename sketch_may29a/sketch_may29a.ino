void setup() {
  
pinMode (4, OUTPUT);    // пин мотора открывания форточки тыла 1 - выход
pinMode (5, OUTPUT);

}

void loop() {

  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);   

  delay(3000);
    
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);

  delay(3000);

}
