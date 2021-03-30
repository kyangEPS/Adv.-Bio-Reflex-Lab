#include <Arduino.h>

/// Pins
// Outputs
constexpr short led_pin = 12;
constexpr short piezo_pin = 11;
constexpr short motor_pin = 10;

// Inputs
constexpr short button_pin = 9;
constexpr short light_pin = A0;

/// Methods
void stop()
{
	while (true)
		;
}

void testOutputs()
{
	// LED
	digitalWrite(led_pin, HIGH);
	delay(500);
	digitalWrite(led_pin, LOW);
	delay(500);
	// Piezo
	tone(piezo_pin, 262);
	delay(500);
	noTone(piezo_pin);
	delay(500);
	// Motor
	digitalWrite(motor_pin, HIGH);
	delay(500);
	digitalWrite(motor_pin, LOW);
}

/// Tests
// Variables
unsigned int testCount;
float average;
float slowest = 0;
float fastest = 60000; // Inially set fastest to 1 minute
bool dataCopyMode = true;

// Methods
void printResults(float rTime)
{
	// Calculate results
	testCount++;											   // Mark a new test
	average = (average * (testCount - 1) + rTime) / testCount; // Recalculate new average
	slowest = max(slowest, rTime);
	fastest = min(fastest, rTime);

	// Print them
	if (dataCopyMode)
	{
		Serial.println(rTime);
	}
	else
	{
		Serial.print("Reaction time: ");
		Serial.print(rTime);
		Serial.print("\t| Average: ");
		Serial.print(average);
		Serial.print("\t| Fastest: ");
		Serial.print(fastest);
		Serial.print("\t| Slowest: ");
		Serial.println(slowest);
	}
}

// Single sense
void lightReactionTest()
{
	// Test
	digitalWrite(led_pin, HIGH);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	digitalWrite(led_pin, LOW);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}
void soundReactionTest()
{
	// Test
	tone(piezo_pin, 262);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	noTone(piezo_pin);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}
void touchReactionTest()
{
	// Test
	digitalWrite(motor_pin, HIGH);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	digitalWrite(motor_pin, LOW);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}

// Combined
void lightAndTouchReactionTest()
{
	// Test
	digitalWrite(motor_pin, HIGH);
	digitalWrite(led_pin, HIGH);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	digitalWrite(motor_pin, LOW);
	digitalWrite(led_pin, LOW);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}
void lightAndSoundReactionTest()
{
	// Test
	tone(piezo_pin, 262);
	digitalWrite(led_pin, HIGH);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	noTone(piezo_pin);
	digitalWrite(led_pin, LOW);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}
void touchAndSoundReactionTest()
{
	// Test
	digitalWrite(motor_pin, HIGH);
	tone(piezo_pin, 262);
	unsigned long startTime = micros();
	while (!digitalRead(button_pin)) // Wait for user to press button again
		;
	unsigned long endTime = micros();
	digitalWrite(motor_pin, LOW);
	noTone(piezo_pin);

	// Report
	float reactionTime = static_cast<float>(endTime - startTime) / 1000.0f; // Reaction time in milliseconds
	printResults(reactionTime);
}