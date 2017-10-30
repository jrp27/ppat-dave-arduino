#ifndef SendIR_h
#define SENDIR_h

#include "Arduino.h"

class SendIR {
public:
	SendIR();
	void sendPower();
	void sendChannelUp();
	void sendChannelDown();
	void sendVolumeUp();
	void sendVolumeDown();
	void send1();
	void send2();
	void send3();
	void send4();
	void send5();
	void send6();
	void send7();
	void send8();
	void send9();
	void send0();
private:
	IRSend irsend(4);
}

#endif