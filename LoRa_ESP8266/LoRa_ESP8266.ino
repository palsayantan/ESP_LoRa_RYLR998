#include <SoftwareSerial.h>

#define RXD2 14
#define TXD2 12

SoftwareSerial mySerial(RXD2, TXD2);

//Set the ADDRESS ID of Lora module 
#define CH_ID 1

String Message = "Hello from ESP8266";

void setup()
{
  Serial.begin(115200);
  mySerial.begin(9600);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() {
  if (Serial.available())
    mySerial.write(Serial.read());

  if (mySerial.available()) {
    String incomming = mySerial.readString();
    if (incomming.length() <= 10)
      Serial.println(incomming);
    else {
      String channel_ID = incomming.substring(incomming.indexOf('=') + 1, incomming.indexOf(','));
      Serial.println("Channel ID : " + channel_ID);

      String str = incomming.substring(incomming.indexOf(',') + 1);

      String msgLength = str.substring(0, str.indexOf(','));
      Serial.println("Message Length : " + msgLength);

      String str2 = str.substring(str.indexOf(',') + 1);

      String message = str2.substring(0, str2.indexOf(','));
      Serial.println("Message : " + message);
      
      digitalWrite(2, LOW);
      delay(2000);
      digitalWrite(2, HIGH);
    }
  }

  // When the button is pressed send the message to other module
  if (digitalRead(0) == LOW) {
    delay(1000);
    String myString = "AT+SEND=" + String(CH_ID) + "," + String(Message.length()) + "," + Message + "\r\n";
    char* buf = (char*) malloc(sizeof(char) * myString.length() + 1);
    myString.toCharArray(buf, myString.length() + 1);
    mySerial.write(buf);
    free(buf);
  }
}
