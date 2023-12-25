#include <Wire.h>

#define PHOTO_RES A0
#define SLAVE 9


bool isCalibration = false;
bool isReportSended = false;
bool dataSend = false;
bool showData = false;
bool wasMinValue = false;
bool wasMaxValue = false;

int minValue = -1;
int maxValue = -1;

int previous = -1;
int cntr = 0;
int records = 0;

const int STEP = 10;
const int DIFF = 10;
const int ARCHIVE_FACTOR = 5;


void setup() {
  pinMode(PHOTO_RES, INPUT);
  Serial.begin(9600);
  Serial.println("Master");
  Wire.begin(D1, D2);
}

void loop() {
   if (showData) {
      Serial.print("Value: ");
      Serial.println(analogRead(PHOTO_RES));
    }

  if (Serial.available()) {
    char cmd = Serial.read();

     if (cmd == 's') {
      showData = !showData;
    }

    if (cmd == 'c') {
      Serial.println("Turn off the light. Input 'o' for confirmation");
    }

    if (cmd == 'r'){
      isCalibration = false;
      isReportSended = false;
      dataSend = false;
      minValue = -1;
      maxValue = -1;
      wasMaxValue = false;
      wasMinValue = false;
      previous = -1;
      cntr = 0;
      records=0;
      Serial.println("Calibration has been reset");
    }

    if (cmd == 'o') {
      if (minValue == -1) {
        minValue = analogRead(PHOTO_RES) + DIFF;
        Serial.println("Turn on the light and input 'o' for confirmation");
      } else if (maxValue == -1) {
        maxValue = analogRead(PHOTO_RES) - DIFF;
        isCalibration = true;

        Wire.beginTransmission(SLAVE);
        Wire.write('r');
        records  = (int)((maxValue - minValue + 1) / STEP);
        Wire.write(records);
        Serial.print("Records to do: ");

        Serial.println(records);


        Wire.endTransmission(SLAVE);
        Serial.println(minValue);
        Serial.println(maxValue);
        Serial.println("Calibration started. Turning off the light and slowly add more light every time");
        delay(5000);
      }
    }
  }
  if (isCalibration) {
    Wire.beginTransmission(SLAVE);
    if (!isReportSended) {
      Wire.write("c");
      isReportSended = true;
    }
    if (isReportSended && !dataSend){
      int res = analogRead(PHOTO_RES);
      if (res <= minValue && !wasMinValue) {
        wasMinValue = true;
      }
      if (res >= minValue && !wasMaxValue) {
        wasMaxValue = true;
      }


      if (res - previous >= STEP){
        Serial.print("Value for calibration: ");
        Serial.println(analogRead(PHOTO_RES));
        Wire.write((int)(res / ARCHIVE_FACTOR));
        cntr += 1;
        previous = res;
      }
      Wire.endTransmission(SLAVE);

      if (previous == -1){
        previous = res;
      }
    }
    if (wasMinValue && wasMaxValue && cntr >= records ) {
      isCalibration = false;
      isReportSended = false;
      dataSend = false;

      minValue = -1;
      maxValue = -1;

      Wire.beginTransmission(SLAVE);
      Wire.write('s');
      Wire.endTransmission(SLAVE);
      Serial.println("Finished");
      showData = true;
    }
  }
}

