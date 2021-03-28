/*
 * Electrónica Digital II
 * Alejandra Samayoa
 * Carnet 18064
 * Lab 5-- Almacenamiento SD

    Se utilizó y se adaptó la librería listfiles.ino de la librería SD:
      creado   Nov 2010
      por David A. Mellis
      modificado 9 Apr 2012
      por Tom Igoe
      modificado 2 Feb 2014
      por Scott Fitzgerald  
    
      "This example code is in the public domain."
   
*/
//*****************************************************************************************************
//                                     Librerías
//*****************************************************************************************************

#include <SPI.h>
#include <SD.h>

//*****************************************************************************************************
//                                      Variables
//*****************************************************************************************************

File root; 
//Input desde la consola
int in = 0; 
//Para los archivos
String nombre = "";
String contenido = ""; 
//Diferentes banderas para los datos
bool in_new = false;
bool in_good = false;
bool init_failed = false; 


//*****************************************************************************************************
//                                      Setup
//*****************************************************************************************************

void setup(){
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  SPI.setModule(0); 
  //Chip Select
  pinMode(PA_3, OUTPUT); 
  //Si no está conectada bien la SD, enciende la bandera
  if (!SD.begin(PA_3)) { 
    Serial.println("initialization failed!");
    init_failed = true; 
    return; 
  }
  
  root = SD.open("/"); 
  printDirectory(root, 0); 
}

//*****************************************************************************************************
//                                            Loop Principal
//*****************************************************************************************************

void loop(){
  //Al haber una entrada y al verificar que la tarjeta esta bien, saca el menu con las opciones de archivos
  if (!in_new && !init_failed) { 
    menu(); 
    in_new = true;
  }
  //Al haber nuevos datos, lee el input in de la consola
  if (Serial.available() > 0) { 
    if (Serial.available() == 1) {
      in_new = false; 
    }
    in = Serial.read();

    // Para hacer las opciones hay que hacer un switch case con los valores en ascii
    // Primero verificamos que las opciones seleccionadas solo estén entre 1 y 4 
    if ((in > 52 || in < 49) && in != 10) { 
      Serial.println("Por favor eligé un número entre 1 y 4");
      delay(1000); 
      for (uint8_t i = 0; i < 15; i++) {
        Serial.println(" "); 
      }
    } 
    //Si sí es un input adecuado, pasa al switch case para las imágenes
    else if (in != 10) { 
      in_good = true; 
      switch (in) { 
        //Si el valor es 1, enseña puerta
        case 49: 
          nombre = "puerta.txt";
          break;
        //Si el valor es 2, enseña cohete
        case 50: 
          nombre = "ship.txt";
          break;
        //Si el valor es 3, enseña sol
        case 51: 
          nombre = "sun.txt";
          break;
        //Si el valor es 4, lee todas las opciones que hay
        case 52: 
          nombre = "/";
          in_good = false; 
          Serial.println(contenido); 
          break;
      }
    }
    Serial.println(""); 
  }

  if (in_good) { 
    //Si el input es válido, y se realizó el switch case bien, abre el archiv
    //correspondiente desde la tarjeta 
    in_good = false; 
    if (nombre == "puerta.txt") { 
      root = SD.open("/puerta.txt"); 
    } 
    else if (nombre == "ship.txt") {
      root = SD.open("/ship.txt");
    } 
    else if (nombre == "sun.txt") {
      root = SD.open("/sun.txt");
    }
   
    if (root) { // Si el documento no está disponible
      while (root.available()) {
         Serial.write(root.read()); 
      }
      root.close(); 
    }
    else { // No se encuentra el archivo
      Serial.println("No se encuentra el archivo"); 
    }
    Serial.println(""); 
  }
} 

//*****************************************************************************************************
//                                          Funciones
//*****************************************************************************************************

// Esta funcion es para buscar el archivo desde la sd y guardarlo como string
void printDirectory(File dir, int numTabs) {
  while (true) {
    File entry =  dir.openNextFile(); 
    if (! entry) { 
      break; 
    }
    for (uint8_t i = 0; i < numTabs; i++) { 
      contenido += '\t';
    }
    contenido += entry.name(); 
    if (entry.isDirectory()) { 
      contenido += "/ \n"; 
      printDirectory(entry, numTabs + 1); 
    } 
    else { 
      contenido += "\t\t"; 
      contenido += entry.size(); 
      contenido += "\n"; 
    }
    entry.close(); 
  }
}

// Para el menu de la consola
void menu(void) {
  Serial.println("Coloca el número de la imágen que quieres ver");
  Serial.println("1. Puerta");
  Serial.println("2. Cohete");
  Serial.println("3. Sol");
  Serial.println("4. Ver todas las opciones");
}
