
//*********************************************************************************
//* PATTERNS BUILD WITH
//* https://www.riyas.org/2013/12/online-led-matrix-font-generator-with.html
//*********************************************************************************

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

#define	LimitNearCM		40
#define LimitFarCM		50

//* PINS FOR RANGING

#define echoPin A4 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin A5 //attach pin D3 Arduino to pin Trig of HC-SR04

// GLOBAL VARIABLES

long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
 
byte * Symbol; 

//update from SAnwandter

#define ROW_1 2
#define ROW_2 3
#define ROW_3 4
#define ROW_4 5
#define ROW_5 6
#define ROW_6 7
#define ROW_7 8
#define ROW_8 9

#define COL_1 10
#define COL_2 11
#define COL_3 12
#define COL_4 13
#define COL_5 A0
#define COL_6 A1
#define COL_7 A2  
#define COL_8 A3

const byte rows[] = {
    ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7, ROW_8
};
const byte col[] = {
  COL_1,COL_2, COL_3, COL_4, COL_5, COL_6, COL_7, COL_8
};

// The display buffer
// It's prefilled with a smiling face (1 = ON, 0 = OFF)
byte OFF[] = {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000};
byte ALL[] = {B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111,B11111111};
byte EX[] = {B00000000,B00010000,B00010000,B00010000,B00010000,B00000000,B00010000,B00000000};
byte A[] = {  B00000000,B00111100,B01100110,B01100110,B01111110,B01100110,B01100110,B01100110};
byte B[] = {B01111000,B01001000,B01001000,B01110000,B01001000,B01000100,B01000100,B01111100};
byte C[] = {B00000000,B00011110,B00100000,B01000000,B01000000,B01000000,B00100000,B00011110};
byte D[] = {B00000000,B00111000,B00100100,B00100010,B00100010,B00100100,B00111000,B00000000};
byte E[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
byte F[] = {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00100000,B00000000};
byte G[] = {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
byte H[] = {B00000000,B00100100,B00100100,B00111100,B00100100,B00100100,B00100100,B00000000};
byte I[] = {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
byte J[] = {B00000000,B00011100,B00001000,B00001000,B00001000,B00101000,B00111000,B00000000};
byte K[] = {B00000000,B00100100,B00101000,B00110000,B00101000,B00100100,B00100100,B00000000};
byte L[] = {B00000000,B00100000,B00100000,B00100000,B00100000,B00100000,B00111100,B00000000};
byte M[] = {B00000000,B00000000,B01000100,B10101010,B10010010,B10000010,B10000010,B00000000};
byte N[] = {B00000000,B00100010,B00110010,B00101010,B00100110,B00100010,B00000000,B00000000};
byte O[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
byte P[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100000,B00100000,B00000000};
byte Q[] = {B00000000,B00111100,B01000010,B01000010,B01000010,B01000110,B00111110,B00000001};
byte R[] = {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
byte S[] = {B00000000,B00111100,B00100000,B00111100,B00000100,B00000100,B00111100,B00000000};
byte T[] = {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte U[] = {B00000000,B01000010,B01000010,B01000010,B01000010,B00100100,B00011000,B00000000};
byte V[] = {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
byte W[] = {B00000000,B10000010,B10010010,B01010100,B01010100,B00101000,B00000000,B00000000};
byte X[] = {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
byte Y[] = {B00000000,B01000100,B00101000,B00010000,B00010000,B00010000,B00010000,B00000000};
byte Z[] = {B00000000,B00111100,B00000100,B00001000,B00010000,B00100000,B00111100,B00000000};

//byte UP1[] = {B10011001, B00100100, B01000010, B10011001, B00100100, B01000010, B10011001, B00100100};
//byte UP2[] = {B00100100, B01000010, B10011001, B00100100, B01000010, B10011001, B00100100, B01000010};
//byte UP3[] = {B01000010, B10011001, B00100100, B01000010, B10011001, B00100100, B01000010, B10011001};

byte UP1[] = {B00011000, B00100100, B01000010, B10000001, B00011000, B00100100, B01000010, B10000001};
byte UP2[] = {B00100100, B01000010, B10000001, B00011000, B00100100, B01000010, B10000001, B00011000};
byte UP3[] = {B01000010, B10000001, B00011000, B00100100, B01000010, B10000001, B00011000, B00100100};
byte UP4[] = {B10000001, B00011000, B00100100, B01000010, B10000001, B00011000, B00100100, B01000010};

byte UP_ARROW[]   = {B00011000, B00111100, B01111110, B11011011, B10011001, B00011000, B00011000, B00011000};
byte DOWN_ARROW[] = {B00011000, B00011000, B00011000, B10011001, B11011011, B01111110, B00111100, B00011000};
byte STOP[]       = {B00000000, B00000000, B00000000, B11111111, B11111111, B00000000, B00000000, B00000000};

float timeCount = 0;

void setup() 
{
    // Open serial port

    Serial.begin(115200);
    
    // Set all used pins to OUTPUT
    // This is very important! If the pins are set to input
    // the display will be very dim.

    for (byte i = 2; i <= 13; i++) pinMode(i, OUTPUT);
    pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	
  	pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  	pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT	
  	
  	Symbol = OFF;
}

void loop() 
{

    // This could be rewritten to not use a delay, which would make it appear brighter

    timeCount += 1;

	// SHOW SYMBOL
	
    if(timeCount <  25) {
        drawScreen (Symbol);
        return;
    }
    
    // OFF
    
    if (timeCount <  50) {
        drawScreen (OFF);
        return;
    } 
    
    // back to the start
    
    timeCount = 0;

    // MEASURE DISTANCE
    
	// Clears the trigPin condition

	digitalWrite (trigPin, LOW);
	delayMicroseconds(2);

	// Sets the trigPin HIGH (ACTIVE) for 10 microseconds

	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	// Reads the echoPin, returns the sound wave travel time in microseconds

	duration = pulseIn (echoPin, HIGH, 15000);

	// Calculating the distance

	distance = float (duration) * 0.034 / 2.0; // Speed of sound wave divided by 2 (go and back)

	// Displays the distance on the Serial Monitor

	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" cm");

	
	if (distance == 0) {
		Symbol = OFF;
		return;
	}	
	
	if (distance < LimitNearCM) {
		Symbol = DOWN_ARROW;
		return;
	}
	
	if (distance > LimitFarCM) {
		Symbol = UP_ARROW;
		return;
	}
	
	Symbol = STOP;
}

void  drawScreen(byte buffer2[])
{ 
	// Turn on each row in series

	for (byte i = 0; i < 8; i++)        // count next row
	{
		digitalWrite(rows[i], HIGH);    //initiate whole row
		for (byte a = 0; a < 8; a++)    // count next row
		{
			// if You set (~buffer2[i] >> a) then You will have positive
		
			digitalWrite(col[a], ((~ buffer2[i]) >> a) & 0x01); // initiate whole column
			
			delayMicroseconds(100);       // uncoment deley for diferent speed of display
			//delayMicroseconds(1000);
			//delay(10);
			//delay(100);
			
			digitalWrite(col[a], 1);      // reset whole column
		}
		digitalWrite(rows[i], LOW);     // reset whole row
		// otherwise last row will intersect with next row
	}
}
// 
  /* this is siplest resemplation how for loop is working with each row.
    digitalWrite(COL_1, (~b >> 0) & 0x01); // Get the 1st bit: 10000000
    digitalWrite(COL_2, (~b >> 1) & 0x01); // Get the 2nd bit: 01000000
    digitalWrite(COL_3, (~b >> 2) & 0x01); // Get the 3rd bit: 00100000
    digitalWrite(COL_4, (~b >> 3) & 0x01); // Get the 4th bit: 00010000
    digitalWrite(COL_5, (~b >> 4) & 0x01); // Get the 5th bit: 00001000
    digitalWrite(COL_6, (~b >> 5) & 0x01); // Get the 6th bit: 00000100
    digitalWrite(COL_7, (~b >> 6) & 0x01); // Get the 7th bit: 00000010
    digitalWrite(COL_8, (~b >> 7) & 0x01); // Get the 8th bit: 00000001
}*/


