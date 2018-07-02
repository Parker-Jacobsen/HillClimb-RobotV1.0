//PLAY
#include <Servo.h>            
#include <Wire.h>         
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C  lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus for LCD

Servo gas;    //Servo object instantiation
Servo brake;  //

int gasOn=    25; //
int gasOff=   30; //Servo angle key
int brakeOn=  78; //
int brakeOff= 72; //

int gasBtn=   2; //
int brakeBtn= 3; //Btn Pin locations
int playBtn=  4; //
int exitBtn=  5; //

int brakeState= 0; //
int gasState=   0; //Btn States
int exitState=  0; //
int playState=  0; //

int delayClock= 0;

int swaps[]=      {-4,-3,-2,-1, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};      //Directional Changes
int timer[]=      {417,135,573,125, 914,21000,271,200,66,  5009,416,838,131,2095,  910,792,427,1018,192, 757,145,7875};  //How long new direction is used
int directions[]= {0,1,0,1, 0,1,0,-1,0, 1,0,-1,0,1, 0,-1,0,1,0, -1,0,1 }; // -1= reverse, 0= halt, 1=forward Direction

void setup() 
{
  pinMode(brakeBtn, INPUT); //
  pinMode(gasBtn, INPUT);   //Pin modes
  pinMode(exitBtn, INPUT);  //
  pinMode(playBtn, INPUT);  //
  
  // activate LCD module
  lcd.begin (16,2); // for 16 x 2 LCD module
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);

  lcd.home (); // set cursor to 0,0 Print to the first line of LCD
  lcd.print("Hill Climb Robot"); 

  Serial.begin(9600);
  
  gas.attach(9);
  brake.attach(10);
  brake.write(brakeOff);
  gas.write(gasOff);

  if( sizeof(swaps) != sizeof(timer) || sizeof(swaps)!=sizeof(directions) )
  {
       Serial.println("ERROR Arrays Not Same Size");
  }
}

void loop() 
{
  while(playState==0) //#Used initially for testing, move to setup and ensure button release click to avoid ovveride interactions
  {
    delay(50);
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("Press Play to Start");
    playState=digitalRead(playBtn);
  }
  while(playState==1) //#Used initially for testing
  {
    delay(50);
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("                 ");
    playState=digitalRead(playBtn);
  }

  for (int i=0;i< 16;i++)
  {
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print(swaps[i]);
    lcd.print("   ");
    Serial.print(swaps[i]);
    Serial.print(" (");
    Serial.print(directions[i]);
    Serial.print(")");
    if (directions[i]== 1)
    {
        Serial.print(" GAS ");
        lcd.setCursor (3,1);        // go to start of 2nd line
        lcd.print(directions[i]);
        lcd.print("  ");
        gas.write(gasOn);
        Serial.print(timer[i]);
        //delay(timer[i]);      //Going to have to check for override button in here
        while(delayClock<timer[i])
        {
          delay(500);
          delayClock=500+delayClock;
          lcd.setCursor(7,1);
          lcd.print(delayClock);
          lcd.print("/");
          lcd.print(timer[i]);
        }
        delayClock=0;
        gas.write(gasOff);
    }
    if (directions[i]== 0)
    {
        Serial.print(" COAST ");
        lcd.setCursor (7,1);        // go to start of 2nd line
        lcd.print(directions[i]);
        lcd.print("  ");
        Serial.print(timer[i]);
        delay(timer[i]);      ////Going to have to check for override button in here
    }
    if (directions[i]== -1)
    {
        Serial.print(" BRAKE ");
        lcd.setCursor (7,1);        // go to start of 2nd line
        lcd.print(directions[i]);
        lcd.print("  ");
        brake.write(brakeOn);
        Serial.print(timer[i]);
        delay(timer[i]);      //Going to have to check for override button in here
        brake.write(brakeOff);
    }
    delay(1);
    Serial.println("\nNext Swap");
  }
    lcd.setCursor (0,1);        // go to start of 2nd line
    lcd.print("Exit Sequence here");
    delay(1000);
}



