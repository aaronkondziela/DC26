// Set your message here! _x, space(), eol()
#define _MESSAGE _R _E _S _I _S _T

const uint8_t outpin = PB0;
const uint8_t dotlen = 192; // divisible by rampstep
const uint8_t rampstep = 16; // power of 2
const uint8_t ramplen = dotlen / rampstep / 2;

// Digital output for clean on/off action
//#define _DIGITAL_OUTPUT
// PWM output for smoothed pulses and noisy signal
#define _PWM_OUTPUT

// Morse Code table
// For short messages this is more space-efficient than some kind
// of lookup table and dispatch system. ATtiny13 only has 1k!
#define _A dot();dash();ch();
#define _B dash();dot();dot();dot();ch();
#define _C dash();dot();dash();dot();ch();
#define _D dash();dot();dot();ch();
#define _E dot();ch();
#define _F dot();dot();dash();dot();ch();
#define _G dash();dash();dot();ch();
#define _H dot();dot();dot();dot();ch();
#define _I dot();dot();ch();
#define _J dot();dash();dash();dash();ch();
#define _K dash();dot();dash();ch();
#define _L dot();dash();dot();dot();ch();
#define _M dash();dash();ch();
#define _N dash();dot();ch();
#define _O dash();dash();dash();ch();
#define _P dot();dash();dash();dot();ch();
#define _Q dash();dash();dot();dash();ch();
#define _R dot();dash();dot();ch();
#define _S dot();dot();dot();ch();
#define _T dash();ch();
#define _U dot();dot();ch();
#define _V dot();dot();dot();dash();ch();
#define _W dot();dash();dash();ch();
#define _X dash();dot();dot();dash();ch();
#define _Y dash();dot();dash();dash();ch();
#define _Z dash();dash();dot();dot();ch();

#define _1 dot();dash();dash();dash();dash();ch();
#define _2 dot();dot();dash();dash();dash();ch();
#define _3 dot();dot();dot();dash();dash();ch();
#define _4 dot();dot();dot();dot();dash();ch();
#define _5 dot();dot();dot();dot();dot();ch();
#define _6 dash();dot();dot();dot();dot();ch();
#define _7 dash();dash();dot();dot();dot();ch();
#define _8 dash();dash();dash();dot();dot();ch();
#define _9 dash();dash();dash();dash();dot();ch();
#define _0 dash();dash();dash();dash();dash();ch();

void setup() {
  pinMode(outpin, OUTPUT);
}

void loop() {
  _MESSAGE eol();
}

void dot() {
#ifdef _DIGITAL_OUTPUT
  digitalWrite(outpin, HIGH); delay(dotlen);
  digitalWrite(outpin, LOW); delay(dotlen);
#endif
#ifdef _PWM_OUTPUT
  uint8_t i;
  for(i = (256-rampstep); i -= rampstep; i > 0) {
    analogWrite(outpin, 255 - i); delay(ramplen);
  }
  analogWrite(outpin, 254); delay(ramplen * (240/rampstep/2) );
  for(i = (256-rampstep); i -= rampstep; i > 0) {
    analogWrite(outpin, i); delay(ramplen);
  }
  analogWrite(outpin, 0); delay(dotlen);
#endif
}

void dash() {
#ifdef _DIGITAL_OUTPUT
  digitalWrite(outpin, HIGH); delay(dotlen * 3);
  digitalWrite(outpin, LOW); delay(dotlen);
#endif
#ifdef _PWM_OUTPUT
  uint8_t i;
  for(i = 240; i -= rampstep; i > 0) {
    analogWrite(outpin, 255 - i); delay(ramplen);
  }
  analogWrite(outpin, 254); delay(ramplen * (240/rampstep) * 3);
  for(i = 240; i -= rampstep; i > 0) {
    analogWrite(outpin, i); delay(ramplen);
  }
  analogWrite(outpin, 0); delay(dotlen);
#endif
}

void ch() {
  delay(dotlen * 2);
}

void space() {
  delay(dotlen * 6);
}

void eol() {
  delay(dotlen * 8);
}


