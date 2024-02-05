#define OUTPUT_PIN8 5
#define OUTPUT_PIN9 4
#define INPUT_PIN10 2
#define INPUT_PIN11 3

int pins[] = {OUTPUT_PIN8, OUTPUT_PIN9};
int pressed_buttons[] = {0, 0, 0, 0};
bool states[] ={1, 0};

void setup()
{
  Serial.begin(9600);
  
  pinMode(OUTPUT_PIN8, OUTPUT);
  pinMode(OUTPUT_PIN9, OUTPUT);
  pinMode(INPUT_PIN10, INPUT_PULLUP);
  pinMode(INPUT_PIN11, INPUT_PULLUP);
}

void loop(){
  for (int i=0; i<2; i++){
  	digitalWrite(pins[i], states[i]);
  }
  check_buttons();
  
  for (int i=0; i<2; i++){
  	digitalWrite(pins[i], !states[i]);
  }
  check_buttons();
  delay(500);
  print_pressed_buttons();
}

void check_buttons(){
  int pin8_value = digitalRead(OUTPUT_PIN8);
  
  int pin10_value = digitalRead(INPUT_PIN10);
  int pin11_value = digitalRead(INPUT_PIN11);
    
  if (pin10_value == LOW){
    if(pin8_value == HIGH){
      pressed_buttons[2] = 1;
      // Serial.println("Button 3 pressed");
    }
    else{
      pressed_buttons[0] = 1;
      // Serial.println("Button 1 pressed");
    }
  }
       
  if (pin11_value == LOW){
    if(pin8_value == HIGH){
      pressed_buttons[3] = 1;
      // Serial.println("Button 4 pressed");
    }
    else{
      pressed_buttons[1] = 1;
      // Serial.println("Button 2 pressed");
    }
  }
}

void print_pressed_buttons(){
  Serial.println("Pressed buttons");
  for (int i =0; i<4; i++){
    Serial.print(pressed_buttons[i]);
    pressed_buttons[i] = 0;
  	Serial.print(" ");
  }
  Serial.println("");
}