#include <ESP8266WebServer.h>

ESP8266WebServer server(WEB_SERVER_PORT);

void handle_root(){
  String page_code = "<form action=\"/LED\" method=\"POST\">";
  page_code += "<input type=\"submit\" value=\"Switch Ted\"></form>";
  server.send(200, "text/html", page_code);
}

void handle_led(){
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  server.sendHeader("Location", "/");
  server.send(303);
}

void handle_sensor(){
  int val = analogRead(A0);
  server.send(200, "text/html", String(val));
}

void handle_not_found(){
  server.send(404, "text/html", "404: check URL");
}

void server_init(){
  server.on("/", HTTP_GET, handle_root);
  server.on("/LED", HTTP_POST, handle_led);
  server.on("/SENSOR", HTTP_GET, handle_sensor);
  server.onNotFound(handle_not_found);

  server.begin();
  Serial.print("Server start on port: ");
  Serial.println(WEB_SERVER_PORT);
}