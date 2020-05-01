unsigned long previousMillies = 0, previousMilliesMotor = 0, previousMilliesWait = 0; //some dely variables   
byte buffer = 0, currentPostion = 0, steps = 0, minimumRequest = 9, maxmumRequest = 0, keyPadButton = 9; //the request buffer(buffer) and current Postion of elevator(current Postion), motor steps(steps), minimum request(minimumRequest), maxmim request(minimumRequest), keypad pressed button (keyPadButton)
bool overload = false, forward = true, wait = false, move = false; //overload status (overload), if evlevator moves up the forward status will be true else it will be false and that means that it moves down(forward), wait status if a requested floor is reached (wait), move status if the elevator is moving (move)
const byte Output[1] = {8}, Input[8] = { 5, 6, 7, 1, 12, 11, 10, 9}; //Output is an array of pins attached to rows of the keypad (Output), Input is an array of pins attached to colomns of the keypad (Intput) 
void setup(){ DDRB  = 1, PORTB |= 62, DDRD = 25, PORTD |= 226, DDRC = 7,  attachInterrupt(digitalPinToInterrupt(2), overLoad, RISING);} // set the In/Out pins directions and attach Interrupt of overload to pin 2 
void loop(){
  if (millis() - previousMillies > 200 && !overload ){ //wait 200 millis to take input from the keypad or switches
      previousMillies = millis(),keyPadButton = keypad() ,buffer |= (B00000001 << keyPadButton); if(keyPadButton != 50)cFloor(keyPadButton); // take keypad input and store it in the buffer bits
      int button = analogRead(A3); // take analoge signal to know what switch is pressed
      checks(0, 400, 500, 1, button), checks(1, 300, 400, 2, button), checks(2, 200, 300, 4, button), checks(3, 150, 200, 8, button), checks(4, 120, 150, 16, button), checks(5, 100, 120, 32, button), checks(6, 70, 100, 64, button), checks(7, 0, 70, 128, button); } // determaine the exact switch
  if(overload) PORTD &= 231, PORTD |= 1; //if we have overload we stop the motor
  if (millis() - previousMilliesWait > 1000 && wait) wait = false; //if we reached a requested floor we wait 1000 millis
  if(!(PIND & 4)) overload = false, PORTD &= 254; //if overload is gone we turn off the led and continue or tasks
  PORTC &= (248 + currentPostion), PORTC |= currentPostion ; //update the seven segments displays
  if(buffer && !wait && !overload && move){
    if((millis() - previousMilliesMotor > 200)){  previousMilliesMotor = millis(); if(forward) {up(), steps++; if(steps == 8) {steps = 0, currentPostion++;}} else {down(), steps++; if(steps == 8) {currentPostion--, steps = 0;}}} //move up or down and update the postion 
      reach(1,0), reach(2,1), reach(4,2), reach(8,3), reach(16,4), reach(32,5), reach(64,6), reach(128,7);} //clear buffer bit if we reached the requested floor
 if(currentPostion == maxmumRequest){ if(buffer != 0) forward = false; else move = false;  maxmumRequest = 0;}// if we reached the maxmum request 
 if(currentPostion == minimumRequest){ if(buffer != 0) forward = true; else move = false; minimumRequest = 9;}// if we reached the minimum request
}
void   up(){PORTD &= 231, PORTD &= 239, PORTD |= 8, PORTD |= 16, PORTD |= 24, PORTD &= 247;} //motor up sequence
void down(){PORTD &= 247, PORTD |= 16, PORTD |= 24, PORTD &= 239, PORTD |= 8, PORTD &= 231;} //motor down sequence
void reach(byte bin, byte floor){ if(bin & buffer && currentPostion == floor) buffer &= (255 - bin), wait = true, previousMilliesWait = millis();} //clear bit if floor is reached
void checks(byte floor, int left, int right, byte value, int button){if( button > left && button < right) buffer |= value, cFloor(floor);} // check what switch of 8 switches is pressed
void cFloor(byte cP ){if(currentPostion == cP)return; if(!move && currentPostion < cP) forward = true; else if(!move) forward = false; move = true; if(currentPostion < cP && maxmumRequest < cP) maxmumRequest = cP; else if(currentPostion > cP && minimumRequest > cP) minimumRequest = cP;} //update minimum and max requests
void overLoad() { overload = true;} //overlaod inturrpt
byte keypad(){ static bool no_press_flag = 0; 
  for (byte x = 0; x < 8; x++){ // checks colums if we have a pressed buttons
    if ( x < 4 && !(PIND & (1 << (Input[x] % 8))) || x >= 4 && !(PINB & (1 << (Input[x] % 8)))) break;
    if (x == (8 - 1)) no_press_flag = 1;}
  if (no_press_flag == 1) { PORTB &= 254;
    for (byte c = 0; c < 8; c++) { if (c < 4 && (PIND & (1 << (Input[c] % 8))) || c >= 4 && (PINB & (1 << (Input[c] % 8)))) continue;
      else {  PORTB |= 1;
          if (c < 4 && (PIND & (1 << (Input[c] % 8))) || c >= 4 && (PINB & (1 << (Input[c] % 8)))) { no_press_flag = 0, PORTB &= 254;
            return  c;}}}} // we return the pressed button
  return 50;} // if no pressed button we return 50
