int val, sender;
void setup() {
  // put your setup code here, to run once:

  pinMode (2, OUTPUT);
  pinMode (3, OUTPUT);
  pinMode (4, OUTPUT);
  pinMode (5, OUTPUT);
  pinMode (6, OUTPUT);
  pinMode (7, OUTPUT);
  pinMode (8, OUTPUT);
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);
  pinMode (12, OUTPUT);
  pinMode (13, OUTPUT);
  pinMode (38, OUTPUT);
  pinMode (39, OUTPUT);

  pinMode (22, INPUT);
  pinMode (23, INPUT);
  pinMode (24, INPUT);
  pinMode (25, INPUT);
  pinMode (26, INPUT);
  pinMode (27, INPUT);
  pinMode (28, INPUT);
  pinMode (29, INPUT);
  pinMode (30, INPUT);
  pinMode (31, INPUT);
  pinMode (32, INPUT);
  pinMode (33, INPUT);
  pinMode (36, INPUT);
  pinMode (37, INPUT);

  Serial.begin(9600);

  sender = 0;
}

void loop() {
  if (Serial.available() > 0) {
    delay(1);
    val = Serial.read();
    digitalWrite(38, LOW);
    digitalWrite(39, HIGH);
    if (val == 'a') {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      Serial.println("send_25");
      sender = 1;
    }
    else if (val == 's') {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      Serial.println("send_125");
      sender = 1;
    }
    else if (val == 'd') {
      digitalWrite(2, HIGH);
      digitalWrite(3, HIGH);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      digitalWrite(9, HIGH);
      digitalWrite(10, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      Serial.println("send_255");
      sender = 1;
    }
    else if (val == 'f') {
      digitalWrite(2, LOW);
      digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, LOW);
      Serial.println("send_300");
      sender = 1;
    }
    digitalWrite(38, LOW);
    digitalWrite(39, LOW);
    while (sender == 1) {
      int R13 = digitalRead(36);
      int R14 = digitalRead(37);
      int R_2 = R13 + R14;
      if (R_2 == 2) {
        delay(1);
        int R1 = digitalRead(22);
        int R2 = digitalRead(23);
        int R3 = digitalRead(24);
        int R4 = digitalRead(25);
        int R5 = digitalRead(26);
        int R6 = digitalRead(27);
        int R7 = digitalRead(28);
        int R8 = digitalRead(29);
        int R9 = digitalRead(30);
        int R10 = digitalRead(31);
        int R11 = digitalRead(32);
        int R12 = digitalRead(33);

        int R = R1 + R2 * 2 + R3 * 4 + R4 * 8 + R5 * 16 + R6 * 32 + R7 * 64 + R8 * 128 + R9 * 256 + R10 * 512 + R11 * 1024 + R12 * 2048;

        digitalWrite(38, HIGH);
        digitalWrite(39, HIGH);

        if (R == 1433) {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, LOW);
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);
          Serial.println("25");
        }
        else if (R == 2010) {
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(6, HIGH);
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);
          digitalWrite(9, HIGH);
          digitalWrite(10, HIGH);
          digitalWrite(11, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);
          Serial.println("125");
        }
        else if (R == 2181) {
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, HIGH);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);
          Serial.println("255");
        }
        else if (R == 1031) {
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          digitalWrite(6, LOW);
          digitalWrite(7, LOW);
          digitalWrite(8, LOW);
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          digitalWrite(11, LOW);
          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);
          Serial.println("300");
        }
        digitalWrite(38, LOW);
        digitalWrite(39, LOW);
        sender = 0;
        break;
      }
    }
  }
}
