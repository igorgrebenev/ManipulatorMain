// Maksim Gebenev

#include "SGServo.h"

int SGServo::getDegDelay() {
  return degDelay;
}

int SGServo::getPortNumber() {
  return portNumber;
}

SGServo::SGServo () {
  portNumber = UNDEFINED;
  degDelay = INITIAL_SERVO_DELAY;
  minMicroseconds = 0; 
  maxMicroseconds = 0; 
}

void SGServo::setTimes(int min, int max) {
  minMicroseconds = min;
  maxMicroseconds = max;
}

void SGServo::resetTimes() {
  minMicroseconds = 0;
  maxMicroseconds = 0;
}
  
bool SGServo::PWDInitialized() {
  return (minMicroseconds > 0 && maxMicroseconds > 0);
}

void SGServo::setDegDelay(int value) {
  degDelay = value;
}

bool SGServo::isInitialized() {
  return portNumber != UNDEFINED;
}

void SGServo::initialize(int port) {
  if (isInitialized()) {
    return; // сервопривод уже инициализирован
  }
  portNumber = port; // сохраняем назначенный порт для проверки 
  servo.attach(portNumber); // поключить сервопривод к порту
}

void SGServo::perform (int from, int to, int delay) {
  int startPosition = from;
  int direction = (to - startPosition) > 0 ? 1 : -1;
  int pos = startPosition;
  while (pos != to) {
    performImmediately(pos);
    pos += direction;
    ::delay(delay);
  }
}

void SGServo::performImmediately (int to) {
  if (PWDInitialized()) {
    servoPerformImmediatelyByPWD(to);
  } else {
    servo.write(to);
  }
}

//Прямое управление ШИМ
void SGServo::servoPerformImmediatelyByPWD(int angle) {
  int mappedAngleToTime = map(angle, 0, 180, minMicroseconds, maxMicroseconds);
  servo.writeMicroseconds(mappedAngleToTime);
}

// исполнение сервопривода с установленной задержкой
// Предпочтительно настроить все сервоприводы при их инициализации
// присоединяем к порту
// servo.initialize(DIGITAL_PORT_NUMBER);
// настраиваем скорость вращения путем инициализации времени задержки (в мс)
// после поворота сервомашинки на 1 градус
// servo.setDegDelay(DELAY_TIME_PER_1GRAD_ms)
void SGServo::perform (int from, int to) {
  perform(from, to, degDelay);
}
