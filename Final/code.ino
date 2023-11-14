#include <LiquidCrystal.h>
#include <Keypad.h>
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int tempPin = 0;
int val;

short celcius;
char tempValue[16];
//Keypad
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Four columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 0, A5}; // Connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A3, A2, A1}; // Connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int upperThreshold = 30; // Default upper temperature threshold
int lowerThreshold = 20; // Default lower temperature threshold

enum State {
  HOME,
  SETUP,
  AMBIENT,
  HEAT,
  COLD,
  SET_UPPER_THRESHOLD,
  SET_LOWER_THRESHOLD
};

State currentState = HOME;
// Define custom character for the degree Celsius symbol
byte degreeSymbol[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

// Fan speed control variables
int fanSpeed = 0;
int fanSpeedPin = 6; // PWM pin for controlling fan speed

void setup() {
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(fanSpeedPin, OUTPUT); // Set fan speed pin as an OUTPUT
  analogWrite(fanSpeedPin, fanSpeed); // Initialize fan speed to 0
  lcd.createChar(0, degreeSymbol); // Define custom character at position 0
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(0, 1);
  lcd.print("Fan Speed:    ");
}

void loop() {
  Readtemp();

  // NORMAL TEMP
  if (celcius <= 25 && celcius >= 20) {
    fanSpeed = 2; // Set fan speed to 2 (minimum)
    analogWrite(fanSpeedPin, fanSpeed);
    digitalWrite(2, HIGH); // Green light
    digitalWrite(3, LOW); // Red Light
    digitalWrite(1, LOW); // Blue light
  }
  // HIGH TEMP
  else if (celcius > 25 && celcius < 30) {
    fanSpeed = map(celcius, 25, 30, 2, 255); // Gradually increase fan speed
    analogWrite(fanSpeedPin, fanSpeed);
    digitalWrite(2, LOW); // Green light
    digitalWrite(3, HIGH); // Red light
    digitalWrite(1, LOW); // Blue light
  }
  // MAX TEMP
  else if (celcius >= 30) {
    fanSpeed = 255; // Set fan speed to maximum
    analogWrite(fanSpeedPin, fanSpeed);
    digitalWrite(2, LOW); // Green light
    digitalWrite(3, HIGH); // Red light
    digitalWrite(1, LOW); // Blue light
  }
  // LOW TEMP
  else {
    fanSpeed = 0; // Set fan speed to 0
    analogWrite(fanSpeedPin, fanSpeed);
    digitalWrite(2, LOW); // Red light
    digitalWrite(3, LOW); // Green light
    digitalWrite(1, HIGH); // Blue light
  }

  // Update the fan speed display
  lcd.setCursor(12, 1);
  lcd.print("   "); // Clear fan speed value
  lcd.setCursor(12, 1);
  lcd.print(fanSpeed);

  delay(1000); // Add a delay to prevent flickering of display
}

void Readtemp() {
  lcd.setCursor(6, 0);
  lcd.print("  "); // Clear temperature value
  val = analogRead(tempPin);
  celcius = val * 4.88 / 10;
  lcd.setCursor(6, 0);
  lcd.print(celcius);
  lcd.write(byte(0)); // Display custom degree Celsius symbol
}
void setup0() {
  Serial.begin(9600);	/* Define baud rate for serial communication */
}

void loop0() {
  int adc_val;
  adc_val = analogRead(A1);	/* Read input from keypad */
  if (adc_val>850)
  {
    Serial.print("Key Pressed : ");
    Serial.println("0");
    delay(100);
  }
  else if ( adc_val>450  && adc_val<510)
  {
    Serial.print("Key Pressed : ");
    Serial.println("1");
    delay(100);
  }
  else if ( adc_val>300  && adc_val<350)
  {
    Serial.print("Key Pressed : ");
    Serial.println("2");
    delay(100);
  }
  else if ( adc_val>230  && adc_val<270)
  {
    Serial.print("Key Pressed : ");
    Serial.println("3");
    delay(100);
  }
  else if ( adc_val>160  && adc_val<180)
  {
    Serial.print("Key Pressed : ");
    Serial.println("4");
    delay(100);
  }
  else if ( adc_val>145  && adc_val<155)
  {
    Serial.print("Key Pressed : ");
    Serial.println("5");
    delay(100);
  }
  else if ( adc_val>125  && adc_val<135)
  {
    Serial.print("Key Pressed : ");
    Serial.println("6");
    delay(100);
  }
  else if ( adc_val>105  && adc_val<120)
  {
    Serial.print("Key Pressed : ");
    Serial.println("7");
    delay(100);
  }
  else if ( adc_val>92  && adc_val<99)
  {
    Serial.print("Key Pressed : ");
    Serial.println("8");
    delay(100);
  }
  else if ( adc_val>82  && adc_val<90)
  {
    Serial.print("Key Pressed : ");
    Serial.println("9");
    delay(100);
  }
  else if ( adc_val>77  && adc_val<81)
  {
    Serial.print("Key Pressed : ");
    Serial.println("A");
    delay(100);
  }
  else if ( adc_val>72  && adc_val<76)
  {
    Serial.print("Key Pressed : ");
    Serial.println("B");
    delay(100);
  }
  else if ( adc_val>63  && adc_val<68)
  {
    Serial.print("Key Pressed : ");
    Serial.println("C");
    delay(100);
  }
  else if ( adc_val>60  && adc_val<62)
  {
    Serial.print("Key Pressed : ");
    Serial.println("D");
    delay(100);
  }
  else if ( adc_val>57  && adc_val<59)
  {
    Serial.print("Key Pressed : ");
    Serial.println("E");
    delay(100);
  }
  else if( adc_val>52  && adc_val<56)
  {
    Serial.print("Key Pressed : ");
    Serial.println("F");
    delay(100);
  }
  else
  {
	  
  }
  delay(100);
}