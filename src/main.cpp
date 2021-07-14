/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include "Adafruit_Soundboard.h"
#include <HCSR04.h>

/* Enable serial debugging */
#define DEBUG 1

/* Pin defs */
#ifndef LED_BUILTIN
#define LED_BUILTIN 13
#endif
#define SOUND_RESET 12
#define TRIGGER 11
#define ECHO 10

Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SOUND_RESET);
UltraSonicDistanceSensor sensor = UltraSonicDistanceSensor(TRIGGER, ECHO);

void log(const char *str) {
    if(DEBUG) {
        Serial.println(str);
    }
}

void logFileList() {
    uint8_t files = sfx.listFiles();

    Serial.print("Found "); Serial.print(files); Serial.println(" files");
    Serial.println("========================");
    for (uint8_t f=0; f<files; f++) {
        Serial.print(f); 
        Serial.print("\tname: "); Serial.print(sfx.fileName(f));
        Serial.print("\tsize: "); Serial.println(sfx.fileSize(f));
    }
    Serial.println("========================");
}

void setup() {
    if (DEBUG) {
        Serial.begin(115200);
        int timeout = 100;
        while (!Serial && timeout) {
            delay(10); // wait for serial port to connect. Needed for native USB
            timeout--;
        }
    }

    log("rikerstick startup");
    
    /* Setup IO pins */
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(SOUND_RESET, OUTPUT);

    log("Connecting and resetting sound board");

    /* Start sound board serial */
    Serial1.begin(9600);
  
    if (!sfx.reset()) {
        Serial.println("Soundboard didn't reset");
        while (1);
    }
    Serial.println("Soundboard reset");

    logFileList();
}

void loop() {
    log("Playing audio");

    sfx.playTrack((uint8_t) 0);

    delay(1000);
}