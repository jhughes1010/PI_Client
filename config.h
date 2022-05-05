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
byte txPin = 8;          // Assign TX output
byte mainSamplePin = 9;  // Assign main sample pulse
byte efeSamplePin = 10;  // Assign EFE sample pulse
byte delayPin = A0;      // Assign delay pot


//=================================
// Program variables
//=================================
word txOnCount  = 2;                           // TX pulse
word mainDelayCount  = 2;                      // Main sample delay
word mainSampleCount  = 2;                      // Main sample pulse
word efeDelayCount  = 2;                       // EFE sample delay
word efeSampleCount  = 2;                       // EFE sample pulse
word txPeriodCount  = 15000;                     // TX period
word delayVal = 0;                               // Delay pot value
bool readDelayPot = false;                       // Delay pot read (true or false)
byte readDelayCounter = 0;                       // Read delay pot counter
byte readDelayLimit = 100;
byte intState = 0;                               // Interrupt state machine
bool boost = false;
