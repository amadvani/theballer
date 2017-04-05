#include <Stepper.h>

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;

const int buzzer = 13;

const int hall_effect = A0;

const int steps = 200;
const int speed = 100;

const int stage_time = 5;

int buzzer_countdown = stage_time;

unsigned long buzzer_time = millis();
unsigned long countdown_timer = 0;
unsigned long motor_time = 0;
unsigned long currentMillis = 0;

bool buzz = false;
bool exec_stage = false;
bool run = false;

int motor_stage = 0;
int time_stage = 0;

Stepper motor(steps, 9, 11, 10, 12);

const int digit_patterns[10][7] = {
// A  B  C  D  E  F  G
  {1, 1, 1, 1, 1, 1, 0}, //0
  {0, 1, 1, 0, 0, 0, 0}, //1
  {1, 1, 0, 1, 1, 0, 1}, //2
  {1, 1, 1, 1, 0, 0, 1}, //3
  {0, 1, 1, 0, 0, 1, 1}, //4
  {1, 0, 1, 1, 0, 1, 1}, //5
  {1, 0, 1, 1, 1, 1, 1}, //6
  {1, 1, 1, 0, 0, 0, 0}, //7
  {1, 1, 1, 1, 1, 1, 1}, //8
  {1, 1, 1, 0, 0, 1, 1}, //9
};


void setup() {

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(buzzer, OUTPUT);

  pinMode(hall_effect, INPUT);
  
  motor.setSpeed(speed);

  display_digit(buzzer_countdown);

}

void display_digit(byte digit){

  if(digit > 9)
    return;
    
  for(int i = 0; i < 7; ++i){
    digitalWrite(A+i, digit_patterns[digit][i]);
  }
  
}

void loop() {

  if(analogRead(hall_effect) < 1000){
    run = true;
  }
  if(run == true){
    currentMillis = millis();

    if(buzz && currentMillis - buzzer_time < 1000){
    digitalWrite(buzzer, HIGH);
    delay(2);
    digitalWrite(buzzer, LOW);
    delay(2);
    }else if(buzz){
    buzz = false;
    buzzer_time = currentMillis;
    }

    if(motor_stage < 2){

    if(currentMillis - countdown_timer >= 1000){
      display_digit(--buzzer_countdown);
      countdown_timer = currentMillis;
    }

    if(buzzer_countdown == 0){
      time_stage++;
      exec_stage = true;
      buzz = true;
      buzzer_time = currentMillis;
      motor_time = currentMillis;
      if(time_stage < 2)buzzer_countdown=stage_time;
      else buzzer_countdown = 0;
      display_digit(buzzer_countdown);
    }

    if(motor_stage == 0){
        if(exec_stage && currentMillis - motor_time < 1000){
          motor.step(-steps / 100);
        }else if (exec_stage && currentMillis - motor_time < 1600){
          motor.step(steps / 100);
        }else if(exec_stage){
          motor_time = currentMillis;
          exec_stage = false;
          motor_stage++;
        }
      }else if(motor_stage == 1){
        if(exec_stage && currentMillis - motor_time < 1000){
          motor.step(steps / 100);
        }else if (exec_stage && currentMillis - motor_time < 1600){
          motor.step(-steps / 100);
        }else if(exec_stage){
          motor_time = currentMillis;
          exec_stage = false;
          motor_stage++;
        }
     }
    }
  }
  
  
}
