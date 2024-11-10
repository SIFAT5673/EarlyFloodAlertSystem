#include <LiquidCrystal.h>
#include <dht.h>

#define dht_apin A0
#define trigger 6
#define echo 7

float time = 0, distance = 0;
dht DHT;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
}

void loop() {
  DHT.read11(dht_apin);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);
  distance = time * 340 / 20000;


  distance=(100*distance)/11;



  lcd.setCursor(0, 0);
  lcd.print(String(DHT.humidity) + " H");
  lcd.setCursor(8, 0);
  lcd.print(String(DHT.temperature) + " T");
  lcd.setCursor(0, 1);

  if(distance<30)
  {
      lcd.print(String(distance) + "% HIG");
      Serial.println("HIGH");

  }
  else if(distance<70)
  {
      lcd.print(String(distance) + "% MID");
      Serial.println("MID");
  }
  else
  {
    lcd.print(String(distance) + "% LOW");
    Serial.println("LOW");
  }
  delay(1000);


}
