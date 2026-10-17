#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int ir_s1 = 2;
int ir_s2 = 3;
int count = 0;
int in =0;
int out = 0;

LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup()
{
  Serial.begin(9600);

  pinMode(ir_s1, INPUT);
  pinMode(ir_s2, INPUT);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("PSN");

  lcd.setCursor(0, 1);
  lcd.print(count);
  lcd.setCursor(5, 0);
  lcd.print("IN");
  lcd.setCursor(5,1);
  lcd.print(in);
  lcd.setCursor(10,0);
  lcd.print("OUT");
  lcd.setCursor(10,1);
  lcd.print(out);
}
void loop()
{
  //in loop
  if (digitalRead(ir_s1) == LOW) //sensor1 detected
  {
    while (digitalRead(ir_s2) == HIGH)//waiting for sensor2 detection
    {
    }

    count++;//count increase by one
    in++;// in increased by one
    while (digitalRead(ir_s1) == LOW || digitalRead(ir_s2) == LOW)//waiting for crossing the door
    {
    }
    Serial.print(count);
    Serial.print("\t");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(count);
    lcd.setCursor(5,1);
    lcd.print("    ");
    lcd.setCursor(5, 1);
    lcd.print(in);
  }
  //out loop
  else if (digitalRead(ir_s2) == LOW)//sensor2 detected
  {
    while (digitalRead(ir_s1) == HIGH)//waiting for sensor1 detection
    {
    }

    if (count > 0)
    {
      count--;// decrease count by one
      out++;// increase out by one
    }

    while (digitalRead(ir_s1) == LOW || digitalRead(ir_s2) == LOW)//waiting for crossing the door
    {
    }
    Serial.print(count);
    Serial.print("\t");
    lcd.setCursor(0, 1);
    lcd.print("    ");
    lcd.setCursor(0, 1);
    lcd.print(count);
    lcd.setCursor(10,1);
    lcd.print("    ");
    lcd.setCursor(10,1);
    lcd.print(out);
  }
}