/*Final version of PS/2 to USB adapter written by Chamath Colombage
  This sketch will not give any readable output on a serial monitor.
  Don't change the baud rate(9600) or Arduino will start doing random keypresses.*/
#include <PS2KeyAdvanced.h>

/* Keyboard constants  Change to suit your Arduino
   define pins used for data and clock from keyboard */
#define DATAPIN 3
#define IRQPIN  2
#define LED     13

uint16_t c;
byte buf[8] = {0};
int let = 0;
byte keym[8] = {0};
int tkey = 0;
bool dup = 0;
byte mod = 0;

PS2KeyAdvanced keyboard;

void setup() {
  pinMode(LED, OUTPUT);
  keyboard.begin( DATAPIN, IRQPIN );
  keyboard.setNoRepeat(1);
  Serial.begin(9600);       // DON'T CHANGE TO SOMETHING ELSE !!!!
  intest(2);
}

void loop() {
  if ( keyboard.available( ) ){
    c = keyboard.read( );
    let = (c & 0xFF); //ps2_scancode
    tkey = 0; //hid_scancode
      if (!(c & PS2_BREAK)){ //if a key pressed

       //modifier key make
        if (let == PS2_KEY_L_CTRL)    mod |= (1 << 0); //L_CTRL
        if (let == PS2_KEY_L_SHIFT)   mod |= (1 << 1); //L_SHIFT
        if (let == PS2_KEY_L_ALT)     mod |= (1 << 2); //L_ALT
        if (let == PS2_KEY_L_GUI)     mod |= (1 << 3); //L_GUI
        if (let == PS2_KEY_R_CTRL)    mod |= (1 << 4); //R_CTRL
        if (let == PS2_KEY_R_SHIFT)   mod |= (1 << 5); //R_SHIFT
        if (let == PS2_KEY_R_ALT)     mod |= (1 << 6); //R_ALT
        if (let == PS2_KEY_R_GUI)     mod |= (1 << 7); //R_GUI

        //main block 
          if (let >= 0x61 && let <= 0x6C) tkey = (let - 39); //F1-F12               
          if (let >= 0x41 && let <= 0x5A) tkey = (let - 61); //letter
          if (let == 0x40) tkey =53; //`~
          if (let >= 0x31 && let <= 0x39) tkey = (let - 19); //1-9
          if (let == 0x30) tkey =39; //0
          if (let == 0x1B) tkey =41; //ESC
          if (let == 0x1C) tkey =42; //BCKSP
          if (let == 0x1D) tkey =43; //TAB
          if (let == 0x1E) tkey =40; //ENTER
          if (let == 0x1F) tkey =44; //SPACE
        
          if (let == 0x3A) tkey =52; //apos
          if (let == 0x3B) tkey =54; //comma
          if (let == 0x3C) tkey =45; //minus
          if (let == 0x3D) tkey =55; //dot
          if (let == 0x3E) tkey =56; //div
          if (let == 0x5B) tkey =51; //semi
          if (let == 0x5C) tkey =49; //backslash
          if (let == 0x5D) tkey =47; //[
          if (let == 0x5E) tkey =48; //]
          if (let == 0x5F) tkey =46; //equal

        //middle block
          if (let == 0x10) tkey =154; //sysreq
          if (let == 0x11) tkey =74; //home
          if (let == 0x12) tkey =77; //end
          if (let == 0x13) tkey =75; //pgup
          if (let == 0x14) tkey =78; //pgdn
          if (let == 0x19) tkey =73; //insert
          if (let == 0x1A) tkey =76; //del
          if (let == 0x04) tkey =70; //prtscrn
          if (let == 0x05) tkey =72; //pause
        //ditrectional
          if (let == 0x15) tkey =80; //left
          if (let == 0x16) tkey =79; //right  
          if (let == 0x17) tkey =82; //up
          if (let == 0x18) tkey =81; //down
          if (let == 0x0E) tkey =118; //menu

        //keypad
          if (let == 0x20) tkey =98; //kp0
          if (let >= 0x21 && let <= 0x29) tkey = (let + 56); //kp1-9
          if (let == 0x2A) tkey =99; //kpdot
          if (let == 0x2B) tkey =88; //kpent
          if (let == 0x2C) tkey =87; //kpplus
          if (let == 0x2D) tkey =86; //kpminus
          if (let == 0x2E) tkey =85; //kp*
          if (let == 0x2F) tkey =84; //kp/


        if (tkey != 0) { //non-mod key pressed

          for (int i = 2; i < 8; i++){
            dup = 0; //reset duplicate counter

            for (int n = 2; n < 8; n++){
              if (tkey == buf[n]) dup = 1; //found duplicate
            }
            
            if (dup == 1){ //if duplicate do nothing
              //break;
            }else if(buf[i] == 0){  //else check for empty
              buf[i] = tkey;  //set hid code
              keym[i]= let;   //memorize ps2 code
            }
          }

        }

        buf[0] = mod; //set modifier keys
        Serial.write(buf,8);

        //Toggle ON lock keys
        if (let == PS2_KEY_NUM)     singleUseKey(83);
        if (let == PS2_KEY_CAPS)    singleUseKey(57);
        if (let == PS2_KEY_SCROLL)  singleUseKey(71);

        //if (let == 0x12) releaseKey(); //kill Switch END for emergencies

      }else{  //if a key released
        
       //modifier key brake
        if (let == PS2_KEY_L_CTRL)    mod &= ~(1 << 0); //L_CTRL
        if (let == PS2_KEY_L_SHIFT)   mod &= ~(1 << 1); //L_SHIFT
        if (let == PS2_KEY_L_ALT)     mod &= ~(1 << 2); //L_ALT
        if (let == PS2_KEY_L_GUI)     mod &= ~(1 << 3); //L_GUI
        if (let == PS2_KEY_R_CTRL)    mod &= ~(1 << 4); //R_CTRL
        if (let == PS2_KEY_R_SHIFT)   mod &= ~(1 << 5); //R_SHIFT
        if (let == PS2_KEY_R_ALT)     mod &= ~(1 << 6); //R_ALT
        if (let == PS2_KEY_R_GUI)     mod &= ~(1 << 7); //R_GUI

        for (int i = 2; i < 8; i++){
            if (let == keym[i]){ //clear the released key
              buf[i] = 0;
              keym[i]= 0;
            }
          }

        buf[0] = mod; //set modifier keys
        Serial.write(buf, 8);
        
        //Toggle OFF lock keys
        if (let == PS2_KEY_NUM)     singleUseKey(83);
        if (let == PS2_KEY_CAPS)    singleUseKey(57);
        if (let == PS2_KEY_SCROLL)  singleUseKey(71);
      }

}else{
    //digitalWrite(LED, LOW);
  }
}

void releaseKey() { //Degub feature
    memset(buf, 0, sizeof(buf));
    Serial.write(buf,8); // Release key
  }

void singleUseKey(int key) { //Use to Toggle Lock Keys
    memset(buf, 0, sizeof(buf));
    buf[2]= key;
    Serial.write(buf,8); //Press signle key
    memset(buf, 0, sizeof(buf));
    Serial.write(buf,8); //Release Key
  }

void intest(int x){ //intialized indicator
    for (int y = 1; y <= x; y++){
      digitalWrite(LED, HIGH);
      delay(100);
      digitalWrite(LED, LOW);
      delay(300);
    }
  }
