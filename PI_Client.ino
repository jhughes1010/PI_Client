
#include "config.h"
#include <Wire.h>

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

void loop() {
  // put your main code here, to run repeatedly:

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

  while (Wire.available())
  {
    int x = Wire.read();
    debug(x);
  }

  txOnCount = in[0];
  txOnCount |= in[1] << 8;

  mainDelayCount = in[2];
  mainDelayCount |= in[3] << 8;

  mainSampleCount = in[4];
  mainSampleCount |= in[5] << 8;

  efeDelayCount = in[6];
  efeDelayCount |= in[7] << 8;

  efeSampleCount = in[8];
  efeSampleCount |= in[9] << 8;

  txPeriodCount = in[10];
  txPeriodCount |= in[11] << 8;
}
