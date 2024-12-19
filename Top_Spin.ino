#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2048;
const int quarter_round = stepsPerRevolution / 4;
const int half_round = stepsPerRevolution / 2;

Stepper stepper(stepsPerRevolution, 2, 4, 3, 5);

int highest_pos = 100;
int lowest_pos = 165;
int pos = highest_pos;
Servo servo;

void setup() {
  stepper.setSpeed(14);
  Serial.begin(9600);
  servo.attach(6);
  servo.write(pos);
}

void loop() {
  delay(1000);
  plattform_down();
  delay(1000);
  stepper.step(half_round);
  delay(500);
  stepper.step(-quarter_round * 3);
  delay(500);
  stepper.step(stepsPerRevolution);
  delay(500);
  stepper.step(quarter_round);
  delay(500);
  stepper.step(quarter_round);
  delay(500);
  stepper.step(-quarter_round);
  delay(1000);
  stepper.step(-quarter_round * 3);
  delay(1000);
  plattform_up();
  stepper.step(-quarter_round);
  delay(1000);
}

void shake() {
  stepper.setSpeed(12);

  for (int i = 0; i < 20; i++) {

    if (i % 2 == 0 || i == 0)
      stepper.step(20);
    else
      stepper.step(-20);
  }
  stepper.setSpeed(10);
}

void plattform_up() {
  for (pos = lowest_pos; pos >= highest_pos; pos -= 1) {
    servo.write(pos);
    delay(15);
  }
}

void plattform_down() {
  for (pos = highest_pos; pos <= lowest_pos; pos += 1) {
    servo.write(pos);
    delay(15);
  }
}