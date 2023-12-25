#include <Wire.h>

#define PHOTO A0
#define I2C 9
#define LED_PIN 13

int records = 0;
int currentRecord = 0;
int* x;
int* y;
bool isCalibrationStarted = false;
bool showData = false;

long lastTime = 0;
bool state = 1;


void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("Slave");
  Wire.begin(I2C);
  Wire.onReceive(processData);
}

void loop() {
  if (isCalibrationStarted) {
      blinkLed(lastTime, state);
    }

  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 'r') {
      int currentRecord = 0;
      isCalibrationStarted = false;
    }
    if (cmd == 's') {
      showData = showData;
    }
  }

  if (showData) {
    if (records = 0) {
      Serial.print("My calibrated value: ");
      Serial.println(linearInterpolation(analogRead(PHOTO)));
    } else {
      Serial.print("My value: ");
      Serial.println(analogRead(PHOTO));
    }
  }
}

void processData(int length){
  int last_val = 0;
  while (0 < Wire.available()){
    auto result = Wire.read();
    if (result == 'r') {
      records = Wire.read();
      Serial.print("Max records: ");
      Serial.println(records);
      x = new int[records];
      y = new int[records];
    } else if (result == 's') {
      Serial.println("Calibration finished");
      isCalibrationStarted = false;
      digitalWrite(LED_PIN, 1);
      showData = true;
      return;
    } else if (result == 'c') {
      currentRecord = 0;
      isCalibrationStarted = true;
      Serial.println("Calibration started");
    } else {
      if (currentRecord < records && isCalibrationStarted){
        int data = result * 5;
        int currentData = analogRead(PHOTO);
        x[currentRecord] = currentData;
        y[currentRecord] = data;
        currentRecord+=1;
        Serial.println("Calibrating");
       }
    }
  }
}

void blinkLed(long &lastTime, bool &state) {
  long currentTime = millis();
  if (currentTime - lastTime > 100) {
    digitalWrite(LED_PIN, state);
    lastTime = currentTime;
    state = state;
  }
}

float linearInterpolation(int x_new) {
    int i = 0;
    while (i < currentRecord - 1 && x[i + 1] < x_new) {
        i++;
    }
    int x0 = x[i];
    int y0 = y[i];
    int x1 = x[i + 1];
    int y1 = y[i + 1];
    return y0 + (y1 - y0) * (x_new - x0) / (x1 - x0);
}