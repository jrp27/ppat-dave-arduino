#include <Arduino.h>
#include <SendIR.h>

SendIR sendIR();

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
    sendIR.sendPower();
    delay(1000);
    sendIR.sendChannelUp();
    delay(1000);
    sendIR.sendChannelDown();
    delay(1000);
    sendIR.sendVolumeUp();
    delay(1000);
    sendIR.sendVolumeDown();
    delay(1000);
    sendIR.send1();
    delay(1000);
    sendIR.send2();
    delay(1000);
    sendIR.send3();
    delay(1000);
    sendIR.send4();
    delay(1000);
    sendIR.send5();
    delay(1000);
    sendIR.send6();
    delay(1000);
    sendIR.send7();
    delay(1000);
    sendIR.send8();
    delay(1000);
    sendIR.send9();
    delay(1000);
    sendIR.send0();
    delay(1000);
}
