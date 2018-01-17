/*
  Wapuu.h - Library for a Wapuu virtual pet.
  Created by George Stephanis, January 16th, 2018.
  License: GPLv3+
*/

#ifndef Wapuu_h
#define Wapuu_h

#include "Arduino.h"

class Wapuu {
  private:

    /**
     * What life stage is the Wapuu at?
     *  0 : Eggpuu
     *  1 : Newpuu
     *  2 : Teenpuu
     *  3 : Wapuu
     *  4 : Oldpuu
     *  5 : Deadpuu
     */
    int stage;

    /**
     * How hungry is Wapuu?
     *  Range: 0 (full) - 1023 (starving)
     */
    int hunger;

    /**
     * Current health level.
     *  Range: 0 (dead) - 1023 (max health)
     */
    int health;

    /**
     * Are there poops?
     */
    int poops;

    /**
     * The number of ticks that the Wapuu has lived.
     */
    int age;

  public:

    /**
     * Initialize a new Wapuu.
     */
    Wapuu();

    /**
     * Increments the `stage` private member variable, unless it's at max already.
     */
    int evolve();

    /**
     * Make the donuts. Increase hunger, age, generate poops, check bounds, etc.
     * 
     * Should trigger off a SimpleTimer.
     */
    void tick();

    /**
     * Print a report of the current state to Serial.
     */
    void report();
};

#endif
