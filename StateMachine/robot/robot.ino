// 4, 7 - for direction
// 5, 6 - for speed
// 0, 1 - нельзя

#define LEFT_WHEEL 4 // HIGH - forward, LOW - back
#define SPEED_LEFT 5

#define RIGHT_WHEEL 7
#define SPEED_RIGHT 6

const int FULL_SPEED = 255;
const int SLOW_SPEED = 100;

int counter = 0;
void setup() {
  for(int i = 4; i<= 7; i++){
    pinMode(i, OUTPUT);
  }
  counter = millis() + 1250;
  Serial.begin(9600);
}

void move(bool lforward, bool rforward, int lvelocity, int rvelocity){
  digitalWrite(RIGHT_WHEEL, rforward); 
  digitalWrite(LEFT_WHEEL, lforward); 
  analogWrite(SPEED_RIGHT, rvelocity);
  analogWrite(SPEED_LEFT, lvelocity);
}

void move_forward(int velocity){
  move(false, true, velocity, velocity);
}

void move_back(int velocity){
  move(true, false, velocity, velocity);
}

void rotate_left(int velocity){
  move(false, false, velocity, velocity);
}

void rotate_right(int velocity){
  move(true, true, velocity, velocity);
}

void turn_right(int lvelocity, int rvelocity){
  move(false, true, lvelocity, rvelocity);
}

void turn_left(int lvelocity, int rvelocity){
  move(false, true, lvelocity, rvelocity);
}

void stop(){
  move(true, true, 0, 0);
}

void loop() {
  if (Serial.available() > 0){
    String command = Serial.readString();
    if (command == "f"){
      move_forward(FULL_SPEED);
    }
    if (command == "b"){
      move_back(FULL_SPEED);
    }
    if (command == "rr"){
      rotate_right(FULL_SPEED);
    }
    if (command == "rl"){
      rotate_left(FULL_SPEED);
    }
    if (command == "tr"){
      turn_right(SLOW_SPEED, FULL_SPEED);
    }
    if (command == "tl"){
      turn_left(FULL_SPEED, SLOW_SPEED);
    }
    if (command == "s"){
      stop();
    }
  }
  delay(50);
}
