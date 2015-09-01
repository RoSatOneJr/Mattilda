int m1,m3, ok, ch3, c, ch1,marja_frana=50,i=0, m1_centru, m3_centru,dif1,dif2, m3_fata_max;
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
     m3 += ch3;
     ch1 = pulseIn(50,HIGH,15000);
     m1 += ch1;
   }
   m3 /= 60;
   m1 /= 60;
}


void afisare(){
  Serial.print("Channel3:");
  Serial.println(ch3);

  Serial.print("Channel1:");
  Serial.println(ch1);

  Serial.println("###########################");
}

void comenzi(){
  if (Serial.available() > 0) {
        inchar = Serial.read();
          if (inchar == 'c'){
              start_millis= millis();
              while(true){
                current_millis=millis();

                if(current_millis - start_millis < 2500){
                  Serial.println("Incep calibrarea.");
                  Serial.println("\n Tine joystick-ul centrat pentru doua secunde");
                  delay(500);
                  citire_medie_calibrare();
                  m1_centru = m1;
                  m3_centru = m3;
                  Serial.println("Valoarile luate: CH1:"); Serial.println(m1);Serial.println("; CH3: ");Serial.println(m3);
              }
               if((current_millis - start_millis < 5000) && (current_millis - start_millis > 2500)){
                 Serial.println("\n #######################################");
                 Serial.println("\n Tine joystick-ul in fata doua secunde");
                 delay(500);
                 citire_medie_calibrare();
                 m3_fata_max = m3;
                 Serial.println("\n Valoare luata: "); Serial.println(m3);
               	}
            }
        }
    }
}
void loop(){
  comenzi();
}
