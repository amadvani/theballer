#include <Stepper.h>

const int button1 = 0;
const int button2 = 0;

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
const int G = 8;

const int buzzer = 13;

const int steps = 200;
const int speed = 100;

int stage = 0;

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

  //Serial.begin(9600);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(buzzer, OUTPUT);
  
  motor.setSpeed(speed);

}

void display_digit(byte digit){

  if(digit > 9)
    return;
    
  for(int i = 0; i < 7; ++i){
    digitalWrite(A+i, digit_patterns[digit][i]);
  }
  
}

void loop() {

  if(stage < 2){

   for(int i = 5; i >= 0; --i){
     display_digit(i);
     Serial.println(i);
     delay(1000);
   }

   for(int j = 0; j <= 250; j++){
     digitalWrite(buzzer, HIGH);
     delay(2);
     digitalWrite(buzzer, LOW);
     delay(2);
   }

  if(stage == 0){
    for(int k = 0; k <= 300; ++k){
        motor.step(-steps / 100);
      }
  
      for(int l = 0; l <= 300; ++l){
        motor.step(steps / 100);
      }
      stage++;
    }else if(stage == 1){
      for(int k = 0; k <= 300; ++k){
          motor.step(steps / 100);
        }
  
      for(int l = 0; l <= 300; ++l){
          motor.step(-steps / 100);
        }
      stage++;
    }
  }
  
}
