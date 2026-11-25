#include <Servo.h>

const int LDR_LEFT = A0;   // LDR 1
const int LDR_RIGHT = A1;  // LDR 2
const int SERVO_PIN = 9;   // SG90 Signal (D9)

const int TOLERANCE = 20;  // Deadband to prevent servo jitter
int servoPos = 90;         // Start centered at 90 degrees

Servo trackerServo;

void setup() {
  trackerServo.attach(SERVO_PIN);
  trackerServo.write(servoPos);
  Serial.begin(9600);
  delay(500);
}

void loop() {
  int leftVal = analogRead(LDR_LEFT);
  int rightVal = analogRead(LDR_RIGHT);
  int diff = leftVal - rightVal;

  if (abs(diff) > TOLERANCE) {
    if (leftVal > rightVal) {
      servoPos = min(servoPos + 1, 170);  // Move toward left LDR
    } else {
      servoPos = max(servoPos - 1, 10);   // Move toward right LDR
    }
    trackerServo.write(servoPos);
  }

  Serial.print("L: ");
  Serial.print(leftVal);
  Serial.print(" | R: ");
  Serial.print(rightVal);
  Serial.print(" | Servo: ");
  Serial.println(servoPos);

  delay(25);
}
