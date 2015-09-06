//Cod de miscare versiunea 3.
//Feautures: Autocalibrare
//          Folosirea unui singur pin PWM/motor

int m1,m3, ok, ch3, c, ch1,marja_frana=50,i=0, m1_centru;
int m3_centru,dif1,dif2, m3_fata_max, m3_spate_max, m1_stanga_max;
int m1_dreapta_max, m3_fata_min, m3_spate_min, m1_stanga_min, m1_dreapta_min;
int motor1_a=2, motor1_b=30, motor2_a=3, motor2_b=31, motor3_a=4, motor3_b=32;
int motor4_a=5, motor4_b=33;
int m1_dreapta_max_m, m1_dreapta_min_m, m3_spate_min_m, m3_spate_max_m; //NOTA: inturile cu _m sunt folosite pentru a stoca marja pentru miscarile cu PWM pe ground
int stanga_mm = true, dreapta_mm = false, fata_mm = true, spate_mm = false;
int m3_pwm_fata, m3_pwm_spate, m1_pwm_stanga, m1_pwm_dreapta;
int coeficient_viraj = 0.25;
unsigned long current_millis, start_millis;
float m_fata,n_fata,m_spate,n_spate,m_dreapta,n_dreapta,m_stanga,n_stanga;
char inchar;
void setup() {
  pinMode(48, INPUT); //input canal 3
  pinMode(50, INPUT); //input canal 1
  pinMode(motor1_a, OUTPUT); //output motor1_a
  pinMode(motor1_b, OUTPUT); //output motor 1_b
  pinMode(motor2_a, OUTPUT); //output motor 2_a
  pinMode(motor2_b, OUTPUT); //output motor 2_b
  pinMode(motor3_a, OUTPUT); //output motor 3_a
  pinMode(motor3_b, OUTPUT); //output motor 3_b
  pinMode(motor4_a, OUTPUT); //output motor 4_a
  pinMode(motor4_b, OUTPUT); //output motor 4_b

  ok = false; //bool medie
  Serial.begin(19200); //baud-rate

}


void medie_pwm_fata(){
  m3_pwm_fata=m_fata * m3 + n_fata;
  if(m3_pwm_fata>255) m3_pwm_fata=255; Serial.println(m3_pwm_fata);

}

void medie_pwm_spate(){
  m3_pwm_spate=m_spate * m3 + n_spate;
  if (m3_pwm_spate>255) m3_pwm_fata=255;

}

void medie_pwm_dreapta(){
   m1_pwm_dreapta=m_dreapta * m1 + n_dreapta;
   if (m1_pwm_dreapta>255) m1_pwm_dreapta=255; Serial.println(m1_pwm_dreapta);

}

void medie_pwm_stanga(){
   m1_pwm_stanga=m_stanga * m1 + n_stanga;
   if(m1_pwm_stanga>255) m1_pwm_stanga=255; Serial.println(m1_pwm_stanga);

}

void citire_medie(){
   m3 = pulseIn(48,HIGH,15000); //citire canal 3 telecomanda
   m1 = pulseIn(50, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=1;c<=10;c++){
     ch3 = pulseIn(48,HIGH,15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(50,HIGH,15000);
     m1 = (m1 + ch1) / 2;
     if(c==1) dif1=ch3;
     if(c==10) dif2=ch3;
     if((dif2-dif1) > marja_frana ) frana();
   }
   ok=true;
   c=0;
}




//Functia folosita pentru virare Stanga+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaST_FATA(){

  if(((m1 > m1_stanga_min && stanga_mm == true) || (m1 < m1_stanga_min && m1 > 10 && dreapta_mm == true)) && ((m3 > m3_fata_min && fata_mm == true) || (m3 < m3_fata_min && m3 > 10 && spate_mm == true))) {
      medie_pwm_fata();
      medie_pwm_stanga();
      Serial.println("Comanda ST_FATA");

      analogWrite(motor1_a, m3_pwm_fata*coeficient_viraj);
      digitalWrite(motor1_b, LOW);

     analogWrite(motor2_a, m1_pwm_stanga);
     digitalWrite(motor2_b, LOW);

      analogWrite(motor3_a, m3_pwm_fata*coeficient_viraj);
      digitalWrite(motor3_b, LOW);

      analogWrite(motor4_a, m1_pwm_stanga);
      digitalWrite(motor4_b, LOW);
  }
}

//Functia folosita pentru virare Stanga+Spate "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1

