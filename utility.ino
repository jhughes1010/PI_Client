void setDefaultTiming( void)
{
  cycle.txWidthCount = 752;
  cycle.sampleDelayCount = 241;
  cycle.sampleWidthCount = 752;
  cycle.efeDelayCount = 2654;
  cycle.efeWidthCount = 736;
  cycle.aquirePeriod = 15518;
}

void setDefaultMinTiming( void)
{
  cycle.txWidthCount = 1;
  cycle.sampleDelayCount = 1;
  cycle.sampleWidthCount = 1;
  cycle.efeDelayCount = 1;
  cycle.efeWidthCount = 1;
  cycle.aquirePeriod = 15518;
}

void calcCNT1( void)
{
  countUp.txWidthCount = maxCount - cycle.txWidthCount;
  debug("TX2");
  debugln(cycle.txWidthCount);
  countUp.sampleDelayCount =  maxCount - cycle.sampleDelayCount;
  countUp.sampleWidthCount =  maxCount - cycle.sampleWidthCount;
  countUp.efeDelayCount =  maxCount - cycle.efeDelayCount;
  countUp.efeWidthCount =  maxCount - cycle.efeWidthCount;
  countUp.aquirePeriod = maxCount - (cycle.aquirePeriod - (cycle.txWidthCount + cycle.sampleDelayCount + cycle.sampleWidthCount + cycle.efeDelayCount + cycle.efeWidthCount));
}

void setIO(void)
{
  pinMode(txPin, OUTPUT);
  pinMode(mainSamplePin, OUTPUT);
  pinMode(efeSamplePin, OUTPUT);
  pinMode(boostPin, INPUT_PULLUP);

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
  delayVal = analogRead(delayPin);
  cycle.sampleDelayCount = 0 + delayVal;
}

void outputCNT( void)
{
  debug("\n----------\nTX:");
  debugln(cycle.txWidthCount);
  debug("Sample Delay:");
  debugln(cycle.sampleDelayCount);
  debug("Sample Width:");
  debugln(cycle.sampleWidthCount);
  debug("EFE Delay:");
  debugln(cycle.efeDelayCount);
  debug("EFE Width:");
  debugln(cycle.efeWidthCount);
  debug("Aquire Period:");
  debugln(cycle.aquirePeriod);
}



void readBoostSwitch (void)
{
  static word priorCount = cycle.txWidthCount;
  if (digitalRead(boostPin) == HIGH)
  {
    cycle.txWidthCount = priorCount;
  }
  else
  {
    cycle.txWidthCount = BOOSTPOWERCOUNT;
  }
  //debugln(cycle.txWidthCount);
}
