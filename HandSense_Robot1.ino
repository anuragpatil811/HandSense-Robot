
/*
  Project: HandSense Robot
  Board: Arduino UNO

  Components:
  - HC-SR04 Ultrasonic Sensor
  - L293D Motor Driver Module
  - 2 DC Gear Motors

  Working:
  Hand detected within 15 cm -> Robot moves
  Hand removed -> Robot stops
*/

// Motor A connections
const int MOTOR_A1 = 8;
const int MOTOR_A2 = 9;
const int ENA = 11;

// Motor B connections
const int MOTOR_B1 = 6;
const int MOTOR_B2 = 7;
const int ENB = 10;

// Ultrasonic Sensor
const int TRIG_PIN = A1;
const int ECHO_PIN = A0;

// Robot Settings
const int MOTOR_SPEED = 180;
const int DETECTION_DISTANCE = 15;

void setup() {

  Serial.begin(9600);

  // Configure Motor A
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Configure Motor B
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configure Ultrasonic Sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  stopMotors();

  Serial.println("HandSense Robot Ready!");
}

void loop() {

  // Generate ultrasonic pulse
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration
  unsigned long duration =
      pulseIn(ECHO_PIN, HIGH, 30000UL);

  // Calculate distance in centimeters
  float distance = duration * 0.0343 / 2.0;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Hand detection condition
  if (duration > 0 &&
      distance >= 2 &&
      distance <= DETECTION_DISTANCE) {

    moveForward();

    Serial.println("Hand Detected - Moving Forward");

  } else {

    stopMotors();

    Serial.println("Hand Removed - Robot Stopped");
  }

  delay(50);
}

// Function to move robot forward
void moveForward() {

  // Motor A forward
  digitalWrite(MOTOR_A1, HIGH);
  digitalWrite(MOTOR_A2, LOW);

  // Motor B forward
  digitalWrite(MOTOR_B1, HIGH);
  digitalWrite(MOTOR_B2, LOW);

  // Set motor speed
  analogWrite(ENA, MOTOR_SPEED);
  analogWrite(ENB, MOTOR_SPEED);
}

// Function to stop robot
void stopMotors() {

  // Disable motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  // Motor A stop
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);

  // Motor B stop
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
}
