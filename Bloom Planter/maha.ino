#include <Servo.h>
#include <Adafruit_NeoPixel.h>

// Define the button pin
const int buttonPin = 10;

// Define the LED strip parameters
const int ledPin1 = 2;
const int ledPin2 = 3;
const int numLeds1 = 3;
const int numLeds2 = 20;
const uint32_t yellow = Adafruit_NeoPixel::Color(255, 255, 0);

// Create servo objects to control servos
Servo myservo;
Servo myservo2;

// Create NeoPixel objects
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(numLeds1, ledPin1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(numLeds2, ledPin2, NEO_GRB + NEO_KHZ800);

// Variable to store the servo position
int pos = 0;

// Variables to store the button state and debouncing
int buttonState = HIGH;
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Attach the servos to the specified pins
  myservo.attach(4);
  myservo2.attach(5);

  // Initialize the LED strips
  strip1.begin();
  strip2.begin();
  strip1.show(); // Initialize all pixels to 'off'
  strip2.show(); // Initialize all pixels to 'off'

  // Set the button pin as an input with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize serial communication for debugging
  Serial.begin(9600);

  // Set the LEDs to yellow initially
  for (int i = 0; i < numLeds1; i++) {
    strip1.setPixelColor(i, yellow);
  }
  strip1.show();

  for (int i = 0; i < numLeds2; i++) {
    strip2.setPixelColor(i, yellow);
  }
  strip2.show();
}

void loop() {
  // Read the button state
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // Reset the debouncing timer
  }
  Serial.println(reading);

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // If the button state has been stable for longer than the debounce delay
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed
      if (buttonState == LOW) {
        Serial.println("Button pressed");

        // Move both servos to 90 degrees
        pos = 90;
        myservo.write(pos);
        myservo2.write(pos);
        delay(2000); // Wait for 2 seconds

        // Make the LEDs blink for 7 seconds
        for (int j = 0; j < 7; j++) {
          Serial.println("Blinking LEDs on");
          
        for (int i = 0; i < numLeds1; i++) {
          strip1.setPixelColor(i, yellow);
        }
        strip1.show();

        for (int i = 0; i < numLeds2; i++) {
          strip2.setPixelColor(i, yellow);
        }
        strip2.show();
          delay(500);

          Serial.println("Blinking LEDs off");
          strip1.clear();
          strip2.clear();
          strip1.show();
          strip2.show();
          delay(500);
        }

        // Move both servos back to 0 degrees
        Serial.println("Returning servos to 0 degrees");
        pos = 0;
        myservo.write(pos);
        myservo2.write(pos);
        delay(2000); // Wait for 2 seconds

        // Turn off the LEDs
        strip1.clear();
        strip2.clear();
        strip1.show();
        strip2.show();

        // Restore the LEDs to yellow
        for (int i = 0; i < numLeds1; i++) {
          strip1.setPixelColor(i, yellow);
        }
        strip1.show();

        for (int i = 0; i < numLeds2; i++) {
          strip2.setPixelColor(i, yellow);
        }
        strip2.show();
      }
    }
  }

  // Save the current reading as the last button state
  lastButtonState = reading;
   Serial.println("Returning servos to 0 degrees");
        pos = 90;
        myservo.write(pos);
        myservo2.write(pos);
        delay(200); // Wait for 2 seconds

  // Add a small delay to reduce CPU usage
  delay(10);
}
