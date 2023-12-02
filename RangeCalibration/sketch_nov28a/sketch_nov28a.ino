#define PIN_TRIG 10
#define PIN_ECHO 9

long duration, cm;

int min = 0;
int max = 0;
int data_len =0;
double* data;
bool is_showed = false;

void setup() {
  Serial.begin (9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  if (min == 0 || max == 0) {
    Serial.println("Введите диапазон:");
    while (min == 0) {
      if (Serial.available() > 0) {
        min = Serial.parseInt();
      }
    }
    while (max == 0) {
      if (Serial.available() > 0) {
        max = Serial.parseInt();
      }
    }

    data_len = max - min;
    data = new double[data_len];
    for (int i = 0; i < data_len; i++) {
      data[i] = 0;
    }
    
  } else {
    work();
  }
}


void work() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);

  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  duration = pulseIn(PIN_ECHO, HIGH);

  cm = (duration / 2) / 29.1;

  if (check_is_enough()) {
    if (!is_showed) {
      send_message();
      is_showed = true;
    }
  } else {
    if (cm >= min && cm <= max) {
    double val = analogRead(A0);
    val = val * 5.0 / 2046.0;
    data[cm - min] = val;
    
    Serial.print("Расстояние до объекта: ");
    Serial.print(cm);
    Serial.print(" см. ");
    Serial.println(val);
    } else if (cm <= min) {
      Serial.print("Расстояние меньше допустимого диапазона:");
      Serial.println(min);
    } else if (cm >= max){
      Serial.print("Расстояние больше допустимого диапазона:");
      Serial.println(max);
    }
  }

  delay(1000);
}

bool check_is_enough() {
  int last_not_zero = 0;
  double count = 0.0;
  for (int i = 0; i < data_len; i++) {
      if (data[i] != 0) {
        count++;
      } else {
        if (i - last_not_zero >= 2) {
          return false;
        }
        last_not_zero = i;
      }
    }
  return count / (data_len) >= 0.9;
}


void send_message() {
  Serial.println("Build graph");
  Serial.println(data_len);
  for (int i = 0; i < data_len; i++) {
    String stringValue = String(data[i], 3);
    Serial.println(stringValue);
    Serial.println(i + min);
  }
}