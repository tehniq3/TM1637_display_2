/*
 * used https://github.com/avishorp/TM1637 library
 * chrometer by Nicu FLORICA (niq_ro)
 * v.0 - initial version (minutes : seconds)
 * v.1 - automatic changes to hours : minutes when hours > 0
*/

//#include <Arduino.h>
#include <TM1637Display.h>  // https://github.com/avishorp/TM1637

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   500

TM1637Display display(CLK, DIO);

int k = 0;
unsigned long timp0, timp;
int h, m, s;


void setup()
{
  display.setBrightness(2); // 0...15
  timp0 = millis()/1000;
}

void loop()
{ 
      timp = millis()/1000 - timp0;
      h = timp/3600;
      m = (timp%3600)/60;
      s = (timp%3600)%60;
      if (h == 0)
       display.showNumberDecEx(100*m+s, (0x80 >> k%2), true); 
      else
       display.showNumberDecEx(100*h+m, (0x80 >> k%2), true); 
k++;
delay(TEST_DELAY);
}
