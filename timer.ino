int A = 2;
int B = 3;
int C = 4;
int D = 5;
int E = 6;
int F = 7;
int G = 8;

int buzzer = 12;

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

  Serial.begin(9600);

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);

  pinMode(buzzer, OUTPUT);

}

void display_digit(byte digit){

  if(digit > 9)
    return;
    
  for(int j = 0; j < 7; ++j){
    if(digit_patterns[digit][j]) digitalWrite(A+j, HIGH);
    else digitalWrite(A+j, LOW);
  }
  
}

void loop() {

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
  

}
