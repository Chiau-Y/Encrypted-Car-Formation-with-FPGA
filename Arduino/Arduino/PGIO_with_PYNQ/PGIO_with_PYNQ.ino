int val;
void setup() {
  // put your setup code here, to run once:
 
 pinMode (2,OUTPUT);
 pinMode (3,OUTPUT);
 pinMode (4,OUTPUT);
 pinMode (5,OUTPUT);
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 val=Serial.read();
 if(val=='a'){ 
 digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 Serial.write('a');
 }
  else if(val=='s'){ 
 digitalWrite(2, HIGH);
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 Serial.write('s');
 }
 else  if(val=='d'){ 
 digitalWrite(2, LOW);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 }
 else  if(val=='f'){ 
 digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, LOW);
 digitalWrite(5, LOW);
 }
 else  if(val=='g'){ 
 digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, LOW);
 }
 else  if(val=='h'){ 
 digitalWrite(2, HIGH);
 digitalWrite(3, LOW);
 digitalWrite(4, HIGH);
 digitalWrite(5, LOW);
 }
 else  if(val=='j'){ 
 digitalWrite(2, LOW);
 digitalWrite(3, HIGH);
 digitalWrite(4, HIGH);
 digitalWrite(5, LOW);
 }
 else  if(val=='k'){ 
 digitalWrite(2, HIGH);
 digitalWrite(3, HIGH);
 digitalWrite(4, HIGH);
 digitalWrite(5, LOW);
 }
 else  if(val=='l'){ 
 digitalWrite(2, LOW);
 digitalWrite(3, LOW);
 digitalWrite(4, LOW);
 digitalWrite(5, HIGH);
 }
}
