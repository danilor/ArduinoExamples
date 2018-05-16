/**
   Sensor 1 variables
*/
const byte pirPin =  2; // This is the pin that is goin to receive the information of the sensor
const byte pinLed1 = 3; // The first indicating led

/**
   Sensor 2 variables
*/
const byte pirPin2 =  8; // This is the pin that is goin to receive the information of the sensor
const byte pinLed2 = 10; // The first indicating led

/**
   Serial Output
*/
const int serialOutput = 9600; // This is the serial area where to print the messages

const byte buzzPin = 9; // The ping where the buzz is located

const byte buttonPin = 13;

bool reading = false;
bool reading2 = false;

byte counter1 = 0;
byte counter2 = 0;


int buttonState = 0;         // variable for reading the pushbutton status


void setup() {
  // put your setup code here, to run once:
  Serial.begin( serialOutput );
  pinMode(  pirPin     ,   INPUT     );
  pinMode(  pirPin2    ,   INPUT     );
  pinMode(  pinLed1    ,   OUTPUT    );
  pinMode(  pinLed2    ,   OUTPUT    );
  pinMode(  buttonPin  ,   INPUT_PULLUP     );
  printScoreboard();

}


/**
   The Main Loop
*/
void loop() {
  PIRSensor();
  buttonRead();
  /*buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    Serial.println( "High" );
  } else {
    // turn LED off:
    Serial.println( "Low" );
  }*/
}

void buttonRead(){
  int sensorVal = digitalRead( buttonPin );
  // Serial.println( sensorVal );
  if (sensorVal == LOW) {
    // Resseting the counter
    Serial.println( "Resseting the game" );
    counter1 = 0;
    counter2 = 0;
    printScoreboard();
  }
}

void printScoreboard(){
  Serial.println("");
  Serial.println("");
  Serial.println("            SCOREBOARD               ");
  Serial.println("|===================================|");
  Serial.println("|  TEAM A                   TEAM B  |");
  Serial.print("     ");
  Serial.print( counter1 );
  Serial.print("                        ");
  Serial.print( counter2 );
  Serial.println("");
  Serial.println("|===================================|");
  Serial.println("");
  Serial.println("");
}

void increaseCounter1( int i ) {
  counter1 += i;
  printScoreboard();
  BuzzSound();
}

void increaseCounter2( int i ) {
  counter2 += i;
  printScoreboard();
  BuzzSound();
}

void BuzzSound() {
  /*
     const int tonos[] = {261, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494};
  */
  return;

  const int tones[] = { 261 , 230 , 415 };
  const int sze = sizeof( tones ) / sizeof( tones[0] ) ;

  // Serial.println( "Sizes tones" );
  // Serial.println( sze );

  for ( int i; i < sze ; i++ ) {
    // Serial.println( "Tone: " );
    // Serial.println( tones[ i ] );
    tone( buzzPin, tones[ i ]);
    delay(150);
  }
  noTone( buzzPin );
}

/**
   This function will read the PIRSensor Information
*/
void PIRSensor() {
  IRSensor1();
  IRSensor2();
}

void IRSensor1() {
  if (digitalRead( pirPin ) == HIGH ) {
    if ( reading == false ) {
      Serial.println( "Starting reading sensor 1" );
      digitalWrite( pinLed1 , HIGH );

      increaseCounter1( 1 );
      reading = true;
    }
  }
  if (digitalRead( pirPin ) == LOW ) {
    if ( reading  == true ) {
      reading = false;
      digitalWrite( pinLed1 , LOW );

      Serial.println( "Stopping Counting sensor 1" );
    }
  }
}

void IRSensor2() {
  if (digitalRead( pirPin2 ) == HIGH ) {
    if ( reading2 == false ) {
      // Serial.println( "Starting reading sensor 2" );
      digitalWrite( pinLed2 , HIGH );

      increaseCounter2( 1 );
      reading2 = true;
    }
  }
  if (digitalRead( pirPin2 ) == LOW ) {
    if ( reading2  == true ) {
      reading2 = false;
      digitalWrite( pinLed2 , LOW );

      // Serial.println( "Stopping Counting sensor 2" );
    }
  }
}


