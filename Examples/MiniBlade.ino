#include <VS1838.h>

#define RECEPTOR_PIN 3 //El vs1838 esta conectado al pin3
#define LED 13 //Parpadea el led al presionar una tecla
unsigned int keyIR; //Variable para almacenar la tecla presionada

//Crea el objeto
VS1838 IRModule(RECEPTOR_PIN); 
//VS1838 IRModule(RECEPTOR_PIN,LED); //Hace uso del LED

void setup() {
Serial.begin(9600);
while(!Serial);
Serial.println("Presione una tecla del control remoto...");
}

void loop() {
  keyIR = IRModule.read();
  if(keyIR){
   Serial.print("Value: ");
   Serial.println(keyIR, HEX);
  }
}
