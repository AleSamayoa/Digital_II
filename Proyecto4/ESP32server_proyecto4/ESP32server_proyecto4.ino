//**************************************************************************************************************
// María Alejandra Samayoa Gómez
// Carnet 18064
// Electrónica Digital II
//**************************************************************************************************************

/*************************************************************************************************
  ESP32 Web Server
  Ejemplo de creación de Web server 
  Basándose en los ejemplos de: 
  https://lastminuteengineers.com/creating-esp32-web-server-arduino-ide/
  https://electropeak.com/learn
**************************************************************************************************/
//************************************************************************************************
// Librerías
//************************************************************************************************
#include <WiFi.h>
#include <WebServer.h>
//************************************************************************************************
// Variables globales
//************************************************************************************************
// SSID & Password
const char* ssid = "TIGO-61AA";  // Enter your SSID here
const char* password = "2NJ555305178";

WebServer server(80);

uint8_t dataHandler = 0;

uint8_t par1s=0;
uint8_t par2s=0;
uint8_t par3s=0;
uint8_t par4s=0;

//Parqueo # state
bool par1o=false;
bool par2o=false;
bool par3o=false;
bool par4o=false;

//Para el display
uint8_t disp=4;
uint8_t A=36;
uint8_t B=39;
uint8_t C=34;
uint8_t D=35;
uint8_t E=32;
uint8_t F=33;
uint8_t G=25;

