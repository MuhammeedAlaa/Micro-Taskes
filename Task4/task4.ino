bool currentPattern[10][10] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
int numbers[10][10] = {
  { 510, 897, 705, 609, 561, 537, 525, 519, 515, 510 },
  { 16, 48, 112, 240, 48, 48, 48, 48, 48, 252 },
  { 120, 252, 398, 390, 6, 12, 24, 48, 96, 510 },
  { 508, 2, 2, 6, 28, 6, 2, 2, 258, 252 },
  { 6, 30, 54, 102, 198, 511, 1023, 6, 6, 6 },
  { 510, 256, 256, 508, 2, 2, 2, 2, 258, 252 },
  { 252, 258, 258, 256, 256, 508, 258, 258, 258, 252 },
  { 510, 510, 12, 24, 48, 48, 48, 48, 48, 48 },
  { 252, 258, 258, 258, 258, 252, 258, 258, 258, 252 },
  { 252, 258, 258, 258, 254, 2, 2, 2, 258, 252 }
};
int emojis[10][10] = {
  {0, 462, 1023, 1023, 1023, 510, 252, 120, 48, 0},
  {120, 390, 513, 513, 585, 513, 585, 306, 258, 252},
  {120, 390, 513, 513, 585, 513, 561, 330, 258, 252},
  {120, 390, 513, 585, 513, 561, 585, 306, 258, 252},
  {120, 390, 561, 585, 513, 513, 585, 258, 258, 252},
  {120, 390, 513, 585, 513, 513, 513, 258, 258, 252},
  {120, 390, 585, 513, 513, 765, 513, 258, 258, 252},
  {24, 24, 12, 1020, 1023, 255, 255, 127, 127, 63},
  {96, 96, 192, 255, 1023, 1020, 1020, 1016, 1016, 1008},
  {216, 219, 75, 105, 255, 447, 831, 447, 511, 63}
};
byte index = 10, indexPassword = 0;
byte password[4] = {1, 2, 3, 4}, lastPattarn[4] = {0, 0, 0, 0}, palindrome = false;
bool mode = false, skip = false;
int melody[10] = { 3830,  1912,  1502,  3038,  1601,   2028,  3400,  2864,  2272,  2550};
long tempo = 4000;
int tone_ = 0;
int beat = 8;
unsigned long duration  = 0;
void setup()
{
  Serial.begin(9600);
  DDRD  = 255, DDRB |= 3, DDRC &= 254;
  for (int i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      PORTD = i + 16 * j, PORTB |= 1, PORTB &= 0;
    }
    delay(200);
    for (size_t k = 0; k < 10; k++) {
      PORTD = i + 16 * k, PORTB |= 1, PORTB &= 0;
    }
  }
  delay(200);
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      PORTD = i * 16 + j, PORTB |= 1, PORTB &= 0;
    }
    delay(200);
    for (size_t k = 0; k < 10; k++) {
      PORTD = i * 16 + k, PORTB |= 1, PORTB &= 0;
    }
  }
}
void loop() {
  if (!skip)
    getIndex(analogRead(A0));
  delay(200);
  if (index != 10) {
    if (indexPassword > 3) indexPassword %= 4;
    lastPattarn[indexPassword] = index;
    playTone(index);
    if ((password[0] == password[3]) && (password[1] == password[2])) palindrome = true; else palindrome = false;
    if (!palindrome) {
      if ((lastPattarn[0] == password[0]) && (lastPattarn[1] == password[1]) && (lastPattarn[2] == password[2]) && (lastPattarn[3] == password[3])) mode = true,  tempo = 100000 , playTone(index);;
      if ((lastPattarn[0] == password[3]) && (lastPattarn[1] == password[2]) && (lastPattarn[2] == password[1]) && (lastPattarn[3] == password[0])) mode = false, tempo = 100000 ,playTone(index);;
    } else
      mode = !mode;
	tempo = 4000;
    if ((lastPattarn[0] == 1) && (lastPattarn[1] == 2) && (lastPattarn[2] == 1) && (lastPattarn[3] == 2)) {
      int change = 0;
      while (change != 4) {
        getIndex(analogRead(A0));
        delay(200);
        if (index != 10)
          lastPattarn[change] = index, change++;
      }
      password[3] = lastPattarn[3], password[2] = lastPattarn[2], password[1] = lastPattarn[1], password[0] = lastPattarn[0];
    }
    if (!mode)
      skip = drawPattarn(getPattarn(numbers[index]));
    else
      skip = drawPattarn(getPattarn(emojis[index]));
  }
}
bool drawPattarn(bool **drawen) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      getIndex(analogRead(A0));
      if (index != 10) {
        deletePattarn(drawen);
        indexPassword++;
        return true;
      }
      PORTD = i * 16 + j;
      if (currentPattern[i][j] != drawen[i][j])
      {
        PORTB |= 1, PORTB &= 0, currentPattern[i][j] = drawen[i][j];
      }
      else
        PORTB &= 0;
      delay(30);
    }
  }
  deletePattarn(drawen);
  indexPassword++;
  return false;
}
void getIndex(int signal) {
  if (signal == 50) index = 0;
  else if (signal == 135) index = 1;
  else if (signal == 156) index = 2;
  else if (signal == 184) index = 3;
  else if (signal == 84) index = 4;
  else if (signal == 92) index = 5;
  else if (signal == 101) index = 6;
  else if (signal == 61) index = 7;
  else if (signal == 65) index = 8;
  else if (signal == 69) index = 9;
  else index = 10;
}
bool** getPattarn(int * Nums) {
  bool **pat = new bool* [10];
  for (size_t i = 0; i < 10; i++) {
    pat[i] = new bool[10];
  }
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
      pat[i][j] = 0;
    }
  }
  for (size_t j = 0; j < 10; j++)
  {
    int number = Nums[j];
    int k = 9;
    while (number) {
      int re = number % 2;
      pat[j][k] = (bool)re;
      number /= 2;
      k--;
    }
  }
  return pat;
}
void deletePattarn(bool ** pat) {
  for (size_t i = 0; i < 10; i++) {
    delete pat[i] ;
  }
  delete []pat;
}
void playTone(int index) {
  tone_ = melody[index];
  duration = beat * tempo;
  unsigned long elapsed_time = 0;
  if (tone_ > 0)
    while (elapsed_time < duration) {
      PORTB |= 2;
      delayMicroseconds(tone_ / 2);
      // DOWN
      PORTB &= 253;
      delayMicroseconds(tone_ / 2);
      elapsed_time += (tone_);
    }                
}