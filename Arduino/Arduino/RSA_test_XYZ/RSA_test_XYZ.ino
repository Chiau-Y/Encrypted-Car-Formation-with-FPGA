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
  delay(2000);
  digitalWrite(38, LOW);
  digitalWrite(39, HIGH);
  
  digitalWrite(2, LOW);
  
  digitalWrite(3, HIGH);  
  digitalWrite(4, HIGH);     //x,799(11)
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  Serial.println("send_x,799");
  
  digitalWrite(38, LOW);
  digitalWrite(39, LOW);

  delay(100);
  
  digitalWrite(38, LOW);
  digitalWrite(39, HIGH);
    
  digitalWrite(2, HIGH);
  
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);     //y,1108(140)
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  digitalWrite(9, HIGH);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  Serial.println("send_y,1108");

  digitalWrite(38, LOW);
  digitalWrite(39, LOW);
}