void setup() {
  //Igual que en el ejemplo, nos conectamos al internet y nos dira si logramos hacer la conección
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  
  Serial2.begin(115200, SERIAL_8N1, 16, 17);
  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/s1", handle_s1);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
void loop() {
  //Empieza a ver los datos de la Uart
  server.handleClient();
  if (Serial2.available() > 0) {
    uint8_t tempData;
    tempData = Serial2.read();
    if (tempData > 40) {
      dataHandler = tempData;
      Serial.println(dataHandler);
    }

  //Banderas para ver espacios
   par1o=false;
   par2o=false;
   par3o=false;
   par4o=false;
    if(par1s){
      par1o= true;
      }
    if(par2s){
      par2o= true;
      }
    if(par3s){
      par3o= true;
      }
    if(par4s){
      par4o= true;
      }
    //Para el display tenemos que enseñar la cantidad de parqueos disponibles
    //4 es el máximo y por cada ocupado que tenemos se le resta uno
    //Esta variable disp entra entonces a un switch case para enseñar los valores
    disp=4-(par1o+par2o+par3o+par4o);
     switch (disp) { 
        case 4: 
          digitalWrite(G, LOW);
          digitalWrite(F, LOW);
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(A, HIGH);
          digitalWrite(D, HIGH);
          digitalWrite(E, HIGH);
          break;
        case 3: 
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(G, LOW);
          digitalWrite(C, LOW);
          digitalWrite(D, LOW);
          digitalWrite(E, HIGH);
          digitalWrite(F, HIGH);
          break;
        case 2: 
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(G, LOW);
          digitalWrite(E, LOW);
          digitalWrite(D, LOW);
          digitalWrite(C, HIGH);
          digitalWrite(F, HIGH);
          break;
        case 1: 
          digitalWrite(B, LOW);
          digitalWrite(C, LOW);
          digitalWrite(A, HIGH);
          digitalWrite(D, HIGH);
          digitalWrite(E, HIGH);
          digitalWrite(F, HIGH);
          digitalWrite(G, HIGH);
          break;
        case 0: 
          digitalWrite(A, LOW);
          digitalWrite(B, LOW);
          digitalWrite(F, LOW);
          digitalWrite(E, LOW);
          digitalWrite(D, LOW);
          digitalWrite(C, LOW);
          digitalWrite(G, HIGH);
          break;
      }
  }
  parqueos(dataHandler, &par1s, &par2s, &par3s, &par4s); 
}

void handle_OnConnect() {

  server.send(200, "text/html", SendHTML(par1s, par2s, par3s, par4s)); 
}

//S1 que cambia el estado de los botones según el estado de parqueo 
void handle_s1() {
  String ptr = String("<p>Espacio 1</p>");
  if (par1s) {
    ptr += String("<a class=\"button button-on\">Carro</a>");
  } else {
    ptr += String("<a class=\"button button-off\">Libre</a>");
  }
  ptr += String("<p>Espacio 2</p>");
  if (par2s) {
    ptr += String("<a class=\"button button-on\">Carro</a>");
  } else {
    ptr += String("<a class=\"button button-off\">Libre</a>");
  }
  ptr += String("<p>Espacio 3</p>");
  if (par3s) {
    ptr += String("<a class=\"button button-on\">Carro</a>");
  } else {
    ptr += String("<a class=\"button button-off\">Libre</a>");
  }
  ptr += String("<p>Espacio 4</p>");
  if (par4s) {
    ptr += String("<a class=\"button button-on\">Carro</a>");
  } else {
    ptr += String("<a class=\"button button-off\">Libre</a>");
  }
  server.send(200, "text/plane", ptr);
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

//Creando el HTML original, con 4 botones que cambian de color según los estados 
String SendHTML(uint8_t par1, uint8_t par2, uint8_t par3, uint8_t par4) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\" http-equiv=\"refresh\" content=\"10\">\n";
  ptr += "<title>Parqueo ESP32</title>\n";
  ptr += "<style>html { font-family: Times New Roman; color: black display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 25px; background-color: #D1D8F0; color: black;} h1 {color: black; margin: 10px auto 20px auto;} h3 {color: black ;margin-bottom: 20px; margin-top: 10px;}\n";
  ptr += ".button {display: block;width: 50px;background-color: #FFFFFF;border: #413391;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 2px;}\n";
  ptr += ".button-on {background-color: #DB4130;}\n";
  ptr += ".button-on:active {background-color:#DB4130;}\n";
  ptr += ".button-off {background-color: #CCEB6E;}\n";
  ptr += ".button-off:active {background-color: #CCEB6E;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 5px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>PROYECTO NO. 4</h1>\n";
  ptr += "<h3>Parqueos</h3>\n";

  ptr += "<span id=\"s1\">";
  ptr += "<p>Espacio 1</p><a class=\"button\"> - - </a>\n";
  ptr += "<p>Espacio 2</p><a class=\"button\"> - - </a>\n";
  ptr += "<p>Espacio 3</p><a class=\"button\"> - - </a>\n";
  ptr += "<p>Espacio 4</p><a class=\"button\"> - - </a>\n";
  ptr += "</span>";

  ptr += "<script> setInterval(function(){getSite1();}, 1500);"; // Call a function repetatively with 2 Second interval
  ptr += "function getSite1(){";
  ptr += "var xhttp = new XMLHttpRequest();";
  ptr += "xhttp.onreadystatechange = function(){";
  ptr += "if (this.readyState == 4 && this.status == 200){";
  ptr += "document.getElementById(\"s1\").innerHTML = this.responseText;}";
  ptr += "};";
  ptr += "xhttp.open(\"GET\", \"s1\", true);";
  ptr += "xhttp.send();";
  ptr += "}";


  ptr += "</script>";
  ptr += "</html>\n";
  return ptr;
}

//Lee los datos de la UART y enciende los estados de parqueos según los datos que le llegan
void parqueos(uint8_t rx, uint8_t* par1s, uint8_t* par2s, uint8_t* par3s, uint8_t* par4s) {
  if ((rx && 1) == 0) { 
    *par1s = 1;
  }
  else {
    *par1s = 0;
  }

  if ((rx && 2) == 0) { 
    *par2s= 1;
  }
  else {
    *par2s = 0;
  }

  if ((rx && 4) == 0) { 
    *par3s = 1;
  }
  else {
    *par3s = 0;
  }

  if ((rx && 8) == 0) { 
    *par4s = 1;
  }
  else {
    *par4s = 0;
  }
}
