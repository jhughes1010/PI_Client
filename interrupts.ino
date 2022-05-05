//=================================
//setInterruptDetails()
//=================================
void setInterruptDetails(void)
{
  noInterrupts();                   // Disable interrupts
  TCCR1A = 0;                       // Initialize Timer1 registers
  TCCR1B = 0;
  TIMSK0 = 0;                       // Clear Timer0 mask register to eliminate jitter
  TIMSK2 = 0;
  TCNT1 = txOnCount;                // Load Timer1 with TX-on count
  TCCR1B |= (1 << CS10);            // No prescaling for Timer1
  TIMSK1 |= (1 << TOIE1);           // Enable Timer1 overflow interrupt
  interrupts();                     // Enable interrupts
}

//=================================
//ISR for timer events
//=================================
ISR(TIMER1_OVF_vect)
{
  switch (intState) {
    case 0:
      TCNT1 = txOnCount;                           // Load Timer1 with TX-ON count
      PORTB |= (1 << 0);                           // TX coil on
      break;

    case 1:
      TCNT1 = mainDelayCount;                      // Load Timer1 with main sample delay count
      //TCNT1 = 0xfffd;
      PORTB &= ~(1 << 0);                          // TX coil off
      break;

    case 2:
      PORTB &= ~(1 << 1);                          // Sample pulse enable
      TCNT1 = mainSampleCount;                     // Load Timer1 with main sample pulse count
      break;

    case 3:
      TCNT1 = efeDelayCount;                       // Load Timer1 with EFE sample delay count
      PORTB |= (1 << 1);                           // Sample pulse disable
      break;

    case 4:
      TCNT1 = efeSampleCount;                      // Load Timer1 with EFE sample pulse count
      PORTB &= ~(1 << 2);                          // EFE pulse enable
      break;

    case 5:
      TCNT1 = txPeriodCount;                       // Load Timer1 with TX period count
      PORTB |= (1 << 2);                           // EFE pulse disable

      //update counter to allow for periodic reading of delay pot
      if (readDelayPot == false)
      {
        readDelayCounter++;                        // Increment read delay counter
        readDelayCounter = readDelayCounter % readDelayLimit;
        if (!readDelayCounter)                      // Check if read delay counter is zero
        {
          readDelayPot = true;
        }
      }
      break;

    default:
      TCNT1 = 0xfffd;
      intState = -1;
      break;
  }

  //Increment to next state machine value but always ensure intState is between 0 - 5
  intState ++;
  intState = intState % 6;
}
/*
  void intTimerOff(void)
  {
  noInterrupts();                   // Disable interrupts
  //TCCR1A = 0;                       // Initialize Timer1 registers
  //TCCR1B = 0;
  //TIMSK1 = 0;                       // Clear Timer0 mask register to eliminate jitter
  //TIMSK2 = 0;
  //TCNT1 = txOnCount;                // Load Timer1 with TX-on count
  //TCCR1B |= (1 << CS10);            // No prescaling for Timer1
  TIMSK1 &= ~(1 << TOIE1);           // Enable Timer1 overflow interrupt
  interrupts();                     // Enable interrupts
  }


  void intTimerOn(void)
  {
  noInterrupts();                   // Disable interrupts
  TIMSK1 |= (1 << TOIE1);           // Enable Timer1 overflow interrupt
  intState = 6;
  interrupts();                     // Enable interrupts
  }
*/
