#define RXD2 16
#define TXD2 17

//Set the ADDRESS ID of Lora module 
#define CH_ID 2

String Message = "Hello from ESP32";

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);
}

void loop() {
  if (Serial.available())
    Serial1.write(Serial.read());

  if (Serial1.available()) {
    String incomming = Serial1.readString();
    if (incomming.length() <= 10)   // Show only OK and error messages
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
      
      digitalWrite(2, HIGH);
      delay(2000);
      digitalWrite(2, LOW);
    }
  }

  // When the button is pressed send the message to other module
  if (digitalRead(0) == LOW) {
    delay(1000);
    String myString = "AT+SEND=" + String(CH_ID) + "," + String(Message.length()) + "," + Message + "\r\n";
    char* buf = (char*) malloc(sizeof(char) * myString.length() + 1);
    myString.toCharArray(buf, myString.length() + 1);
    Serial1.write(buf);
    free(buf);
  }
}
