#include "VS1838.h"
#include "Arduino.h"
/* 
 *  Libreria para hacer uso del receptor infrarojo de control remoto
 *  Autor: Michael Vargas
 *  Creditos: http://blog.drk.com.ar/2013/control-remoto-infrarrojo-con-arduino
 *  1/04/2016
 */ 
// Cantidad de pulsos
#define TRAIN_LENGTH 32
// En microsegundos
#define LOW_LIMIT 600
#define HIGH_LIMIT 1800
#define INIT_LIMIT 4000

volatile uint32_t value;
volatile uint8_t pos = 0;
volatile boolean has_value = false;
volatile byte IN,ledPin;

void inputPin(){
static long start, delta = 0;
  if (has_value) return;
  
  noInterrupts();
  if (digitalRead(IN) == HIGH) {
      if(ledPin!=255) digitalWrite(ledPin, LOW);
    start = micros();
  }
  else {
    delta = micros() - start;
    if (delta < LOW_LIMIT) {
      if(ledPin!=255) digitalWrite(ledPin, LOW);
      value <<= 1;
      value |= 1;
      ++pos;
    }
    else if (delta < HIGH_LIMIT) {
      if(ledPin!=255) digitalWrite(ledPin, HIGH);
      value <<= 1;
      value |= 0;
      ++pos;
    }
    else if (delta > INIT_LIMIT) {
      value = 0;
      pos = 0;
    }
 
    if (pos == TRAIN_LENGTH) {
      if(ledPin!=255) digitalWrite(ledPin, LOW);
      value &= 0x0000FFFF;  //Elimina los '1' al final de cada direccion, para asi poder convertir la direccion en variables de 16 bits
      has_value = true;
    }
  }
  interrupts();
}
VS1838::VS1838(unsigned char pin,unsigned char LED){
  if(LED!=255) {
    _led=LED;
    pinMode(LED, OUTPUT);
  }
  _pin = pin;
  pinMode(pin, INPUT);
  setPins();
  attachInterrupt(digitalPinToInterrupt(pin),inputPin, CHANGE);
}

void VS1838::setPins(){
 IN = _pin;
  ledPin = _led;
}

unsigned int VS1838::read(){
  if(has_value==true && value > 0) {
    has_value = false;
     return value;
  }else{
    return 0;
  }

}




