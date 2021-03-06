const int pinCanal4 = 42; //Fata-Spate
const int pinCanal5 = 44; //Comanda pate!
const int pinCanal7 = 46; //Mod doar un motor
const int pinCanal8 = 48; //Switch Strangere-Desfacere

const int motorSD1_a = 10;
const int motorSD1_b = 11;

const int motorSD2_a = 12;
const int motorSD2_b = 13;

const int motorFS1_a = 6;
const int motorFS1_b = 7;

const int motorFS2_a = 4;
const int motorFS2_b = 5;


const int pinSenzorCurent = A0;
const int valMaxStr = 2000;//trebuie schimbata

const int pinSwitchStanga = 52;
const int pinSwitchDreapta = 50;

int stareSwitch;
int lastSwitch = LOW;
int citireSwitch;
long lastDebounceTime = 0;
long debounceDelay = 50;

int ok, m4, ch4, ch5, ch7, m7, ch8;
int RawValue= 0;
double Voltage = 0;
int fata_max, fata_centru, fata_min;
int strans_max, strans_min;
int m4_pwm_Fata, m4_pwm_Spate, m7_pwm_Strangere, m7_pwm_Desfacere;
int caz;
char inchar;
bool doarUnMotor = false;

double m_fata, m_spate;

void setup() {

  pinMode(pinCanal4, INPUT); //input canal 4
  pinMode(pinCanal5, INPUT); //input canal 5
  pinMode(pinCanal7, INPUT); //input canal 7
  pinMode(pinCanal8, INPUT); //input canal 8

  pinMode(pinSwitchStanga, INPUT);
  pinMode(pinSwitchDreapta, INPUT);

  pinMode(motorFS1_a, OUTPUT); //output motorSus Jos 1_a
  pinMode(motorFS1_b, OUTPUT); //output motor Sus Jos 1_b
  pinMode(motorFS2_a, OUTPUT); //output motor Sus Jos 2_a
  pinMode(motorFS2_b, OUTPUT); //output motor Sus Jos 2_b

  pinMode(motorSD1_a, OUTPUT); //output motor Fata Spate 1_a
  pinMode(motorSD1_b, OUTPUT); //output motor Fata Spate 1_b
  pinMode(motorSD2_a, OUTPUT); //output motor Fata Spate 2_a
  pinMode(motorSD2_b, OUTPUT); //output motor Fata Spate 2_b
  ok = false; //bool medie
  Serial.begin(19200); //baud-rate

}

//NOTA: "directie" trebuie sa fie 1 pentru fata-spate si 2 pentru sttrangere-desfacere
int schimbare(int x, int directie){
  int maxim, minim;

  switch (directie){
    case 1: { maxim = fata_max; minim = fata_min; break;}
    case 2: { maxim = strans_max; minim = strans_min; break;}
  }
  if(caz & (1 << (directie - 1) )){

    return maxim + minim - x;
  }

   else return x;
}


int pwmFata(int x){
  m4_pwm_Fata = (x - schimbare(fata_centru + 50, 1)) * m_fata + 100;
}

void pwmSpate(int x){
  m4_pwm_Spate = (x - schimbare(fata_min, 1) ) * m_spate;
}

