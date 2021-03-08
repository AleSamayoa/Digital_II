#include "config.h"

String dataIn = ""; // guarda dataIn que manda el pic
String G;
float aX,aY,aZ,T;
char *valor1;
char *valor2;
#define IO_LOOP_DELAY 10000
unsigned long lastUpdate = 0;

AdafruitIO_Feed *Ax = io.feed("Ax");
AdafruitIO_Feed *Ay = io.feed("Ay");
AdafruitIO_Feed *Az = io.feed("Az");
AdafruitIO_Feed *p1 = io.feed("p1");
AdafruitIO_Feed *p2 = io.feed("p2");
AdafruitIO_Feed *Temperatura = io.feed("Temperatura");
//AdafruitIO_Feed *Giroscopio= io.feed("Giroscopio");
//Ya no se van a mandar los datos del giroscopio porque se traba mucho adafruit
void setup() {

  // start the serial connection
  Serial.begin(9600);
  Serial2.begin(9600);
  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();
//es lo de handle message para poder comunicarse con los switches de on y off
  p1->onMessage(varP1);
  p2->onMessage(varP2);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  //counter->get();

}

void loop() {

//main loop, aquí se convierten los datos a floats
// previo a esto se parte la string para separar los datos
//se mandan los datos tambien
  
  while(Serial2.available()){
      char varIN = Serial2.read();
      if( varIN != '\n') dataIn.concat(varIN);
      else{
    
        aX = (dataIn.substring(0,7)).toFloat();
        aY = (dataIn.substring(7,14)).toFloat();
        //Serial.println(dataIn.substring(14,21));
        aZ = (dataIn.substring(14,21)).toFloat();
        T = (dataIn.substring(21,28)).toFloat();
        //G =(dataIn.substring(28,49));
        dataIn = "";
      }
  }

 
  io.run();

  if (millis() > (lastUpdate + IO_LOOP_DELAY)) {

    Serial.print("sending -> ");
    Serial.println(aX);
    Ax->save(aX);
    Serial.print("sending -> ");
    Serial.println(aY);
    Ay->save(aY);
    Serial.print("sending -> ");
    Serial.println(aZ);
    Az->save(aZ);
    Serial.print("sending -> ");
    Serial.println(T);
    Temperatura -> save(T);
    Serial.print("sending -> ");
    Serial.println(G);
    //Giroscopio -> save(G);
    // after publishing, store the current time
    lastUpdate = millis();
  }

}

//con las funciones varP se envia un valor específico según el estado del switch
//se coloco en el switch un 0 y un 1 en lugar de on y off
//por facilidad
void varP1(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor1 =  data->value();
  Serial.println(valor1);
  if(*valor1 == '1') Serial2.print('led1on'); 
  else Serial2.print('led1off'); 
  return;
}

void varP2(AdafruitIO_Data *data){
  Serial.print("received <- ");
  valor2 =  data->value(); 
  Serial.println(valor2);
  if(*valor2 == '1') Serial2.print('led2on'); 
  else Serial2.print('led2off'); 
  return;
}
