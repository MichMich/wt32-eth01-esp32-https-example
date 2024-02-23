#include <Arduino.h>
#include <ETH.h>
#include <PsychicHttp.h>
#include <PsychicHttpsServer.h>
#include "cert.h"
#include "key.h"

PsychicHttpsServer server;

/**
 * Handles the incoming request
*/
esp_err_t handleRequest(PsychicRequest *request) {
  Serial.println("New request received!");
  return request->reply("Hello World!");
}

/**
 * Connects to the Ethernet network
*/
void connectEthernet() {
  ETH.begin();
  ETH.setHostname("esp32");

  while (ETH.linkUp() != 1) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Ethernet connected!");
}

/**
 * Setup function
*/
void setup() {
  Serial.begin(115200);
  connectEthernet();
  
  server.listen(443, SERVER_CERT, SERVER_KEY);

  server.on("/", HTTP_GET, handleRequest);
  Serial.println("HTTPS server started.");
}

/**
 * Loop function
*/
void loop() {
  Serial.print("Waiting on requests on: ");
  Serial.println(ETH.localIP());
  delay(1000);
}
