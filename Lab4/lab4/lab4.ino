/*
 * Electrónica Digital II
 * Alejandra Samayoa
 * Carnet 18064
 * Lab 4-- Juego de Carreras

*/
//*****************************************************************************************************
//                                          Variables
//*****************************************************************************************************

const int ledG =  GREEN_LED;    
const int ledB =  BLUE_LED; 
const int ledR =  RED_LED;   
int flag=0;
int c1=0;
int c2=0;
int play1= PUSH1;
int play2= PUSH2;
int buttonPin = PE_0;   
int buttonState = 0;         
int button1 = 0; 
int button2 = 0; 
//*****************************************************************************************************
//                                          Setup
//*****************************************************************************************************

void setup() {
  Serial.begin(9600);
  pinMode(ledB, OUTPUT);  
  pinMode(ledG, OUTPUT);  
  pinMode(ledR, OUTPUT);   
 //Semáforo  
  pinMode(buttonPin, INPUT_PULLUP);  
// Botones para jugar
  pinMode(play1, INPUT_PULLUP);  
  pinMode(play2, INPUT_PULLUP);    

//Las diferentes LEDS para nuestro contador 
  pinMode(PA_5, OUTPUT);
  pinMode(PA_6, OUTPUT);
  pinMode(PA_7, OUTPUT); 
  pinMode(PB_0, OUTPUT);
  pinMode(PB_1, OUTPUT);
  pinMode(PB_4, OUTPUT);
  pinMode(PB_5, OUTPUT);
  pinMode(PD_0, OUTPUT);
  pinMode(PD_1, OUTPUT);
  pinMode(PD_2, OUTPUT);
  pinMode(PD_3, OUTPUT);
  pinMode(PE_1, OUTPUT);
  pinMode(PE_2, OUTPUT);
  pinMode(PE_3, OUTPUT);
  pinMode(PE_4, OUTPUT);
  pinMode(PE_5, OUTPUT);
//Función para limpiar todo 
  zero();

}
//*****************************************************************************************************
//                                          Loop Principal
//*****************************************************************************************************

void loop(){
  //Activa función semáforo que activa una flag
  buttonState = digitalRead(buttonPin);
  if (buttonState == LOW) {   
    semaforo();
  } 
//Al haberse activado la flag, podemos jugar 
  while (flag==HIGH){
    player1();
    player2();
    winner();
    }

}

//*****************************************************************************************************
//                                          Funciones
//*****************************************************************************************************

void semaforo(){
    digitalWrite(ledR, HIGH);  
    delay(1000);  
    digitalWrite(ledG, HIGH);  
    delay(1000);
    digitalWrite(ledR, LOW);
    delay(50);
    digitalWrite(ledG, HIGH);
    delay(1000); 
    flag=1;
    c2=1;
    c1=1;
 
  }
  //Jugador 1
void player1(){
  button1 = digitalRead(play1);
  if (button1 == LOW) {   
    c1 ++;
    delay(40);
  }
  switch (c1) {
    case 1:
      digitalWrite(PB_5, HIGH);
      break;
    case 2:
      digitalWrite(PB_0, HIGH);
      break;
    case 4:
      digitalWrite(PB_1, HIGH);
      break;
    case 8:
      digitalWrite(PE_4, HIGH);
      break;
    case 16:
      digitalWrite(PE_5, HIGH);
      break;
    case 32:
      digitalWrite(PB_4, HIGH);
      break;
    case 64:
      digitalWrite(PA_5, HIGH);
      break;
    case 128:
      digitalWrite(PA_6, HIGH);
      break;
    default:
      digitalWrite(ledG, LOW);
      digitalWrite(ledR, LOW);
      break;
  }
}
  

 //Jugador 2
void player2(){
  button2 = digitalRead(play2);
    if (button2 == LOW) {   
    c2 ++;
    delay(40);
  }
    switch (c2) {
    case 1:
      digitalWrite(PD_0, HIGH);
      break;
    case 2:
      digitalWrite(PD_1, HIGH);
      break;
    case 4:
      digitalWrite(PD_2, HIGH);
      break;
    case 8:
      digitalWrite(PD_3, HIGH);
      break;
    case 16:
      digitalWrite(PE_1, HIGH);
      break;
    case 32:
      digitalWrite(PE_2, HIGH);
      break;
    case 64:
      digitalWrite(PE_3, HIGH);
      break;
    case 128:
      digitalWrite(PA_7, HIGH);
      break;
    default:
      digitalWrite(ledG, LOW);
      digitalWrite(ledR, LOW);
      break;
  }
}
//Función para que todos los LEDs estén apagados
void zero (void) { 
  digitalWrite(PA_5, LOW);
  digitalWrite(PA_6, LOW);
  digitalWrite(PA_7, LOW);
  digitalWrite(PB_0, LOW);
  digitalWrite(PB_1, LOW);
  digitalWrite(PB_4, LOW);
  digitalWrite(PB_5, LOW);
  digitalWrite(PD_0, LOW);
  digitalWrite(PD_1, LOW);
  digitalWrite(PD_2, LOW);
  digitalWrite(PD_3, LOW);
  digitalWrite(PE_1, LOW);
  digitalWrite(PE_2, LOW);
  digitalWrite(PE_3, LOW);
  digitalWrite(PE_4, LOW);
  digitalWrite(PE_5, LOW);
  
}
//Se declara el ganador 
void winner(void){ //Morado para jugador 1
   if (c1==128) {
    digitalWrite(ledB, HIGH); 
    digitalWrite(ledR, HIGH);
    digitalWrite(ledG, LOW);
    delay(1000)
  }
  else if (c2==128) {//Turquesa para jugador 2
    digitalWrite(ledB, HIGH); 
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, HIGH);
    delay(1000);  
    }
  else  {
    digitalWrite(ledB, LOW); 
    digitalWrite(ledG, LOW);
    digitalWrite(ledR, LOW);
  }
  
  }
