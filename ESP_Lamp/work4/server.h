#include <ESP8266WebServer.h>

ESP8266WebServer server(WEB_SERVER_PORT);

void handle_root(){
  String page_code = "<form action=\"/LED\" method=\"POST\">"; 
  page_code += "<input type=\"submit\" value=\"Switch Ted\">";
  page_code += "</form>";
  server.send(200, "text/html", page_code);
}


void handle_wifi(){
  String page_code = "<form action=\"/CONNECT\" method=\"POST\">";
  page_code += "Wi-Fi SSID: <input type=\"text\" name=\"ssid\"><br>";
  page_code += "Wi-Fi Password: <input type=\"password\" name=\"password\"><br>";
  page_code += "<input type=\"submit\" value=\"Connect to Wi-Fi\">";
  page_code += "</form>";

  server.send(200, "text/html", page_code);
}

char* foo(const char* ch) {
    return (char*)ch;
}


void handle_connect() {
  String ssid = server.arg("ssid");
  String password = server.arg("password");
  CLI_SSID = foo(ssid.c_str());
  PASS_SSID = foo(password.c_str());
  
  Serial.println("Connect name: " + String(CLI_SSID) + " pass: " + String(PASS_SSID));
  start_client_mode(2);
  if (wifiMulti.run() == WL_CONNECTED) {
    CONNECT1 = true;
    // Успешно подключено к Wi-Fi
    server.send(200, "text/html", "Connected to your Wi-Fi!");
    Serial.println("Conneted your Wi-Fi");

    init_MQTT();
    
    mqtt_client.subscribe(topic.c_str());
    mqtt_client.publish(state_topic.c_str(), "hello");
    Serial.println("See me at " + state_topic);
    
    off_AP_mode();
    
  } else {    
    Serial.println("Didn't connect your Wi-Fi");
    CONNECT1 = false;
    // Ошибка подключения
    server.send(200, "text/html", "Failed to connect to Wi-Fi. Please try again.");
  }
}


void handle_led(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/HANDLE");
  server.send(303);
}


void handle_hand_led(){
    (LED_BUILTIN, !digitalRead(LED_BUILTIN));
  
  server.send(200, "text/html", String(digitalRead(LED_BUILTIN)));
}


void handle_sensor(){
  int val = analogRead(A0);
  server.send(200, "text/html", String(val));
}

void handle_not_found(){
  server.send(404, "text/html", "404: check URL");
}

void server_init(){
  server.on("/", HTTP_GET, handle_wifi);
  server.on("/LED", HTTP_POST, handle_led);
  server.on("/LED_H", HTTP_GET, handle_hand_led);
  server.on("/SENSOR", HTTP_GET, handle_sensor);
  server.on("/HANDLE", HTTP_GET, handle_root);
  server.on("/CONNECT", HTTP_POST, handle_connect);


  server.onNotFound(handle_not_found);

  server.begin();
  Serial.println("Server start on port: ");
  Serial.println(WEB_SERVER_PORT);
}