int pinCanal4 = 38;
int ch4,m4, citireSwitch;
int pinSwitchStanga = 52;
int pinSwitchDreapta = 50;
const int motorSD1_a = 10;
const int motorSD1_b = 11;
int strans = false;
const int motorSD2_a = 12;
const int motorSD2_b = 13;
const int senzor = A1;
long timp1;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinCanal4, INPUT);
}

int Switch(int brat) { //0-stanga; 1-dreapta
  if(brat == 0) {citireSwitch = digitalRead(pinSwitchStanga);}
  else {citireSwitch = digitalRead(pinSwitchDreapta);}
  return citireSwitch;
}


void Desfacere(){
   Serial.println("Desfacere");Serial.print("\n\n");
    strans = false;
    if(Switch(0) == 0){
      
    digitalWrite(motorSD1_a, LOW);
    digitalWrite(motorSD1_b, HIGH);
    }
    
    if(Switch(0) == 1){
      
    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, HIGH);
    }
    
    
    if(Switch(1) == 0){
      digitalWrite(motorSD2_a, LOW);
      digitalWrite(motorSD2_b, HIGH);
    }
      
    if(Switch(1) == 1){
      digitalWrite(motorSD2_a, HIGH);
      digitalWrite(motorSD2_b, HIGH);
    }

}




void Strangere(){
  
   Serial.print("Strangere \n\n");
    
   if(analogRead(senzor) > 480 && strans == false) {
     
    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, LOW);
        
    digitalWrite(motorSD2_a, HIGH);
    digitalWrite(motorSD2_b, LOW);
    }

   if(analogRead(senzor) < 475 && strans == false) {
    strans = true;
    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, HIGH);
        
    digitalWrite(motorSD2_a, HIGH);
    digitalWrite(motorSD2_b, HIGH);
   }
    
}

void Scurt(){
  
   digitalWrite(motorSD1_a, HIGH);
   digitalWrite(motorSD1_b, HIGH); 
   digitalWrite(motorSD2_a, HIGH);
   digitalWrite(motorSD2_b, HIGH);
}

/*int mediereSenzor(){
  int medieSenzor = 0;
  for (int c=1; c<=10; c++){
   medieSenzor += analogRead(senzor); 
  }
  medieSenzor /= 5;
  return medieSenzor;
}
*/


void loop() {
  // put your main code here, to run repeatedly:
   for (int c=1;c<=10;c++) {
     ch4 = pulseIn(pinCanal4,HIGH,15000);
     m4 += ch4;
    }
   m4 /= 10;
  if(m4  > 1700) Desfacere();
  if(m4 < 1500) Strangere();
  if(m4 > 1500 && m4 < 1700) {Scurt(); }
  Serial.println(m4);
  Serial.print("Senzor: ");Serial.print(analogRead(senzor));Serial.print("\n");

}
