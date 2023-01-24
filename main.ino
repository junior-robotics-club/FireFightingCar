#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
int sensor = 4;
void setup()
{

  pinMode(sensor , INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600);
  
  Serial.println("Initializing...");
  delay(1000);
}

void loop()
{
  int state = digitalRead(sensor);
  if(state == 0)
  {
      sendsms();
     
    
  }


}



void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}



void makecall()
{
  Serial.println("calling..");
  mySerial.println("AT");
  updateSerial();
  mySerial.println("ATD+ +8801975021104;");
  updateSerial();
  delay(20000);
  mySerial.println("ATH");
  updateSerial();
}

void sendsms()
{

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+8801975021104\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  mySerial.print("detected"); //text content
  updateSerial();
  mySerial.write(26);
  delay(500);
  makecall();

}