int Switch(int brat) { //0-stanga; 1-dreapta
  if(brat == 0) {citireSwitch = digitalRead(pinSwitchStanga);}
  else {citireSwitch = digitalRead(pinSwitchDreapta);}
  if (stareSwitch != lastSwitch) {

    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {


    if (citireSwitch != stareSwitch) {
      stareSwitch = citireSwitch;
    }
  }

  lastSwitch = citireSwitch;
  return stareSwitch;
}


void miscareFata() {
  pwmFata(m4);
  analogWrite(motorFS1_a, m4_pwm_Fata);
  digitalWrite(motorFS1_b, LOW);

  if(!doarUnMotor){
    analogWrite(motorFS2_a, m4_pwm_Fata);
    digitalWrite(motorFS2_b, LOW);
  }
}

void miscareSpate() {
  pwmSpate(m4);
  analogWrite(motorFS1_a, m4_pwm_Spate);
  digitalWrite(motorFS1_b, HIGH);

  if(!doarUnMotor){
    analogWrite(motorFS2_a, m4_pwm_Spate);
    digitalWrite(motorFS2_b, HIGH);
  }
}

void miscareStrangere() {
    digitalWrite(motorSD1_a, HIGH);
    digitalWrite(motorSD1_b, LOW);
  if(!doarUnMotor){
    digitalWrite(motorSD2_a, HIGH);
    digitalWrite(motorSD2_b, LOW);
  }


}

void miscareDesfacere(){
  if(Switch(0) == 0){
    digitalWrite(motorSD1_a, LOW);
    digitalWrite(motorSD1_b, HIGH);
  }
  if(!doarUnMotor && Switch(1) == 0){
    digitalWrite(motorSD2_a, LOW);
    digitalWrite(motorSD2_b, HIGH);
  }
}

void brateInScurt() {
  digitalWrite(motorSD1_a, HIGH);
  digitalWrite(motorSD1_b, HIGH);
  digitalWrite(motorSD2_a, HIGH);
  digitalWrite(motorSD2_b, HIGH);
}
void caruciorInScurt() {
  digitalWrite(motorFS1_a, HIGH);
  digitalWrite(motorFS1_b, HIGH);
  digitalWrite(motorFS2_a, HIGH);
  digitalWrite(motorFS2_b, HIGH);
}



int val_senz_curent(){

   RawValue = analogRead(pinSenzorCurent);
   Voltage = (RawValue / 1023.0) * 5000; // Gets you mV

   if(Voltage < valMaxStr)
     return 1;
   else return 0;
}

void comandaStrangere(){

  if(val_senz_curent() == 1){
      miscareStrangere();
 }

}
void comandaDesfacere(){

  miscareDesfacere();
}

void comandaFata(){

  if(schimbare(m4, 1) > (fata_centru + 50) ){
    miscareFata();
  }
}

void comandaSpate(){

  if(schimbare(m4, 1) < (fata_centru - 50) ){
    miscareSpate();
  }

}


void prelucrare_date(){

  Serial.println("\n Incep prelucrarea datelor");
    if(fata_max < fata_centru) caz = (caz | 1);
    if(strans_max > strans_min) caz = (caz | 1 << 1);

    m_fata = 155 / (  schimbare(fata_max, 1) - schimbare(fata_centru + 50, 1) );
    m_spate = 155 / ( schimbare(fata_centru - 50, 1) - schimbare(fata_min, 1) );
}

void citire_medie() {

   ch4 = pulseIn(pinCanal4, HIGH, 15000);//citire canal 4 telecomanda
   ch5 = pulseIn(pinCanal5, HIGH, 15000);//citire canal 5 telecomanda
   ch7 = pulseIn(pinCanal7, HIGH, 15000);//citire canal 7 telecomanda
   ch8 = pulseIn(pinCanal8, HIGH, 15000);//citire canal 8 telecomanda
   for (int c=1;c<=10;c++) {
     ch7 = pulseIn(pinCanal7,HIGH,15000);
     ch4 = pulseIn(pinCanal4,HIGH,15000);
     m4 += ch4;
     m7 += ch7;
   }
   m7 /= 10;
   m4 /= 10;
   ok = true;
}

 void comenzi(){

  if (Serial.available() > 0) {
        inchar = Serial.read();
          if (inchar == 'c'){

              for(int i = 1; i <= 3; i++){

                if(i == 1){
                  Serial.println("Incep calibrarea.");
                  Serial.println("\n Tine joystick-ul centrat ");
                  delay(1000);
                  citire_medie();
                  fata_centru = m4;
                  Serial.print("\n Valoarile luate: CH4:"); Serial.print(fata_centru);
              }
               if(i == 2){
                 Serial.println("\n #######################################");
                 Serial.println("\n Tine joystick-ul in dreapta ");
                 delay(1000);
                 citire_medie();
                 fata_max = m4;
                 Serial.print("\n Valoare luata: "); Serial.print(fata_max);
               }
              if(i == 3){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in stanga ");
                delay(1000);
                citire_medie();
                fata_min = m4;

                 Serial.print("\n Valoare luata: "); Serial.print(fata_min);prelucrare_date();
              }

           }
        }
        if (inchar == 'v'){

          Serial.print("\n Centru FS: ");Serial.print( fata_centru );

            Serial.print("\n Fata maxim: ");Serial.print( schimbare( fata_max, 1) );
            Serial.print("\n Fata min: ");Serial.print( schimbare(fata_centru + 50, 1) ) ;
            Serial.print("\n Spate maxim: ");Serial.print( schimbare(fata_min, 1) );
            Serial.print("\n Spate min: ");Serial.print( schimbare(fata_centru - 50, 1) );

            Serial.print("\n Strans maxim: ");Serial.print( schimbare( strans_max, 2) );
            Serial.print("\n Strans min: ");Serial.print( schimbare( strans_min, 2) );

            Serial.print("\n Caz");Serial.print( caz );

          delay(1000);
      }
    }
  }


bool centrat(){
  if ( m4 > schimbare(fata_centru + 50, 1) || m4 < schimbare(fata_centru - 50, 1) ) {
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
  comenzi();
  if(schimbare(m7, 2) < 1700){
    doarUnMotor = true;
  }
  else {
    doarUnMotor = false;
  }

  if ( !centrat() ) {
    comandaFata();
    comandaSpate();

    if(ch5 > 1550){
      if(ch8 > 1500)
        comandaStrangere();
      else comandaDesfacere();
    }

  }
 else{
   //oprireReleu(); //Cica releul nu va mai fi folosit. \_(o_O)_/
   caruciorInScurt();
 }
}

void loop() {

  principal();

}
