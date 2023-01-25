#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <TinyGPS++.h> 

const String PHONE = "+8801975021104";
const int buttonPin = 10;
SoftwareSerial sim800(3,2);
AltSoftSerial neogps;
TinyGPSPlus gps;

void setup() {

  Serial.begin(115200);
  sim800.begin(9600);
  neogps.begin(9600);
  
  sim800.print("AT+CMGF=1"); 
  delay(1000);

}

void loop() {


}
void sendSmsGPS(String text)
{
  boolean newData = false;
  for (unsigned long start = millis(); millis() - start < 2000;)
  {
    while (neogps.available())
    {
      if (gps.encode(neogps.read()))
      {
        newData = true;
      }
    }
  }
  if (newData)     
  {
    float flat, flon;
    unsigned long age;
    Serial.print("Latitude= "); 
    Serial.print(gps.location.lat(), 6);
    Serial.print(" Longitude= "); 
    Serial.println(gps.location.lng(), 6);
    newData = false;
    delay(300);
    sim800.print("AT+CMGF=1\r");
    delay(1000);
    sim800.print("AT+CMGS=\""+PHONE+"\"\r");
    delay(1000);
    sim800.print("There is too much fire, I can't handle this. Help me ");
    sim800.print("http://maps.google.com/maps?q=loc:");
    sim800.print(gps.location.lat(), 6);
    sim800.print(",");
    sim800.print(gps.location.lng(), 6);
    delay(100);
    sim800.write(0x1A);

  }
}

void makeCall() {
  Serial.begin(9600);
  sim800.println("ATD+8801975021104;"); 
  delay(15000);
  sim800.println("ATH");
  delay(1000);
  sendSmsGPS("Location");
  delay(1000);
}
