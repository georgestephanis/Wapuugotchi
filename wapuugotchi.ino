/*
 * Wapuugotchi
 * by George Stephanis
 * https://github.com/georgestephanis/wapuugotchi
 */

#include <Wire.h>
#include <Bounce2.h>
#include <ESP8266WiFi.h>
#include <SFE_MicroOLED.h>

#include "Wapuu.h"
#include "SimpleTimer.h"

#define PIN_RESET 255
#define DC_JUMPER 0
#define PIN_A D5
#define PIN_B D6
#define PIN_C D7
#define PIN_SPEAKER D8

MicroOLED oled( PIN_RESET, DC_JUMPER );

String mac = WiFi.macAddress();

Bounce bounce_a = Bounce();
Bounce bounce_b = Bounce();
Bounce bounce_c = Bounce();

SimpleTimer timer;

Wapuu wapuu;

void WapuuTick() {
  wapuu.tick();
  wapuu.report();
}

void setup() {
  Serial.begin( 74880 );
  Serial.println();
  Serial.println();
  Serial.println( "Mac Address: " + mac );
  Serial.println();

  oled.begin();
  oled.clear( ALL );
  oled.display();

  pinMode( PIN_A, INPUT_PULLUP );
  bounce_a.attach( PIN_A );
  bounce_a.interval( 5 );

  pinMode( PIN_B, INPUT_PULLUP );
  bounce_b.attach( PIN_B );
  bounce_b.interval( 5 );

  pinMode( PIN_C, INPUT_PULLUP );
  bounce_c.attach( PIN_C );
  bounce_c.interval( 5 );

  timer.setInterval( 1000, WapuuTick );
}

void loop() {
  timer.run();

  bounce_a.update();
  bounce_b.update();
  bounce_c.update();

  if ( bounce_a.fell() ) {
    Serial.println( "Button A Pressed!" );
    wapuu.feed();
    wapuu.report();
  }
  if ( bounce_b.fell() ) {
    Serial.println( "Button B Pressed!" );
    wapuu.report();
  }
  if ( bounce_c.fell() ) {
    Serial.println( "Button C Pressed!" );
    wapuu.clean_poop();
    wapuu.report();
  }
}
