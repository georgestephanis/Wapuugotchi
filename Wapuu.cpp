/*
  Wapuu.h - Library for a Wapuu virtual pet.
  Created by George Stephanis, January 16th, 2018.
  License: GPLv3+
*/

#include "Arduino.h"
#include "Wapuu.h"

Wapuu::Wapuu() {
  this->stage = 0;
  this->hunger = 512;
  this->health = 1023;
  this->poops = 0;
  this->age = 0;
}

int Wapuu::evolve() {
  if ( this->stage < 5 ) {
    this->stage++;
  }
  return this->stage;
}

void Wapuu::tick() {
  int ouchies = 0;

  this->age++;

  this->hunger++;
  if ( this->hunger > 1023 ) {
    this->hunger = 1023;
    ouchies++;
  }

  // Only lose health if there's untidied poops.
  ouchies += this->poops;

  // Make a poop every 200 ticks?  May need tweaking.
  if ( 0 == this->age % 200 ) {
    this->poops++;
  }

  // Apply all the health dings, or if all is shipshape, heal a point.
  if ( ouchies > 0 ) {
    this->health -= ouchies;
  } else {
    this->health++;
  }

  // Bound checking.
  if ( this->health > 1023 ) {
    this->health = 1023;
  } else if ( this->health <= 0 ) {
    this->health = 0;
    this->stage = 5;
  }
}

void Wapuu::report() {
  Serial.printf(
      "Stage: %d | Age: %d | Hunger: %d | Health: %d | Poops: %d",
      this->stage,
      this->age,
      this->hunger,
      this->health,
      this->poops
    );
  Serial.println();
}

void Wapuu::feed() {
  if ( this->hunger > 100 ) {
    Serial.println( "Feeding Wapuu some food!" );
    this->hunger -= 100;
    this->health += 20;

    if ( this->health > 1023 ) {
      this->health = 1023;
    }
    if ( this->hunger < 0 ) {
      this->hunger = 0;
    }
  } else {
    Serial.println( "Wapuu isn't hungry right now." );
  }
}

void Wapuu::clean_poop() {
  if ( this->poops > 0 ) {
    Serial.println( "Scooping the poops!" );
  } else {
    Serial.println( "No poops to scoop." );
  }
  this->poops = 0;
}

int Wapuu::get_stage() {
  return this->stage;
}

int Wapuu::get_age() {
  return this->age;
}

int Wapuu::get_hunger() {
  return this->hunger;
}

int Wapuu::get_health() {
  return this->health;
}

int Wapuu::get_poops() {
  return this->poops;
}

