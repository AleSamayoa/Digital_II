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

bool LED1status = LOW;

uint8_t dataHandler = 0;
uint8_t lastHandler = 0;
uint8_t numSel = 0;
uint8_t par1=4;
uint8_t par2=5;
uint8_t par3= 12;
uint8_t par4=15;
bool par1s=false;
bool par2s=false;
bool par3s=false;
bool par4s=false;

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);
  pinMode(par1,INPUT);
  pinMode(par2,INPUT);
  pinMode(par3,INPUT);
  pinMode(par4,INPUT);
  
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
  server.on("/s1", handle_sites);

  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
  delay(100);
}
void loop() {
    

  par1s = (digitalRead(par1)==LOW);
  par2s = (digitalRead(par2)==LOW);
  par3s = (digitalRead(par3)==LOW);
  par4s = (digitalRead(par4)==LOW);
  server.handleClient();
  if (Serial2.available() > 0) {
    uint8_t tempData;
    tempData = Serial2.read();
    if (tempData > 40) {
      dataHandler = tempData;
      Serial.println(dataHandler);
      //dataHandler = getUartNumber(dataHandler); // traduciendo dato ascii
    }
  }
 // parkingData(dataHandler, &par1s, &par2s, &par3s, &par4s); 
}

void handle_OnConnect() {

  server.send(200, "text/html", SendHTML(par1s, par2s, par3s, par4s)); 
}

void handle_sites() {
  String value = String("<p>Espacio 1</p>");
  if (par1s) {
    value += String("<a class=\"button button-on\">Carro</a>");
  } else {
    value += String("<a class=\"button button-off\">Libre</a>");
  }
  value += String("<p>Espacio 2</p>");
  if (par2s) {
    value += String("<a class=\"button button-on\">Carro</a>");
  } else {
    value += String("<a class=\"button button-off\">Libre</a>");
  }
  value += String("<p>Espacio 3</p>");
  if (par3s) {
    value += String("<a class=\"button button-on\">Carro</a>");
  } else {
    value += String("<a class=\"button button-off\">Libre</a>");
  }
  value += String("<p>Espacio 4</p>");
  if (par4s) {
    value += String("<a class=\"button button-on\">Carro</a>");
  } else {
    value += String("<a class=\"button button-off\">Libre</a>");
  }
  server.send(200, "text/plane", value); //Send ADC value only to client ajax request
}
void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

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

  ptr += "<span id=\"sites\">";
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
  ptr += "document.getElementById(\"sites\").innerHTML = this.responseText;}";
  ptr += "};";
  ptr += "xhttp.open(\"GET\", \"s1\", true);";
  ptr += "xhttp.send();";
  ptr += "}";


  ptr += "</script>";
  ptr += "</html>\n";
  return ptr;
}

void parkingData(uint8_t rxdata, uint8_t* p1, uint8_t* p2, uint8_t* p3, uint8_t* p4) {
  numSel = 0;
  if ((rxdata & 1) == 0) { // Revisando primer parqueo
    *p1 = HIGH;
  }
  else {
    *p1 = LOW;
    numSel++;
  }

  if ((rxdata & 2) == 0) { // Revisando segundo parqueo
    *p2 = HIGH;
  }
  else {
    *p2 = LOW;
    numSel++;
  }

  if ((rxdata & 4) == 0) { // Revisando tercer parqueo
    *p3 = HIGH;
  }
  else {
    *p3 = LOW;
    numSel++;
  }

  if ((rxdata & 8) == 0) { // Revisando cuarto parqueo
    *p4 = HIGH;
  }
  else {
    *p4 = LOW;
    numSel++;
  }
}
