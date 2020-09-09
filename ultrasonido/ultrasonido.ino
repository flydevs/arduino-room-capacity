
#include <LiquidCrystal.h> // Incluye la Libreria LiquidCrystal
int MAXAMOUNT = 0;
long dis;
long tiem;
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Crea un Objeto LC. Parametros: (rs, enable, d4, d5, d6, d7) 
 
void setup() {
  pinMode(10, OUTPUT); //salida del pulso generado por el sensor ultrasónico
  pinMode(9, INPUT);//entrada del pulso generado por el sensor ultrasónico
  pinMode(13, OUTPUT);//alarma de la distancia(encenderá el led)
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("PAX: ");
  lcd.print(MAXAMOUNT);
  Serial.begin(115200);
}

void loop() {
  digitalWrite(10,LOW);//recibimiento del pulso.
  delayMicroseconds(5);
  digitalWrite(10, HIGH);//envió del pulso.
  delayMicroseconds(10);
  tiem=pulseIn(9, HIGH);//fórmula para medir el pulso entrante.
  dis= long(0.017*tiem);//fórmula para calcular la distancia del sensor ultrasónico.
  
  if(dis<100){ //comparativo para la alarma se ingresa la distancia en la que encenderá o apagara.
    digitalWrite(13, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("PAX: ");
    lcd.print(MAXAMOUNT++);
  }
  else
  {
    digitalWrite(13,LOW);
  }
  
  Serial.println("LA DISTANCIA MEDIDA ES:");
  Serial.println(dis);
  Serial.println("cm");
  delay(500);
  
}
