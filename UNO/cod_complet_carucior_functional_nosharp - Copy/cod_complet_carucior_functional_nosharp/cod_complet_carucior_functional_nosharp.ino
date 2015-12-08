const int pinCanal4 = 42; //Fata-Spate
const int pinCanal5 = 44; //Comanda pate!
const int pinCanal7 = 46; //Mod doar un motor
const int pinCanal8 = 48; //Switch Strangere-Desfacere

const int motorSD1_a = 10;//stanga
const int motorSD1_b = 11;

const int motorSD2_a = 4;//dreapta
const int motorSD2_b = 5;

const int motorFS1_a = 6;//
const int motorFS1_b = 7;

const int motorFS2_a = 0;
const int motorFS2_b = 0;


const int senzor_brate = A0;
const int senzor_fata_spate = A0;

const int pinSwitchStanga = 52;
const int pinSwitchDreapta = 50;

int ch4, m4, ch5, ch8, ch7, citireSwitch;
int strans = false, maxim_fata = false, maxim_spate = false;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pinCanal4, INPUT);
  pinMode(pinCanal5, INPUT);
  pinMode(pinCanal7, INPUT);
  pinMode(pinCanal8, INPUT);
  pinMode(pinSwitchStanga, INPUT);
  pinMode(pinSwitchDreapta, INPUT);
  pinMode(senzor_brate, INPUT);
  pinMode(pinCanal4, INPUT);
  pinMode(motorSD1_a, OUTPUT);
  pinMode(motorSD1_b, OUTPUT);
  pinMode(motorSD2_a, OUTPUT);
  pinMode(motorSD2_b, OUTPUT);
  pinMode(motorFS1_a, OUTPUT);
  pinMode(motorFS1_b, OUTPUT);
  pinMode(motorFS2_a, OUTPUT);
  pinMode(motorFS2_b, OUTPUT);
  digitalWrite(motorSD1_a, LOW);
  digitalWrite(motorSD1_b, LOW);
  digitalWrite(motorSD2_a, LOW);
  digitalWrite(motorSD2_b, LOW);
  digitalWrite(motorFS1_a, LOW);
  digitalWrite(motorFS1_b, LOW);
  digitalWrite(motorFS2_a, LOW);
  digitalWrite(motorFS2_b, LOW);
  
  
}

int Switch(int brat) { //0-stanga; 1-dreapta
  if(brat == 0) {citireSwitch = digitalRead(pinSwitchStanga);}
  else {citireSwitch = digitalRead(pinSwitchDreapta);}
  Serial.print("Switch: ");Serial.print(citireSwitch);Serial.print("\n"); 
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

  if(ch7 > 1500){
    Serial.println("MOTOR 2");
    if(Switch(1) == 0){
      digitalWrite(motorSD2_a, LOW);
      digitalWrite(motorSD2_b, HIGH);
    }

    if(Switch(1) == 1){
      digitalWrite(motorSD2_a, HIGH);
      digitalWrite(motorSD2_b, HIGH);
    }
  }
}

void Strangere(){

   Serial.print("Strangere \n\n");

   if(analogRead(senzor_brate) > 480 && strans == false) {

    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, LOW);

    digitalWrite(motorSD2_a, HIGH);
    digitalWrite(motorSD2_b, LOW);
    }
  if(ch7 > 1500){
    Serial.println("MOTOR 2");
   if(analogRead(senzor_brate) < 475 && strans == false) {
    strans = true;
    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, HIGH);

    digitalWrite(motorSD2_a, HIGH);
    digitalWrite(motorSD2_b, HIGH);
   }
  }

}

void Scurt_brate(){

   digitalWrite(motorSD1_a, HIGH);
   digitalWrite(motorSD1_b, HIGH);
   digitalWrite(motorSD2_a, HIGH);
   digitalWrite(motorSD2_b, HIGH);
}


void Fata(){
   Serial.println("Fata");
   if((analogRead(senzor_fata_spate) > 460) && maxim_fata == false){
    
   digitalWrite(motorFS1_a, HIGH);
   digitalWrite(motorFS1_b, LOW);
   digitalWrite(motorFS2_a, HIGH);
   digitalWrite(motorFS2_b, LOW);
   maxim_spate = false;
  }

 if((analogRead(senzor_fata_spate)  < 460) && maxim_fata == false){
   digitalWrite(motorFS1_a, HIGH);
   digitalWrite(motorFS1_b, HIGH);
   digitalWrite(motorFS2_a, HIGH);
   digitalWrite(motorFS2_b, HIGH);
   maxim_fata = true;
 }
  
}

void Spate(){
   Serial.println("Spate");

   if((analogRead(senzor_fata_spate) > 460) && maxim_spate == false){
    
   digitalWrite(motorFS1_a, LOW);
   digitalWrite(motorFS1_b, HIGH);
   digitalWrite(motorFS2_a, LOW);
   digitalWrite(motorFS2_b, HIGH);
   maxim_fata = false;
  }

 if((analogRead(senzor_fata_spate) < 460 ) && maxim_spate == false){

   digitalWrite(motorFS1_a, HIGH);
   digitalWrite(motorFS1_b, HIGH);
   digitalWrite(motorFS2_a, HIGH);
   digitalWrite(motorFS2_b, HIGH); 
   maxim_spate = true;
  } 
}

void Scurt_fata_spate(){
  
   digitalWrite(motorFS1_a, HIGH);
   digitalWrite(motorFS1_b, HIGH);
   digitalWrite(motorFS2_a, HIGH);
   digitalWrite(motorFS2_b, HIGH);
}

void Citire(){
  for (int c=1;c<=10;c++) {  
    ch4 = pulseIn(pinCanal4,HIGH,30000);
    m4 += ch4;
  }
   m4 /= 10;
   ch5 = pulseIn(pinCanal5, HIGH, 28000);
   ch7 = pulseIn(pinCanal7, HIGH, 28000);
   ch8 = pulseIn(pinCanal8, HIGH, 28000);
}


void loop() {
  Citire();
  if(ch5  > 1200){
    
    if(ch8 < 1500){ Desfacere();}
    if(ch8 > 1500){ Strangere();}
   }
  if(ch5 < 1200 ) {Scurt_brate();}
  
  if(m4 > 1700) { Fata();}
  if(m4 < 1450) { Spate();}
  if(m4 > 1500 && m4 < 1700) {Scurt_fata_spate();}
  Serial.print("A0: ");Serial.print(analogRead(A0));Serial.print("\n");
  Serial.print("A1: ");Serial.print(analogRead(A1));Serial.print("\n");
  Serial.print("A2: ");Serial.print(analogRead(A2));Serial.print("\n");
 //Serial.println(ch5);
  //Serial.println(m4);
 // Serial.println(ch7);
 //   Serial.println("##############");
//    Serial.print("Senzor: ");Serial.print(analogRead(senzor));Serial.print("\n");

}
