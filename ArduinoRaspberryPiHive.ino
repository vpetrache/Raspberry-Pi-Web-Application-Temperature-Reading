#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include "HX711.h"

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

HX711 scale(A1, A0);	


#define DHT21_PIN 10

dht DHT;


int buttonState1 = 0;
const int But2 = 11; 
 
int buttonState = 0; 
const int But1 = 12; 

byte termometru[8] = {B00100, B01010, B01010, B01110, B01110, B11111, B11111, B01110}; //chart for temperatura

byte picatura[8] = {B00100, B00100, B01010, B01010, B10001, B10001, B10001, B01110,}; //char for humidity

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); //lcd address
 
void setup()
{
	scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights;
	scale.tare();				        // reset the scale to 0
	lcd.begin(20,2);
	lcd.backlight();
	lcd.clear(); 
	lcd.createChar(1,termometru);
	lcd.createChar(2,picatura);
	pinMode(But1, INPUT);
	pinMode(But2, INPUT);
	Serial.begin(19200); 
 }

void display()
{
  lcd.setCursor(2,0); 
  lcd.print(scale.get_units(20),1);  //does an average of 20 readings from scale and displays on the lcd
  lcd.setCursor(12, 0);
  lcd.print("Kg");  
 
  lcd.setCursor(0, 1);
  lcd.write(1); 
  lcd.setCursor(2,1); 
  lcd.print(DHT.temperature, 1); 
  lcd.setCursor(6, 1);
  lcd.print(" ");
  lcd.setCursor(7, 1);
  lcd.print((char)223); 
  lcd.print("C"); 
   
  lcd.setCursor(10, 1);
  lcd.write(2); 
  lcd.setCursor(12, 1);
  lcd.print(DHT.humidity, 1); 
  lcd.setCursor(14, 1);
  lcd.print(" "); 
  lcd.setCursor(15,1);
  lcd.print("%"); 
 } 
 
void buton()
{
buttonState = digitalRead(But1);
     delay(10); 
    if (buttonState == HIGH) 
        { lcd.backlight(); }
        else {
        lcd.noBacklight(); 
        }}
		
void resetScale()
{
buttonState1 = digitalRead(But2);
     delay(10); 
    if (buttonState1 == HIGH) 
        {scale.tare();}
        else {
       
        }}

void loop() 
{
	int chk = DHT.read21(DHT21_PIN);
	display(); 
	resetScale();
	buton();
	
	Serial.print("T: ");
	Serial.println(DHT.temperature));
	Serial.print("H: ");
	Serial.println(DHT.humidity);
	Serial.print("W: ");
	Serial.println(scale.get_units(20),1);
  
}
