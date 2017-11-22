#define BAUD_RATE 115200

void setup() {
  // the BLE Slave already set up to auto connect to the master.
  Serial.begin(BAUD_RATE);
  Serial1.begin(BAUD_RATE);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}

void loop() {
  // This if statements that if we get an incoming message write it to the serial monitor of the arduino.
  if (Serial1.available() > 0)
  {
    auto c = Serial1.readString();
    Serial.println(c);
    // if c is a certain message utilized to wake up the Keychain from sleep then we wake it up from sleep mode and activate everything
    if (c == "ON")
    {
      // make led light up
      digitalWrite(6, HIGH);
      // create speaker tone
      tone(5, 500);
      // vibration
      digitalWrite(7, HIGH);
    }
    else if ( c == "OFF")
    {
            // make led light up
      digitalWrite(6, LOW);
      // create speaker tone
      tone(5, 0);
      // vibration
      digitalWrite(7, LOW);
    }
      
  }
  // uncomment to see what's being sent to the keychain
//  if (Serial.available())
//    Serial1.write(Serial.read());
}
