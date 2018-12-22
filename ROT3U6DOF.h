#ifndef ROT3U6DOF_H
#define ROT3U6DOF_H

#import "SGServo.h"

#define ROT3U6DOF_SERVO_COUNT 6
#define ROT3U6DOF_SERVO_START_PORT 1 // т.е. сервоприводы подключены к портам (1 .. ROT3U6DOF_SERVO_COUNT)

SGServo servos[ROT3U6DOF_SERVO_COUNT]; // 6 серво для ROT3U-6DOF
int servoPositions[ROT3U6DOF_SERVO_COUNT]; // 6 позиций серво

void setupROT3U6DOF (int min, int max) {
  for (int i=0; i<ROT3U6DOF_SERVO_COUNT; i++) {
    SGServo currentServo = servos[i];
    servoPositions[i] = 0;
    int portNumber = i + ROT3U6DOF_SERVO_START_PORT;
    currentServo.initialize(portNumber);
    currentServo.setTimes(min, max); // врямена ШИМ для сервопривода MG995
  }
}

#define PROCESS_STEPS_COUNT 100 // количество шагов для смены положения сервопривода
#define DELAY_FOR_SERVO_STEP 50

void performAllImmediately(int newPositions[ROT3U6DOF_SERVO_COUNT]) {
  for (int i=0; i<ROT3U6DOF_SERVO_COUNT; i++) {
    if (newPositions[i] == UNDEFINED) { // Менять значение не нужно
      continue;
    }
    SGServo currentServo = servos[i];
    currentServo.performImmediately(newPositions[i]);
    servoPositions[i] = newPositions[i];
  }
}

void performServoImmediately(int servoIndex, int newPosition) {
  SGServo currentServo = servos[servoIndex];
  currentServo.performImmediately(newPosition);
  servoPositions[servoIndex] = newPosition;
}
/*
* Установка всех сервоприводов за один раз
* newPositions - массив новых позиций (если значение UNDEFINED, обработка привода пропускается)
*/
void performAllServos(int newPositions[ROT3U6DOF_SERVO_COUNT], int delay) {
  // сохраняем начальные значения приводов
  int initialRanges[ROT3U6DOF_SERVO_COUNT];
  for (int i=0; i<ROT3U6DOF_SERVO_COUNT; i++) {
    initialRanges[i] = servoPositions[i];
  }

  // выполняем смещение приводов 
  for (int step = 0; step < PROCESS_STEPS_COUNT; step++) {
    // 
    for (int i=0; i<ROT3U6DOF_SERVO_COUNT; i++) {
      if (newPositions[i] == UNDEFINED) { // Менять значение не нужно
        continue;
      }
      SGServo currentServo = servos[i];
      if (newPositions[i] == servoPositions[i]) { // Сервопривод уже установлен в текущее положение
        continue;
      }

      int shiftRange = newPositions[i] - initialRanges[i];
      int nextPos = (int) (initialRanges[i] + (((float)(shiftRange*step))/PROCESS_STEPS_COUNT));

      // Перемещаем привод в посчитанное положение.
      currentServo.performImmediately(nextPos);
      servoPositions[i] = nextPos;
    }
    ::delay(delay);
  }
}

void performAllServos(int newPositions[ROT3U6DOF_SERVO_COUNT]) {
  performAllServos(newPositions, DELAY_FOR_SERVO_STEP);
}

#define STARTPOS_SERVO1_DEG 90
#define STARTPOS_SERVO2_DEG 70 //0
#define STARTPOS_SERVO3_DEG 120 //48
#define STARTPOS_SERVO4_DEG 160
#define STARTPOS_SERVO5_DEG 90
#define STARTPOS_SERVO6_DEG 20 // 10-60 ; 10-20 - opened
#define INITIAL_DELAY 3
/*
* Установка начального положения манипулятора
*/
void resetROT3U6DOF() {
  int positions[] = {
    STARTPOS_SERVO1_DEG,
    STARTPOS_SERVO2_DEG,
    STARTPOS_SERVO3_DEG,
    STARTPOS_SERVO4_DEG,
    STARTPOS_SERVO5_DEG,
    STARTPOS_SERVO6_DEG
  };
  performAllImmediately(positions);
}

#endif
