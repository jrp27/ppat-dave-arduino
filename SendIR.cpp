#include "Arduino.h"
#include "SendIR.h"

SendIR::SendIR() {
	IRSend irsend(4);
	irsend.begin();
 	Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
}

void SendIR::sendPower() {
	Serial.println("Sent Power");
	irsend.sendSamsung(0xE0E040BF, 32, 2);
	delay(40);
}

void SendIR::sendChannelUp() {
	Serial.println("Sent Channel Up");
	irsend.sendSamsung(0xE0E048B7, 32, 2);
	delay(40);
}

void SendIR::sendChannelDown() {
	Serial.println("Sent Channel Down");
	irsend.sendSamsung(0xE0E008F7, 32, 2);
	delay(40);
}

void SendIR::sendVolumeUp() {
	Serial.println("Sent Volume Up");
	irsend.sendSamsung(0xE0E0E01F, 32, 2);
	delay(40);
}

void SendIR::sendVolumeDown() {
	Serial.println("Sent Volume Down");
	irsend.sendSamsung(0xE0E0D02F, 32, 2);
	delay(40);
}

void SendIR::send1() {
	Serial.println("Sent Channel Number 1");
	irsend.sendSamsung(0xE0E020DF, 32, 1);
	delay(40);
}

void sendIR::send2() {
	Serial.println("Sent Channel Number 2");
	irsend.sendSamsung(0xE0E0A05F, 32, 1);
	delay(40);
}

void sendIR::send3() {
	Serial.println("Sent Channel Number 3");
	irsend.sendSamsung(0xE0E0609F, 32, 1);
	delay(40);
}

void sendIR::send4() {
	Serial.println("Sent Channel Number 4");
	irsend.sendSamsung(0xE0E010EF, 32, 1);
	delay(40);
}

void sendIR::send5() {
	Serial.println("Sent Channel Number 5");
	irsend.sendSamsung(0xE0E0906F, 32, 1);
	delay(40);
}

void sendIR::send6() {
	Serial.println("Sent Channel Number 6");
	irsend.sendSamsung(0xE0E050AF, 32, 1);
	delay(40);
}

void sendIR::send7() {
	Serial.println("Sent Channel Number 7");
	irsend.sendSamsung(0xE0E030CF, 32, 1);
	delay(40);
}

void sendIR::send8() {
	Serial.println("Sent Channel Number 8");
	irsend.sendSamsung(0xE0E0B04F, 32, 1);
	delay(40);
}

void sendIR::send9() {
	Serial.println("Sent Channel Number 9");
	irsend.sendSamsung(0xE0E0708F, 32, 1);
	delay(40);
}

void sendIR::send0() {
	Serial.println("Sent Channel Number 0");
	irsend.sendSamsun(0xE0E08877, 32, 1);
	delay(40);
}