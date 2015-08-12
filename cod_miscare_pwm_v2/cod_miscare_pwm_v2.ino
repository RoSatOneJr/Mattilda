//Versiunea 2.0 a codului pentru miscare pwm. 
//Obiective: Sistem de virare combinat (vezi schema de pe [pune aici link]) [NOT DONE]
//           Sistem de filtrare eficace [NOT DONE]
//           Micsorarea delay-ului [NOT DONE]
int m3, ok, ch3, c, ch1, m1=1400,m3_pwm_fata,m3_pwm_spate,m1_pwm_stanga,m1_pwm_dreapta;
float m_fata=0.574; 
float n_fata= 749.52;//n_fata negativ
float m_spate=-0.48;
float n_spate=758.75;
float m_dreapta = -0.48;
float n_dreapta = 786.8;
float m_stanga = 0.46;
float n_stanga = -642.9;
void setup() {
  pinMode(48, INPUT); //input canal 3
  pinMode(50, INPUT); //input canal 1
  pinMode(2, OUTPUT); //output motor1_a
  pinMode(3, OUTPUT); //output motor 1_b
  pinMode(4, OUTPUT); //output motor 2_a
  pinMode(5, OUTPUT); //output motor 2_b 
  pinMode(6, OUTPUT); //output motor 3_a
  pinMode(7, OUTPUT); //output motor 3_b
  pinMode(8, OUTPUT); //output motor 4_a
  pinMode(9, OUTPUT); //output motor 4_b

  ok = false; //bool medie
  c = 0; //contor medie

  Serial.begin(19200); //baud-rate
}

//Urmeaza functiile folosite pentru conversia inputului de telecomanda in valori PWM (100-255)
//Nota: Motoarele incep sa se invarta cand **_PWM_**** = 100. (Ex: m3_pwm_fata == 100)

void medie_pwm_fata(){ 
  m3_pwm_fata=m_fata * m3 - n_fata;  Serial.println(m3_pwm_fata);
  if(m3_pwm_fata>255) m3_pwm_fata=255; Serial.println(m3_pwm_fata);
}
void medie_pwm_spate(){
  m3_pwm_spate=m_spate * m3 + n_spate;  Serial.println(m3_pwm_spate);
  if(m3_pwm_spate>255) m3_pwm_fata=255; Serial.println(m3_pwm_fata);
  
  
}
void medie_pwm_dreapta(){
   m1_pwm_dreapta=m_dreapta * m1 + n_dreapta;  Serial.println(m1_pwm_dreapta);
   if(m1_pwm_dreapta>255) m1_pwm_dreapta=255; Serial.println(m1_pwm_dreapta);
  
  
}

void medie_pwm_stanga(){
   m1_pwm_stanga=m_stanga * m1 + n_stanga;  Serial.println(m1_pwm_stanga);
   if(m1_pwm_stanga>255) m1_pwm_stanga=255; Serial.println(m1_pwm_stanga);
   
}

//Functia de citire a semnalului trimis de telecomanda + creearea mediei
void citire_medie(){
   m3 = pulseIn(48,HIGH,15000); //citire canal 3 telecomanda
   m1 = pulseIn(50, HIGH, 15000); //citire canal 1 telecomanda
   for(int c=0;c<=9;c++){
     ch3 = pulseIn(48,HIGH,15000);
     m3 = (m3 + ch3) / 2;
     ch1 = pulseIn(50,HIGH,15000);
     m1 = (m1 + ch1) / 2;
   }
   ok=true;
   c=0;
}

//Functia folosita pentru virare Stanga-Dreapta "CAZ 1" 
//Nota: vezi schema de pe [introdu aici link] pentru a determina cazul.
void comandaSTDR(){
  if(m1 > 1600){ //Stanga
    medie_pwm_stanga();
    digitalWrite(2, LOW);
    analogWrite(3, m1_pwm_stanga);
    analogWrite(4, m1_pwm_stanga);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    analogWrite(7, m1_pwm_stanga);
    analogWrite(8, m1_pwm_stanga);
    digitalWrite(9, LOW); //functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
/*    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);*/
  }
  else if(m1 < 1450 && m1 > 1000){ //Dreapta
    medie_pwm_dreapta(); //functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    analogWrite(2, m1_pwm_dreapta);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    analogWrite(5, m1_pwm_dreapta);
    analogWrite(6, m1_pwm_dreapta);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(9, m1_pwm_dreapta);
/*    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH); */

  }
}

//Functia folosita pentru miscarea-fata spate "CAZ 1"
//Nota: vezi schema de pe [introdu aici link] pentru a determina cazul.
void comandaFATA(){
  if(m3 > 1470){ //fata
    medie_pwm_fata(); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    analogWrite(2, m3_pwm_fata);
    digitalWrite(3, LOW);
    analogWrite(4, m3_pwm_fata);
    digitalWrite(5, LOW);
    analogWrite(6, m3_pwm_fata);
    digitalWrite(7, LOW);
    analogWrite(8, m3_pwm_fata);
    digitalWrite(9, LOW);
  }
  
  else if(m3 < 1430) { //Miscare spate
    medie_pwm_spate(); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    digitalWrite(2, LOW);
    analogWrite(3, m3_pwm_spate);
    digitalWrite(4, LOW);
    analogWrite(5, m3_pwm_spate);
    digitalWrite(6, LOW);
    analogWrite(7, m3_pwm_spate);
    digitalWrite(8, LOW);
    analogWrite(9, m3_pwm_spate);
  }
  
  

}

void frana(){ //Franarea motoarelor prin scurt-circuit

    digitalWrite(2, HIGH); 
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  
}

//Functia folosita pentru afisarea inputului primit de la telecomana.

void afisare(){

  
  Serial.print("Channel3:");
  Serial.println(ch3);
  
  Serial.print("Channel1:");
  Serial.println(ch1);

  Serial.println("###########################");
}

//Void-ul principal. (pune toate functiile impreuna)
void principal(){
 if(ok!=true) citire_medie();
  else{
    if(m1 > 1600 || m1 < 1465)
      comandaSTDR();
     else if(m3 > 1470 || m3 < 1430)
       comandaFATA();
     else {frana();} 

    afisare();
    ok = false;

  }
}


void loop() {
   principal();
}
