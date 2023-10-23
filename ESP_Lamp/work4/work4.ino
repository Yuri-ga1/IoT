#include "config.h"
#include "wifi.h"
#include "MQTTR.h"
#include "server.h"

void setup(){
  Serial.begin(9600);


  pinMode(LED_BUILTIN, OUTPUT);
  
  
  String c = CONNECT1?"1":"0";
  Serial.println("Wake up " + AP_NAME);
  bool is_Wifi_on = init_WIFI(!CONNECT1);
  if (is_Wifi_on){
    server_init();
  }
  
}


void loop(){
  server.handleClient();
  if(CONNECT1){    
    mqtt_client.loop();
    if (wifiMulti.run() != WL_CONNECTED){
      CONNECT1 = false;      
      Serial.println("Your WiFi died!");
      bool is_Wifi_on = init_WIFI(!CONNECT1);
    }
  }
  delay(20);
}