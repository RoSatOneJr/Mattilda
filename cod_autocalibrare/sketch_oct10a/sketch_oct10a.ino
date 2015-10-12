//Cod de miscare versiunea 3.
//Feautures: Autocalibrare
//          Folosirea unui singur pin PWM/motor

int m1, m3, ok, ch3, c, ch1, marja_frana=50, i=0;
float dif1, dif2, m3_fata_max, m3_spate_max, m1_dreapta_max, m1_stanga_max;
int motor1_a=2, motor1_b=30, motor2_a=3, motor2_b=31, motor3_a=4, motor3_b=32;
int motor4_a=5, motor4_b=33;
int m1_dreapta_max_m, m1_dreapta_min_m, m3_spate_min_m, m3_spate_max_m; //NOTA: inturile cu _m sunt folosite pentru a stoca marja pentru miscarile cu PWM pe ground
int m3_pwm_fata, m3_pwm_spate, m1_pwm_stanga, m1_pwm_dreapta;
int coeficient_viraj = 0.25;
double m3_centru = 1450, m_fata = 1870, m_spate = 1050, m1_centru = 1505, m_dreapta = 1920, m_stanga = 1090;
char inchar;
int caz = 0;

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
//NOTA: directie trebuie sa fie 1 pentru fata-spate si 2 pentru stanga-dreapta
int schimbare(int x, int directie){
  int maxim, minim;

  switch (directie){
    case 1: { maxim = m3_fata_max; minim = m3_spate_max; break;} 
    case 2: { maxim = m1_dreapta_max; minim = m1_stanga_max; break;} 
  }
  if(caz & (1 << (directie - 1) )){

    return maxim + minim - x;
  }
    
   else return x;
}

void medie_pwm_stanga(int x){
   m1_pwm_stanga = 100 + ( ( m1_centru - 50) - x ) * m_stanga;
   if(m1_pwm_stanga>255) m1_pwm_stanga=255; Serial.println(m1_pwm_stanga);

   
}

void medie_pwm_dreapta(int x){
   m1_pwm_dreapta = 155 - (x - ( m1_centru + 50 ) ) * m_dreapta;
   if (m1_pwm_dreapta>255) m1_pwm_dreapta=255; Serial.println(m1_pwm_dreapta);

}

void medie_pwm_fata(int x){
  m3_pwm_fata = 100 + ( x - (m3_centru + 50) ) * m_fata;
  if(m3_pwm_fata>255) m3_pwm_fata=255; Serial.println(m3_pwm_fata);

}

void medie_pwm_spate(int x){
  m3_pwm_spate = ( x - schimbare(m3_spate_max, 1) ) * m_spate;
  if (m3_pwm_spate > 255) m3_pwm_fata=255;Serial.println(m3_pwm_spate);

}


