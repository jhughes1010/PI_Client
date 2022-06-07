//Configuration and compile settings
#define NAME "Arduino-PI Client"
#define VERSION "v1.0 - 2022"
//#define CALIBRATE_OFFSETS

#define DEBUG 1

#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

//=================================
//Defines
//=================================
#define MS * 1E-3
#define US * 1E-6
#define NS * 1E-9

//=================================
// Pin assignments
//=================================
byte txPin = 8;
byte mainSamplePin = 9;
byte efeSamplePin = 10;
byte delayPin = A0;
byte boostPin = 12;


//=================================
// Program variables
//=================================
word maxCount = 0xffff;

struct Cycle
{
  word txWidthCount;
  word sampleDelayCount;
  word sampleWidthCount;
  word efeDelayCount;
  word efeWidthCount;
  word aquirePeriod;
};

Cycle cycle;                                     // Counter values from HOST 
Cycle countUp;                                   // Final CNT1 values to be set for count up to overflow


word delayVal = 0;                               // Delay pot value
bool readDelayPot = false;                       // Delay pot read (true or false)
byte readDelayCounter = 0;                       // Read delay pot counter
byte readDelayLimit = 100;
byte intState = 0;                               // Interrupt state machine
bool boost = false;
