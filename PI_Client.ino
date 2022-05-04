void setup()
{
  Serial.begin(115200);
  Serial.println(NAME);

  setIO();
  setInterruptDetails();
  debugln("setup completed");

#ifdef LCD
  LCDInit();
  LCDTitle();
  createCustomChar();
  //checkBattery();
#endif
}

void loop() {
  // put your main code here, to run repeatedly:

}
