volatile int a=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  a = a+1;
  Serial.println("TASK1");
  Serial.println(a);
  delay(20);

  a = a+1;
  Serial.println("TASK2");
  Serial.println(a);
  delay(20);

   a = a+1;
  Serial.println("TASK3");
  Serial.println(a);
  delay(20);
}
