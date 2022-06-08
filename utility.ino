void setDefaultTiming( void)
{
  cycle.txWidthCount = 793;
  cycle.sampleDelayCount = 160;
  cycle.sampleWidthCount = 300;
  cycle.efeDelayCount = 3209;
  cycle.efeWidthCount = 176;
  cycle.aquirePeriod = 15518;
}

void calcCNT1( void)
{
  countUp.txWidthCount = maxCount - cycle.txWidthCount;
  countUp.sampleDelayCount =  maxCount - cycle.sampleDelayCount;
  countUp.sampleWidthCount =  maxCount - cycle.sampleWidthCount;
  countUp.efeDelayCount =  maxCount - cycle.efeDelayCount;
  countUp.efeWidthCount =  maxCount - cycle.efeWidthCount;
  countUp.aquirePeriod = maxCount - (cycle.txWidthCount + cycle.sampleDelayCount + cycle.sampleWidthCount + cycle.efeDelayCount + cycle.efeWidthCount);
}

void setIO(void)
{
  pinMode(txPin, OUTPUT);
  pinMode(mainSamplePin, OUTPUT);
  pinMode(efeSamplePin, OUTPUT);
  pinMode(boostPin, INPUT);

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
  Serial.println(cycle.txWidthCount);
}
