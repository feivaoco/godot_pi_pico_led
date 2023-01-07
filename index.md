# Pi Pico and Godot (PROYECTO AÚN EN DESARROLLO)
## Comunicación entre una Pi Pico y Godot mediante la Serial

![pico_godot](/proyecto/imgs/pico_godot_der.png)

- [Resumen](#resumen)
- [Introducción](#introducción)
- [Desarrollo](#desarollo)
    - [Circuito](#circuito)
    - [Código Arduino IDE](#código-arduino-ide)
    - [Godot](#godot)

# Resumen
Este proyecto se trata solamente de demostrar el funcionamiento de Godot con la Serial para que se le sea posible comunicarse con dispositivos que se comuniquen mediante esta. En este caso se prenderán unos LEDs mediante un programa hecho en Godot y Godot leerá una señal de un botón que se manda por medio de la Pi Pico.

# Introducción
Godot es un Engine para crear videojuegos, pero quiero saber si se le es posible comunicarse mediante la Serial para así interactuar con dispositivos I/O. La Raspberry Pi Pico (RPP), es un minicontrolador el cual ya he utilizado en un anterior proyecto, por lo que ya se cuenta con conocimiento previo del uso básico del minicontrolador. El realizar este proyecto es con el objetivo de asegurar que Godot puede realizar esta comunicación para iniciar demás proyectos que incluyan este proyecto como base; y es que tengo pensado realizar un teclado modular pero necesito una GUI para modificar sus teclas sin necesidad de hacer un nuevo sketch en Arduino. Ah, y trabajeroms con Arduino IDE para programar a la Pi Pico.

# Desarollo

## Circuito
El diagrama del circuito en esta ocasión es el siguiente:
![pipicocircuit](/proyecto/imgs/pipico_circuito_2.drawio.png)
Ya que solamente quiero probar que se puede realizar la comuncación serial con Godot, nada más serán unos LEDs y un Push button. Los LEDs se encienden a través de un mensaje que Godot manda y el botón es para mandar un mensaje a Godot.
## Código Arduino IDE
Arduino IDE permite programar a la Pi Pico por lo que seguiré usándolo hasta que ocurra un inconveniente de que no sirva para algún proyecto. El código está mal, ya que de momento para otro la Pi Pico dejará de comunicarse por Serial pero seguirá encendida, aún no sé porque ocurre esto pero lo dejaré así de momento.
```arduino
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
void loop() {
  while (Serial.available() >0){ 
    strSerial += char(Serial.read());
  }
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
    for(int i = 0; i < ledsNum; i++){
      if(numsSerial[i] == 1)
        digitalWrite(i+1,1);
      else
        digitalWrite(i+1,0);
    }
  }
  btn = digitalRead(btnPin);
  // Serial.print("| ");
  Serial.print(btn);
  Serial.println();
  strSerial = "";
  delay(3);
}
```
Se arregló lo de que se trababa, solamente tenía que hacer lo siguiente:
```arduino
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
``` 
Bueno, prosigo con el programa en Godot.
## Godot