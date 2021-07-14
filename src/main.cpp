/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"

/* Enable serial debugging */
#define DEBUG 1

/* Pin defs */
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif
#define SOUND_RESET 12

void log(const char *str) {
    if(DEBUG) {
        Serial.println(str);
    }
}

void setup()
{
    if (DEBUG) {
        Serial.begin(9600);
        while (!Serial) {
            delay(10); // wait for serial port to connect. Needed for native USB
        }
    }

    log("rikerstick startup");
    
    /* Setup IO pins */
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SOUND_RESET, OUTPUT);

    log("Connecting and resetting sound board");

    /* Start sound board serial */
    Serial1.begin(9600);

    /* Reset sound board */
    digitalWrite(SOUND_RESET, LOW);
    pinMode(SOUND_RESET, OUTPUT);
    delay(10);
    pinMode(SOUND_RESET, INPUT);
    delay(1000);
}

void loop()
{
    digitalWrite(LED_BUILTIN, HIGH);

    Serial1.println("#0");

    // wait for a second
    delay(500);

    // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);

    // wait for a second
    delay(500);
}