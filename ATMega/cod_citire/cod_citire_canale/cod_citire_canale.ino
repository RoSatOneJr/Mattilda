int ok,m1,m3,ch1,ch3,c;

void setup(){
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
   }
   ok=true;
   c=0;
}

void afisare(){
  Serial.print("Channel3:");
  Serial.println(ch3);

  Serial.print("Channel1:");
  Serial.println(ch1);

  Serial.println("###########################");
}

void loop(){
  citire_medie();
  afisare();



}
