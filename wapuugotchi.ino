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
#define PIN_A D7
#define PIN_B D6
#define PIN_C D5
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
  showWapuu( wapuu.get_age(), wapuu.get_hunger(), wapuu.get_health(), wapuu.get_poops() );
}

// Center and print a small title
// This function is quick and dirty. Only works for titles one
// line long.
void printTitle(String title, int font)
{
  int middleX = oled.getLCDWidth() / 2;
  int middleY = oled.getLCDHeight() / 2;
  
  oled.clear(PAGE);
  oled.setFontType(font);
  // Try to set the cursor in the middle of the screen
  oled.setCursor(middleX - (oled.getFontWidth() * (title.length()/2)),
                 middleY - (oled.getFontHeight() / 2));
  // Print the title:
  oled.print(title);
  oled.display();
  delay(1500);
  oled.clear(PAGE);
}

void showWapuu( int age, int hunger, int health, int poops ) {
  oled.clear( PAGE );
  oled.setFontType( 0 );

  int line_height = oled.getFontHeight();
  int cursor_y = 0;

  oled.setCursor( 0, 0 );
  oled.print( "Age: " + String( age ) );

  oled.setCursor( 0, cursor_y += line_height );
  oled.print( "Hngr: " + String( hunger ) );

  
  oled.setCursor( 0, cursor_y += line_height );
  oled.print( "HP: " + String( health ) );

  
  oled.setCursor( 0, cursor_y += line_height );
  oled.print( "Poops: " + String( poops ) );

  oled.display();
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
    printTitle( "Feeding!", 0 );
    Serial.println( "Button A Pressed!" );
    wapuu.feed();
    wapuu.report();
    showWapuu( wapuu.get_age(), wapuu.get_hunger(), wapuu.get_health(), wapuu.get_poops() );
  }
  if ( bounce_b.fell() ) {
    printTitle( "Menu!", 0 );
    Serial.println( "Button B Pressed!" );
    wapuu.report();
    showWapuu( wapuu.get_age(), wapuu.get_hunger(), wapuu.get_health(), wapuu.get_poops() );
  }
  if ( bounce_c.fell() ) {
    printTitle( "Cleaning!", 0 );
    Serial.println( "Button C Pressed!" );
    wapuu.clean_poop();
    wapuu.report();
    showWapuu( wapuu.get_age(), wapuu.get_hunger(), wapuu.get_health(), wapuu.get_poops() );
  }
}
