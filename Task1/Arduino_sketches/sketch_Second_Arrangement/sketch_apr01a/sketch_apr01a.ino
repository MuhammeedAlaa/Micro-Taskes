byte A, B, C, D;
void setup() {
  for ( byte i = 2; i <= 12; i++)
    pinMode(i, i < 9 ? OUTPUT : INPUT);
}
void loop() {
  A = digitalRead(9), B = digitalRead(10), C = digitalRead(11), D = digitalRead(12);
  digitalWrite(2, (!B && !D) || (B && C) || (!A && C) || (A && !D) || (!A && B && D) || (A && !B && !C));
  digitalWrite(3, ((!A && !B) || (!B && !C) ) || (!B && !D) || (!A && !C && !D) || (!A && C && D) || (A &&(C ^ D)));
  digitalWrite(4, ((!A && !C) || (A && !B) || (!A && D) || (!C && D) || (!A && B)));
  digitalWrite(5, ((!B && C) || (!A && B && !C) || (C && !D) || (A && D) || (A && !B)));
  digitalWrite(6, (B && !C && D) || (!B && !D) || (!B && C) || (C && !D) || (A && !C));
  digitalWrite(7, (!B && !D) || (A && B) || (C && !D) || (A && C));
  digitalWrite(8, ((!C && !D) || (B && !D) || (A && C && D) || (!A && B && !C) || (A && !B && !C)));
}
