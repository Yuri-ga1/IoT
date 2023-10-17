#include "config.h"
#include "WiFi.h"
#include "server.h"
#include "MQTT.h"

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  // bool is_wifi_on = start_AP_mode();
  bool is_wifi_on = init_WIFI(false);
  if (is_wifi_on){
    server_init();
    init_MQTT();
  }
  String topic = "Now_I_decide_the_name_myself/command";
  String state_topic = "Now_I_decide_the_name_myself/state";
  mqtt_client.subscribe(topic.c_str());
  mqtt_client.publish(state_topic.c_str(), "hello");
  Serial.println("See me at " + state_topic);
}

void loop() {
  server.handleClient();
  mqtt_client.loop();
  delay(20);
}