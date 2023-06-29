#include <Joystick.h>

// Button_count, HatSwitch count, X-Axis, Y-Axis, Z-Axis, R(X-Axis), R(Y-Axis), R(Z-Axis), Rudder, Throttle, Accelerator, Brake, Steering
Joystick_ Joystick(0x04, JOYSTICK_TYPE_JOYSTICK, 27, 0, false, false, false, false, false, false, false, false, false, false, false);

const bool initAutoSendState = true;

void setup() {
  for(int i = 0; i < 13; i++){
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  Joystick.begin();
}

void loop() {
  avionics(0 , 1, 0, 1);
  Joystick.setButton(2, !digitalRead(2));
  Joystick.setButton(3, digitalRead(2));
  
  Joystick.setButton(4, !digitalRead(3));
  Joystick.setButton(5, digitalRead(3));
  
  Joystick.setButton(6, !digitalRead(4));
  Joystick.setButton(7, digitalRead(4));
  
  Joystick.setButton(8, !digitalRead(5));
  Joystick.setButton(9, digitalRead(5));

  Joystick.setButton(10, !digitalRead(6));
  Joystick.setButton(11, digitalRead(6));
  
  Joystick.setButton(12, !digitalRead(7));
  Joystick.setButton(13, digitalRead(7));

  Joystick.setButton(14, !digitalRead(8));
  Joystick.setButton(15, digitalRead(8));

  Joystick.setButton(16, !digitalRead(9));
  Joystick.setButton(17, digitalRead(9));
  
  Joystick.setButton(18, !digitalRead(10));
  Joystick.setButton(19, digitalRead(10));

  Joystick.setButton(20, !digitalRead(A0));
  Joystick.setButton(21, !digitalRead(A1));
  Joystick.setButton(22, !digitalRead(A2));
  Joystick.setButton(23, !digitalRead(A3));
  Joystick.setButton(24, !digitalRead(A4));
}

void avionics(int pin1, int pin2, int button1, int button2){
  if (!digitalRead(0) == 0 && !digitalRead(1) == 0){
    Joystick.setButton(button1, 1);
    Joystick.setButton(button2, 0);
  }
  else{
    Joystick.setButton(button1, 0);
    Joystick.setButton(button2, 1);
  }
}
