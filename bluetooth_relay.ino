#include <SoftwareSerial.h>

int rxPin = 2;
int txPin = 3;
int ledPin = 5;
int relayPin = 7;

String message;
volatile byte relayState = LOW;

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
    delay(300);
  }
  if(!bluetooth.available()){
    //bluetooth.write("response from arduino");
    if(message!=""){
      if(message == "H"){
        digitalWrite(ledPin, HIGH);
        digitalWrite(relayPin, LOW);
        Serial.println("Led On");
        delay(2000);
        message = "";
      }
      else if(message == "L"){
        digitalWrite(ledPin, LOW);
        digitalWrite(relayPin, HIGH);
        Serial.println("Led OFF");
        delay(2000);
        message = "";
      }
    }
  }
}