void comandaST_SPATE(){

  if(((m1 > m1_stanga_min && stanga_mm == true) || (m1 < m1_stanga_min && m1 > 10 && dreapta_mm == true)) && ((m3 > m3_spate_min && spate_mm == true) || (m3 < m3_spate_min && m3 > 10 && fata_mm == true))) {
    medie_pwm_spate();
    medie_pwm_stanga();
    Serial.println("Comanda ST_spate");

    analogWrite(motor1_a, m3_pwm_spate*coeficient_viraj);
    digitalWrite(motor1_b, HIGH);

   analogWrite(motor2_a, m1_pwm_stanga);
   digitalWrite(motor2_b, HIGH);

    analogWrite(motor3_a, m3_pwm_spate*coeficient_viraj);
    digitalWrite(motor3_b, HIGH);

    analogWrite(motor4_a, m1_pwm_stanga);
    digitalWrite(motor4_b, HIGH);
  }
}


//Functia folosita pentru virare Dreapta+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1

void comandaDR_FATA(){
  if(((m1 > m1_dreapta_min_m && dreapta_mm == true) || (m1 < m1_dreapta_min_m && m1 > 10 && dreapta_mm == true)) && ((m3 > m3_fata_min && fata_mm == true) || (m3 < m3_fata_min && m3 > 10 && spate_mm == true))) {
    medie_pwm_fata();
    medie_pwm_dreapta();
    Serial.println("Comanda DR_fata");

    analogWrite(motor1_a, m1_pwm_dreapta); //pwm_dreapta
    digitalWrite(motor1_b, LOW);

    analogWrite(motor2_a, m3_pwm_fata*coeficient_viraj); Serial.println(m3_pwm_fata*coeficient_viraj);
    digitalWrite(motor2_b, LOW);

    analogWrite(motor3_a, m1_pwm_dreapta); //pwm_drapta
    digitalWrite(motor3_b, LOW);

    analogWrite(motor4_a, m3_pwm_fata*coeficient_viraj); Serial.println(m3_pwm_fata*coeficient_viraj);
    digitalWrite(motor4_b, LOW);


  }
}

void comandaDR_SPATE(){
    if(((m1 > m1_dreapta_min_m && dreapta_mm == true) || (m1 < m1_dreapta_min_m && m1 > 10 && stanga_mm == true)) && ((m3 > m3_spate_min_m && spate_mm == true) || (m3 < m3_spate_min_m && m3 > 10 && fata_mm == true))) {
    Serial.println("Comanda DR_spate");
    medie_pwm_spate();
    medie_pwm_dreapta();

    analogWrite(motor1_a, m1_pwm_dreapta);
    digitalWrite(motor1_b, HIGH);

    analogWrite(motor2_a, m3_pwm_fata*coeficient_viraj);
    digitalWrite(motor2_b, HIGH);

    analogWrite(motor3_a, m1_pwm_dreapta);
    digitalWrite(motor3_b, HIGH);

    analogWrite(motor4_a, m3_pwm_fata*coeficient_viraj);
    digitalWrite(motor4_b, HIGH);

  }

}

void Fata_simplu(){
    analogWrite(motor1_a, m3_pwm_fata);
    digitalWrite(motor1_b, LOW);
    analogWrite(motor2_a, m3_pwm_fata);
    digitalWrite(motor2_b, LOW);
    analogWrite(motor3_a, m3_pwm_fata);
    digitalWrite(motor3_b, LOW);
    analogWrite(motor4_a, m3_pwm_fata);
    digitalWrite(motor4_b, LOW);
  }

void Spate_simplu(){
      analogWrite(motor1_a, m3_pwm_spate);
      digitalWrite(motor1_b, HIGH);
      analogWrite(motor2_a, m3_pwm_spate);
      digitalWrite(motor2_b, HIGH);
      analogWrite(motor3_a, m3_pwm_spate);
      digitalWrite(motor3_b, HIGH);
      analogWrite(motor4_a, m3_pwm_spate);
      digitalWrite(motor4_b, HIGH);
}

void Stanga_simplu(){
      digitalWrite(motor1_a, LOW);
      analogWrite(motor1_b, m1_pwm_stanga);
      analogWrite(motor2_a, m1_pwm_stanga);
      digitalWrite(motor2_b, LOW);
      digitalWrite(motor3_a, LOW);
      analogWrite(motor3_b, m1_pwm_stanga);
      analogWrite(motor4_a, m1_pwm_stanga);
      digitalWrite(motor4_b, LOW);
}

