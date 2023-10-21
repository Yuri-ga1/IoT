void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0) {
    char cmd = Serial.read();
    if (cmd == 'u') {// u for up/on
      digitalWrite(LED_BUILTIN, 0); // use LOW on esp
      Serial.print("led on");
    } 
    if (cmd == 'd') { // d for down/off
      digitalWrite(LED_BUILTIN, 1);
      Serial.print("led off");
    }
  }
}