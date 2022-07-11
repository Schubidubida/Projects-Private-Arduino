
//*********************************************************************************
//* LED LOGIC FROM HERE
//* https://create.arduino.cc/projecthub/SAnwandter1/programming-8x8-led-matrix-23475a
//*********************************************************************************

//*********************************************************************************
//* ULTRASONIC RANGING FROM HERE
//* https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6
//*
//* ---------------------------------------------------------------- 
//* Arduino Ultrasoninc Sensor HC-SR04
//* Re-writed by Arbi Abdul Jabbaar
//* Using Arduino IDE 1.8.7
//* Using HC-SR04 Module
//* Tested on 17 September 2019
//* ---------------------------------------------------------------- 
//*********************************************************************************
                   
#include <SPI.h>

//*********************************************************************************
//* PATTERNS BUILT WITH
//* https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
//*********************************************************************************

// TUNABLES

#define	LIMIT_NEAR_CM	28.0
#define LIMIT_FAR_CM	42.0               

#define DISTANCE_AVERAGE	16
#define DISTANCE_CHANNELS	2

#define DISTANCE_IDLE_EPSILON	2.0
#define DISTANCE_IDLE_COUNT		50000U

// PINS FOR RANGING

#define RANGE_TRIGGER_PIN_1	A5		// ATTACH TO PIN TRIG OF HC-SR04
#define RANGE_ECHO_PIN_1	A4		// ATTACH TO PIN ECHO OF HC-SR04

#define RANGE_TRIGGER_PIN_2	MISO	// ATTACH TO PIN TRIG OF HC-SR04
#define RANGE_ECHO_PIN_2	MOSI	// ATTACH TO PIN ECHO OF HC-SR04

// PINS FOR LED MATRIX

#define LED_ROW_1 2
#define LED_ROW_2 3
#define LED_ROW_3 4
#define LED_ROW_4 5
#define LED_ROW_5 6
#define LED_ROW_6 7
#define LED_ROW_7 8
#define LED_ROW_8 9

#define LED_COL_1 10
#define LED_COL_2 11
#define LED_COL_3 12
#define LED_COL_4 13
#define LED_COL_5 A0
#define LED_COL_6 A1
#define LED_COL_7 A2  
#define LED_COL_8 A3

// DATA TYPES

typedef enum {
	S_IDLE,			// NOTHING TO DO, READ RANGE ONCE A SECOND, WAKEUP ON VALID 
	S_SYMBOL,		// SHOW SYMBOL
	S_RANGING,		// DO RANGING WITH MAXIMUM SPEED, SHOW NO SYMBOL
} EState;

const byte	mayRowPins[] = { LED_ROW_1, LED_ROW_2, LED_ROW_3, LED_ROW_4, LED_ROW_5, LED_ROW_6, LED_ROW_7, LED_ROW_8 };
const byte	mayColPins[] = { LED_COL_1, LED_COL_2, LED_COL_3, LED_COL_4, LED_COL_5, LED_COL_6, LED_COL_7, LED_COL_8 };
const byte	mayRangeTriggerPin[DISTANCE_CHANNELS] = { RANGE_TRIGGER_PIN_1, RANGE_TRIGGER_PIN_2 };
const byte	mayRangeEchoPin[DISTANCE_CHANNELS] = { RANGE_ECHO_PIN_1, RANGE_ECHO_PIN_2 };

// LOTS OF SYMBOLS 

