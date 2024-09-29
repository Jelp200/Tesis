/*
    Tests the pins to confirm the sketch was successfully updated
    Turns on an LED for 0.5 seconds, then off for 0.5 seconds 
    for each pin on the ATtiny 84

    ATtiny Pin 1: 5V
    ATtiny Pin 2: LED 10
    ATtiny Pin 3: LED 9
    ATtiny Pin 4: RESET  
    ATtiny Pin 5: LED 8
    ATtiny Pin 6: LED 7
    ATtiny Pin 7: LED 6
    ATtiny Pin 8: LED 5
    ATtiny Pin 9: LED 4
    ATtiny Pin 10: LED 3  
    ATtiny Pin 11: LED 2
    ATtiny Pin 12: LED 1  
    ATtiny Pin 13: LED 0
    ATtiny Pin 14: LED GND 
 */

// declare pins
int myLED[] = {0,1,2,3,4,5,6,7,8,9,10};
int i =0;

void setup() {                
    pinMode(myLED[0], OUTPUT);
    pinMode(myLED[1], OUTPUT);
    pinMode(myLED[2], OUTPUT);
    pinMode(myLED[3], OUTPUT);
    pinMode(myLED[4], OUTPUT);
    pinMode(myLED[5], OUTPUT);
    pinMode(myLED[6], OUTPUT);
    pinMode(myLED[7], OUTPUT);
    pinMode(myLED[8], OUTPUT);
    pinMode(myLED[9], OUTPUT);
    pinMode(myLED[10], OUTPUT);
}

void loop() {
    i = 0;   //reset i so the loop repeats
    for (i=0; i<11;i++) {
        digitalWrite(myLED[i], HIGH);   
        delay(500);                     
        digitalWrite(myLED[i], LOW);   
        delay(500);
    }
}