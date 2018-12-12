# ManipulatorMain
First project with manipulator ROT3U-6DOF
https://docs.google.com/document/d/1qjbA3oT6aTBYPyMYkEbxOjEk_vtlbl5B4ba-AkSgM2k/edit#heading=h.yepd27gc8s1h

Проект включает в себя следующие модули:
# ROT3U6DOF.h	- основные функции для управления манипулятором
функция setupROT3U6DOF - предназначена для инициализации портов ардуино
Функция resetROT3U6DOF - устанавливает манипулятор в исходное положение.
Исходное положение определяется константами
STARTPOS_SERVO1_DEG, STARTPOS_SERVO2_DEG ...
Для управления манипулятором используются следующие функции:
performAllImmediately(int newPositions[ROT3U6DOF_SERVO_COUNT]) - перемещает все сервоприводы в указанное положение с максимально возможной скоростью.
performServoImmediately(int servoIndex, int newPosition) - перемещает указанный сервопривод с максимально возможной скоростью.
performAllServos - Плавное перемещение всех сервоприводов. Если положение сервопривода менять не нужно, то в качестве передаваемого значения можно передать UNDEFINED (-1).

SGServo - обертка для управления сервоприводом.
ManipulatorMain.ino - основная программа микроконтроллера.
