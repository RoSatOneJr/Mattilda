//Cod pentru controlul caruciorului mobil / "miscare verticala"
//To-Do: Functiile Input -> PWM [ ]
//       Cam tot.
//Neprioritar: Comunicatie intre Mega si UNO
int ok, ch2, ch4, m2, m4;
int pinCanal2 = 12;
int pinCanal4 = 13;
int pinReleu = 14;
int vertical_max, vertical_centru_max;
int vertical_min, vertical_centru_min;
int fata_max, fata_centru_max;
int fata_min , fata_centru_min;
int m2_pwm_sus, m2_pwm_jos;

void setup() {

  pinMode(pinCanal2, INPUT); //input canal 2
  pinMode(pinCanal4, INPUT); //input canal 4
  pinMode(motor1, OUTPUT); //output motor1_a
  pinMode(motor2, OUTPUT); //output motor 2_a
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

void citire_medie() {
   m3 = pulseIn(pinCanal2,HIGH,15000); //citire canal 2 telecomanda
   m1 = pulseIn(pinCanal4, HIGH, 15000); //citire canal 4 telecomanda
   for (int c=1;c<=10;c++) {
     ch3 = pulseIn(pinCanal2,HIGH,15000);
     m3 = (m4 + ch4) / 2;
     ch1 = pulseIn(pinCanal4,HIGH,15000);
     m1 = (m2 + ch2) / 2;
   }

   ok = true;
   c = 0;
}



void miscareSus() {
  analogWrite(motor1, m2_pwm_sus);
  analogWrite(motor2, m2_pwm_sus);
}

void miscareJos() {
  analogWrite(motor1, m2_pwm_jos);
  analogWrite(motor2, m2_pwm_jos);
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
