byte A, B, C, D;
void setup() {
  for ( byte i = 3; i <= 13; i++)
    pinMode(i, i < 7 ? INPUT : OUTPUT);
  pinMode(A0, OUTPUT), pinMode(A1, OUTPUT), pinMode(A2, OUTPUT), pinMode(A3, OUTPUT), pinMode(A4, OUTPUT), pinMode(A5, OUTPUT);
}
void loop() {
  A = digitalRead(3), B = digitalRead(4), C = digitalRead(5), D = digitalRead(6);
  digitalWrite(7, (A || B || C || !D)), digitalWrite(8, (A || !(B ^ D) || C));
  digitalWrite(10, (A || (!B && !D) || (!B && C) || (C && !D) || (B && !C && D)));
  digitalWrite(11, ((A && !C) || (!A && !B && !D) || (D && (B ^ C)) || (B && C && !D)));
  digitalWrite(12, (!A || !B || !D)), digitalWrite(A0, !(D ^ A) || (B ^ C) || (C && !D));
  digitalWrite(13, (A || (!C && !D) || (B && !C) || (B && !D))), digitalWrite(9, (!A || !B || !D || C));
  digitalWrite(A1, (!B && !D) || (C && !D) || (A && C) || (A && B)), digitalWrite(A2, (!B && C) || (C && !D) || (A && !B) || (A && C) || (!A && B && !C));
  digitalWrite(A3, !B || (!A && !(C ^ D)) || (A && !C && D)), digitalWrite(A4, !A || D || C), digitalWrite(A5, (!A && !C) || (!A && D) || (!C && D) || (A ^ B));
}
