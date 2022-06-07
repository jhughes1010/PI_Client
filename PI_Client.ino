
#include "config.h"
#include <Wire.h>

static bool LED = LOW;

void setup()
{
  Serial.begin(115200);
  Serial.println(NAME);

  setIO();
  setDefaultTiming();
  calcCNT1();
  setInterruptDetails();
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  debugln("setup completed");
}

void loop()
{
  if (readDelayPot == true)
  {
    //Serial.println("RPOT");
    DelayPotRead();
    readDelayPot = false;
  }
  digitalWrite(LED_BUILTIN, LED);
}
