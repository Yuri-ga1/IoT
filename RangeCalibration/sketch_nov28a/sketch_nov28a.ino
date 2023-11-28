#define PIN_TRIG 10 
#define PIN_ECHO 9

const int PIN_SHARP = A0; 

long duration, cm;
float v;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

}

void loop() {
  echolocator();
  sharpSignal();
}

void sharpSignal(){
  int sensor_val = analogRead(PIN_SHARP);
  Serial.println(sensor_val);

  // Convert the analog value to distance DEPENDS ON SENSOR
  v = sensor_val*0.0048828125;
  float distance = 29.988 * pow(v, -1.173);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}

void echolocator(){
  // t - отправкa
  // r - прием

  // Создаем короткий импульс длительностью 2 микросекунды
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);

  // Ставим HIGH, ждем около 8-10 микросекунд. В этот момент датчик будет посылать сигналы с частотой 40 КГц
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  //  Время задержки сигнала
  duration = pulseIn(PIN_ECHO, HIGH);
  cm = (duration / 2) / 29.1;

  Serial.print("Расстояние до объекта: ");
  Serial.print(cm);
  Serial.println(" см.");

  delay(250);
}