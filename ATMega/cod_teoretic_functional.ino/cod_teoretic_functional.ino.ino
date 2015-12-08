//Cod de miscare versiunea 3.
//Feautures: Autocalibrare
//          Folosirea unui singur pin PWM/motor

int m1, m3, ok, ch3, c, ch1, marja_frana=50, i=0;
float dif1, dif2, m3_fata_max, m3_spate_max, m1_dreapta_max, m1_stanga_max;
int motor1_a=12, motor1_b=13, motor2_a=10, motor2_b=11, motor3_a=6, motor3_b=7;
int motor4_a=4, motor4_b=5;
int m1_dreapta_max_m, m1_dreapta_min_m, m3_spate_min_m, m3_spate_max_m; //NOTA: inturile cu _m sunt folosite pentru a stoca marja pentru miscarile cu PWM pe ground
int m3_pwm_fata, m3_pwm_spate, m1_pwm_stanga, m1_pwm_dreapta;
int coeficient_viraj = 0.25;
double m3_centru = 1523, m_fata = 1941, m_spate = 1139, m1_centru = 1476, m_dreapta = 1886, m_stanga = 1060;
char inchar;
int caz = 0;
int canal3 = 20;
int canal1 = 18;
int pinQTR_motor1=37;
int pinQTR_motor2=39;
int QTR1, QTR2;
int bool_medie=false;
int lastQTR1=1, lastQTR2=1;
int pinMotor1 = 2;
int pinMotor2 = 3;
int contorQTR1 = 0, contorQTR2 = 0;
//int switchM1, switchM2, switchUrcare;
long medie_motor1,medie_motor2;
long time1,time2,time3,timeQTR_motor1,timeQTR_motor2;
int pinCanal2 = 19, ch2, m2, citireSwitch;
int sus = false;

