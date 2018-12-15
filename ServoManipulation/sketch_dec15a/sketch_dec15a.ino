#include <Servo.h>

//Servo, responsable for controlling Servo Hardware
Servo myServo;
//Angle, responsable for the actual angle on Servo
int angle = 0;
const short MAX_ANGLE = 180;
const short MIN_ANGLE = 0;
char str[20];

enum COMMAND_OPTION {NO_VALUE = 0, INCREASE, DECREASE, INCREASE_DECREASE};

//Initialize Servo on pin 9
//Put Servo in position 0
//wait 0,5 secs
//Initialize Serial for reading
void setup() {
  myServo.attach(9);
  moveServo(0);
  delay(500);
  Serial.begin(9600);
}

//Move Servo with the angle variavel informed.
void moveServo(int angle) {
  if (angle < MIN_ANGLE || angle > MAX_ANGLE) return;
  myServo.write(angle);
}

void loop() {
  str[0] = getCommand();
  switch (atoi(str)) {
    case INCREASE: angle += 5;
      break;
    case DECREASE: angle -= 5;
      break;
    case INCREASE_DECREASE: testServo();
      return;
    case NO_VALUE:
    default:
      return;
  }
  moveServo(angle);
}

char getCommand() {
  return Serial.available() > 0 ? Serial.read() : '0';
}

void testServo() {
  angle = 0;
  moveServo(0);
  delay(500);
  loopTestServo(MIN_ANGLE, MAX_ANGLE + 1, 1);
  loopTestServo(MAX_ANGLE, MIN_ANGLE - 1, -1);
}

void loopTestServo(int ini, int fim, int inc) {
  for (; ini != fim;  ini += inc) {
    moveServo(ini); // Comando para angulo específico
    delay(50);
  }
}
