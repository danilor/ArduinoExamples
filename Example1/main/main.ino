byte ledPin = 2;
int waitTime = 250;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( ledPin , HIGH ); // turn the LED on (HIGH is the voltage level)
   delay( waitTime ); // wait for a second
   digitalWrite(ledPin , LOW ); // turn the LED off by making the voltage LOW
   delay( waitTime ); // wait for a second
}
