void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(digitalRead(3));
  digitalWrite(3,digitalRead(2));
  Serial.println(digitalRead(2));
}
