//Versiunea de test a codului pentru miscare pwm + evitare de obstacole.
//Obiective: Evitarea eficienta a obstacolelor mobile. [ ? ]
int m3, ok, ch3, c, ch1, m1,m3_pwm_fata,m3_pwm_spate,m1_pwm_stanga,m1_pwm_dreapta,dif1,dif2,distanta_stanga,distanta_dreapta;
int distanta, duration;
int trigPin = 0; //Pinul trigger pentru senzorul de distanta
int echoPin = 1; //Pinul echo pentru senzorul de distanta
const int marja_frana=50;
const float coeficient_viraj = 0.25; //coeficientul folosit pentru a creea diferenta dintre D si S in virajul combinat
const float m_fata=0.574;             //Nota:Coeficientul in schma v1 e 0.8, dar cu 0.8 nu functioneaza
const float n_fata= -749.52;
const float m_spate=-0.48;
const float n_spate=758.75;
const float m_dreapta = -0.48;
const float n_dreapta = 786.8;
const float m_stanga = 0.46;
const float n_stanga = -642.9;
const int distanta_sigura = 10;
const int delay_schimbare_directie = 500; //Delayul folosit la schimbarea directiei pentru determinarea distantei

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

  Serial.begin(19200); //baud-rate
}

//Urmeaza functiile folosite pentru conversia inputului de telecomanda in valori PWM (100-255)
//Nota: Motoarele incep sa se invarta cand **_PWM_**** == 100. (Ex: m3_pwm_fata == 100)

void medie_pwm_fata(){
  m3_pwm_fata=m_fata * m3 + n_fata;
  if(m3_pwm_fata>255) m3_pwm_fata=255; Serial.println(m3_pwm_fata);
}
void medie_pwm_spate(){
  m3_pwm_spate=m_spate * m3 + n_spate;
  if(m3_pwm_spate>255) m3_pwm_fata=255;

}
void medie_pwm_dreapta(){
   m1_pwm_dreapta=m_dreapta * m1 + n_dreapta;
   if(m1_pwm_dreapta>255) m1_pwm_dreapta=255; Serial.println(m1_pwm_dreapta);

}

void medie_pwm_stanga(){
   m1_pwm_stanga=m_stanga * m1 + n_stanga;
   if(m1_pwm_stanga>255) m1_pwm_stanga=255; Serial.println(m1_pwm_stanga);
}
//Functia de citire a semnalului trimis de telecomanda + creearea mediei
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

int determinare_distanta(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  if (distanta<=200){
  return distanta = (duration/2) / 29.1;
  Serial.println(distanta);
  }
  else {return distanta = 200; Serial.println("Distanta > 200");}
}

//Functia folosita pentru virare Stanga+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaST_FATA(){

  if((m1 > 1600) && (m3 > 1470)){
      medie_pwm_fata();
      medie_pwm_stanga();
      Serial.println("Comanda ST_FATA");

      analogWrite(2, m3_pwm_fata*coeficient_viraj);
      digitalWrite(3, LOW);

     analogWrite(4, m1_pwm_stanga);
     digitalWrite(5, LOW);

      analogWrite(6, m3_pwm_fata*coeficient_viraj);
      digitalWrite(7, LOW);

      analogWrite(8, m1_pwm_stanga);
      digitalWrite(9, LOW);
  }
}

//Functia folosita pentru virare Stanga+Spate "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1

void comandaST_simpla(){

    Serial.println("Comanda Stanga simpla");
    digitalWrite(2, LOW);
    analogWrite(3, m1_pwm_stanga);
    analogWrite(4, m1_pwm_stanga);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    analogWrite(7, m1_pwm_stanga);
    analogWrite(8, m1_pwm_stanga);
    digitalWrite(9, LOW);
    }

void comandaST_SPATE(){

  if((m1 > 1600) && (m3 < 1430 && m3>1000)){
    medie_pwm_spate();
    medie_pwm_stanga();
    Serial.println("Comanda ST_spate");

    digitalWrite(2, LOW);
    analogWrite(3, m3_pwm_spate*coeficient_viraj);

   digitalWrite(4, LOW);
   analogWrite(5, m1_pwm_stanga);

    digitalWrite(6, LOW);
    analogWrite(7, m3_pwm_spate*coeficient_viraj);

    digitalWrite(8, LOW);
    analogWrite(9, m1_pwm_stanga);
  }
}

//Functia folosita pentru virare Dreapta+Fata "CAZ 2"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaDR_FATA(){
  if((m1 < 1450 && m1 > 1000) && (m3 > 1470)){
    medie_pwm_fata();
    medie_pwm_dreapta();
    Serial.println("Comanda DR_fata");

    analogWrite(2, m1_pwm_dreapta); //pwm_dreapta
    digitalWrite(3, LOW);

    analogWrite(4, m3_pwm_fata*coeficient_viraj); Serial.println(m3_pwm_fata*coeficient_viraj);
    digitalWrite(5, LOW);

    analogWrite(6, m1_pwm_dreapta); //pwm_drapta
    digitalWrite(7, LOW);

    analogWrite(8, m3_pwm_fata*coeficient_viraj); Serial.println(m3_pwm_fata*coeficient_viraj);
    digitalWrite(9, LOW);

  }
}
void comandaDR_simpla(){
    Serial.println("Comanda Dreapta simpla");

    analogWrite(2, m1_pwm_dreapta);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    analogWrite(5, m1_pwm_dreapta);
    analogWrite(6, m1_pwm_dreapta);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(9, m1_pwm_dreapta);
}

