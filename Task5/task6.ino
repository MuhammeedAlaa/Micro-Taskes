unsigned long previousMillies = 0;
void setup()
{
 DDRD = B11111111, DDRB |= B11111111, DDRC &= 254;
}

void loop ()
{  
   eggValveOpen();
   eggValveClose();
   for(size_t i = 0; i < 20; i++){
	moveMixer();
	delay(25);
  } 
  vanillaValveOpen();
  previousMillies = millis();
  for(size_t i = 0; i < 16; i++){
	moveMixer();
	delay(25);
	if(millis() - previousMillies > 100)
	 vanillaValveClose(), previousMillies = millis() ;
  } 
	sugerValveOpen();
	sugerValveClose();
	for(size_t i = 0; i < 40; i++){
		moveMixer();
		delay(25);
  }
  	for(size_t j = 0; j < 4; j++){
	  	folwerValveOpen(); 	
		for(size_t i = 0; i < 16; i++){	
			moveMixer();
			delay(50);
		  }
		flowerValveClose();
		
	  }
	for(size_t j = 0; j < 4; j++){
	  moveProduction();
	  delay(300);
	}
	PORTD |= 4;
	delay(1000);
	PORTD &= 251;
	for(size_t j = 0; j < 4; j++){
	  moveProduction();
	  delay(300);
	}
  delay(1000);
  int key;
  while(1){
		key = analogRead(A0);
		delay(200);
		if(key) break;
	}
	if(getKey(key) == 1) dec1();
	if(getKey(key) == 2) dec2();
	if(getKey(key) == 3) dec3();
	if(getKey(key) == 4) dec4();
	
}
void eggValveOpen(){
	 PORTB |= 2;
	 delay(1); //First delay
	 PORTB &= 253;
	 delay(500);
}
void eggValveClose(){
	  PORTB |= 2;
	  delay(2); //First delay
	  PORTB &= 253;
}
void sugerValveOpen(){
	 PORTB |= 8;
	 delay(1); //First delay
	 PORTB &= 247;
	 delay(200);
}
void sugerValveClose(){
	  PORTB |= 8;
	  delay(2); //First delay
	  PORTB &= 247;
}

void folwerValveOpen(){
	 PORTB |= 16;
	 delay(1); //First delay
	 PORTB &= 239;
	 delay(100);
}
void flowerValveClose(){
	  PORTB |= 16;
	  delay(2); //First delay
	  PORTB &= 239;
	 delay(98); //First delay
}
void vanillaValveOpen(){
     PORTB |= 4;
	 delay(1); //First delay
	 PORTB &= 251;
}
void vanillaValveClose(){
      PORTB |= 4;
	  delay(2); //First delay
	  PORTB &= 251;
}
byte getKey(int key){
	if(key == 119) return 1;
	if(key == 135) return 2;
	if(key == 156) return 3;
	if(key == 184) return 4;
	return 0;
}
void dec1(){
	PORTB |= B00100000;
	delayMicroseconds(2000);
	PORTB &= B11011111;
	PORTD |= B10000000; 
	byte state = 0;
	for(size_t j = 0; j < 28; j++){
	  state %= 4;
	  moveStand(state);
	  delay(300);
	  state++;
	}
	state = 0;
	PORTD &= B01111111;
	PORTB |= B00100000;
	delayMicroseconds(1300);
	PORTB &= B11011111;
	PORTB |= B00000001;
	for(size_t j = 0; j < 28; j++){
	  state %= 4;
	  moveStand(state);
	  delay(300);
	  state++;
	}
	PORTB &= B11111110;
}
void dec2(){
	PORTB |= B00100000;
	delayMicroseconds(2000);
	PORTB &= B11011111;	
	bool flag = true;
	byte state = 0;
	for(size_t j = 1; j <= 28; j++){
	  state %= 4;
	  if( j % 4 == 0) flag = !flag;   
	  if(flag) PORTD |= B10000000; else PORTD &= B01111111;
	  moveStand(state);
	  delay(300);
	  state++;
	}
	PORTD &= B01111111;
	PORTB |= B00100000;
	delayMicroseconds(1300);
	PORTB &= B11011111;	
	flag = true;
	for(size_t j = 1; j <= 28; j++){
	  state %= 4;
	  if( j % 4 == 0) flag = !flag;
	  if(flag) 	PORTB |= B00000001; else PORTB &= B11111110;
	  moveStand(state);
	  delay(300);
	  state++;
	}	
	PORTB &= B11111110;
}
void dec3(){
	PORTB |= B00100000;
	delayMicroseconds(2000);
	PORTB &= B11011111;
	byte state = 0;
	for(size_t j = 0; j < 28; j++){
		state %= 4;   
		if(state % 2 == 0) PORTD |= B10000000; else PORTD &= B01111111;
	 	moveStand(state);
	  	delay(300);
		state++;
	}
	PORTB |= B00100000;
	delayMicroseconds(1500);
	PORTB &= B11011111;	
	PORTB |= B00000001; 
	delay(300);
	PORTB &= B11111110;
}
void dec4(){
	PORTB |= B00100000;
	delayMicroseconds(2000);
	PORTB &= B11011111;
	byte state = 0;
	for(size_t j = 0; j < 28; j++){
		state %= 4;   
		if(state % 2 == 0) PORTD |= B10000000, PORTB &= B11111110; else PORTB |= B00000001, PORTD &= B01111111;
	 	moveStand(state);
	  	delay(300);
		state++;
	}
	PORTB &= B11111110;
	PORTD &= B01111111;
	PORTB |= B00100000;
	delayMicroseconds(1500);
	PORTB &= B11011111;	
	PORTD |= B10000000;
	delay(2000);
	PORTD &= B01111111;
}
void   moveMixer(){PORTD &= 252, PORTD &= 253, PORTD |= 1, PORTD |= 2, PORTD |= 3, PORTD &= 254;} //motor up sequence
void   moveProduction(){PORTD &= 231, PORTD &= 239, PORTD |= 8, PORTD |= 16, PORTD |= 24, PORTD &= 247;} //motor up sequence
void   moveStand(byte state){if(state == 0) PORTD &= 159; if(state == 1) PORTD &= 191, PORTD |= 32; if(state == 2)  PORTD |= 96; if(state == 3) PORTD &= 223, PORTD |= 64;} //motor up sequence