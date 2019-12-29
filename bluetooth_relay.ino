#include <SoftwareSerial.h>

int rxPin = 2;
int txPin = 3;
int ledPin = 5;
int relayPin = 7;

String message;

SoftwareSerial bluetooth(rxPin, txPin);

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("Comunicazione inizializzata");

  pinMode(ledPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}
void loop()
{
  if(bluetooth.available()){
    message+=char(bluetooth.read());
    Serial.println(message);
    delay(100);
  }
  if(!bluetooth.available()){
    //bluetooth.write("response from arduino");
    delay(100);
    if(message!=""){
      if(message == "H"){
        digitalWrite(ledPin, HIGH);
        digitalWrite(relayPin, LOW);
        bluetooth.write("H");
        Serial.println("Led On");
        message = "";
      }
      else if(message == "L"){
        digitalWrite(ledPin, LOW);
        digitalWrite(relayPin, HIGH);
        bluetooth.write("L");
        Serial.println("Led OFF");
        message = "";
      }
    }
  }
}
