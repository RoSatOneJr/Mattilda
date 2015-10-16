//Cod pentru controlul caruciorului mobil / "miscare verticala"
//To-Do: Functiile Input -> PWM [ ]
//       Cam tot.
//Neprioritar: Comunicatie intre Mega si UNO
int ok, ch2, ch4, m2, m4;
const int pinCanal2 = 12;
const int pinCanal4 = 13;
const int pinCanal5 = 14;
const int pinReleu = 15;
const int motorSJ1 = 16;
const int motorSJ2 = 17;
const int motorSD1 = 18;
const int motorSD2 = 19;
int vertical_max, vertical_centru;
int vertical_min;
int fata_max, fata_centru;
int fata_min;
int m2_pwm_sus, m2_pwm_jos;
bool doarUnMotor = false;

void setup() {

  pinMode(pinCanal2, INPUT); //input canal 2
  pinMode(pinCanal4, INPUT); //input canal 4
  pinMode(pinCanal5, INPUT); //input canal 5
  pinMode(motorSJ1, OUTPUT); //output motorSJ1_a
  pinMode(motorSJ2, OUTPUT); //output motor 2_a
  ok = false; //bool medie
  Serial.begin(19200); //baud-rate

}

void pwmSus(){
//Matematica care ne bate aici

}

void pwmJos(){
//Matematica care ne bate aici

}

void pwmStrangere(){
//Matematica care ne bate aici

}

void pwmDesfacere(){
//Matematica care ne bate aici

}

void pwmFata(){
//Matematica care ne bate aici

}

void pwmSpate(){
//Matematica care ne bate aici

}
void citire_medie() {
   m2 = pulseIn(pinCanal2, HIGH,15000); //citire canal 2 telecomanda
   m4 = pulseIn(pinCanal4, HIGH, 15000); //citire canal 4 telecomanda
   ch5 = pulseIn(pinCanal5, HIGH, 15000);//citire canal 5 telecomanda
   for (int c=1;c<=10;c++) {
     ch3 = pulseIn(pinCanal2,HIGH,15000);
     m3 = (m4 + ch4) / 2;
     ch2 = pulseIn(pinCanal4,HIGH,15000);
     m2 = (m2 + ch2) / 2;
   }

   ok = true;
   c = 0;
}



void miscareSus() {
  analogWrite(motorSJ1, m2_pwm_sus);
  if(!doarUnMotor)
    analogWrite(motorSJ2, m2_pwm_sus);
}

void miscareJos() {
  analogWrite(motorSJ1, m2_pwm_jos);
  if(!doarUnMotor)
    analogWrite(motorSJ2, m2_pwm_jos);
}

void miscareStrangere() {
  //comenzile pentru motoare aici

}

void miscareDesfacere(){
  //comenzile pentru motoare aici

}

void comandaSus(){
  //if(conditie){
  miscareSus();
 //}
}

void comandaJos(){
  //if(conditie){
  miscareJos();
 //}
}

void comandaStrangere(){
  //if(conditie){
  miscareStrangere();
 //}
}

void comandaDesfacere(){
  //if(conditie){
  miscareDesfacere();
 //}
}

void oprireReleu(){
  digitalWrite(pinReleu, LOW);

}

bool centrat(){
  if (m2 > vertical_centru_max || m2 < vertical_centru_min || m4 > fata_centru_max || m4 < fata_centru_min ) {
      Serial.println("Nu e centrat");
      return false;
     }
  else {
    Serial.println("E centrat");
    return true;
  }

}

void principal() {
  citire_medie();
  if(ch5 > 1500)
    doarUnMotor = true;
  else doarUnMotor = false;
  
  if ( !centrat() ) {
    comandaSus();
    comandaJos();
    comandaStrangere();
    comandaDesfacere();
    //conditii miscari

  }
 else(){
   oprireReleu();

 }
}

void loop() {

  principal();

}
