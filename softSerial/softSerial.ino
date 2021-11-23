#ifdef ESP8266
#include <SoftwareSerial.h>
#define RXD1 14
#define TXD1 12
SoftwareSerial mySerial(RXD1, TXD1);
#elif defined(ESP32)
#define RXD1 16
#define TXD1 17
#endif

void setup()
{
  Serial.begin(115200);
#ifdef ESP8266
  mySerial.begin(9600);
#elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
#endif
}

void loop()
{
#ifdef ESP8266
  if (mySerial.available())
    Serial.write(mySerial.read());
  if (Serial.available())
    mySerial.write(Serial.read());

#elif defined(ESP32)
  if (Serial1.available())
    Serial.write(Serial1.read());
  if (Serial.available())
    Serial1.write(Serial.read());
#endif
}
