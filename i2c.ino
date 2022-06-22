void receiveEvent(int howMany) {
  byte in[12];
  int position = 0;

  LED = !LED;

  while (Wire.available())
  {
    position = position % 12;
    in[position] = Wire.read();
    debug("\nStream:");
    debug(in[position]);
    debug(" ");
    position++;
  }
  debug("\n\n\n");

  //Data is expected in LB/HB ordering
  cycle.txWidthCount = in[0];
  cycle.txWidthCount |= (word)in[1] << 8;
  debug("TX");
  debugln(cycle.txWidthCount);

  cycle.sampleDelayCount = in[2];
  cycle.sampleDelayCount |= in[3] << 8;

  cycle.sampleWidthCount = in[4];
  cycle.sampleWidthCount |= in[5] << 8;

  cycle.efeDelayCount = in[6];
  cycle.efeDelayCount |= in[7] << 8;
  
  cycle.efeWidthCount = in[8];
  cycle.efeWidthCount |= in[9] << 8;

  cycle.aquirePeriod = in[10];
  cycle.aquirePeriod |= in[11] << 8;
}
