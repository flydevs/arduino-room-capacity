
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
int MAXAMOUNT = 8;
int COUNT = 0;
int val = 0;
int val1 = 0;
long dis;
long tiem;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Crea un Objeto LC. Parametros: (rs, enable, d4, d5, d6, d7) 
 
void setup() {
  pinMode(10, OUTPUT); //salida del pulso generado por el sensor ultrasónico
  pinMode(9, INPUT);//entrada del pulso generado por el sensor ultrasónico
  pinMode(13, OUTPUT);//alarma de la distancia(encenderá el led)
  pinMode(8,INPUT);
  pinMode(11,INPUT);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("PAX: ");
  lcd.print(COUNT);
  lcd.print(" MAX: ");
  lcd.print(MAXAMOUNT);
  Serial.begin(115200);
}

void loop() {
  
  val1= digitalRead(11);
  val= digitalRead(8); 

  digitalWrite(10,LOW);//recibimiento del pulso.
  delayMicroseconds(5);
  digitalWrite(10, HIGH);//envió del pulso.
  delayMicroseconds(10);
  tiem=pulseIn(9, HIGH);//fórmula para medir el pulso entrante.
  dis= long(0.017*tiem);//fórmula para calcular la distancia del sensor ultrasónico.
  
  if(dis<200){ //comparativo para la alarma se ingresa la distancia en la que encenderá o apagara.
    digitalWrite(13, HIGH);
    COUNT = COUNT + 1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PAX: ");
    lcd.print(COUNT);
    lcd.print(" MAX: ");
    lcd.print(MAXAMOUNT);
  }
  else
  {
    digitalWrite(13,LOW);
  }

  if ((val == HIGH)){
    MAXAMOUNT=MAXAMOUNT+1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PAX: ");
    lcd.print(COUNT);
    lcd.print(" MAX: ");
    lcd.print(MAXAMOUNT);
  }
  
  if ((val1 == HIGH) && (MAXAMOUNT != 0)){
    MAXAMOUNT=MAXAMOUNT-1;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PAX: ");
    lcd.print(COUNT);
    lcd.print(" MAX: ");
    lcd.print(MAXAMOUNT);
  }

  delay(50);
  
}
