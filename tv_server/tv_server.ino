#include <ESP8266WiFi.h>
#include <aREST.h>
#include <SendIR.h>
#include "Gsender.h"
#include <EEPROM.h>

// Creates aREST instance
aREST rest = aREST();

// Creates SendIR instance
SendIR sendIR = SendIR();

// WiFi params
const char* ssid = "TBH";
const char* password = "hope today and tomorrow";

// The port to listen for incoming TCP conections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Email body
const char* email_body = "!\n This is an automated message. Do Not Reply.";
//const char* update_email_body = "You are subscribed to receive emails from PPAT arduino!\n This is an automated message. Do Not Reply.";

// Params
const int max_email_size = 30;
const int max_ip_size = 15;
const int max_vol = 20;

void setup() {
  Serial.begin(115200);
  delay(10);

  EEPROM.begin(max_email_size+max_ip_size);
  // Sets the API routes

  // Volume
  rest.function("volume", setVolume);
  rest.function("volumeup", increaseVolume);
  rest.function("volumedown", decreaseVolume);

  // Channel
  rest.function("channel", setChannel);
  rest.function("channelup", increaseChannel);
  rest.function("channeldown", increaseChannel);

  // Power
  rest.function("power", power);

  // Update Email
  rest.function("email", updateEmail);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server startered");

  // Print IP Address
  Serial.print("Communicate with server at: ");
  Serial.print(WiFi.localIP());
  Serial.println("/");

  String oldIp = getIpAddress();
  if (WiFi.localIP().toString() != oldIp){
    Serial.println("IP needs to be updated");
    updateIpAddress(WiFi.localIP().toString());
    sendEmail("IP Address Updated",WiFi.localIP().toString()+email_body);
  } else {
    Serial.println("IP address is the most recent");
  } 
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();
  
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

void error(char* err) {
  Serial.println(err);
}

// Sets volume
int setVolume(String command) {

  Serial.println("Setting volume");
  Serial.println(command);
  int index_bracket_1 = command.indexOf("[");
  int index_bracket_2 = command.indexOf("]");
  int index_comma = command.indexOf(",");
  int initial_volume = command.substring(index_bracket_1+1,index_comma).toInt();
  int new_volume = command.substring(index_comma+1,index_bracket_2).toInt();
  if (initial_volume - new_volume < 0) {
    for (int i = 0; i < (-initial_volume + new_volume); i++) {
      increaseVolume("");
    }
  } else {
    for (int i = 0; i < initial_volume - new_volume; i++) {
      decreaseVolume("");
    }
  }
  return 1;
}
// Increases volume
int increaseVolume(String command){

  // TALK TO TV
  Serial.println("Increase volume");
  sendIR.sendVolumeUp();
  return 1;
}

// Decreases volume
int decreaseVolume(String command){

  // TALK TO TV
  sendIR.sendVolumeDown();
  Serial.println("Decrease volume");
  return 1;
}

// Sets the channel to a specific channel
int setChannel(String command) {
  // TALK TO TV
  for (int x = 0; x < command.length(); x++){
    Serial.println(command[x]);
    switch(command[x]) {
      case '0':
        sendIR.send0();
        break;
      case '1':
        sendIR.send1();
        break;
      case '2':
        sendIR.send2();
        break;
      case '3':
        sendIR.send3();
        break;
      case '4':
        sendIR.send4();
        break;
      case '5':
        sendIR.send5();
        break;
      case '6':
        sendIR.send6();
        break;
      case '7':
        sendIR.send7();
        break;
      case '8':
        sendIR.send8();
        break;
      case '9':
        sendIR.send9();
        break;
      default:
        break;
    }
    delay(250);
  }
  return 1;
}

// Scrolls up in channel
int increaseChannel(String command) {

  // TALK TO TV
  sendIR.sendChannelUp();
  Serial.println("Increase channel");
  return 1;
}

// Scrolls down in channel
int decreaseChannel(String command) {

  // TALK TO TV
  sendIR.sendChannelDown();
  Serial.println("Decrease channel");
  return 1;
}

// Powers button for TV
int power(String command) {

  // TALK TO TV
  Serial.println("I am a power button look at me powering");
  sendIR.sendPower();

  delay(500);
  
  for (int x = 0; x < max_vol; x++){
    decreaseVolume("");
    delay(100);
  }
  for (int x = 0; x < command.toInt(); x++){
    increaseVolume("");
    delay(100);
  }
  return 1;
}

String getIpAddress() {
  String data = "";
  for (int i = max_email_size; i < max_email_size + max_ip_size; i++){
    char value = char(EEPROM.read(i));
    if (int(value) == 0) {
      break;
    } else {
      data += value;
    }
    delay(250);
  }
  return data;
}

void updateIpAddress(String ip) {
  clearIpAddress();
  for (int i = 0; i < ip.length(); i++){
    byte val = ip[i];
    EEPROM.write(i+max_email_size, val);
    delay(200);
  }
  EEPROM.commit();
}

void clearIpAddress(){
  for (int i = max_email_size; i < max_email_size + max_ip_size; i++)
    EEPROM.write(i, 0);
  EEPROM.commit();
}

String getEmail() {
  String data = "";
  for (int i = 0; i < max_email_size; i++){
    char value = char(EEPROM.read(i));
    if (int(value) == 0) {
      break;
    } else {
      data += value;
    }
    delay(250);
  }
  return data;
}

int updateEmail(String command) {
  String body = "You will now receive messages everytime IP address changes."+String(email_body);
  if (sendEmail("Subscribed to TV IP Tracker", body)) {
    clearEmail();
    for (int i = 0; i < command.length(); i++){
      byte val = command[i];
      EEPROM.write(i, val);
      delay(100);
    }
    EEPROM.commit();
  } else {
    body = "Invalid email "+command+ ". Please input a valid email." + email_body;
    sendEmail("Email Update Failed", body);
  }
  return 1;
}

void clearEmail() {
  for (int i = 0; i < max_email_size; i++)
    EEPROM.write(i, 0);
  EEPROM.commit();
}

bool sendEmail(String subject, String body) {
  Gsender *gsender = Gsender::Instance();
  if(gsender->Subject(subject)->Send(getEmail(), body)) {
        Serial.println("Email successfully sent.");
        return true;
  } else {
      Serial.print("Error sending message: ");
      Serial.println(gsender->getError());
      return false;
  }
}