void Dreapta_simpla(){
    analogWrite(motor1_a, m1_pwm_dreapta);
    digitalWrite(motor1_b, HIGH);
    digitalWrite(motor2_a, HIGH);
    analogWrite(motor2_b, m1_pwm_dreapta);
    analogWrite(motor3_a, m1_pwm_dreapta);
    digitalWrite(motor3_b, HIGH);
    digitalWrite(motor4_a, HIGH);
    analogWrite(motor4_b, m1_pwm_dreapta);

}

//Functia folosita pentru virare Stanga-Dreapta "CAZ 1"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaSTDR(){
  if( (( m1 > m1_stanga_min && stanga_mm == true ) || (m1 < m1_stanga_min && m1 > 10 && dreapta_mm == true)) && !((m3 > m3_fata_min && m3 < m3_spate_min_m ) || (m3 > m3_spate_min_m && m3 < m3_fata_min)) ){ //Stanga
    medie_pwm_stanga();//functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Serial.println("Comanda Stanga simpla");
    Stanga_simplu();
  }
  else if( (( m1 > m1_dreapta_min_m && dreapta_mm == true ) || (m1 < m1_dreapta_min_m && m1 > 10 && stanga_mm == true)) && !((m3 > m3_fata_min && m3 < m3_spate_min_m ) || (m3 > m3_spate_min_m && m3 < m3_fata_min)) ){ //Dreapta
    Serial.println("Comanda Dreapta simpla");
    medie_pwm_dreapta(); //functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
  }
}

//Functia folosita pentru miscarea-fata spate
void comandaFATA_SPATE(){
  if( ((m3 > m3_fata_min && fata_mm == true) || (m3 < m3_fata_min && m3 > 10 && spate_mm == true)) && !((m1 > m1_stanga_min && m1 < m1_dreapta_min_m) || (m1 > m1_dreapta_min_m && m1 < m1_stanga_min)) ){ //fata
    Serial.println("Comanda fata simpla");
    medie_pwm_fata(); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Fata_simplu();

  }

  else if( ((m3 > m3_spate_min_m && spate_mm == true) || (m3 < m3_spate_min_m && m3 > 10 && fata_mm == true)) && !((m1 > m1_stanga_min && m1 < m1_dreapta_min) || (m1 > m1_dreapta_min_m && m1 < m1_stanga_min)) ){ // spate
    medie_pwm_spate(); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Serial.println("Comanda spate simpla");
    Spate_simplu();
  }

}

void frana(){
  digitalWrite(motor1_a, HIGH);
  digitalWrite(motor1_b, HIGH);
  digitalWrite(motor2_a, HIGH);
  digitalWrite(motor2_b, HIGH);
  digitalWrite(motor3_a, HIGH);
  digitalWrite(motor3_b, HIGH);
  digitalWrite(motor4_a, HIGH);
  digitalWrite(motor4_b, HIGH);
}

