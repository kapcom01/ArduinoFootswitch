#include <MIDIUSB.h>

void setup() {
  Serial.begin(115200);
  pinMode( 4 , INPUT_PULLUP );
  pinMode( 5 , INPUT_PULLUP );
  pinMode( 6 , INPUT_PULLUP );
  pinMode( 7 , INPUT_PULLUP );
  pinMode( 8 , INPUT_PULLUP );
  pinMode( 9 , INPUT_PULLUP );
  pinMode( 10 , INPUT_PULLUP );
  pinMode( 11 , INPUT_PULLUP );

  pinMode(13, OUTPUT);  // LED
  digitalWrite(13, HIGH);
}

// First parameter is the event type (0x0B = control change).
// Second parameter is the event type, combined with the channel.
// Third parameter is the control number number (0-119).
// Fourth parameter is the control value (0-127).

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t packet = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(packet);
}

void programChange(byte channel, byte program) {
  midiEventPacket_t packet = {0x0C, 0xC0 | channel, program, 0};
  MidiUSB.sendMIDI(packet);
}

void change_preset(byte preset){
  controlChange(0, 32, 0);  // channel 0, LSB Bank Select, Bank 0
  programChange(0, preset); // channel 0, Preset preset
  MidiUSB.flush();
}

void loop() {
  if (!digitalRead(4)) change_preset(7);
  if (!digitalRead(5)) change_preset(6);
  if (!digitalRead(6)) change_preset(5);
  if (!digitalRead(7)) change_preset(4);
  if (!digitalRead(8)) change_preset(0);
  if (!digitalRead(9)) change_preset(1);
  if (!digitalRead(10)) change_preset(2);
  if (!digitalRead(11)) change_preset(3);
}