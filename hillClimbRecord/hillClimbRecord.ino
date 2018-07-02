//RECORD
#include <Servo.h>            //include Libraries
#include <Wire.h>             
#include <LCD.h>        
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus for LCD

Servo gas;    // Servo Object instantiation
Servo brake;  //

int gasOn=    25; //
int gasOff=   30; //  Servo Angle calls
int brakeOn=  78; //
int brakeOff= 72; //

int gasBtn=   2;  //
int brakeBtn= 3;  //  Button Pin locations
int playBtn= 4;  //
int exitBtn=  5;  //

int brakeState= 0; //
int gasState=   0; //Flags for states of buttons
int exitState=  0; //
int playState= 0; //

int swap=  -4;  //Mode change counter

unsigned long startOfPress; //Beginning of button timer
long millisHeld;            //Result of button timer

void setup() 
{
  pinMode(brakeBtn, INPUT); //
  pinMode(gasBtn, INPUT);   // Computer pin type
  pinMode(exitBtn, INPUT);  //
  pinMode(playBtn, INPUT); //

  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // set cursor to 0,0 Print to the first line of LCD
  lcd.print("Hill Climb Robot"); 

  Serial.begin(9600);
  
  gas.attach(9);    // Computer pin attach to servo
  brake.attach(10); //
  
  brake.write(brakeOff); //Set home location for servos
  gas.write(gasOff);     //

  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print("Push play to begin");
  
  while(playState==0) //Prompt user to press a button to start
  {
    playState=digitalRead(playBtn);
    delay(5);
  }
}

void loop() 
{
  lcd.setCursor (0,1);        // go to start of 2nd line
  lcd.print("Swap Number:              ");
  delay(20);
  lcd.setCursor (13,1);        // go to result section of 2nd line
  lcd.print((swap+1));
  checkStates();
  if (brakeState==1) //Brake Pressed
  {
    gasState=0;
    brake.write(brakeOn);
    startOfPress=millis();
    while(brakeState==1)
    {
     delay(5);
     brakeState= digitalRead(brakeBtn);
    }
    brake.write (brakeOff);
    millisHeld=(millis() - startOfPress);
    Serial.print(swap);
    Serial.print("\t");
    Serial.print(millisHeld);
    Serial.println(",\t-1,");
    swap=swap+1;
  } 

  if (gasState==1) //Gas Pressed
  {
    brakeState=0;
    gas.write(gasOn);
    startOfPress=millis();
    while(gasState==1)
    {
     delay(5);
     gasState= digitalRead(gasBtn);
    }
    gas.write (gasOff);
    millisHeld=(millis() - startOfPress);
    Serial.print(swap);
    Serial.print("\t");
    Serial.print(millisHeld);
    Serial.println(",\t1,");
    swap=swap+1;
  } 
  
  startOfPress=millis();
  while(gasState==0 && brakeState==0)
  {
    gasState=   digitalRead(gasBtn);
    brakeState= digitalRead(brakeBtn);
    exitState=  digitalRead(exitBtn);
    if(exitState==1)
    {
      gasState=1;   //for exiting returning loop
      Serial.println("Program has stopped temporarily");
      lcd.setCursor (0,1);        // go to start of 2nd line
      lcd.print("Push play to bgin");
      while(playState==0)
      {
        playState=digitalRead(playBtn);;
        delay(5);
      }
    }
    delay(5);
  }
  millisHeld=(millis() - startOfPress);

  if(exitState!=1)
  {
    Serial.print(swap);
    Serial.print("\t");
    Serial.print(millisHeld);
    Serial.println(",\t0,");
    swap=swap+1;
  }
  else
  {
    swap=-4;
    exitState=0;
    Serial.println("\n");
  }
}

void checkStates()
{
  brakeState =  digitalRead(brakeBtn);
  gasState   =  digitalRead(gasBtn);
  exitState  =  digitalRead(exitBtn);
  playState =   digitalRead(playBtn);
}
