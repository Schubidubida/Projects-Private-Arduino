
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

//*********************************************************************************
//* PATTERNS BUILT WITH
//* https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
//*********************************************************************************

// TUNABLES

#define	LIMIT_NEAR_CM	40
#define LIMIT_FAR_CM	50

// PINS FOR RANGING

#define RANGE_TRIGGER_PIN	A5 // ATTACH TO PIN TRIG OF HC-SR04
#define RANGE_ECHO_PIN		A4 // ATTACH TO PIN ECHO OF HC-SR04

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

const byte	mayRowPins[] = { LED_ROW_1, LED_ROW_2, LED_ROW_3, LED_ROW_4, LED_ROW_5, LED_ROW_6, LED_ROW_7, LED_ROW_8 };
const byte	mayColPins[] = { LED_COL_1, LED_COL_2, LED_COL_3, LED_COL_4, LED_COL_5, LED_COL_6, LED_COL_7, LED_COL_8 };

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

const byte *	mpActiveSymbol;					// POINTS TO ONE OF THE BYTE ARRAYS WITH SYMBOLS 
long			mlTicks;

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
		
  	pinMode (RANGE_TRIGGER_PIN, OUTPUT);	// TRIGGER IS AN OUTPUT
  	pinMode (RANGE_ECHO_PIN, INPUT);		// ECHO IS AN INPUT
  	
  	// INIT GLOBAL VARIABLES
  	
  	mpActiveSymbol = OFF;
  	mlTicks	 	   = 0;
}

//*********************************************************************************
//* CONTINUOUS LOOP
//*********************************************************************************

void loop() 
{
	// DISPATCH WHAT TO DO
	
    mlTicks += 1;

	// SHOW SYMBOL
	
    if (mlTicks < 25) {
        DrawSymbol (mpActiveSymbol);
        return;
    }
    
    // DISPLAY OFF
    
    if (mlTicks < 50) {
        DrawSymbol (OFF);
        return;
    } 
    
    // BACK TO THE START
    
    mlTicks = 0;

    // MEASURE DISTANCE

	long	lRangeDurationMicroSeconds;	// VARIABLE FOR THE DURATION OF SOUND WAVE TRAVEL
	int		nRangeDistanceCM;			// VARIABLE FOR THE DISTANCE MEASUREMENT
    
	// CLEARS THE RANGE_TRIGGER_PIN CONDITION

	digitalWrite (RANGE_TRIGGER_PIN, LOW);
	delayMicroseconds (2);

	// SETS THE RANGE_TRIGGER_PIN HIGH (ACTIVE) FOR 10 MICROSECONDS

	digitalWrite (RANGE_TRIGGER_PIN, HIGH);
	delayMicroseconds (10);
	digitalWrite (RANGE_TRIGGER_PIN, LOW);

	// READS THE RANGE_ECHO_PIN, RETURNS THE SOUND WAVE TRAVEL TIME IN MICROSECONDS

	lRangeDurationMicroSeconds = pulseIn (RANGE_ECHO_PIN, HIGH, 15000);

	// CALCULATING THE DISTANCE

	nRangeDistanceCM = float (lRangeDurationMicroSeconds) * 0.034 / 2.0; // Speed of sound wave divided by 2 (go and back)

	// DISPLAYS THE DISTANCE ON THE SERIAL MONITOR

	Serial.print ("Distance: ");
	Serial.print (nRangeDistanceCM);
	Serial.println (" cm");

	// NOTHING DETECTED AT ALL ?
		
	if (nRangeDistanceCM == 0) {
		mpActiveSymbol = OFF;
		return;
	}
	
	// TOO NEAR ?	
	
	if (nRangeDistanceCM < LIMIT_NEAR_CM) {
		mpActiveSymbol = DOWN_ARROW;
		return;
	}
	
	// TOO FAR AWAY ?
	
	if (nRangeDistanceCM > LIMIT_FAR_CM) {
		mpActiveSymbol = UP_ARROW;
		return;
	}               
	
	// JUST RIGHT !
	
	mpActiveSymbol = SMILE;
}

//*********************************************************************************
//* DRAW ONE SYMBOL
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
			
			delayMicroseconds (100);       
			digitalWrite (mayColPins[yCol], HIGH);  // DISABLE COLUMN
		}                                    
		
		digitalWrite (mayRowPins[yRow], LOW);  		// DISABLE ROW
	}
}