void comandaDR_SPATE(){
  if((m1 < 1450 && m1 > 1000)&&(m3 < 1430 && m3>1000)){
    Serial.println("Comanda DR_spate");
    medie_pwm_spate();
    medie_pwm_dreapta();

    digitalWrite(2, LOW);
    analogWrite(3, m1_pwm_dreapta); //pwm_dreapta

    digitalWrite(4, LOW);
    analogWrite(5, m3_pwm_fata*coeficient_viraj);

    digitalWrite(6, LOW);
    analogWrite(7, m1_pwm_dreapta); //pwm_drapta

    digitalWrite(8, LOW);
    analogWrite(9, m3_pwm_fata*coeficient_viraj);
  }
}

//Functia folosita pentru virare Stanga-Dreapta "CAZ 1"
//Nota: vezi schema de pe GitHub: mattilda/Scheme/Schema moduri de virare_v1
void comandaSTDR(){

  if(m1 > 1600 && !(m3 > 1470 || m3 < 1430)){ //Stanga
    medie_pwm_stanga();//functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    comandaST_simpla();

  }
  else if((m1 < 1450 && m1 > 1000) && !(m3 > 1470 || m3 < 1430) ){ //Dreapta
    medie_pwm_dreapta(); //functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    comandaDR_simpla();

  }
}

void comandaF_simpla(){
  Serial.println("Comanda fata simpla");
  analogWrite(2, m3_pwm_fata);
  digitalWrite(3, LOW);
  analogWrite(4, m3_pwm_fata);
  digitalWrite(5, LOW);
  analogWrite(6, m3_pwm_fata);
  digitalWrite(7, LOW);
  analogWrite(8, m3_pwm_fata);
  digitalWrite(9, LOW);
}


void comandaS_simpla(){
  Serial.println("Comanda spate simpla");
  digitalWrite(2, LOW);
  analogWrite(3, m3_pwm_spate);
  digitalWrite(4, LOW);
  analogWrite(5, m3_pwm_spate);
  digitalWrite(6, LOW);
  analogWrite(7, m3_pwm_spate);
  digitalWrite(8, LOW);
  analogWrite(9, m3_pwm_spate);
}


//Functia folosita pentru miscarea-fata spate
void comandaFATA_SPATE(){
  if(m3 > 1490 && !(m1 > 1600 || m1 < 1465)){ //fata
    medie_pwm_fata();
    comandaF_simpla();
  }

  else if((m3 < 1430 && m3>1000)&&!(m1 > 1600 || m1 < 1465)) { //Miscare spate
    medie_pwm_spate(); //Functia folosita la conversia inputului de la telecomanda in valori de PWM (100-255)
    comandaS_simpla();
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
    if(m1 > 1600 || m1 < 1465 || m3 > 1470 || m3 < 1430){ //verifica daca e joystickul nu e centrat
      if(determinare_distanta() > distanta_sigura){
        comandaST_FATA(); //cazul 2 de virare, pentru stanga+fata
        comandaST_SPATE(); //cazul 2 de virare, pentru stanga+spate
        comandaDR_FATA(); //cazul 2 de virare, pentru dreapta+fata
        comandaDR_SPATE(); //cazul 2 de virare, pentru dreapta+fata
        comandaSTDR(); //cazul 1 de virare
        comandaFATA_SPATE(); //miscare de baza fata-spate
      }
      else if(determinare_distanta() <= distanta_sigura){
        m1_pwm_stanga=180;
        m1_pwm_dreapta=180;
        m3_pwm_fata=180;
        m3_pwm_spate=180;
        comandaST_simpla(); delay(delay_schimbare_directie);
        distanta_stanga = determinare_distanta(); Serial.println("Distanta din partea stanga e: ");Serial.print(distanta_stanga);
        comandaDR_simpla(); delay(delay_schimbare_directie*2-100);
        distanta_dreapta = determinare_distanta(); Serial.println("Distanta din partea dreapta e: ");Serial.print(distanta_dreapta);
        if (distanta_stanga > distanta_dreapta){comandaST_simpla(); delay(delay_schimbare_directie*2);Serial.println("Merg prin stanga");}
        else if(distanta_dreapta>distanta_stanga){comandaDR_simpla();delay(100);Serial.println("Merg prin dreapta");}
          else{comandaF_simpla();delay(500);Serial.println("Distantele sunt egale, o iau in fata");}
        }
      }
    else frana();
    afisare();
    ok = false;
  }
}
void loop() {
   principal();
}

