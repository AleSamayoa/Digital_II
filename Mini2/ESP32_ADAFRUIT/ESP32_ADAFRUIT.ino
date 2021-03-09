#include "config.h"
//aquí ya adaptó mis valores
String dataIn = ""; // guarda dataIn que manda el pic
//Iba a ver lo del giroscopio pero ya no logré que se mostrará
//String G;
//Definimos los datos de dirección 
float aX,aY,aZ;
char *valor1;
char *valor2;
#define IO_LOOP_DELAY 10000
unsigned long lastUpdate = 0;
//Básicamente voy a medir 5 cosas: Los dos botones con un switch 
AdafruitIO_Feed *b1 = io.feed("b1");
AdafruitIO_Feed *b2 = io.feed("b2");

//Y los 3 ejes de dirección 
AdafruitIO_Feed *Ax = io.feed("Ax");
AdafruitIO_Feed *Ay = io.feed("Ay");
AdafruitIO_Feed *Az = io.feed("Az");



void setup() {

  // start the serial connection
  Serial.begin(9600);
  Serial2.begin(9600);
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();
//ENciendo o apago los botones con las funciones que estan abajo 
  b1->onMessage(varB1);
  b2->onMessage(varB2);

  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());


}

void loop() {

  while(Serial2.available()){
    //los datos ya como floats se mandan al IO
      char varIN = Serial2.read();
      if( varIN != '\n') dataIn.concat(varIN);
      else{
    
        aX = (dataIn.substring(0,7)).toFloat();
        aY = (dataIn.substring(7,14)).toFloat();
        aZ = (dataIn.substring(14,21)).toFloat();
       // G =(dataIn.substring(28,49));
        dataIn = "";
      }
  }

 
  io.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {
    //Voy mandando los datos
    Serial.print("sending -> ");
    Serial.println(aX);
    Ax->save(aX);
    Serial.print("sending -> ");
    Serial.println(aY);
    Ay->save(aY);
    Serial.print("sending -> ");
    Serial.println(aZ);
    Az->save(aZ);
    //Serial.print("sending -> ");
    //Serial.println(G);
    //Giroscopio -> save(G);
    // after publishing, store the current time
    lastUpdate = millis();
  }

}

//Con estas funciones mando el dato de encendido o apagado
void varB1(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor1 =  data->value();
  Serial.println(valor1)Serial2.print('1on'); 
  else Serial2.print('1off'); ;
  if(*valor1 == '1'); 
  return;
}

void varB2(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor2 =  data->value(); 
  Serial.println(valor2);
  if(*valor2 == '1')Serial2.print('2on'); 
  else Serial2.print('2off'); ;
  return;
}
