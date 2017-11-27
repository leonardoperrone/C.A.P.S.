/*
  Software serial multple serial test
  Receives from the hardware serial, sends to software serial.
  Receives from software serial, sends to hardware serial.
  The circuit:
   RX is digital pin 10 (connect to TX of other device)
   TX is digital pin 11 (connect to RX of other device)
  Note:
  Not all pins on the Mega and Mega 2560 support change interrupts,
  so only the following can be used for RX:
  10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
  Not all pins on the Leonardo and Micro support change interrupts,
  so only the following can be used for RX:
  8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
  created back in the mists of time
  modified 25 May 2012
  by Tom Igoe
  based on Mikal Hart's example
  This example code is in the public domain.
*/
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6); // RX, TX

const int triggerPin = 13;
const int triggerDistance = 60;  //maximum distance between the keychain and the base before alarm


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for native USB port only  
    Serial.println("Hardware Serial Initialized successfully....");
    // set the data rate for the SoftwareSerial port
  mySerial.begin(115200);

  //mySerial.print("AT+START");  //initially used this. It worked but very inconsistently
  mySerial.write("AT+START");
  delay (50);
//  while(!mySerial.available())
//       ; //wait for serial data to be availble
       Serial.println("Software Serial Initialized successfully...");
   pinMode(triggerPin, OUTPUT);
   digitalWrite(triggerPin, LOW);

  }

void loop() { // run over and over
  
       int distance =0;  
       const int counter = 5;

    for (int i = 0; i < counter; i++){
       mySerial.write("AT+RSSI?");
       while(!mySerial.available())
       ; //wait for serial data to be availble

         auto c = mySerial.parseInt();
       if (c<=0){
         c = -1*c;  //convert rssi to positive number
       }
       distance = distance + c;
    }
    distance = distance/counter;
    Serial.print(distance);
    Serial.print("  ");

    if(distance >= triggerDistance){
      digitalWrite(triggerPin, HIGH);
    }else{
      digitalWrite(triggerPin, LOW);
    }
   
  
  //if (Serial.available()) {
  //  mySerial.write(Serial.read());
 // }
}

