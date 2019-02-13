 // Maksim Grebenev 2018
#import "SGServo.h"
#import "ROT3U6DOF.h"

void setup() {
  setupROT3U6DOF(0, 0); // 500-900Initialize servos ROT3U6DOF_SERVO_COUNT/ROT3U6DOF_SERVO_START_PORT
  resetROT3U6DOF(); // установим кутяплю в исходное положение
  delay(6000); // подождем 1 мин для прогрева потенцииометра
}

void loop() {
  int positions00[] = {27, 65, 120, 180, 15, 20};
  performAllServos(positions00);

  int positions01[] = {UNDEFINED, 64, UNDEFINED, 131, UNDEFINED, UNDEFINED};
  performAllServos(positions01);
  
  int positions02[] = {UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, 70};
  performAllServos(positions02); 

  int positions03[] = {UNDEFINED, 90, 45, UNDEFINED, UNDEFINED, UNDEFINED};
  performAllServos(positions03);  

  int positions04[] = {142, 0, 102, 0, 0, UNDEFINED};
  performAllServos(positions04);
  
  // бросить шарик
  int positions05[] = {UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, UNDEFINED, 20};
  performAllServos(positions05);

  // подготовка у подъему манипулятора
  int positions06a[] = {UNDEFINED, UNDEFINED, 0, 0, UNDEFINED, UNDEFINED};
  performAllServos(positions06a);

  int positions06[] = {UNDEFINED, 90, 45, 20, UNDEFINED, UNDEFINED};
  performAllServos(positions06);

  delay(3000); 
}
