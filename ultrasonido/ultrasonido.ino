
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
#include <Ultrasonic.h> //
#include "FIFO.h"

int last_MAXAMOUNT = 8;
int last_COUNT = 0;
int MAXAMOUNT = 8;
int COUNT = 0;
int ButtonIncrement = 0;
int ButtonDecrement = 0;
int MaxDetection = 100;
int ButtonDelay = 100;
int buttonCountDelay = 0;
long last_Distance1;
long last_Distance2; 
long Distance1;
long Distance2; 
bool last_sensor1 = false;
bool last_sensor2 = false;
bool sensor1 = false;
bool sensor2 = false;
int lastState=0; 
int lastIndex =0;
FIFO myBuffer1;
FIFO myBuffer2;
int lastValues1[10] = {0,0,0,0,0,0,0,0,0,0};
int lastValues2[10] = {0,0,0,0,0,0,0,0,0,0};
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Crea un Objeto LC. Parametros: (rs, enable, d4, d5, d6, d7) 

Ultrasonic ultrasonic1(10, 9);  // An ultrasonic sensor HC-04 
Ultrasonic ultrasonic2(13, 12);  // An ultrasonic sensor HC-04 
void setup() { 
  
  // BUTTONS
  pinMode(8,INPUT);
  pinMode(11,INPUT);
  
  delay(100);
  // SCREEN
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME!");  
  
  for (byte i = 0; i < 10; i++) { 
    myBuffer1.push(lastValues1[i]); 
  }
  for (byte i = 0; i < 10; i++) { 
    myBuffer2.push(lastValues2[i]); 
  }
  
}

void loop() {

  
  ButtonIncrement=digitalRead(11);
  ButtonDecrement=digitalRead(8); 

  last_Distance1 = Distance1;
  last_Distance2 = Distance2;
  last_sensor1 = sensor1;
  last_sensor2 = sensor2;
  Distance1=ultrasonic1.read();//fórmula para calcular la distancia del sensor ultrasónico.
  Distance2=ultrasonic2.read();//fórmula para calcular la distancia del sensor ultrasónico.

  sensor1 = Distance1>0 and Distance1<MaxDetection;
  sensor2 = Distance2>0 and Distance2<MaxDetection;

  myBuffer1.push(sensor1);
  myBuffer2.push(sensor2);
  
  // INFORM BY DISPLAY, ONLY IF THERE ARE NEW VALUES

  if (
    last_sensor1 != sensor1 ||
    last_sensor2 != sensor2 ||
    last_Distance1 != Distance1 ||
    last_Distance2 != Distance2
    
    ){ 
      lcd.setCursor(0,0); 
      lcd.print(Distance1);
      
      lcd.setCursor(3,0);
      lcd.print("/");
      lcd.print(Distance2); 
      
      lcd.setCursor(7,0);
      lcd.print("  [");
      lcd.print(sensor1);
      lcd.print(",");
      lcd.print(sensor2);
      lcd.print("]");
    
      lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);

    }
// Botones


  if (buttonCountDelay<ButtonDelay){
    buttonCountDelay+=50;
  }else{
    buttonCountDelay=0;

    last_MAXAMOUNT=MAXAMOUNT;
    last_COUNT=COUNT;
    if ((ButtonIncrement == HIGH)){
      MAXAMOUNT=MAXAMOUNT+1;
      
      lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
    if ((ButtonDecrement == HIGH) && (MAXAMOUNT != 0)){
      MAXAMOUNT=MAXAMOUNT-1;
      
      lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
  } 
  
    // increment index
    lastIndex++;
    if (lastIndex>9){
      lastIndex=0;
    }
  delay(10);
}
