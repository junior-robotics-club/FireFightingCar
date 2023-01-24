#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 2); 
void setup()
{
 
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

}

void loop()
{
}

void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());
  }
}

void makecall()
{


  mySerial.println("AT"); 
  updateSerial();
  mySerial.println("ATD+ +ZZxxxxxxxxxx;");
  updateSerial();
  delay(20000);
  mySerial.println("ATH"); //hang up
  updateSerial();
}
