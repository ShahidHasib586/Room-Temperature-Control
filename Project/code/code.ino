#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Keypad.h>

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int tempPin = 0;
int val;
short celcius;
char tempValue[16];

// Keypad
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 4, 0, A5};
byte colPins[COLS] = {A4, A3, A2, A1};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// Define state constants
const int HOME = 0;
const int SETUP = 1;
const int AMBIENT = 2;
const int HEAT = 3;
const int COLD = 4;
const int SET_UPPER_THRESHOLD = 5;
const int SET_LOWER_THRESHOLD = 6;
int currentState = HOME; // Initialize to HOME state

int upperThreshold = 30; // Default upper temperature threshold
int lowerThreshold = 20; // Default lower temperature threshold

// Function to set the upper temperature threshold
void setUpperThreshold(char key) {
  if (key >= '0' && key <= '9') {
    // If a numeric key is pressed, update the upper threshold
    upperThreshold = (upperThreshold * 10) + (key - '0');
  } else if (key == '#') {
    // If '#' is pressed, save the upper threshold to EEPROM
    EEPROM.write(0, upperThreshold);
    // Return to the SETUP menu
    currentState = SETUP;
  }
}

// Function to set the lower temperature threshold
void setLowerThreshold(char key) {
  if (key >= '0' && key <= '9') {
    // If a numeric key is pressed, update the lower threshold
    lowerThreshold = (lowerThreshold * 10) + (key - '0');
  } else if (key == '#') {
    // If '#' is pressed, save the lower threshold to EEPROM
    EEPROM.write(1, lowerThreshold);
    // Return to the SETUP menu
    currentState = SETUP;
  }
}

void displaySetupMenu(); // Function declaration
void handleSetupMenu(char key);
void Readtemp();

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
  char key = keypad.getKey();
  
  switch (currentState) {
    case HOME:
      if (key == '0') {
        currentState = SETUP;
        displaySetupMenu();
      }
      break;

    case SETUP:
      handleSetupMenu(key);
      break;

    case AMBIENT:
      // Handle AMBIENT menu logic here
      break;

    case HEAT:
      // Handle HEAT menu logic here
      break;

    case COLD:
      // Handle COLD menu logic here
      break;

    case SET_UPPER_THRESHOLD:
      setUpperThreshold(key);
      break;

    case SET_LOWER_THRESHOLD:
      setLowerThreshold(key);
      break;
  }
  // Temperature and Fan Control Logic
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

  delay(1000); // Add a delay to prevent flickering of the display
}

void Readtemp() {
  lcd.setCursor(6, 0);
  lcd.print("  "); // Clear the temperature value
  val = analogRead(tempPin);
  celcius = val * 4.88 / 10;
  lcd.setCursor(6, 0);
  lcd.print(celcius);
  lcd.write(byte(0)); // Display the custom degree Celsius symbol
}

void displaySetupMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1. Operation Mode");
  lcd.setCursor(0, 1);
  lcd.print("2. Ambient");
}

void handleSetupMenu(char key) {
  switch (key) {
    case '1':
      // Set the current state to AMBIENT
      currentState = AMBIENT;
      // Display relevant information on the LCD screen
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("AMBIENT MODE");
      lcd.setCursor(0, 1);
      lcd.print("Description:");
      
      break;
      
    case '2':
      // Set the current state to HEAT
      currentState = HEAT;
      // Display relevant information on the LCD screen
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("HEAT MODE");
      lcd.setCursor(0, 1);
      lcd.print("Description:");
      
      break;
      

    default:
      break;
  }
}
