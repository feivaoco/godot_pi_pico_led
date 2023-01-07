#include <ctype.h>

int btnPin = 0;

int ledsNum = 4;



int numsSerial[110];


String strSerial;
String strUser;


int btn = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(btnPin,INPUT);
  for(int i = 1; i <= ledsNum; i++){
    pinMode(i,OUTPUT);    
  }
  
  
}


//PIPICO SOLO AGUANTA STRING CON 60 DIGITOS, BUENO, HASTA AHI HICE EL DEBUG
void loop() {
  while (Serial.available() >0){ 
    
    strSerial += char(Serial.read());
    if(strSerial.length() > 0)
    strUser = strSerial;
    

    if (strUser.length() > 0){
      // Serial.print(strUser);

      char str[strUser.length()];
      for(int i = 0; i < strUser.length()-1; i++){
        str[i] = strUser[i];
      }       

      char* token;
      char* rest = str;
      int cantNumsSerial = 0;
      while ((token = strtok_r(rest, " ", &rest))){
        numsSerial[cantNumsSerial] = atoi(token);
        cantNumsSerial += 1;

      }
      
      // for(int i = 0; i<cantNumsSerial; i++){
      //   Serial.print(numsSerial[i]);
      //   Serial.print(" ");
        
      // }
      for(int i = 0; i < ledsNum; i++){
        if(numsSerial[i] == 1)
          digitalWrite(i+1,1);
        else
          digitalWrite(i+1,0);
      }
      
    }
  }

  
  
  btn = digitalRead(btnPin);
  
  // Serial.print("| ");
  Serial.print(btn);
  Serial.println();
  

  strSerial = "";
  
  delay(3);

}