void citire_medie(){
   m3 = pulseIn(48,HIGH,15000); //citire canal 3 telecomanda
   m1 = pulseIn(50, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=1;c<=10;c++){
     ch3 = pulseIn(48,HIGH,15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(50,HIGH,15000);
     m1 = (m1 + ch1) / 2;
     if( c==1 ) dif1=ch3;
     if( c==10 ) dif2=ch3;
     if( (dif2-dif1) > marja_frana ) frana();
   }
   ok = true;
   c = 0;
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

void Dreapta_simplu(){
    analogWrite(motor1_a, m1_pwm_dreapta);
    digitalWrite(motor1_b, HIGH);
    digitalWrite(motor2_a, HIGH);
    analogWrite(motor2_b, m1_pwm_dreapta);
    analogWrite(motor3_a, m1_pwm_dreapta);
    digitalWrite(motor3_b, HIGH);
    digitalWrite(motor4_a, HIGH);
    analogWrite(motor4_b, m1_pwm_dreapta);
}




//Functia folosita pentru virare Stanga+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaST_FATA(){

  if( schimbare(m1, 2) < (m1_centru - 50) && schimbare(m3, 1) > (m3_centru + 50) ){
      medie_pwm_fata( schimbare(m3, 1) );
      medie_pwm_stanga( schimbare(m1, 2) );
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

  if( schimbare(m1, 2) < (m1_centru - 50) && schimbare(m3, 1) < (m3_centru - 50) ){
    medie_pwm_spate( schimbare(m3, 1) );
    medie_pwm_stanga( schimbare(m1, 2) );
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
  if( schimbare(m1, 2) > (m1_centru + 50) && schimbare(m3, 1) > (m3_centru + 50) ){
    medie_pwm_fata( schimbare(m3, 1) );
    medie_pwm_dreapta( schimbare(m1, 2) );
    Serial.println("Comanda DR_fata");

    analogWrite(motor1_a, m1_pwm_dreapta); //pwm_dreapta
    digitalWrite(motor1_b, LOW);

    analogWrite(motor2_a, m3_pwm_fata * coeficient_viraj); Serial.println(m3_pwm_fata * coeficient_viraj);
    digitalWrite(motor2_b, LOW);

    analogWrite(motor3_a, m1_pwm_dreapta); //pwm_drapta
    digitalWrite(motor3_b, LOW);

    analogWrite(motor4_a, m3_pwm_fata * coeficient_viraj); Serial.println(m3_pwm_fata * coeficient_viraj);
    digitalWrite(motor4_b, LOW);
  }
}

void comandaDR_SPATE(){
    if( schimbare(m1, 2) > (m1_centru + 50) && schimbare(m3, 1) < (m3_centru - 50) ){
    Serial.println("Comanda DR_spate");
    medie_pwm_spate( schimbare(m3, 1) );
    medie_pwm_dreapta( schimbare(m1, 2) );

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



//Functia folosita pentru virare Stanga-Dreapta "CAZ 1"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaSTDR(){
  
  if( schimbare(m1, 2) < (m1_centru - 50) ){ //Stanga
    medie_pwm_stanga( schimbare(m1, 2) );//functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Serial.println("Comanda Stanga simpla");
    Stanga_simplu();
  }
  else if( schimbare(m1, 2) > (m1_centru + 50) ){ //Dreapta
    Serial.println("Comanda Dreapta simpla");
    medie_pwm_dreapta( schimbare(m1, 2) ); //functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Dreapta_simplu();
  }
}

//Functia folosita pentru miscarea-fata spate
void comandaFATA_SPATE(){

  if( schimbare(m3, 1) > (m3_centru + 50) ){ //fata
    Serial.println("Comanda fata simpla");
    medie_pwm_fata( schimbare(m3, 1) ); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    Fata_simplu();

  }

  else if( schimbare(m3, 1) < (m3_centru - 50) ){ // spate
    medie_pwm_spate( schimbare(m3, 1) ); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
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
   m3 = pulseIn(48, HIGH, 15000); //citire canal 3 telecomanda
   m1 = pulseIn(50, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=1;c<=60;c++){
     ch3 = pulseIn(48, HIGH, 15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(50, HIGH, 15000);
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
  Serial.println("\n Incep prelucrarea datelor");
    if(m3_fata_max < m3_centru) caz = (caz | 1);
    if(m1_stanga_max > m1_centru) caz = (caz | 1 << 1);
    
    
    m_fata = 155 / (  schimbare(m3_fata_max, 1) - (m3_centru + 50) );
    m_spate = 155 / ( (m3_centru - 50) - schimbare(m3_spate_max, 1) );
    m_stanga = 155 / ( (m1_centru - 50) - schimbare(m1_stanga_max, 2) );
    m_dreapta = 155 / ( schimbare(m1_dreapta_max, 2) - (m1_centru + 50) );
}








void comenzi(){
  if (Serial.available() > 0) {
        inchar = Serial.read();
          if (inchar == 'c'){

              for(i = 0; i <= 5; i++){

                if(i == 1){
                  Serial.println("Incep calibrarea.");
                  Serial.println("\n Tine joystick-ul centrat ");
                  delay(1000);
                  citire_medie_calibrare();
                  m1_centru = m1;
                  m3_centru = m3;
                  Serial.print("\n Valoarile luate: CH1:"); Serial.print(m1);Serial.print("; CH3: ");Serial.print(m3);
              }
               if(i == 2){
                 Serial.println("\n #######################################");
                 Serial.println("\n Tine joystick-ul in fata ");
                 delay(1000);
                 citire_medie_calibrare();
                 m3_fata_max = m3;
                 Serial.print("\n Valoare luata: "); Serial.print(m3_fata_max);
               }
              if(i == 3){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in spate ");
                delay(1000);
                citire_medie_calibrare();
                 m3_spate_max = m3;

                 Serial.print("\n Valoare luata: "); Serial.print(m3_spate_max);
              }
              if(i == 4){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in stanga ");
                delay(1000);
                citire_medie_calibrare();
                m1_stanga_max = m1;
                Serial.print("\n Valoare luata: "); Serial.print(m1_stanga_max);
              }
               if(i == 5){
                Serial.println("\n #######################################");
                Serial.println("\n Tine joystick-ul in dreapta");
                delay(1000);
                citire_medie_calibrare();
                m1_dreapta_max = m1;
                Serial.print("\n Valoare luata: "); Serial.print(m1_dreapta_max); prelucrare_date();
              }

           }
        }
        if (inchar == 'v'){
        
          Serial.print("\n Centru FS: ");Serial.print( m3_centru );
          
            Serial.print("\n Fata maxim: ");Serial.print( schimbare( m3_fata_max, 1) );
            Serial.print("\n Fata min: ");Serial.print( (m3_centru + 50) ) ;
            Serial.print("\n Spate maxim: ");Serial.print( schimbare(m3_spate_max, 1) );
            Serial.print("\n Spate min: ");Serial.print( (m3_centru - 50) );

            Serial.print("\n Centru SD: ");Serial.print( m1_centru );
            
            Serial.print("\n Stanga maxim: ");Serial.print( schimbare( m1_stanga_max, 2) );
            Serial.print("\n Stanga min: ");Serial.print( (m1_centru - 50) );
            Serial.print("\n Dreapta maxim: ");Serial.print( schimbare( m1_dreapta_max, 2) );
            Serial.print("\n Dreapta min: ");Serial.print( (m1_centru + 50) );  
            
            Serial.print("\n Caz");Serial.print( caz );

          delay(1000);
      }
    }
  }

bool centrat(){
  
  if( ( schimbare(m1, 2) > (m1_centru - 50) ) && ( schimbare(m1, 2) < (m1_centru + 50) ) && ( schimbare(m3, 1) > (m3_centru - 50) ) && ( schimbare(m3, 1) < (m3_centru + 50) ) ){
    Serial.println("E centrat");
    return true;
  }
    
   else{Serial.println("Nu e centrat"); return false;}
}

void principal(){ //Pune functiile impreuna
  comenzi();
 if(ok!=true) citire_medie();
  else{
    if( !centrat() ){ //verifica daca e joystickul nu e centrat
      
      comandaST_FATA(); //cazul 2 de virare, pentru stanga+fata
      comandaST_SPATE(); //cazul 2 de virare, pentru stanga+spate
      comandaDR_FATA(); //cazul 2 de virare, pentru dreapta+fata
      comandaDR_SPATE(); //cazul 2 de virare, pentru dreapta+fata
      
      if( schimbare(m3, 1) > (m3_centru - 50) && schimbare(m3, 1) < (m3_centru + 50) )// daca joystick-ul nu e deplasat pe axa fata-spate
        comandaSTDR(); //cazul 1 de virare
      if( schimbare(m1, 2) > (m1_centru - 50) && schimbare(m1, 2) < (m1_centru + 50) )// daca joystick-ul nu e deplasat pe axa dreapta-stanga
      comandaFATA_SPATE(); //miscare de baza fata-spate
    }
     else {frana();}
    //afisare();
    delay(300);
    ok = false;
  }
}



void loop(){

 principal();
}
