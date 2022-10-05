//--------------------1
#define Tempin_Sensor A0
#include <LiquidCrystal.h>

float voltage = 0; // Thiet lap mot so gia tri ban dau
float sensor = 0;
float celsius = 0;
float fahrenheit = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//--------------------2
const int ledPin = 10;
const int ldrPin= A1;
//--------------------3
int Sensor = A2;
int clap = 0;
long detection_range_start = 0;
long detection_range = 0;
boolean status_lights = false;



void setup() {
  //--------------------1
  lcd.begin(16, 2);
  lcd.setCursor(3, 0);
  lcd.print("Nhiet Do:");
    //--------------------2
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(ldrPin, INPUT);
      //--------------------3
      pinMode(Sensor, INPUT);
      pinMode(8, OUTPUT);
}



void loop() {
  //--------------------1
    sensor = analogRead(Tempin_Sensor);
    voltage = (sensor*5000)/1024;
    voltage = voltage - 495;
    celsius = voltage/10;
    lcd.setCursor(5, 1);
    lcd.print(celsius);
    int ldrStatus = analogRead(ldrPin);
  //--------------------2
  if(ldrStatus <= 300){
   digitalWrite(ledPin, HIGH);
   Serial.println("LDR is DARK, LED is ON");
  }
  else{
   digitalWrite(ledPin, LOW);
   Serial.println("--------------");
  }
  //--------------------3
  int status_sensor = digitalRead(Sensor);
  if (status_sensor == 0)
  {
    if (clap == 0)
    {
      detection_range_start = detection_range = millis();
      clap++;
    }
    else if (clap > 0 && millis() - detection_range >= 50)
    {
      detection_range = millis();
      clap++;
    }
  }
  if (millis() - detection_range_start >= 400)
  {
    if (clap == 2)
    {
      if (!status_lights)
      {
        status_lights = true;
        digitalWrite(8, HIGH);
      }
      else if (status_lights)
      {
        status_lights = false;
        digitalWrite(8, LOW);
      }
    }
    clap = 0;
  }
}
