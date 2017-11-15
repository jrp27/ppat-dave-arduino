#include <ESP8266WiFi.h>
#include <aREST.h>
#include <SendIR.h>

// Creates aREST instance
aREST rest = aREST();

// Creates SendIR instance
SendIR sendIR = SendIR();

// WiFi params
const char* ssid = "StataEECS";//"MIT GUEST";
const char* password = "";

// The port to listen for incoming TCP conections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

const int max_vol = 20;

void setup() {
  Serial.begin(115200);
  delay(10);

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

  for (int x = 0; x < max_vol; x++){
    decreaseVolume("");
  }
  for (int x = 0; x < command.toInt(); x++){
    increaseVolume("");
  }
  // TALK TO TV
  Serial.println("I am a power button look at me powering");
  sendIR.sendPower();
  return 1;
}

