unsigned long previousMillis = 0, previousMillis2 = 0, previousMillis3 = 0, previousMillis5 = 0 , previousMicrosf = 0, previousMicrosr = 0, previousMicrosl = 0 ; 
bool ledState = false, trigState = false, stopState= false, fireState = false, forwardState = true, backwardState = false, rightState = false, leftState = false;
byte US_state = 0, turn_left = 0, turn_right = 0;
void setup() {
  DDRD = B11111011, DDRB = B00101111, DDRC = B00011000, attachInterrupt(digitalPinToInterrupt(2), fan, RISING);
}
void loop() {
  unsigned long currentMillis = millis(), currentMicros = micros(), x;
  if(PINB & B00010000){
    if ((unsigned long)(currentMillis - previousMillis2) >= 1000) 
    { ledState = !ledState, PORTC ^= B00010000 * ledState, previousMillis2 = millis(); }
    if(!stopState){
     if (currentMillis - previousMillis >= 10)  {
       forward_check(x, currentMicros), right_check(x, currentMicros), left_check(x, currentMicros), backward_check(x, currentMicros), previousMillis = millis();}}}
  if (((unsigned long)(currentMillis - previousMillis5) >= 500)) { if(stopState){ stop(),fireState = true;}
      previousMillis5 = millis(); }
  if ((unsigned long)(currentMillis - previousMillis3) >= 15) { if(fireState) {PORTB = B00001010, PORTB =  B00000110, PORTB = B00000101, PORTB = B00001001;}
      previousMillis3 = millis(); }
  if(!(PIND & B00000100)) {fireState = false, stopState = false; }     
}
void forward_check(unsigned long x, unsigned long currentMillis) {
  if ( forwardState) {
    x = UltraSonic(currentMillis,previousMicrosf, 0);
    if (x != 255)
      if (x > 20){ PORTD |= B10101010, PORTD &= B10101110, PORTB &= B11011111, PORTD |= B01100010, PORTD &= B01100110, PORTB |= B00100000;
        PORTD |= B01010001, PORTD &= B01010101, PORTB |= B00100000, PORTD |= B10011001, PORTD &= B10011101, PORTB &= B11011111 ;
      } else { forwardState = false, rightState = true;}}}
void backward_check(unsigned long x, unsigned long currentMillis){ 
  if ( backwardState) { PORTD |= B10011001, PORTD &= B10011101, PORTB &= B11011111, PORTD |= B01010001, PORTD &= B01010101, PORTB |= B00100000;
    PORTD |= B01100010, PORTD &= B01100110, PORTB |= B00100000, PORTD |= B10101010, PORTD &= B10101110, PORTB &= B11011111;
    rightState = true, backwardState = false; }}
void left_check(unsigned long x, unsigned long currentMillis) {
 if ( leftState) {
    x = UltraSonic(currentMillis, previousMicrosl, 1);
    if (x != 255)
      if (x > 20){ PORTD |= B00001010, PORTD &= B00001110, PORTB &= B11011111, PORTD |= B00000010, PORTD &= B00000110, PORTB |= B00100000; 
        PORTD |= B00000001, PORTD &= B00000101, PORTB |= B00100000, PORTD |= B00001001, PORTD &= B00001101, PORTB &= B11011111, turn_left++;
        if(turn_left == 360 / 4) {forwardState = true, leftState = false;} } else { leftState = false, backwardState = true; }}}
void right_check(unsigned long x, unsigned long currentMillis) { 
  if ( rightState) { x = UltraSonic(currentMillis, previousMicrosr, 2);
    if (x != 255)
      if (x > 20) { PORTD |= B10101010, PORTD &= B10101110, PORTB &= B11011111, PORTD |= B01100000, PORTD &= B01101111; 
                    PORTD |= B01010000, PORTD &= B01011111, PORTD |= B10010000, PORTD &= B10011111, turn_right++;
                    if(turn_right == 360 / 4) {rightState = false, forwardState = true;}
      } else { leftState = true, rightState = false; }}}
void stop(){ PORTD &= B00000100, PORTB &= B11011111; }
void fan() { stopState = true;}
unsigned char UltraSonic(unsigned long currentMicros, unsigned long previousMicros, byte pin) {
  if (US_state == 0) {
    PORTC &= B11110111; US_state = 1;
    return 255;
  } else if (US_state == 1 && (currentMicros - previousMicros ) >= 15 ) {
    previousMillis = currentMicros, PORTC ^= B00001000, US_state = 2;
    return 255;
  } else if (US_state == 2 && (currentMicros - previousMicros ) >= 25) {
    previousMicros = currentMicros, PORTC ^= B00001000, US_state = 0;
    int counter = 0, duration = 0;
    unsigned long time;
    while (  --counter != 0  ){
      if (PINC & (B00000001 << pin)) { time = micros();
      break;}}
    while ( --counter != 0 ){
      if ((PINC & (B00000001 << pin)) == 0 ){ duration = micros() - time;
      break;}}
    return (( duration / 2) * 0.0344);}}
