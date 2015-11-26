int binar_m1[21], binar_m2[21], streak_m1[21], streak_m2[21], last_streak;
int timeQTR_motor1, timeQTR_motor2, viteza_bruta, viteza_m1, viteza_m2, ultima_viteza,citire_serial,c=0;
int pinMotor1 = 0, pinMotor2 = 0, pinQTR_motor1 = 0, pinQTR_motor2 = 0;
int segment_m1, segment_m2;
float medie_motor1,medie_motor2;
unsigned long time1, time2, time3;
bool bool_medie = false;

void setup(){
  pinMode(pinMotor1, OUTPUT);
  pinMode(pinMotor2, OUTPUT);
  Serial.begin(9600);
}


int prelucrareMotor1(){
    int last = binar_m1[1];
    int j=1;
    for(int i=1;i<=20;i++){
        if(last == binar_m1[i]){streak_m1[j]++;}
        if(last != binar_m1[i]){j=j+1;last=binar_m1[i];streak_m1[j]++;}
    }
    last_streak=streak_m1[1];
     for(int i=1;i<=20;i++){
          if(streak_m1[i]>last_streak) {last_streak = streak_m1[i];}
    }
  //Serial.print("Decizie finala: ");Serial.print(last_streak);Serial.print("\n");
    return last_streak;
}

int prelucrareMotor2(){
    int last = binar_m2[1];
    int j=1;
    
    for(int i=1;i<=20;i++){
        if(last == binar_m2[i]){streak_m2[j]++;}
        if(last != binar_m2[i]){j=j+1;last=binar_m2[i];streak_m2[j]++;}
    }
    last_streak=streak_m2[1];
     for(int i=1;i<=20;i++){
          if(streak_m2[i]>last_streak) {last_streak = streak_m2[i];}
    }
  //Serial.print("Decizie finala: ");Serial.print(last_streak);Serial.print("\n");
    return last_streak;
}


void medieQTR(){
  if(!bool_medie){
    for(int i=1;i<=100;i++){
      pinMode(pinQTR_motor1,OUTPUT);
      pinMode(pinQTR_motor2,OUTPUT);
      digitalWrite(pinQTR_motor1,HIGH);
      digitalWrite(pinQTR_motor2,HIGH);
      delayMicroseconds(200);
      pinMode(pinQTR_motor1,INPUT);
      pinMode(pinQTR_motor2,INPUT);
      time1 = micros();
      while(digitalRead(pinQTR_motor1)) {}
      time2 = micros();
      while(digitalRead(pinQTR_motor2)) {}
      time3 = micros();
      timeQTR_motor1 = time2 - time1;
      timeQTR_motor2 = time2 - time3;
      medie_motor1 += timeQTR_motor1;
      medie_motor2 += timeQTR_motor2;
    }
    medie_motor1 /= 100;
    medie_motor2 /= 100;
    bool_medie = true;
  }
}

void citireQTR()
{
  if(bool_medie){
    for(int i=1;i<=20;i++){
      pinMode(pinQTR_motor1,OUTPUT);
      pinMode(pinQTR_motor2,OUTPUT);
      digitalWrite(pinQTR_motor1,HIGH);
      digitalWrite(pinQTR_motor2,HIGH);
      delayMicroseconds(200);
      pinMode(pinQTR_motor1,INPUT);
      pinMode(pinQTR_motor2,INPUT);
      time1 = micros();
      while(digitalRead(pinQTR_motor1)) {}
      time2 = micros();
      while(digitalRead(pinQTR_motor2)) {}
      time3 = micros();
      timeQTR_motor1 = time2 - time1;
      timeQTR_motor2 = time2 - time3;
      if(timeQTR_motor1 >= medie_motor1) {binar_m1[i]=1;}
      if(timeQTR_motor1 < medie_motor1) {binar_m1[i]=0;}
      if(timeQTR_motor2 >= medie_motor2) {binar_m2[i]=1;}
      if(timeQTR_motor2 < medie_motor2) {binar_m2[i]=0;}
    }
  }
}

void echilibrare(){
    segment_m1 = prelucrareMotor1();
    segment_m2 = prelucrareMotor2();
    if(segment_m1 > segment_m2){
      viteza_m2 = viteza_bruta*segment_m1/segment_m2; viteza_m1 = viteza_bruta;
      if (viteza_m2 > 255){
        viteza_m1 = viteza_bruta*segment_m2/segment_m1; viteza_m2 = viteza_bruta;
      }
    }
    if(segment_m2 > segment_m1){
      viteza_m1 = viteza_bruta*segment_m2/segment_m1; viteza_m2 = viteza_bruta;
      if(viteza_m1 > 255) {
        viteza_m2 = viteza_bruta*segment_m1/segment_m2; viteza_m1 = viteza_bruta;
      }
    }
}

void scrie(){
  Serial.print("Motor1:");Serial.print(viteza_m1);Serial.print(" Motor2:");Serial.print(viteza_m2);Serial.print("\n");
  analogWrite(pinMotor1, viteza_m1);
  analogWrite(pinMotor2, viteza_m2);
}


void loop(){

 if(viteza_bruta == 0){
  while(true){
   if (Serial.available() > 0) {
      citire_serial = Serial.read()- '0';
      
      c++;
      if(c==1){ viteza_bruta = citire_serial*100;}
      if(c==2){ viteza_bruta += citire_serial*10;}
      if(c==3){ viteza_bruta += citire_serial;c=0;break;}
     }
   }
 }
  if(viteza_bruta != 0 && viteza_bruta != ultima_viteza){
    medieQTR();
    citireQTR();
    echilibrare();
    scrie();
    ultima_viteza = viteza_bruta;

  }
  else if(viteza_bruta == ultima_viteza) {
    scrie();
  }


}
