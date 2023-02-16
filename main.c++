#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Tone.h>
#include <FastLED.h>

// Initialize the motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

// Define the speaker pin
int speakerPin = 9;

// Define the button pin
int buttonPin = 2;

// Define the LED strip data pin
int ledPin = 6;

// Define the number of LEDs in the strip
int numLeds = 60;

// Define the LED brightness
int brightness = 255;

// Define the LED color
CRGB color = CRGB::Red;

// Define the LED strip object
CRGB leds[numLeds];

// Initialize the Tone library
Tone tone1;

void setup() {
  // Initialize the motor shield
  AFMS.begin();

  // Initialize the LED strip
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, numLeds);
  FastLED.setBrightness(brightness);

  // Set the motor speed
  myMotor->setSpeed(255);

  // Set up the button
  pinMode(buttonPin, INPUT_PULLUP);

  // Set up the speaker
  tone1.begin(speakerPin);
}

void loop() {
  // Check if the button is pressed
  if (digitalRead(buttonPin) == LOW) {
    // Turn on the motor
    myMotor->run(FORWARD);

    // Play a sound from the speaker
    tone1.play(NOTE_A7, 200);

    // Cycle the LED color
    for (int i = 0; i < numLeds; i++) {
      leds[i] = color;
      FastLED.show();
      delay(10);
    }
    color = color + 5;
  } else {
    // Turn off the motor
    myMotor->run(RELEASE);
  }
}
