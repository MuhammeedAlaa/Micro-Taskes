int LED_arr[16]={B0111111,B0000110,B1011011,B1001111,B1100110,B1101101,B1111101,B0000111,B1111111,B1101111,B1110111,B1111100,B0111001,B1011110,B1111001,B1110001}; //LED pattern Array

void setup()
{
  DDRD = B01111111; //initializing portD from D0-D6 as output (LEDs are connected to portD in my design)
  //Initializing the 4 least significant pins of portB as input pullup to connect them to the switches
  DDRB = 0x10;
  PORTB = 0x0f;
}
void loop()
{ 
  //shifting the values on inverted values on pins 8-11 and oring them together to access the element in the LED array corresponding to the user input
  // to input a high value close the switch and low is by opening the switch
  PORTD = LED_arr[((!digitalRead(8))|((!digitalRead(9))<<1) | ((!digitalRead(10))<<2) | ((!digitalRead(11))<<3))]; //each pin is inverted to get the user value (due to working with PullUp)
}
