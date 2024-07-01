#include <IRremote.h>
#include <MotorDriver.h>

// IR Remote Setups
const int RECV_PIN = 10;      // Define the pin where your IR receiver is connected
unsigned long lastValue = 0;  // Variable to store the last valid received value
IRrecv irrecv(RECV_PIN);
decode_results results;

// Buttons
#define Button_0 0xFF6897

#define Button_1 0xFF30CF
#define Button_2 0xFF18E7
#define Button_3 0xFF7A85

#define Button_4 0xFF10EF
#define Button_5 0xFF38C7
#define Button_6 0xFF5AA5

#define Button_7 0xFF42BD
#define Button_8 0xFF4AB5
#define Button_9 0xFF52AD

// Motor Pins
int motor1pin1 = 2;
int motor1pin2 = 3;
int motor2pin1 = 8;
int motor2pin2 = 9;

// YFROBOT PM-R3 SETUP
#define MOTORTYPE YF_PMR3
MotorDriver motorDriver = MotorDriver(MOTORTYPE);

const int offseta = 1;
const int offsetb = 1;
uint8_t SerialDebug = 1;


// Functions For Moving
// Button 0
void stop()
{
  motorDriver.setMotor(0, 0);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

// Button 1
void left_diagonal_up()
{
  motorDriver.setMotor(0, 255);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
}

// Button 2
void forward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

  motorDriver.setMotor(255, 255);
}

// Button 3
void right_diagonal_up()
{
  motorDriver.setMotor(255, 0);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}

// Button 4
void left()
{
  motorDriver.setMotor(-255, 255);
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);

}

// Button 5
void automatic()
{

}

// Button 6
void right()
{
  motorDriver.setMotor(255, -255);
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

// Button 7
void left_diagonal_down()
{
  motorDriver.setMotor(-255, 0);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);
}


// Button 8
void backwards() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);

  motorDriver.setMotor(-255, -255);
}

// Button 9
void right_diagonal_down()
{
  motorDriver.setMotor(0, -255);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();  // Start the receiver

  // Motor Pin Modes
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  // PM-R3 Motor Setup
  motorDriver.motorConfig(offseta, offsetb);
  motorDriver.setMotor(0, 0);
}

void loop() {
  if (irrecv.decode(&results)) {  //if we have received an IR signal
    if (results.value == 0xFFFFFFFF) {
      results.value = lastValue;
    }

    switch (results.value) {
      case Button_0: stop(); break;

      case Button_1: left_diagonal_up(); break;

      case Button_2: forward(); break;

      case Button_3: right_diagonal_up(); break;

      case Button_4: left(); break;

      case Button_5: automatic(); break;

      case Button_6: right(); break;

      case Button_7: left_diagonal_down(); break;

      case Button_8: backwards(); break;

      case Button_9: right_diagonal_down(); break;
    }
    Serial.println(results.value, HEX);  //display HEX results
    irrecv.resume();                     //next value
  }
  lastValue = results.value;
}