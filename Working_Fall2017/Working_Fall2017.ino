/*
  The Super Six:
  EE 595
  Fall 2017

  Members: Lena ,Malcom, Willhelmi, Tony, Kyle, and  Leonardo
*/

#include <SPI.h>  //for SD shield
#include <SD.h>  //for communication with SD shield
#include <DS3231.h>  //for RTC - Real Time Clock
#include <LiquidCrystal.h>  //for LCD 
#include <SoftwareSerial.h> // for BLE
#define SD_ChipSelectPin 53

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);  // initialize the LCD library with the numbers of the interface pins
DS3231  rtc(SDA, SCL);  //Init the DS3231 using the hardware interface
SoftwareSerial mySerial(14, 15); // for Keychain Connection BLE

//Function Prototypes
void audio_play(int const &audio);  //Function to play audio
void saveData();  // write data to SD card
void display(String dspl1, String dspl2, String dspl3);  //display on the LCD

 String kcStatus;
 String spkStatus;
String dataString, dataString1, dataString2, dataString3, dataString4;
int val;  //varible to store temperature reading
int tempPin = A0;  //Analogue pin A0
int sensorThres = 400;  //threshold value for fumes sensor
const int chipSelect = 53;  //Card Select pin
int rssiInput = 49;
int speaker = 48;
bool keyFlag = false;
int keyCounter = 0;
const int counter = 5000;

void setup()
{
  Serial.begin(9600);  // Open serial communications and wait for port to open:
  rtc.begin();  // Initialize the rtc object (the clock module)


  // ******************Uncommented the following thee lines to Set the Date and Time********************
  //
  //  rtc.setDOW(SUNDAY);     // Set Day-of-Week to SUNDAY
  //  rtc.setTime(4, 02, 00);     // Set the time to 12:00:00 (24hr format)
  //  rtc.setDate(26, 11 , 2017);   // Set the date to January 1st, 2014



  pinMode(speaker, OUTPUT); // audio output pin
  pinMode(rssiInput, INPUT); //input for distance readings

  lcd.begin(20, 4);  //Initialize the LCD to 20 collums and 4 rows (set up the LCD's number of columns and rows)
  lcd.print("      C.A.P.S."); // Print a permanent message to the LCD.

  digitalWrite(speaker, HIGH);

  Serial.print("Initializing SD card...");  //see if SD card reader and the card are present and can be initialized:
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("Card failed, or not present");
    return;
  }
  Serial.println("card initialized.");
  mySerial.begin(115200);
  mySerial.write("AT+START");
  delay(50);
}

void loop()
{
  // if rssi digital pin high then
  // mySerial.print("ON");
  // if rssi digital pin low
  // mySerial.print("OFF");

  // check the input if pin 49 and see if it's active
  if ( digitalRead(rssiInput) == HIGH)
  {
    keyFlag = true;
     kcStatus = "OUT";
    
  }
  else
  {
    keyFlag = false;
     kcStatus = "IN ";
  }
  if (keyFlag)
  {
    mySerial.print("ON");

  }
  else
  {
    mySerial.print("OFF");
  }

float avr_temp;
//float cel;
 for(int i =0; i< counter; i++)
  {
  val = analogRead(tempPin);
  float mv = ( val / 1024.0) * 5000;
  float cel = mv / 10;
  float farh = (cel * 9) / 5 + 32;
  avr_temp = avr_temp + farh;
  }
float farh = avr_temp/counter;
 
  

  //dataString = String(rtc.getDOWStr()) + "," + String(rtc.getDateStr()) + "," + String(rtc.getTimeStr()) + "," + String(cel) + "," + "*C" + "," + String(farh) + "," +  "*F"; // convert to CSV for data logging
  dataString1 = String(rtc.getDateStr()) + " " + String(rtc.getTimeStr());
  dataString2 = "Temp is:  " + String(farh) +  "*F" ;
  dataString3 = "KC: " + kcStatus;
  dataString4 = "SP: " + spkStatus;

  //Serial.println(dataString);
  //saveData(); // save to SD card
  Serial.println(dataString);
  //delay(1000);  //delay for this amount of time (1000 == 1 second)

  display(dataString1, dataString2, dataString3, dataString4);  //send data to LCD

  if (farh > 80) {
    digitalWrite(speaker, LOW);
    spkStatus = " bCrying ";
  } else {
    digitalWrite(speaker, HIGH);
    spkStatus =" nSound ";
  }



  //  delay(1000);


}
//End of the main loop  #########################################################



//#######################################################################################

//write to the log file
void saveData()
{

  // now append new data file
  File sensorData = SD.open("data.csv", FILE_WRITE);
  if (sensorData)
  {
    sensorData.println(dataString);
    sensorData.close(); // close the file
    Serial.println(dataString);
  }

  else
  {

    Serial.println("Error writing to file !");
  }

}


//#######################################################################################



//function to display on LCD

void display(String dspl1, String dspl2, String dspl3, String dspl4)
{
  //Print on the LCD
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  //Set cursor to the 3rd row, colume zero
  lcd.setCursor(0, 1);
  lcd.print(dspl1);
  lcd.setCursor(0, 2);
  lcd.print(dspl2);
  lcd.setCursor(0, 3);
  lcd.print(dspl3);
  lcd.setCursor(8, 3);
  lcd.print(dspl4);
}