void citire_medie_calibrare(){
   m3 = pulseIn(48,HIGH,15000); //citire canal 3 telecomanda
   m1 = pulseIn(50, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=1;c<=60;c++){
     ch3 = pulseIn(48,HIGH,15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(50,HIGH,15000);
     m1 = (m1 + ch1) / 2;
   }
}

void afisare(){
  Serial.print("Channel3:");
  Serial.println(ch3);

  Serial.print("Channel1:");
  Serial.println(ch1);

  Serial.println("###########################");
}


void prelucrare_date(){
  Serial.print("\n Incep prelucrarea datelor");
    if(m3_fata_max > m3_spate_max) {m3_fata_min = m3_centru + 50;m3_spate_min = m3_centru - 50; fata_mm = true;}
     else{m3_fata_min = m3_centru-50; m3_spate_min=m3_centru + 50; spate_mm = true;}
    if(m1_stanga_max > m1_dreapta_max){m1_stanga_min=m1_centru + 50;m1_dreapta_min=m1_centru - 50; stanga_mm = true;}
      else{m1_stanga_min=m1_centru - 50;m1_dreapta_min=m1_centru + 50; dreapta_mm = true;}

    //a = min
    //b = max
    int m1_dreapta_max_c = m1_dreapta_max; //copie a m1_dreapta_max
    m1_dreapta_max_m = m1_dreapta_max; //Marja
    m1_dreapta_max = m1_dreapta_min; //liniile astea au fost adaugate pentru ca pe dreapta voi folosi PWM ca ground si trebuia inversata functia
    m1_dreapta_min_m = m1_dreapta_min; //Marja
    m1_dreapta_min = m1_dreapta_max_c;

    int m3_spate_max_c = m3_spate_max; //Citeste comentariile de mai sus
    m3_spate_max_m = m3_spate_max; //Marja
    m3_spate_max = m3_spate_min; //Aceeasi chestie si aici ^
    m3_spate_min_m = m3_spate_min; //Marja
    m3_spate_min = m3_spate_max_c;

    m_fata = 155 / (m3_fata_max - m3_fata_min);
    n_fata = 100 - (155 / (m3_fata_max - m3_fata_min))*m3_fata_min;
    m_spate = 255 / (m3_spate_max - m3_spate_min);
    n_spate = 0 - (155 / (m3_spate_max - m3_spate_min))*m3_spate_min;
    m_stanga = 155/(m1_stanga_max - m1_stanga_min);
    n_stanga = 100 - (155 / (m1_stanga_max - m1_stanga_min))*m1_stanga_min;
    m_dreapta = 255 / (m1_dreapta_max - m1_dreapta_min);
    n_dreapta = 0 - (155 / (m1_dreapta_max - m1_dreapta_min))*m1_dreapta_min;

}
void comenzi(){
  if (Serial.available() > 0) {
        inchar = Serial.read();
          if (inchar == 'c'){
//              start_millis= millis();
              for(i=0;i<=5;i++){
//                current_millis=millis();
                if(i==1){
                  Serial.println("Incep calibrarea.");
                  Serial.println("\n Tine joystick-ul centrat ");
                  delay(1000);
                  citire_medie_calibrare();
                  m1_centru = m1;
                  m3_centru = m3;
                  Serial.print("\n Valoarile luate: CH1:"); Serial.print(m1);Serial.print("; CH3: ");Serial.print(m3);
              }
               if(i==2){
                 Serial.println("\n #######################################");
                 Serial.println("\n Tine joystick-ul in fata ");
                 delay(1000);
                 citire_medie_calibrare();
                 m3_fata_max = m3;
                 Serial.print("\n Valoare luata: "); Serial.print(m3_fata_max);
               }
              if(i==3){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in spate ");
                delay(1000);
                citire_medie_calibrare();
                 m3_spate_max = m3;
                 Serial.print("\n Valoare luata: "); Serial.print(m3_spate_max);
              }
              if(i==4){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in stanga ");
                delay(1000);
                citire_medie_calibrare();
                m1_stanga_max = m1;
                Serial.print("\n Valoare luata: "); Serial.print(m1_stanga_max);
              }
               if(i==5){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in dreapta");
                delay(1000);
                citire_medie_calibrare();
                m1_dreapta_max = m1;
                Serial.print("\n Valoare luata: "); Serial.print(m1_dreapta_max); break;
              }
              prelucrare_date();
           }
        }
    }
  }

bool centrat(){
  if( (fata_mm == true && m3 < m3_fata_min && m3 > m3_spate_min_m ) && ( stanga_mm == true && m1 < m1_stanga_min && m1 > m1_dreapta_min_m ) ) {return false;}
  if( (fata_mm == true && m3 < m3_fata_min && m3 > m3_spate_min_m ) && ( dreapta_mm == true && m1 < m1_dreapta_min_m && m1 > m1_stanga_min ) ) {return false;}
  if( (spate_mm == true && m3 < m3_spate_min_m && m3 > m3_fata_min ) && ( stanga_mm == true && m1 < m1_stanga_min && m1 > m1_dreapta_min_m ) ) {return false;}
  if( (spate_mm == true && m3 < m3_spate_min_m && m3 > m3_fata_min ) && ( dreapta_mm == true && m1 < m1_dreapta_min_m && m1 > m1_stanga_min ) ) {return false;}
  return true;
}


void principal(){ //Pune functiile impreuna
  comenzi();
 if(ok!=true) citire_medie();
  else{
    if( centrat() ){ //verifica daca e joystickul nu e centrat
      comandaST_FATA(); //cazul 2 de virare, pentru stanga+fata
      comandaST_SPATE(); //cazul 2 de virare, pentru stanga+spate
      comandaDR_FATA(); //cazul 2 de virare, pentru dreapta+fata
      comandaDR_SPATE(); //cazul 2 de virare, pentru dreapta+fata
      comandaSTDR(); //cazul 1 de virare
      comandaFATA_SPATE(); //miscare de baza fata-spate
    }
     else {frana();}
    afisare();
    ok = false;
//whatever
  }
}


void loop(){
  principal();
}
