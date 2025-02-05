/*
 * used https://github.com/avishorp/TM1637 librarry
 * chrometer by Nicu FLORICA (niq_ro)
 * v.0 - initial version (minutes : seconds)
 * v.1 - automatic changes to hours : minutes when hours > 0
 * v.2 - return to v.0 + show short time in seconds and hundredths
 * v.3 - added a trigger (button to gnd)
*/

//#include <Arduino.h>
#include <TM1637Display.h>  // https://github.com/avishorp/TM1637

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

#define buton 4

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   500

TM1637Display display(CLK, DIO);

int k = 1;
unsigned long timp0, timp;
int s, ss;

byte stare = 0;

void setup()
{
  display.setBrightness(2); // 0...15
//  timp0 = millis()/10;  // hundredths
  pinMode(buton, INPUT);
  digitalWrite(buton, HIGH);
  display.showNumberDecEx(100*s+ss, (0x80 >> k%2), true); 
}

void loop()
{ 

if ((stare == 0) and (digitalRead(buton) == LOW))
  {
   timp0 = millis()/10;  // hundredths
   stare = 1; 
  }
if (stare == 1)
  { 
  timp = millis()/10 - timp0;
      s = (timp)/100;
      ss = (timp)%100;
      display.showNumberDecEx(100*s+ss, (0x80 >> k%2), true); 
 //  k++;
   }
if ((stare == 1) and (digitalRead(buton) == HIGH))
  {
   delay(2000);  // debounce time
   stare = 0; 
  }
delay(1);    
//delay(TEST_DELAY);
}  // end main loop
