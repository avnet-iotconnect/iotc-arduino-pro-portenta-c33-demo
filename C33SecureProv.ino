#include <WiFiC3.h>
#include <ESP_SSLClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <MqttClient.h>
#include <ArduinoJson.h>
#include <TimeLib.h>
#include <time.h>
#include "arduino_secrets.h"
#include <Arduino_ConnectionHandler.h>
#include <arduino-timer.h>

WiFiConnectionHandler conMgr(SECRET_SSID, SECRET_PASS);

StaticJsonDocument<200> doc;

auto timer = timer_create_default(); // create a timer with default settings

// NTP Time 
WiFiUDP NTPUdp;
NTPClient timeClient(NTPUdp,"pool.ntp.org");
             
// Clients
ESP_SSLClient ssl_client;
WiFiClient wfi_client;
MqttClient mq_client(ssl_client);

void setup() {
  Serial.begin(115200);
  while(!Serial) {
    delay(1000);
  }

  pinMode(LED_BUILTIN, OUTPUT); // set LED pin to OUTPUT
  timer.every(60000, publishData);  

  // Init SSL with certificates and keys
  ssl_client.setCACert(SECRET_ROOTCERT);
  ssl_client.setCertificate(SECRET_DEVCERT);
  ssl_client.setPrivateKey(SECRET_PRIKEY);
  ssl_client.setDebugLevel(1);  // 0=none; 1=error; 2=warn; 3=info; 4=dump
  ssl_client.setClient(&wfi_client);
  
  // Init MQTT client
  mq_client.setId(SECRET_CLIENT_ID);
  mq_client.onMessage(onMQTTMessage);

  // Connection Manager callbacks
  conMgr.addCallback(NetworkConnectionEvent::CONNECTED, onNetworkConnect);
  conMgr.addCallback(NetworkConnectionEvent::DISCONNECTED, onNetworkDisconnect);
  conMgr.addCallback(NetworkConnectionEvent::ERROR, onNetworkError);
  
  // JSON Payload formatting
  // Refer to the IoTConnect D2C documentation for formatting 
  JsonObject data = doc["d"][0].createNestedObject("d");      
  data["Temperature"] = 0;
  data["text"] = "HELLO FROM C33!!";
  serializeJson(doc, msg_buffer);                                                      
   
}


void loop() {
  mq_client.poll();
  timer.tick(); 
  const auto conStatus = conMgr.check();

  if (conStatus == NetworkConnectionState::CONNECTED){
    timeClient.update();
    if (!mq_client.connected()) {    // MQTT client is disconnected, set validation time & connect
      Serial.println("Setting X509 time");
      ssl_client.setX509Time(timeClient.getEpochTime());
      connectMQTT();
    }
  }
  else{
    // Serial.println("NetworkConnectionState not Connected");
    ;
  }

}

 // =================== Networking Handlers ======================================

void onNetworkConnect() {
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  Serial.println();
  timeClient.begin();
}


void onNetworkDisconnect(){
  Serial.println(">>>> DISCONNECTED from network <<<<<");
}


void onNetworkError(){
   Serial.println(">>>> NETWORK ERROR <<<<");
}

 // =================== MQTT Handlers ======================================

void connectMQTT(){
  while (!mq_client.connect(SECRET_BROKER, 8883)) {
      //Serial.print(".");
      Serial.println(mq_client.connectError());
  }
  Serial.println(" MQTT connected!");

  // subscribe topic
  mq_client.subscribe(SECRET_CMD_TOPIC);
}


void onMQTTMessage(int messageSize){
   // we received a message, print out the topic and contents
  Serial.print("Received ");
  Serial.print(messageSize);
  Serial.print(" bytes from topic: ");
  Serial.print(mq_client.messageTopic());
  Serial.print(" and payload:  '");
  while (mq_client.available()) {
    Serial.print((char)mq_client.read());
  }
  Serial.println();
}


bool publishData(void *) {
  if(mq_client.connected()) {
    // Post data to IoTCOnnect
    Serial.print("Posting msg to topic: ");
    doc["d"][0]["d"]["Temperature"] = random(1, 212);
    doc["d"][0]["d"]["text"] = timeClient.getFormattedTime();
    mq_client.beginMessage(SECRET_TOPIC);
    serializeJson(doc, mq_client);
    mq_client.endMessage();
    return true;
 }
 else
  return false;
}


bool toggle_led(void *) {
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // toggle the LED
  return true; // repeat? true
}
