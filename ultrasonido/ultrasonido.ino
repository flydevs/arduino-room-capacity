
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
#include <Ultrasonic.h> //

int MAXAMOUNT = 8;
int COUNT = 0;
int ButtonIncrement = 0;
int ButtonDecrement = 0;
int MaxDetection = 100;
int ButtonDelay = 100;
int buttonCountDelay = 0;
long Distance1;
long Distance2;
long receiver1;
long receiver2;
bool sensor1 = false;
bool sensor2 = false;
int lastState=0;

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Crea un Objeto LC. Parametros: (rs, enable, d4, d5, d6, d7) 

Ultrasonic ultrasonic1(10, 9);  // An ultrasonic sensor HC-04 
Ultrasonic ultrasonic2(13, 12);  // An ultrasonic sensor HC-04 
void setup() {
  


  // BUTTONS
  pinMode(8,INPUT);
  pinMode(11,INPUT);

  // SCREEN
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("WELCOME!");  
}

void loop() {
  
  ButtonIncrement=digitalRead(11);
  ButtonDecrement=digitalRead(8); 

  
  
  Distance1=ultrasonic1.read();//fórmula para calcular la distancia del sensor ultrasónico.
  Distance2=ultrasonic2.read();//fórmula para calcular la distancia del sensor ultrasónico.

  sensor1 = Distance1>0 and Distance1<MaxDetection;
  sensor2 = Distance2>0 and Distance2<MaxDetection;

  // INFORM BY DISPLAY
  
  lcd.clear();
  lcd.setCursor(0,0); 
  lcd.print(Distance1);
  
  lcd.setCursor(3,0);
  lcd.print("/");
  lcd.print(Distance2);
  
  lcd.setCursor(9,0);
  lcd.print("[");
  lcd.print(sensor1);
  lcd.print(",");
  lcd.print(sensor2);
  lcd.print("]");


    lcd.setCursor(0,1);
    lcd.print("R: ");
    lcd.print(COUNT);
    lcd.print(" MAX: ");
    lcd.print(MAXAMOUNT);
  // Botones


  if (buttonCountDelay<ButtonDelay){
    buttonCountDelay+=50;
  }else{
    buttonCountDelay=0;
      
    if ((ButtonIncrement == HIGH)){
      MAXAMOUNT=MAXAMOUNT+1;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
    
    if ((ButtonDecrement == HIGH) && (MAXAMOUNT != 0)){
      MAXAMOUNT=MAXAMOUNT-1;
      lcd.clear();
      lcd.setCursor(0,1);
      lcd.print("R: ");
      lcd.print(COUNT);
      lcd.print(" MAX: ");
      lcd.print(MAXAMOUNT);
    }
  }
  
  delay(10);
}