const byte OFF[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
const byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
const byte EX[]  = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};
const byte A[]   = {B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
const byte B[]   = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
const byte C[]   = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
const byte D[]   = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
const byte E[]   = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
const byte F[]   = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
const byte G[]   = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
const byte H[]   = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
const byte I[]   = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
const byte J[]   = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
const byte K[]   = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
const byte L[]   = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
const byte M[]   = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
const byte N[]   = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
const byte O[]   = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
const byte P[]   = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
const byte Q[]   = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
const byte R[]   = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
const byte S[]   = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
const byte T[]   = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
const byte U[]   = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
const byte V[]   = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
const byte W[]   = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
const byte X[]   = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
const byte Y[]   = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
const byte Z[]   = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

// UP CARETS FOR SCROLLING ILLUSION
                   
const byte UP_3_1[] = {B10011001, B00100100, B01000010, B10011001, B00100100, B01000010, B10011001, B00100100};
const byte UP_3_2[] = {B00100100, B01000010, B10011001, B00100100, B01000010, B10011001, B00100100, B01000010};
const byte UP_3_3[] = {B01000010, B10011001, B00100100, B01000010, B10011001, B00100100, B01000010, B10011001};

const byte UP_4_1[] = {B00011000, B00100100, B01000010, B10000001, B00011000, B00100100, B01000010, B10000001};
const byte UP_4_2[] = {B00100100, B01000010, B10000001, B00011000, B00100100, B01000010, B10000001, B00011000};
const byte UP_4_3[] = {B01000010, B10000001, B00011000, B00100100, B01000010, B10000001, B00011000, B00100100};
const byte UP_4_4[] = {B10000001, B00011000, B00100100, B01000010, B10000001, B00011000, B00100100, B01000010};

// UP, DOWN AND STOP

const byte UP_ARROW[]   = {B00011000, B00111100, B01111110, B11011011, B10011001, B00011000, B00011000, B00011000};
const byte DOWN_ARROW[] = {B00011000, B00011000, B00011000, B10011001, B11011011, B01111110, B00111100, B00011000};
const byte STOP[]       = {B00000000, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000};

const byte SMILE[]	    = {B01100110, B11100111, B11100111, B00000000, B10000001, B11000011, B01111110, B00111100};

// GLOBAL VARIABLES

const byte *	mpActiveSymbol;		// POINTS TO ONE OF THE BYTE ARRAYS WITH SYMBOLS 
EState			meState;
unsigned long	mdwNextTicks;		// NEXT TIME TO CHECK FOR STATE CHANGE
float			mnLastDistance;
unsigned int	mnDistanceNoChange;

//*********************************************************************************
//* ONE TIME INIT
//*********************************************************************************

void setup() 
{
    // OPEN SERIAL PORT

    Serial.begin (115200);
    
    // SET ALL USED LED PINS TO OUTPUT
    // THIS IS VERY IMPORTANT! IF THE PINS ARE SET TO INPUT
    // THE DISPLAY WILL BE VERY DIM.

    for (byte i = 2; i <= 13; i++) pinMode (i, OUTPUT);
    pinMode (A0, OUTPUT);
	pinMode (A1, OUTPUT);
	pinMode (A2, OUTPUT);
	pinMode (A3, OUTPUT);

	// SET RANGING PINS
		                    
	SPI.end ();		                    
  	pinMode (RANGE_TRIGGER_PIN_1, OUTPUT);	// TRIGGER IS AN OUTPUT
  	pinMode (RANGE_ECHO_PIN_1, INPUT);		// ECHO IS AN INPUT
  	pinMode (RANGE_TRIGGER_PIN_2, OUTPUT);	// TRIGGER IS AN OUTPUT
  	pinMode (RANGE_ECHO_PIN_2, INPUT);		// ECHO IS AN INPUT
  	
  	
  	// INIT GLOBAL VARIABLES
  	
  	mpActiveSymbol = OFF;
  	mnLastDistance = 0.0; 
  	mnDistanceNoChange = 0U;
  	meState        = S_IDLE;
	Serial.println ("--> IDLE");
  	mdwNextTicks   = millis () + 333UL;
}

//*********************************************************************************
//* CONTINUOUS LOOP
//*********************************************************************************

void loop() 
{    
	unsigned long	dwTicks;
	unsigned long	dwDelta;
	bool			bStateCheck;

	// TIME TO CHECK FOR STATE CHANGE ? 
		
    dwTicks = millis ();
    dwDelta = dwTicks - mdwNextTicks;						// THIS MAY WRAP AROUND
    bStateCheck = (dwDelta > 0 && dwDelta < 0x80000000);	// "POSITIVE" DELTA ?
	if (bStateCheck) mdwNextTicks += 333UL;
		            
	// DISPATCH CURRENT STATE
			            
	switch (meState) {
	
		// SWITCH TO ACTIVE (SYMBOL) STATE IF SOMETHING IS DETECTED
		
		case S_IDLE:
			if (bStateCheck) {
				if (ReadDistance ()) {
					meState = S_SYMBOL;
					Serial.println ("--> SYMBOL");
					break;
				}
			}
			break;				
			
		// SHOW SYMBOL
		
		case S_SYMBOL: {
			DrawSymbol (mpActiveSymbol);
			if (bStateCheck) {   
			    DrawSymbol (OFF);
				meState = S_RANGING;
				Serial.println ("--> RANGING");
			}
			break;
		}
			
		// MEASURE DISTANCE AND SET NEW SYMBOL AND STATE
		
		case S_RANGING: {
		
		    // MEASURE DISTANCE
		
			float	nRangeDistanceCM;			// VARIABLE FOR THE DISTANCE MEASUREMENT
		    
			nRangeDistanceCM = ReadDistance ();
		
			// NOTHING DETECTED AT ALL ?
				
			if (nRangeDistanceCM == 0.0) {
				mpActiveSymbol = OFF;
				meState = S_IDLE;     
				Serial.println ("--> IDLE");
				break;
			}
			
			// NEW STATE ?
			
			if (bStateCheck) {
				meState = S_SYMBOL;
				Serial.println ("--> SYMBOL");
			}
			
			// TOO NEAR ?	
			
			if (nRangeDistanceCM < LIMIT_NEAR_CM) {
				mpActiveSymbol = DOWN_ARROW;
				break;
			}
			
			// TOO FAR AWAY ?
			
			if (nRangeDistanceCM > LIMIT_FAR_CM) {
				mpActiveSymbol = UP_ARROW;
				break;
			}               
			
			// JUST RIGHT !
			
			mpActiveSymbol = SMILE;
			break;
		}
	}				
}

//*********************************************************************************
//* DRAW ONE SYMBOL. 
//* THIS WILL TAKE 8 x 8 x (150 + OVERHEAD) µs, WHICH IS 10328 µs ON MY ARDUINO UNO
//* OVERHEAD IS THEREFOR AROUND 11 µs 
//*********************************************************************************

void DrawSymbol (const byte aySymbolBits[])
{
	// LOOP OVER EACH ROW

	for (byte yRow = 0; yRow < 8; yRow++) {
		digitalWrite (mayRowPins[yRow], HIGH);		// ENABLE ROW
		
		// IF YOU REMOVE THE ~ BEFORE aySymbolBits YOU WILL HAVE AN INVERSE DISPLAY

		byte	ySymbolBits = ~ aySymbolBits[yRow];
		
		// LOOP OVER EACH COLUMN

		for (byte yCol = 0; yCol < 8; yCol++) {
			digitalWrite (mayColPins[yCol], (ySymbolBits >> yCol) & 0x01);	// ENABLE COLUMN
			
			// NOW ONE LED AT THE ROW/COL POS IS ILLUMINATED. WAIT A MOMENT, THEN SWITCH THE COLUMN OFF
			
			delayMicroseconds (150);       
			digitalWrite (mayColPins[yCol], HIGH);  // DISABLE COLUMN
		}                                    
		
		digitalWrite (mayRowPins[yRow], LOW);  		// DISABLE ROW
	}
}

//*********************************************************************************
//* READ DISTANCE AVERAGE OVER THE LAST MEASUREMENTS (IN CM)
//*********************************************************************************

float ReadDistance ()
{
	static float	anDistances[DISTANCE_CHANNELS][DISTANCE_AVERAGE];
	static int		nIndex = -1;
	
	int				nChannel;
	
	// FIRST TIME INIT
	
	if (nIndex < 0) {
		memset (anDistances, 0, sizeof (anDistances));
		nIndex = 0;
	}  
	
	// READ NEXT DISTANCE VALUE 
	                           
	nChannel = nIndex & 0x0001; 	                           
	anDistances[nChannel][nIndex >> 1] = ReadOneDistance (nChannel);
	if (++nIndex >= DISTANCE_AVERAGE * DISTANCE_CHANNELS) nIndex = 0;
	                 
	// AVERAGE BOTH CHANNELS

	float	anRangeDistanceCM[DISTANCE_CHANNELS];			
	float	nRangeDistanceCM;			
		
	for (int nC=0; nC<DISTANCE_CHANNELS; nC++) {		
		float	nSum   = 0.0;
		int		nCount = 0;
		
		for (int nI=0; nI<DISTANCE_AVERAGE; nI++) {
			if (anDistances[nC][nI]) {
				nSum += anDistances[nC][nI];
				nCount++;
			}
		}	

		if (nCount) {
			anRangeDistanceCM[nC] = nSum / float (nCount);
		} else {
			anRangeDistanceCM[nC] = 0.0;
		}
	}
	
	// USE NEARER (LOWER, BUT NOT ZERO) VALUE

	if (anRangeDistanceCM[0]) {
		if (anRangeDistanceCM[1]) {
			nRangeDistanceCM = anRangeDistanceCM[0] < anRangeDistanceCM[1] ? anRangeDistanceCM[0] : anRangeDistanceCM[1];
		} else {
			nRangeDistanceCM = anRangeDistanceCM[0];
		}
	} else {
		nRangeDistanceCM = anRangeDistanceCM[1];
	}
	
	// SAME AS LAST ONE ??
	
	if (abs (nRangeDistanceCM - mnLastDistance) < DISTANCE_IDLE_EPSILON) {
		if (mnDistanceNoChange > DISTANCE_IDLE_COUNT) {
			return 0.0;
		} else {
			mnDistanceNoChange++;
   		}
	} else {
		if (mnDistanceNoChange) {
			Serial.print ("Changing again  ");
			Serial.print (mnDistanceNoChange);
			Serial.print ("  "); 
			Serial.print (mnLastDistance); 
			Serial.print ("  "); 
			Serial.println (nRangeDistanceCM);
			mnDistanceNoChange = 0U;
		}
		mnLastDistance = nRangeDistanceCM;
	}

	return nRangeDistanceCM;	
}

//*********************************************************************************
//* READ ONE DISTANCE VALUE FROM SENSOR
//*********************************************************************************

float ReadOneDistance (int nChannel)
{
    // MEASURE DISTANCE

	long	lRangeDurationMicroSeconds;		// VARIABLE FOR THE DURATION OF SOUND WAVE TRAVEL
	float	nRangeDistanceCM;				// VARIABLE FOR THE DISTANCE MEASUREMENT
    
	// CLEARS THE RANGE_TRIGGER_PIN CONDITION

	digitalWrite (mayRangeTriggerPin[nChannel], LOW);
	while (digitalRead (mayRangeEchoPin[nChannel]) == HIGH);
	delayMicroseconds (5);

	// SETS THE RANGE_TRIGGER_PIN HIGH (ACTIVE) FOR 10 MICROSECONDS

	digitalWrite (mayRangeTriggerPin[nChannel], HIGH);
	delayMicroseconds (12);
	digitalWrite (mayRangeTriggerPin[nChannel], LOW);

	// READS THE RANGE_ECHO_PIN, RETURNS THE SOUND WAVE TRAVEL TIME IN MICROSECONDS

	lRangeDurationMicroSeconds = pulseIn (mayRangeEchoPin[nChannel], HIGH, 15000);

	// CALCULATE THE DISTANCE [WIKIPEDIA: "Die Schallgeschwindigkeit in trockener Luft von 20 °C beträgt 343,2 m/s (1236 km/h)"]

	nRangeDistanceCM = float (lRangeDurationMicroSeconds) * 0.03432 / 2.0; // SPEED OF SOUND WAVE DIVIDED BY 2 (GO AND BACK)
	
 	return nRangeDistanceCM;
}