#define BAUD_RATE 115200

void setup() {
  // the BLE Slave already set up to auto connect to the master.
  Serial.begin(BAUD_RATE);
  Serial1.begin(BAUD_RATE);

  pinMode(6, OUTPUT);

}

void loop() {
  // This if statements that if we get an incoming message write it to the serial monitor of the arduino.
  if (Serial1.available() > 0)
  {
    String c = Serial1.readString();
    Serial.println(c);
    // if c is a certain message utilized to wake up the Keychain from sleep then we wake it up from sleep mode and activate everything
    if (c == "ON" || c == "ONON")
    {
      // make led light up
      digitalWrite(6, HIGH);
      // create speaker tone
      tone(5, 500);
      // vibration?
    }
    // else the keychain will remain in a sleeping state broadcasting a low power
    else if ( c == "OFF" || c == "OFFOFF")
    {
      // turn everything off
      digitalWrite(6, LOW);
      noTone(5);
    }
  }
//  else
//  {
//    // turn everything off
//    digitalWrite(6, LOW);
//    noTone(5);
//  }
  //
  //  This if statement means that if we write something to the serial monitor it'll write to the Serial of the Bluetooth module
  //  if (Serial.available())
  //    Serial1.write(Serial.read());
  //  digitalWrite(5, HIGH);
}
