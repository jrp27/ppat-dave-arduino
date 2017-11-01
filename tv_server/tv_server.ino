#include <ESP8266WiFi.h>
#include <aREST.h>

//#define LIGHTWEIGHT 1

// Creates aREST instance
aREST rest = aREST();

// WiFi params
const char* ssid = "MIT GUEST";
const char* password = "";

// The port to listen for incoming TCP conections
#define LISTEN_PORT 80

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Sets up restful API stuff

  //rest.set_id("123456");
  //rest.set_name("esp8266");

  // Sets the API routes

  // Volume
  rest.function("volume/up", increaseVolume);
  rest.function("volume/down", decreaseVolume);

  // Channel
  rest.function("channel/set", setChannel);
  rest.function("channel/up", increaseChannel);
  rest.function("channel/down", increaseChannel);

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

// Increases volume
int increaseVolume(String command){

  // Gets the value from command
  int volume = command.toInt();

  // TALK TO TV
  
  return 1;
}

// Decreases volume
int decreaseVolume(String command){

  // Gets the value from command
  int volume = command.toInt();

  // TALK TO TV
  
  return 1;
}

// Sets the channel to a specific channel
int setChannel(String command) {
  
  // Gets the value from command
  int channel = command.toInt();

  // TALK TO TV
  
  return 1;
}

// Scrolls up in channel
int increaseChannel(String command) {

  // Gets the value from command
  int displacement = command.toInt();

  // TALK TO TV

  return 1;
}

// Scrolls down in channel
int decreaseChannel(String command) {

  // Gets the value from command
  int displacement = command.toInt();

  // TALK TO TV

  return 1;
}

// Powers button for TV
int power(String command) {

  // TALK TO TV

  return 1;
}

