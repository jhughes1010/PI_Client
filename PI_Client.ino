
#include "config.h"
#include <Wire.h>

static bool LED = LOW;

void setup()
{
  Serial.begin(115200);
  Serial.println(NAME);
  Serial.println(VERSION);

  setIO();
  setDefaultTiming();
  calcCNT1();
  setInterruptDetails();
  Wire.begin(8);
  //Wire.end();
  Wire.onReceive(receiveEvent);
  debugln("setup completed");
  if (digitalRead(boostPin) == LOW)
  {
    setDefaultMinTiming();
    calcCNT1();
    debugln("Minimum timing enabled");
  }
}

void loop()
{
  if (readDelayPot == true)
  {
    //readBoostSwitch();
    DelayPotRead();
    readDelayPot = false;
    calcCNT1();
    outputCNT();
    debug("TX loop: ");
    debugln(countUp.txWidthCount);
    digitalWrite(LED_BUILTIN, LED);
  }
}
