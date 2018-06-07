const int buttonpin           =     2; // define the Reed sensor interfaces
bool button_press             =     false;

// LEDs
const byte led_alarm_off      =     3;
const byte led_door_opened    =     4;
const byte led_alarm_on       =     5;

// Button

const int button              =     8;


// Blinking Light
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis  = 0;
const long blinking_time       =     1000;
int ledState                  = LOW;

boolean alarm     =     false; // Indicates if we are in alarm mode
boolean opened    =     false;

int serial_port   =     9600;
void setup ()
{
  Serial.begin( serial_port );      // open the serial port at 9600 bps:    
  pinMode (buttonpin, INPUT) ;// output interface as defined Reed sensor
  pinMode( led_alarm_off , OUTPUT );
  pinMode( led_door_opened , OUTPUT );
  pinMode( led_alarm_on , OUTPUT );
  pinMode( button , INPUT_PULLUP );
  digitalWrite( led_alarm_on , LOW );
  digitalWrite( led_alarm_off , LOW );
  alarm = false;
}
void loop (){
  reedSensor();
  blinking();
  alarmSetUp();
  doorCheck();
  buttonSensor();
  
}

void buttonSensor(){
  int v = digitalRead( button );
  if( v == HIGH ){
    button_press = false;
  }else{
    if( button_press == false ){
      alarm = !alarm;
      button_press = true;
    }
    
  }
}

void reedSensor(){
  int val = digitalRead (buttonpin) ;// digital interface will be assigned a value of 3 to read val
  if (val == HIGH){ // When the Reed sensor detects a signal, LED flashes
    opened = true;
  } else {
    opened = false;
  }
}

void doorCheck(){
    if( alarm ){
      digitalWrite( led_alarm_on , HIGH );
      digitalWrite( led_alarm_off , LOW );
    }else{
      digitalWrite( led_alarm_on , LOW );
      digitalWrite( led_alarm_off , HIGH );  
    }
  if( alarm and opened ){
    // This is the alert
    Serial.println( "Alarm!" );
  }
}

void alarmSetUp(){
  if( opened ){
      
  }else{
    
  }
}

void blinking(){
  if( opened ){
       unsigned long currentMillis = millis();
      if (currentMillis - previousMillis >= blinking_time) {
        // save the last time you blinked the LED
        previousMillis = currentMillis;
    
        // if the LED is off turn it on and vice-versa:
        if (ledState == LOW) {
          ledState = HIGH;
          digitalWrite( led_door_opened , HIGH );
        } else {
          ledState = LOW;
          digitalWrite( led_door_opened , LOW );
        }
      }
  }else{
    digitalWrite( led_door_opened , LOW );    
  }
  
  
}
