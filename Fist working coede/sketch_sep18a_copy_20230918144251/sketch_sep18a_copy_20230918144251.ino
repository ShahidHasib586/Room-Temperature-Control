#include <LiquidCrystal.h>
const int rs = 13 , en = 12 , d4 = 11 , d5 = 10 , d6 = 9 , d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int tempPin = 0;
int val;

short celcius;
char temp[16];


void setup() {
  pinMode (7, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (2, OUTPUT);
  pinMode (1, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp: (temperature value from the temperature sensor) °C"); 
  lcd.setCursor(1, 1);
  lcd.print("Fan Speed: (Numerical Motor Speed) RPM");
}

void loop() {
  Readtemp();
  //NORMAL TEMP
  if (celcius <= 30 && celcius >= 20) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(1, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);    
  }
  //HIGH TEMP
  else if (celcius > 30) {
    FanON();
    digitalWrite(1, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    delay(800);
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: (Numerical Motor Speed) RPM");
    lcd.setCursor(1, 1);
    
  }
  //LOW TEMP
  else if (celcius < 20) {
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(1, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW); 
    delay(800); 
    lcd.setCursor(0, 1);
    lcd.print("Fan Speed: (Numerical Motor Speed) RPM");
    lcd.setCursor(0, 1);
     
  }

}

void Readtemp() {
  delay(500);
  lcd.setCursor(0, 1);
  lcd.print("                 ");
  val = analogRead(tempPin);
  celcius = val*4.88/10;
  sprintf(temp, "%0.2d", celcius);
    lcd.setCursor(1, 1);
    lcd.print("Fan Speed: (Numerical Motor Speed) RPM");
    lcd.print(temp);
    lcd.write(B11011111);
    lcd.print("C");    
}

void FanON() {
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);  
  delay(100);
}
