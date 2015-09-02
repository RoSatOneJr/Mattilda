int m1,m3, ok, ch3, c, ch1,marja_frana=50,i=0, m1_centru;
int m3_centru,dif1,dif2, m3_fata_max, m3_spate_max, m1_stanga_max;
int m1_dreapta_max,i,m3_fata_min,m3_spate_min,m1_stanga_min,m3_dreapta_min;
unsigned long current_millis, start_millis;

char inchar;
void setup() {
  pinMode(48, INPUT);
  pinMode(50, INPUT); //input canal 1
  ok = false; //bool medie
  Serial.begin(19200); //baud-rate

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

void frana(){}

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
    if(m3_fata_max > m3_spate_max) {m3_fata_min = m3_centru+50;m3_spate_min = m3_centru-50;}
     else{me_fata_min = m3_centru-50; m3_spate-min=m3_centru+50;}
    if(m1_stanga_max > m1_dreapta_max){m1_stanga_min=m1_centru+50;m1_dreapta_min=m1_centru-50;}
      else{m1_stanga_min=m1_centru-50;m1_dreapta_min=m1_centru+50;}

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
void loop(){
  comenzi();
}
