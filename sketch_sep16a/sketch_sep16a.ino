// Defining the pins
const int TRIG_PIN   = 9;
const int ECHO_PIN   = 10;
const int GREEN_LED  = 7;
const int RED_LED    = 13;
const int BUZZER_PIN = 11;

void setup() {
  // Initializing serial monitor for debugging
  Serial.begin(9600);

  // Configure pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Trigger a 10 microsecond pulse to Ultrasonic Sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read echo travel time in microseconds
  long duration = pulseIn(ECHO_PIN, HIGH);

  // Calculate distance in cm 
  // Speed of sound = 0.034 cm/us
  int distanceCm = duration * 0.034 / 2;

  // Print distance output to serial monitor
  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Logic for distance
  if (distanceCm > 30 || distanceCm <= 0) {
    // All clear + Green LED is on
    setIndicators(HIGH, LOW);
    noTone(BUZZER_PIN);
  } 
  else if (distanceCm > 15 && distanceCm <= 30) {
    // Beep slowly
    setIndicators(LOW, HIGH);
    triggerBeep(1000, 200); // 1kHz tone, 200ms delay
  } 
  else if (distanceCm > 5 && distanceCm <= 15) {
    // Beep faster
    setIndicators(LOW, HIGH);
    triggerBeep(1500, 80); // 1.5kHz tone, 80ms delay
  } 
  else {
    // Loud alarm tone + Turn both LED on
    //If < 5cm
    setIndicators(HIGH, HIGH);
    tone(BUZZER_PIN, 2000); // Continuous 2kHz warning
  }

  delay(50); // Small delay
}

// Update LED states
void setIndicators(bool green, bool red) {
  digitalWrite(GREEN_LED, green);
  digitalWrite(RED_LED, red);
  
}

// Pulse the buzzer
void triggerBeep(int frequency, int delayMs) {
  tone(BUZZER_PIN, frequency);
  delay(50);
  noTone(BUZZER_PIN);
  delay(delayMs);
}