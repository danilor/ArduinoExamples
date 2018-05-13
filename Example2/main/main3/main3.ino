const int ledPin =  2;      // the number of the LED pin

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
 
}

void loop() {

  digitalWrite( ledPin , HIGH );
  delay( 500 );
  digitalWrite( ledPin , LOW );
  delay( 500 );
  
}
