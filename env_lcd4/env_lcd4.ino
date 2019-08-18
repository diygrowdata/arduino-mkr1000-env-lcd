#include <LiquidCrystal.h>
#include <Arduino_MKRENV.h>

LiquidCrystal lcd(0,1,2,3,4,5);

float Tf = 0.0;
float rH = 0.0;
float P = 0.0;
float Light = 0.0;
float UVA = 0.0;
float UVB = 0.0;
float UVI = 0.0;
float Dewf = 0.0;

void getReadings() {
  //get sensor readings 
  Tf = ENV.readTemperature(FAHRENHEIT);
  rH = ENV.readHumidity();
  P = ENV.readPressure();
  Light = ENV.readIlluminance();
  UVA = ENV.readUVA();
  UVB = ENV.readUVB();
  UVI = ENV.readUVIndex();
  Dewf = Tf - (9 * (100 - rH) / 25);
}

void printReadings(float Tf, float rH, float Dewf, float P, float Light, float UVA, float UVB, float UVI) {

  Serial.print("Tf = ");
  Serial.print(Tf);
  Serial.print("°F  ");
    
  Serial.print("rH = ");
  Serial.print(rH);
  Serial.print("%  ");

  Serial.print("dew:");
  Serial.print(round(Dewf));
  Serial.print("°F  ");
  
  Serial.print("P = ");
  Serial.print(P); 
  Serial.print("kPa  ");
    
  Serial.print("lux = ");
  Serial.print(Light);
  Serial.print("  ");
  
  Serial.print("UVA = ");
  Serial.print(UVA); 
  Serial.print("  ");
 
  Serial.print("UVB = ");
  Serial.print(UVB); 
  Serial.print("  ");
    
  Serial.print("UVI = ");
  Serial.print(UVI); 
  Serial.println("  "); 
}

void displayReadings(float Tf, float rH, float Dewf, float P, float Light, float UVA, float UVB, float UVI) {
  lcd.home();

  //Temperature
  lcd.setCursor(0,0); 
  lcd.print("Tf:");
  lcd.print(round(Tf));
  lcd.print((char)223);
  lcd.print("F ");
  //Humidity
  lcd.setCursor(0,1);
  lcd.print("rH:");
  lcd.print(round(rH));
  lcd.print("% ");

  //Dewpoint
  lcd.setCursor(8,0); 
  lcd.print("dew:");
  lcd.print(round(Dewf));
  lcd.print((char)223);
  lcd.print("F ");
  //Pressure
  lcd.setCursor(8,1);
  lcd.print("P:");
  lcd.print(round(P));
  lcd.print("kPa ");
    
  delay(5000);
  lcd.clear();
  
  //Light (Illuminance)
  lcd.setCursor(0,0);
  lcd.print("lux:");
  lcd.print(round(Light));  

  //UVA
  lcd.setCursor(0,1);
  
  lcd.print("uva:");
  lcd.print(round(UVA));   

  //UVB
  lcd.setCursor(10,0);
  lcd.print("uvb:");
  lcd.print(round(UVB));  

  //UV Index
  lcd.setCursor(10,1);
  lcd.print("uvi:");
  lcd.print(round(UVI));
  
  delay(5000);
  lcd.clear();
}

void displayIntro(String line1,  String line2) {
  lcd.setCursor(0,0); 
  lcd.print(line1);
  lcd.setCursor(0,1); 
  lcd.print(line2);
}

void setup() {
  lcd.begin(16, 2);
  
  displayIntro("@diygrowdata",  "diygrowdata.com");
  
  Serial.begin(9600);
  while (!Serial);
  
  if (!ENV.begin()) {
    Serial.println("Failed to initialize MKR ENV shield!");
    while (1);
  }
}

void loop() {
  getReadings();
  printReadings(Tf, rH, Dewf, P, Light, UVA, UVB, UVI);
  displayReadings(Tf, rH, Dewf, P, Light, UVA, UVB, UVI);
  
}
