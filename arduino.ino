#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

#define sensorPin A0

// LCD configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial espSerial(3, 2); // RX = Pin 3, TX = Pin 2

void setup()
{
  Serial.begin(9600);
  espSerial.begin(9600); // Initialize SoftwareSerial for ESP8266 communication
  lcd.init();
  lcd.backlight();
}

void loop()
{
  // Get the voltage reading from the LM35
  int reading = analogRead(sensorPin);

  // Convert that reading into voltage
  float voltage = reading * (5.0 / 1024.0);

  // Convert the voltage into the temperature in Celsius
  float temperatureC = voltage * 100;
  // Clear the LCD and set cursor to display temperature in Celsius
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(temperatureC);
  lcd.print("C ");

  // Print the temperature in Celsius to the Serial Monitor
  Serial.print("Temperature in Celsius: ");
  Serial.print(temperatureC);
  Serial.println("C");

  // Convert Celsius to Fahrenheit
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;

  // Set cursor to display temperature in Fahrenheit on the LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp:");
  lcd.print(temperatureF);
  lcd.print("F");

  // Print the temperature in Fahrenheit to the Serial Monitor
  Serial.print("Temperature in Fahrenheit: ");
  Serial.print(temperatureF);
  Serial.println("F");

  // Send temperature data to ESP8266
  sendToESP(temperatureC);

  delay(2000); // Wait for 2 second between readings
}

void sendToESP(float temperatureC)
{
  // Create a string containing the temperature data to send to ESP8266
  String postData = "temperature=" + String(temperatureC);

  // Send the temperature data to ESP8266 using SoftwareSerial
  espSerial.println(postData);
}