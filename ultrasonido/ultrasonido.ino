
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
int MAXAMOUNT = 8;
int COUNT = 0;
int ButtonIncrement = 0;
int ButtonDecrement = 0;
int MaxDetection = 200;
int ButtonDelay = 200;
int buttonCountDelay = 0;
long Distance1;
long Distance2;
long receiver1;
long receiver2;
bool sensor1 = false;
bool sensor2 = false;
int lastState=0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Crea un Objeto LC. Parametros: (rs, enable, d4, d5, d6, d7) 
 
void setup() {
  // Sensor 1
  pinMode(10, OUTPUT); //salida del pulso generado por el sensor ultrasónico
  pinMode(9, INPUT);//entrada del pulso generado por el sensor ultrasónico
  // Sensor 2 
  pinMode(13, OUTPUT); //salida del pulso generado por el sensor ultrasónico
  pinMode(12, INPUT);//entrada del pulso generado por el sensor ultrasónico

  // BUTTONS
  pinMode(8,INPUT);
  pinMode(11,INPUT);

  // SCREEN
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME!"); 
  Serial.begin(115200);
}

void loop() {
  
  ButtonIncrement=digitalRead(11);
  ButtonDecrement=digitalRead(8); 

  // Sensors
  digitalWrite(10,LOW); //recibimiento del pulso.
  digitalWrite(13,LOW); //recibimiento del pulso.
  delayMicroseconds(5);
  digitalWrite(10, HIGH);//envió del pulso.
  digitalWrite(13, HIGH);//envió del pulso.
  delayMicroseconds(10);
  receiver1=pulseIn(9, HIGH);//fórmula para medir el pulso entrante.
  receiver2=pulseIn(12, HIGH);//fórmula para medir el pulso entrante.
  
  Distance1=long(0.017*receiver1);//fórmula para calcular la distancia del sensor ultrasónico.
  Distance2=long(0.017*receiver2);//fórmula para calcular la distancia del sensor ultrasónico.

  sensor1 = Distance1>0 and Distance1<MaxDetection;
  sensor2 = Distance2>0 and Distance2<MaxDetection;
/*
  Serial.println("Sensor 1: ");
  Serial.println(sensor1);
  Serial.println("Sensor 2: ");
  Serial.println(sensor2);*/


  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(Distance1);
  
  lcd.setCursor(3,0);
  lcd.print(" - ");
  lcd.print(Distance2);
  
  lcd.setCursor(9,0);
  lcd.print("CM");

   
  lcd.setCursor(0,1); 
  lcd.print(sensor1);
  
  lcd.setCursor(1,1);
  lcd.print(" / ");
  lcd.print(sensor2);

    
  lcd.setCursor(9,1);
  lcd.print("LIGHT");
  /*
  if(Distance1<MaxDetection){ //comparativo para la alarma se ingresa la distancia en la que encenderá o apagara.
    digitalWrite(13, HIGH);
    COUNT = COUNT + 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("R: ");
    lcd.print(COUNT);
    lcd.print(" MAX: ");
    lcd.print(MAXAMOUNT);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  */

  // Botones


  if (buttonCountDelay<ButtonDelay){
    buttonCountDelay+=50;
  }else{
    buttonCountDelay=0;
      
    if ((ButtonIncrement == HIGH)){
      MAXAMOUNT=MAXAMOUNT+1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("PAX: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
    
    if ((ButtonDecrement == HIGH) && (MAXAMOUNT != 0)){
      MAXAMOUNT=MAXAMOUNT-1;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
  }
  
  delay(50);
}
