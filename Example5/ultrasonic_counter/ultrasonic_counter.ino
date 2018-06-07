#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// GLOBAL VARIABLES
int ledPin = 2; // This is the pin that turns on everytime the sensor returns an "object found"
int statusLedPin = 4; // This is the led that is on always
int serialMonitorID = 9600; // This is the serial monitor to return console information
int buttonPin = 9;

int USTriggerPin = 7; // The trigger pin of the ultrasonic sensor
int USEchoPin = 8; // The echo pin of the ultrasonic sensor

float currentDistance = 0; // This current distance will calculate the original distance (of the wall) when the arduno starts


/**
 * The following two variables exist because we
 * dont want to print the information constantly into the display. This will
 * help to see the information without blinking
 */
unsigned long previousMillisDisplay = 0;
const long intervalDisplay = 500;

float variant = 0.8; // This varian is created to avoid false positives on ultrasonic device
float initialDistance = 0; // This is the initial distance of the wall
float maxFixedDistance = 0; // This is a variable that will short a little the original distance (with the variant)

/**
 * Miliseconds control for the counter
 */
unsigned long previousMillisCounter = 0;
const long intervalCounter = 1800; // This is the number of seconds (miliseconds)


/**
 * Counters
 */
 int counter_a = 0;
 int counter_b = 0;


  bool counter_a_status = false;
  bool counter_b_status = false;

/**
 * LED CRYSTAL object
 * The first variable is the address of the display
 * I don't understand what the following numbers mean
 * The POSITIVE variable indicates the type of the display. We can use NEGATIVE also.
 */
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); // Led crystal object. 

/**
 * Runs when the arduino loads
 */
void setup() {

  /**
   * Lets initialize the display and indicate the size x = 16 and y = 2
   */
  lcd.begin(16,2);
  lcd.backlight(); // turn off backlight
  blinkDisplayMessage( "    Starting    " , "" , 5 , 500 );
  blinkDisplayMessage( "Setting up pins" , "" , 1 , 1000 );
  /**
   * Lets set up the pins input or output
   */
  pinMode(    ledPin        ,     OUTPUT          );
  pinMode(    statusLedPin  ,     OUTPUT          );
  pinMode(    USTriggerPin  ,     OUTPUT          );
  pinMode(    USEchoPin     ,     INPUT           );
  pinMode(    buttonPin     ,     INPUT_PULLUP    );
  /**
   * Lets start the serial object (for console use only)
   */
  Serial.begin( serialMonitorID );


  /**
   * Print the initial score
   */
   printScore();
  
  // Status LED PIN
  digitalWrite( statusLedPin , HIGH ); // This is only to indicate that is working
}

// the loop function runs over and over again forever
void loop() {
  echoRead( );
  buttonRead( );
}


void blinkDisplayMessage( String l1, String l2, int times, int interval){
  for( int i = 0;  i < times ; i++ ){
    printDisplayNow( l1 , l2 );
    delay( interval );
    clearDisplay();
    delay( interval );
  }
}

/**
 * Reads the button
 */
void buttonRead(){
  int sensorVal = digitalRead( buttonPin );
  if (sensorVal == LOW) {
    resetCounter( );
  }
}

/**
 * It resets the counters
 */
void resetCounter(){
  counter_a = 0;
  counter_b = 0;
  printScore( );
}

/**
 * This function will display a string into the display. Each parameter is a line
 */
void printDisplay( String l1, String l2 ){
  unsigned long currentMillis = millis();
   if ( currentMillis - previousMillisDisplay >= intervalDisplay ) {
      previousMillisDisplay = currentMillis;
      printDisplayNow( l1 , l2 );
    }
}

void printDisplayNow( String l1, String l2 ){
  unsigned long currentMillis = millis();   
  previousMillisDisplay = currentMillis;
  clearDisplay();
  lcd.print( String( l1 ) );
  lcd.setCursor(0,1);
  lcd.print( String( l2 ) );
}


void clearDisplay(){
  lcd.home();
  lcd.clear();
  lcd.setCursor(0,0);  
}

/**
 * This funtion will read the information of the ultrasonic sensor,
 * and if it is less than the original fixed initial value, it will execute a function
 */
void echoRead(){
  int microseconds_delay_1 = 2;
  int microseconds_delay_2 = 10;
  // Clears the trigPin
  digitalWrite( USTriggerPin , LOW);
  delayMicroseconds( microseconds_delay_1 );
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite( USTriggerPin, HIGH);
  delayMicroseconds( microseconds_delay_2 );
  digitalWrite( USTriggerPin , LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  float duration = pulseIn(USEchoPin, HIGH);
  // Calculating the distance
  float distance = getDistance( duration );
  // Prints the distance on the Serial Monitor
  // Serial.print("Distance: ");
  // Serial.println(distance);
  if( initialDistance == 0 ){
    initialDistance = distance;
    maxFixedDistance = variant * initialDistance;
  }
  // printDisplay(  String( distance ) , "I: " + String( initialDistance ) + " M: " + maxFixedDistance  );

  Serial.println(" => " + String( distance ));
  // Serial.println(" => " + "I: " + String( initialDistance ) + " M: " + maxFixedDistance);
  
  currentDistance = distance;
  if( distance <= maxFixedDistance ){
    /**
     * We have to calculate if we can increase the counter or not
     */
    ledControl( HIGH );
    unsigned long currentMillis = millis();
    if ( currentMillis - previousMillisCounter >= intervalCounter && counter_a_status == false) {
      counter_a_status = true;
      previousMillisCounter = currentMillis;
      increaseCounterA( 1 );
    }
  }else{
    counter_a_status = false;
    ledControl( LOW );  
  }
}

/**
 * Funtion to get current distance
 */
float getDistance( float duration ){
  return duration * 0.034/2;
}

/**
 * This will increase the counter A
 */
void increaseCounterA( int v ){
  counter_a += v;
  printScore();
}

/**
 * This will increase the counter B
 */
void increaseCounterB( int v ){
  counter_b += v;
  printScore();
}

/**
 * This will print the current score
 */
void printScore(){
  Serial.println( "===============================" );
  Serial.println( "Team A: " + String( counter_a ) );
  Serial.println( "Team B: " + String( counter_b ) );
  Serial.println( "===============================" );

  printDisplayNow( "Team A: " + String( counter_a ) , "Team B: " + String( counter_b ) );
}

void ledControl(int c){
  digitalWrite( ledPin ,c );
}
