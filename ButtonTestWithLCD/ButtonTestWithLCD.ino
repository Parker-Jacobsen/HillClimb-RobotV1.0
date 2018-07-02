#include <Wire.h>

#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus for LCD
const int gasBtn = 2;
const int brakeBtn = 3;
const int startBtn = 4;
const int stopBtn = 5;

// variables will change:
int gasSt = 0;         // variable for reading the pushbutton status
int brakeSt = 0;         // variable for reading the pushbutton status
int startSt = 0;         // variable for reading the pushbutton status
int stopSt = 0;         // variable for reading the pushbutton status
void setup() 
{
  Serial.begin(9600);      // open the serial port at 9600 bps:    
  pinMode(gasBtn, INPUT);
  pinMode(brakeBtn, INPUT);
  pinMode(startBtn, INPUT);
  pinMode(stopBtn, INPUT);

  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // set cursor to 0,0 Print to the first line of LCD
  lcd.print("Hill Climb Robot"); 
}

void loop() 
{
  gasSt=digitalRead(gasBtn);
  brakeSt=digitalRead(brakeBtn);
  startSt=digitalRead(startBtn);
  stopSt=digitalRead(stopBtn);
  
  Serial.print(gasSt);
  Serial.print(brakeSt);
  Serial.print(startSt);
  Serial.println(stopSt);
  
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print("G:");
  lcd.setCursor (2,1);
  lcd.print(gasSt);
  
  lcd.setCursor (4,1);        // go to start of 2nd line
  lcd.print("B:");
  lcd.setCursor (6,1);
  lcd.print(brakeSt);

  lcd.setCursor (8,1);        // go to start of 2nd line
  lcd.print("S:");
  lcd.setCursor (10,1);
  lcd.print(startSt);

  lcd.setCursor (12,1);        // go to start of 2nd line
  lcd.print("s:");
  lcd.setCursor (14,1);
  lcd.print(stopSt);
  
  delay(200);
}
