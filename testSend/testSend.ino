#include <Arduino.h>
#include <SendIR.h>

SendIR sendIR;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  SendIR sendIR();
}

void loop() {
  // put your main code here, to run repeatedly:
    sendIR.sendPower();
    Serial.println("Sent Power");
    delay(1000);
    sendIR.sendChannelUp();
    Serial.println("Sent Channel Up");
    delay(1000);
    sendIR.sendChannelDown();
    Serial.println("Sent Channel Down");
    delay(1000);
    sendIR.sendVolumeUp();
    Serial.println("Sent Volume Up");
    delay(1000);
    sendIR.sendVolumeDown();
    Serial.println("Sent Volume Down");
    delay(1000);
    sendIR.send1();
    Serial.println("Sent Channel Number 1");
    delay(1000);
    sendIR.send2();
    Serial.println("Sent Channel Number 2");
    delay(1000);
    sendIR.send3();
    Serial.println("Sent Channel Number 3");
    delay(1000);
    sendIR.send4();
    Serial.println("Sent Channel Number 4");
    delay(1000);
    sendIR.send5();
    Serial.println("Sent Channel Number 5");
    delay(1000);
    sendIR.send6();
    Serial.println("Sent Channel Number 6");
    delay(1000);
    sendIR.send7();
    Serial.println("Sent Channel Number 7");
    delay(1000);
    sendIR.send8();
    Serial.println("Sent Channel Number 8");
    delay(1000);
    sendIR.send9();
    Serial.println("Sent Channel Number 9");
    delay(1000);
    sendIR.send0();
    Serial.println("Sent Channel Number 0");
    delay(1000);
}
