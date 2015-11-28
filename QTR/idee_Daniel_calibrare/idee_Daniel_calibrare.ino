unsigned long time1, time2, time3,timeQTR_motor1,timeQTR_motor2;
bool val1[11], val2[10], const1 = 1, const2 = 1;
int pinQTR_motor1 = 37, pinQTR_motor2 = 39,medie_motor2,medie_motor1;
float medie1, medie2, medie1N, medie2N;
int nrPasi1, nrPasi2;
bool faza1, faza2, faza1V, faza2V;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(43, OUTPUT);
  pinMode(41, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(33, OUTPUT);
}


void calibrareMedie(){
  
  for(int i = 1; i <= 1000; ++i){
    pinMode(pinQTR_motor1,OUTPUT);
      pinMode(pinQTR_motor2,OUTPUT);
      digitalWrite(pinQTR_motor1,HIGH);
      digitalWrite(pinQTR_motor2,HIGH);
      delayMicroseconds(2000);
      pinMode(pinQTR_motor1,INPUT);
      pinMode(pinQTR_motor2,INPUT);
      
      pinMode(43, OUTPUT);
      pinMode(41, OUTPUT);
      pinMode(33, OUTPUT);
      pinMode(35, OUTPUT);
      
      time1 = micros();
      while(digitalRead(pinQTR_motor1)) {}
      time2 = micros();
      while(digitalRead(pinQTR_motor2)) {}
      time3 = micros();
      timeQTR_motor1 = time2 - time1;
      timeQTR_motor2 = time3 - time2;
      if(timeQTR_motor1 < 0) {timeQTR_motor1 = -timeQTR_motor1;}
      if(timeQTR_motor2 < 0) {timeQTR_motor2 = -timeQTR_motor2;}
      medie_motor1 += timeQTR_motor1;
      medie_motor2 += timeQTR_motor2;
    }
    medie_motor1 /= 1000;
    medie_motor2 /= 1000;
}

bool constf(){
   pinMode(pinQTR_motor1,OUTPUT);
   pinMode(pinQTR_motor2,OUTPUT);
   digitalWrite(pinQTR_motor1,HIGH);
      digitalWrite(pinQTR_motor2,HIGH);
      delayMicroseconds(2000);
      pinMode(pinQTR_motor1,INPUT);
      pinMode(pinQTR_motor2,INPUT);
      
      pinMode(43, OUTPUT);
      pinMode(41, OUTPUT);
      pinMode(33, OUTPUT);
      pinMode(35, OUTPUT);
      
      time1 = micros();
      while(digitalRead(pinQTR_motor1)) {}
      time2 = micros();
      while(digitalRead(pinQTR_motor2)) {}
      time3 = micros();
      timeQTR_motor1 = time2 - time1;
      timeQTR_motor2 = time3 - time2;
      if(timeQTR_motor1 < 0) {timeQTR_motor1 = -timeQTR_motor1;}
      if(timeQTR_motor2 < 0) {timeQTR_motor2 = -timeQTR_motor2;}
      
      if(timeQTR_motor1 < medie_motor1){
         val1[const1 % 7] = 0;
      }
      else {
        val1[const1 % 7] = 1;
      }
      
      if(timeQTR_motor2 < medie_motor2){
        val2[const2 % 7] = 0;
      }
        
      else {
        val2[const2 % 7] = 1;
      }
  
      for(int i = 1; i <= 7; ++i){
        medie1 = (medie1 + val1[i]) / 2;
        medie2 = (medie2 + val2[i]) / 2;
      }
      
  faza1 = (medie1 > 0.5) ? 1 : 0;
  faza2 = (medie2 > 0.5) ? 1 : 0;
  Serial.print(faza1);
  Serial.print(".........");
  Serial.println(faza2);
  ++const1;
  ++const2;
}


void initial(){
  for(int i = 1; i <= 7; ++i){
    pinMode(pinQTR_motor1,OUTPUT);
      pinMode(pinQTR_motor2,OUTPUT);
      digitalWrite(pinQTR_motor1,HIGH);
      digitalWrite(pinQTR_motor2,HIGH);
      delayMicroseconds(2000);
      pinMode(pinQTR_motor1,INPUT);
      pinMode(pinQTR_motor2,INPUT);
      
      pinMode(43, OUTPUT);
      pinMode(41, OUTPUT);
      pinMode(33, OUTPUT);
      pinMode(35, OUTPUT);
      
      time1 = micros();
      while(digitalRead(pinQTR_motor1)) {}
      time2 = micros();
      while(digitalRead(pinQTR_motor2)) {}
      time3 = micros();
      timeQTR_motor1 = time2 - time1;
      timeQTR_motor2 = time3 - time2;
      if(timeQTR_motor1 < 0) {timeQTR_motor1 = -timeQTR_motor1;}
      if(timeQTR_motor2 < 0) {timeQTR_motor2 = -timeQTR_motor2;}
      if(timeQTR_motor1 < medie_motor1){
         val1[i] = 0;
         medie1 /= 2;
      }
      else {
        val1[i] = 1;
        medie1 = (medie1 + 1) / 2;
      }
      
      if(timeQTR_motor2 < medie_motor2){
        val2[i] = 0;
        medie2 /= 2;
      }
        
      else {
        val2[i] = 1;
        medie2 = (medie2 + 1) / 2;
      }
  }
  faza1V = (medie1 > 0.5) ? 1 : 0;
  faza2V = (medie2 > 0.5) ? 1 : 0;

}

int ok = true;
void loop() {
  // put your main code here, to run repeatedly:
  
    digitalWrite(43, LOW);
    digitalWrite(33, LOW);
    digitalWrite(41, HIGH);
    digitalWrite(35, HIGH);
    analogWrite(2, 255);
    analogWrite(3, 85);

    if(ok){ calibrareMedie(); initial(); ok = false;}

    constf();
    

}
