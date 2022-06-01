
#include "config.h"
#include <Wire.h>

static bool LED = LOW;

void setup()
{
  Serial.begin(115200);
  Serial.println(NAME);

  setIO();
  setInterruptDetails();
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  debugln("setup completed");
}

void loop()
{
  if (readDelayPot == true)
  {
    DelayPotRead();
    readDelayPot = false;
  }
  digitalWrite(LED_BUILTIN, LED);
}

void setIO(void)
{
  pinMode(txPin, OUTPUT);           // Set TX pin to output mode
  pinMode(mainSamplePin, OUTPUT);   // Set main sample pin to output mode
  pinMode(efeSamplePin, OUTPUT);    // Set EFE sample pin to output mode

  //LED and A1 defined
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(A1, INPUT);
  //Pulse LED for 1000ms to indicate boot
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
}

void DelayPotRead( void)
{
  delayVal = analogRead(delayPin);                   // Read the delay pot
}

void receiveEvent(int howMany) {
  byte in[12];
  int position = 0;

  LED = !LED;

  while (Wire.available())
  {
    position = position % 12;
    in[position] = Wire.read();
    debug(in[position]);
    position++;
  }

  //Data is expected in LB/HB ordering
  txOnCount = in[0];
  txOnCount |= in[1] << 8;
  txOnCount = maxCount - txOnCount;

  mainDelayCount = in[2];
  mainDelayCount |= in[3] << 8;
  mainDelayCount = maxCount - mainDelayCount;

  mainSampleCount = in[4];
  mainSampleCount |= in[5] << 8;
  mainSampleCount = maxCount - mainSampleCount;

  efeDelayCount = in[6];
  efeDelayCount |= in[7] << 8;
  efeDelayCount = maxCount - efeDelayCount;

  efeSampleCount = in[8];
  efeSampleCount |= in[9] << 8;
  efeSampleCount = maxCount - efeSampleCount;

  txPeriodCount = in[10];
  txPeriodCount |= in[11] << 8;
  txPeriodCount = maxCount - txPeriodCount;
}
