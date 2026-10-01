
const int LDR_pin = A0;
const int LED_pin = 13;
const int LIGHT_THRESHOLD = 400; 

void setup() {

  Serial.begin(9600);
  pinMode(LED_pin, OUTPUT); }

void loop() {

  int light_Level = analogRead(LDR_pin);
  Serial.print("Sensor Read (A0): ");
  Serial.println(light_Level);

  // Trigger Logic
  if (light_Level < LIGHT_THRESHOLD) {
    digitalWrite(LED_pin, HIGH);
  } else {
    digitalWrite(LED_pin, LOW);
  }
  delay(300); 
}