void setup() {
  pinMode(canal3, INPUT); //input canal 3
  pinMode(canal1, INPUT); //input canal 1
  pinMode(motor1_a, OUTPUT); //output motor1_a 12,13
  pinMode(motor1_b, OUTPUT); //output motor 1_b 
  pinMode(motor2_a, OUTPUT); //output motor 2_a 10,11
  pinMode(motor2_b, OUTPUT); //output motor 2_b
  pinMode(motor3_a, OUTPUT); //output motor 3_a  
  pinMode(motor3_b, OUTPUT); //output motor 3_b
  pinMode(motor4_a, OUTPUT); //output motor 4_a
  pinMode(motor4_b, OUTPUT); //output motor 4_b
  pinMode(43, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(28, OUTPUT);
  Serial.begin(19200);
  ok = false; //bool medie

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
   if(m1_pwm_stanga>255) m1_pwm_stanga=255;
   Serial.println(m1_pwm_stanga);
   if(m1_pwm_stanga<0) m1_pwm_stanga=0;


}

void medie_pwm_dreapta(int x){
   m1_pwm_dreapta = 155 - (x - ( m1_centru + 50 ) ) * m_dreapta;
   if (m1_pwm_dreapta>255) m1_pwm_dreapta=255; 
   Serial.println(m1_pwm_dreapta);
   if (m1_pwm_dreapta<0) m1_pwm_dreapta=0; 

}

void medie_pwm_fata(int x){
  m3_pwm_fata = 100 + ( x - (m3_centru + 50) ) * m_fata;
  if(m3_pwm_fata>255) m3_pwm_fata=255; 
  Serial.println(m3_pwm_fata);
  if(m3_pwm_fata<0) m3_pwm_fata=0; 

}

void medie_pwm_spate(int x){
  m3_pwm_spate = ( x - schimbare(m3_spate_max, 1) ) * m_spate;
  if (m3_pwm_spate > 255) m3_pwm_fata=255;
  Serial.println(m3_pwm_spate);
  if (m3_pwm_spate < 0) m3_pwm_fata=0;

}


void citire_medie(){
   m3 = pulseIn(canal3,HIGH,15000); //citire canal 3 telecomanda
   m1 = pulseIn(canal1, HIGH, 15000); //citire canal 1 telecomanda
   ch2 = pulseIn(pinCanal2, HIGH, 15000);
   for(int c=1;c<=10;c++){
     ch3 = pulseIn(canal3,HIGH,15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(canal1,HIGH,15000);
     m1 = (m1 + ch1) / 2;
     if( c==1 ) dif1=ch3;
     if( c==10 ) dif2=ch3;
     if( (dif2-dif1) > marja_frana ) frana();
     m2 += ch2;
   }
   m2 /= 10;   
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
      analogWrite(motor1_a, m1_pwm_stanga);
      digitalWrite(motor1_b, LOW);      
      
      digitalWrite(motor2_a, LOW);
      analogWrite(motor2_b, m1_pwm_stanga);
      
      
      analogWrite(motor3_a, LOW);
      digitalWrite(motor3_b, m1_pwm_stanga);
      
      
      digitalWrite(motor4_a, m1_pwm_stanga);
      analogWrite(motor4_b, LOW);
      
}

void Dreapta_simplu(){
    analogWrite(motor1_a, m1_pwm_dreapta);
    digitalWrite(motor1_b, HIGH);
    
    digitalWrite(motor2_a, HIGH);
    analogWrite(motor2_b, m1_pwm_dreapta);
    
    digitalWrite(motor3_a, m1_pwm_dreapta);
    analogWrite(motor3_b, HIGH);
    
    analogWrite(motor4_a, HIGH);
    digitalWrite(motor4_b, m1_pwm_dreapta);

}




//Functia folosita pentru virare Stanga+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaST_FATA(){

  if( schimbare(m1, 2) < (m1_centru - 100) && schimbare(m3, 1) > (m3_centru + 100) ){
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

  if( schimbare(m1, 2) < (m1_centru - 100) && schimbare(m3, 1) < (m3_centru - 100) ){
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
  if( schimbare(m1, 2) > (m1_centru + 100) && schimbare(m3, 1) > (m3_centru + 100) ){
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
    if( schimbare(m1, 2) > (m1_centru + 100) && schimbare(m3, 1) < (m3_centru - 100) ){
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
   m3 = pulseIn(canal3, HIGH, 15000); //citire canal 3 telecomanda
   m1 = pulseIn(canal1, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=1;c<=60;c++){
     ch3 = pulseIn(canal3, HIGH, 15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(canal1, HIGH, 15000);
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




void citire(){
  if(bool_medie == true){

    pinMode(pinQTR_motor1,OUTPUT);
    pinMode(pinQTR_motor2,OUTPUT);
    digitalWrite(pinQTR_motor1,HIGH);
    digitalWrite(pinQTR_motor2,HIGH);
    delayMicroseconds(15);
    pinMode(pinQTR_motor1,INPUT);
    pinMode(pinQTR_motor2,INPUT);
    time1 = micros();
    while(digitalRead(pinQTR_motor1)) {}
    time2 = micros();
    while(digitalRead(pinQTR_motor2)) {}
    time3 = micros();
    timeQTR_motor1 = time2 - time1;
    timeQTR_motor2 = time3 - time2;
    if(timeQTR_motor1 < medie_motor1){QTR1 = 0;}
    if(timeQTR_motor1 > medie_motor1){QTR1 = 1;}
    if(timeQTR_motor2 < medie_motor2){QTR2 = 0;}
    if(timeQTR_motor2 > medie_motor2){QTR2 = 1;}
  }
}



void medie(){
 if(!bool_medie){
  digitalWrite(43, LOW);
  digitalWrite(33, LOW);
  digitalWrite(41, HIGH);
  digitalWrite(35, HIGH); 
  for(int i=1;i<=100;i++){ 
  Serial.println("Vezi ca fac media");
    pinMode(pinQTR_motor1,OUTPUT);
    pinMode(pinQTR_motor2,OUTPUT);
    digitalWrite(pinQTR_motor1,HIGH);
    digitalWrite(pinQTR_motor2,HIGH);
    delayMicroseconds(15);
    pinMode(pinQTR_motor1,INPUT);
    pinMode(pinQTR_motor2,INPUT);
    time1 = micros();
    while(digitalRead(pinQTR_motor1)) {}
    time2 = micros();
    while(digitalRead(pinQTR_motor2)) {}
    time3 = micros();
    timeQTR_motor1 = time2 - time1;

    timeQTR_motor2 = time3 - time2;
    medie_motor1 += timeQTR_motor1;
    medie_motor2 += timeQTR_motor2;
//        Serial.println(medie_motor1);
    
  }
  medie_motor1 /= 100;
  medie_motor2 /= 100;
 // Serial.println(medie_motor1);
  digitalWrite(43, HIGH);
  digitalWrite(33, HIGH);
  digitalWrite(41, HIGH);
  digitalWrite(35, HIGH); 


  bool_medie = true;
 }
}

int Switch(int motor){
 //motor = 3 - switch urcare
 if(motor == 3){
    citireSwitch = digitalRead(24);
   }
 if(motor == 2){
    citireSwitch = digitalRead(26);
   }
 if(motor == 1){
    citireSwitch = digitalRead(28);
   }
 return citireSwitch;
 
}

void susJos() {
  // put your main code here, to run repeatedly:
  
/*  digitalWrite(43, LOW);
  digitalWrite(33, LOW);
  digitalWrite(41, HIGH);
  digitalWrite(35, HIGH); */
  analogWrite(pinMotor1, 255);
  analogWrite(pinMotor2, 200);
    
  medie();
  citire();
  if(timeQTR_motor1 > medie_motor1){QTR1 = 1;}
  if(timeQTR_motor1 < medie_motor1){QTR1 = 0;}
  if(timeQTR_motor2 > medie_motor2){QTR2 = 1;}
  if(timeQTR_motor2 < medie_motor2){QTR2 = 0;}
  if(QTR1 != lastQTR1) {contorQTR1++; lastQTR1=QTR1;}
  if(QTR2 != lastQTR2) {contorQTR2++; lastQTR2=QTR2;}

  if(m2 > 1750){
    
    if(Switch(3) == 0){
    Serial.println(" tot mai sus");
    digitalWrite(43, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(41, LOW);
    digitalWrite(35, LOW);
    }
    else{
    
    digitalWrite(43, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(41, HIGH);
    digitalWrite(35, HIGH);
    }

  }
  if(m2 < 1550){
    
    if(Switch(2) == 1 || Switch(1) == 1){
      digitalWrite(43, LOW);
      digitalWrite(33, LOW);
      digitalWrite(41, HIGH);
      digitalWrite(35, HIGH);
    }
    else {
      
      digitalWrite(43, HIGH);
      digitalWrite(33, HIGH);
      digitalWrite(41, HIGH);
      digitalWrite(35, HIGH);
    }   
    sus = false;
  }
  if( (m2 > 1550 && m2 < 1750) || m2 == 0){
    digitalWrite(43, HIGH);
    digitalWrite(33, HIGH);
    digitalWrite(41, HIGH);
    digitalWrite(35, HIGH);
  }  
}
void principal(){ //Pune functiile impreuna
 comenzi();
 if(ok!=true) citire_medie();
  else{
    susJos();
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
