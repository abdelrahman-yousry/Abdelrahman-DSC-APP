//_______________________________________________________________//
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
//_______________________________________________________________//
#define FIREBASE_HOST "covidoximeter.firebaseio.com"
#define FIREBASE_AUTH "zsOtL8GqoD0XUt348mxcV5xHC6r4IB67lwkj68sn"
#define WIFI_SSID "ahmed 2"
#define WIFI_PASSWORD "100200300"
//_______________________________________________________________//
String pulse;
String oxygen;
//**//
FirebaseData firebaseData;
SoftwareSerial SerialInput(D6, D5);
//_______________________________________________________________//
void setup()
{
  Serial.begin(9600);
  SerialInput.begin(9600);
  //**//
  WiFi.disconnect();
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }  
  Serial.println();
  Serial.print("Connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
//_______________________________________________________________//
void loop()
{
  if (SerialInput.available() > 0)
  {
    //00,00
    String dataLine = SerialInput.readStringUntil('*');
    //
    Serial.println(dataLine);
    for (int i = 0; i < dataLine.length(); i++)
    {
      if (dataLine.substring(i, i + 1) == ",")
      {
        pulse = dataLine.substring(0, i);
        oxygen= dataLine.substring(i + 1);
        break;
      }
    }
    if (isValidNumber(pulse))
    {
      int p = pulse.toInt();
      Firebase.setInt(firebaseData, "data/pulse", p);
    }
    if (isValidNumber(oxygen))
    {
      int s = oxygen.toInt();
      Firebase.setInt(firebaseData, "data/spo", s);
    }
  }
}
//_______________________________________________________________//
boolean isValidNumber(String str)
{
  for(byte i = 0; i < str.length(); i++)
   {
      if (isDigit(str.charAt(i))) 
      {
        return true;
      }
   }
   return false;
} 
//_______________________________________________________________//
