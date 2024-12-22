#include <LiquidCrystal.h>

// Pin Definitions
const int temp = A1;                // Temperature sensor on A1
const int motor_terminal1 = 10;     // Motor terminal 1 on pin 10
const int motor_terminal2 = 11;     // Motor terminal 2 on pin 11
const int LedRed = 12;              // Red LED for high temp
const int LedGreen = 9;             // Green LED for normal temp
const int Buzzer = 8;               // Buzzer on pin 8

// LCD Pins: RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

void setup() {
  Serial.begin(9600);               // Start serial communication
  Serial.println("Smart irrigation system");

  lcd.begin(16, 2);                 // Initialize the LCD (16x2)
  lcd.print("Smart Irrigation");
  lcd.setCursor(4, 1);
  lcd.print("System!!");

  // Set pin modes
  pinMode(Buzzer, OUTPUT);
  pinMode(LedRed, OUTPUT);
  pinMode(LedGreen, OUTPUT);
  pinMode(motor_terminal1, OUTPUT);
  pinMode(motor_terminal2, OUTPUT);

  delay(2000);                      // Pause to display welcome message
  lcd.clear();
  lcd.print("Temp = ");
  lcd.setCursor(0, 1);
  lcd.print("WaterPump= ");
}

void loop() {
  int value = analogRead(temp);     // Read the analog value from the temp sensor
  float Temperature = (value * 5.0 / 1023.0) * 100;  // Convert analog reading to temperature

  Serial.print("Soil Temperature = ");
  Serial.println(Temperature);

  lcd.setCursor(6, 0);
  lcd.print(Temperature);           // Display the temperature on the LCD
  lcd.setCursor(11, 1);

  if (Temperature > 50) {           // If temperature is above 30°C
    digitalWrite(motor_terminal2, LOW);  // Turn off the water pump
    digitalWrite(motor_terminal1, LOW);
    noTone(Buzzer);                 // Turn off the buzzer
    digitalWrite(LedRed, LOW);      // Turn off red LED
    digitalWrite(LedGreen, HIGH);   // Turn on green LED (indicating normal condition)
    lcd.print("OFF");               // Show pump status as OFF on LCD
    Serial.println("Soil Temperature is high... Water pump is OFF.");
  }
  else {                            // If temperature is below 30°C
    digitalWrite(motor_terminal2, HIGH); // Turn on the water pump
    digitalWrite(motor_terminal1, LOW);
    digitalWrite(LedRed, HIGH);     // Turn on red LED (indicating water pump is ON)
    digitalWrite(LedGreen, LOW);    // Turn off green LED
    tone(Buzzer, 220);              // Turn on the buzzer
    lcd.print("ON ");               // Show pump status as ON on LCD
    Serial.println("Soil temperature is low, water pump is ON.");
  }

  delay(1000);                      // Pause for 1 second before repeating
}