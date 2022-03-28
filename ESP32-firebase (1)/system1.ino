//Libraries
#include <SPI.h>//https://www.arduino.cc/en/reference/SPI
#include <MFRC522.h>//https://github.com/miguelbalboa/rfid
#include <map>
#include <iostream>
#include <string>

//Constants
#define SS_PIN 5
#define RST_PIN 2

#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
//#define WIFI_SSID "Altibox218028"
//#define WIFI_PASSWORD "ntDkNGjB"

#define WIFI_SSID "Nissanth"
#define WIFI_PASSWORD "12345678"


// Insert Firebase project API Key
#define API_KEY "AIzaSyB2xEC3xlXWnlFNZDy2akIdKfW_Vp6vsLw"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://nett-e5517-default-rtdb.europe-west1.firebasedatabase.app/"

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//Parameters
const int ipaddress[4] = {103, 97, 67, 25};

struct Players
{
  char *Name; 
  byte numbers[4]; 
  int count;
};

Players collecting[] =
{
  {"Highscore/Nissanth",{225, 21, 69, 38}, 0},
  {"Highscore/Elise",{53, 1, 147, 172}, 0},
};

int status;
int testing;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

//Variables
byte nuidPICC[4] = {0, 0, 0, 0};
MFRC522::MIFARE_Key key;
MFRC522 rfid = MFRC522(SS_PIN, RST_PIN);

void setup() {
  //Init Serial USB
  Serial.begin(115200);
  Serial.println(F("Initialize System"));
  //init rfid D8,D5,D6,D7
  SPI.begin();
  rfid.PCD_Init();

  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("ok");
    signupOK = true;
  }
  else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
  readRFID();
}

void toFirebase(char *Name, int count)
{
  if (Firebase.ready() && signupOK) {
    // Write an Int number on the database path test/int
    if (Firebase.RTDB.setInt(&fbdo, Name, count)) {
      Serial.println("PASSED");
      Serial.println("PATH: " + fbdo.dataPath());
      Serial.println("TYPE: " + fbdo.dataType());
    }
    else {
      Serial.println("FAILED");
      Serial.println("REASON: " + fbdo.errorReason());
    }
  }
}

void readRFID(void ) { /* function readRFID */
  ////Read RFID card

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
  // Look for new 1 cards
  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if (  !rfid.PICC_ReadCardSerial())
    return;

  // Store NUID into nuidPICC array
  for (byte i = 0; i < 4; i++) {
    nuidPICC[i] = rfid.uid.uidByte[i];
  }

  Serial.print(F("RFID In dec: "));
  printDec(rfid.uid.uidByte, rfid.uid.size);
  Serial.println();

  // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

}

void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
  
  givePoints();
  /*
  for (int i = 0; i < 4; i++)
  {
    Serial.print(nuidPICC[i]);
  }
  compareByte(nuidPICC, collecting[1].numbers);
  */
}

int compareByte(byte *buffer1, byte *buffer2)
{
  int check = 0;
  for (int i = 0; i < 4; i++)
  {
    if (buffer1[i] == buffer2[i])
    {
      check += 1;
    }
  }

  if (check == 4)
  {
    Serial.print("its a match");
    return 1;
  }

  else
  {
    Serial.print("Its not a match");
    return 0;
  }
}

void givePoints()
{
  for (int i = 0; i < 2; i++)
  {
    if (compareByte(nuidPICC, collecting[i].numbers) == 1)
    {
      collecting[i].count += 1;  
      toFirebase(collecting[i].Name, collecting[i].count);
    }
  }
}
