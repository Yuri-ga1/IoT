#include <PubSubClient.h>

PubSubClient mqtt_client(wifiClient);

void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("There is message in topic: ");
  Serial.println(topic);
  Serial.println("Message is: ");
  for (int i=0; i<length; i++){
    Serial.print((char) payload[i]);
  }
  Serial.println("");
}

bool init_MQTT(){
  mqtt_client.setServer(mqtt_broker, mqtt_port); //connect to broker
  mqtt_client.setCallback(callback);
  while (!mqtt_client.connected()){
    String client_id = "Now_I_decide_the_name_myself"; //"esp8266_" + id();
    if (mqtt_client.connect(client_id.c_str())){
      Serial.println("MQTT client is connected");
    } else {
      Serial.println("Failed to connect MQTT");
      delay(500);
    }
  }
  return true;
}