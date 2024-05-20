int ledpins[] = {3, 5, 6, 9};
int groundpins[] = {12, 13};
int delaytime = 10;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(ledpins[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(groundpins[i], OUTPUT);
  }
}

void loop() {
  twist();
  diagonal();
}

void applyState(const int state[2][4]) {
  for (int k=0; k<10; k++){
    for (int i = 0; i < 2; i++) {
      digitalWrite(groundpins[i], HIGH);
      for (int j = 0; j < 4; j++) {
        digitalWrite(ledpins[j], state[i][j]);
      }
      delay(delaytime);
      digitalWrite(groundpins[i], LOW);
      for (int j = 0; j < 4; j++) {
        digitalWrite(ledpins[j], LOW);
      }
    }
  }
}

void diagonal() {
  int diagonalStates[][2][4] = {
    {{LOW, HIGH, HIGH, HIGH}, {HIGH, HIGH, LOW, HIGH}},
    {{HIGH, LOW, HIGH, HIGH}, {HIGH, HIGH, HIGH, LOW}},
    {{HIGH, HIGH, LOW, HIGH}, {LOW, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, LOW}, {HIGH, LOW, HIGH, HIGH}},
    {{LOW, HIGH, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, LOW, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, LOW, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, HIGH, LOW}},
    {{HIGH, LOW, HIGH, LOW}, {HIGH, LOW, HIGH, LOW}},
    {{LOW, HIGH, LOW, HIGH}, {LOW, HIGH, LOW, HIGH}}
  };

  for (int i = 0; i < 10; i++) {
    applyState(diagonalStates[i]);
  }
}

void twist() {
  int twistStates[][2][4] = {
    {{LOW, HIGH, HIGH, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, LOW, HIGH, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, HIGH, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, LOW, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, LOW, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, HIGH, LOW}},
    
    {{HIGH, LOW, HIGH, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, LOW, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, LOW, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, LOW, HIGH, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, LOW, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, HIGH, LOW}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, LOW, HIGH, HIGH}},
    
    {{HIGH, HIGH, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, LOW, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, HIGH, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, LOW, LOW, HIGH}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, HIGH, LOW, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, HIGH, LOW, LOW}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, LOW, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, LOW, HIGH}},
    
    {{HIGH, HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{LOW, HIGH, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, LOW, HIGH, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, LOW, LOW}, {HIGH, HIGH, HIGH, HIGH}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, HIGH, HIGH, LOW}},
    {{HIGH, HIGH, HIGH, HIGH}, {LOW, HIGH, HIGH, LOW}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, LOW, HIGH, LOW}},
    {{HIGH, HIGH, HIGH, HIGH}, {HIGH, HIGH, LOW, LOW}},
  };

  for (int i = 0; i < 32; i++) {
    applyState(twistStates[i]);
  }
}
