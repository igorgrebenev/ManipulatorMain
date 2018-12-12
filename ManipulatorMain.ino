// Maksim Grebenev 2018
#import "SGServo.h"
#import "ROT3U6DOF.h"

void setup() {
  setupROT3U6DOF(0, 0); // 500-900Initialize servos ROT3U6DOF_SERVO_COUNT/ROT3U6DOF_SERVO_START_PORT
  resetROT3U6DOF(); // установим кутяплю в исходное положение
  delay(2000); // подождем 2 сек
}

void loop() {
  // хватаем хваталку
  performServoImmediately(5,90);
  delay(3000);
  //
  int positions01[] = {140, UNDEFINED, 22, 120, 180, 10};
  performAllServos(positions01);
  delay(3000);

  // открываем хваталку
  performServoImmediately(5,10);
  delay(3000);

  int positions02[] = {UNDEFINED, UNDEFINED, 40, 155, UNDEFINED, UNDEFINED};
  performAllServos(positions02);
  delay(3000);

  // хватаем хваталку
  performServoImmediately(5,90);
  delay(3000);

  int positions03[] = {UNDEFINED, UNDEFINED, 22, 120, UNDEFINED, UNDEFINED};
  performAllServos(positions03);
  delay(3000);

  int positions04[] = {15, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED};
  performAllServos(positions04);
  delay(3000);

  // открываем хваталку
  performServoImmediately(5,10);
  delay(3000);
  
  delay(900000); // стоп
}
