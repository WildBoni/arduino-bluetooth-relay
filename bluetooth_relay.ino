#include <SoftwareSerial.h>

// bluetooth
int rxPin = 2;
int txPin = 3;

int ledPin = 5;
int alarmPin = 6;
int relayPin = 7;
int pirPin = 8;
int buzzPin = 9;

String message;


SoftwareSerial bluetooth(rxPin, txPin);

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);
  Serial.println("Comunicazione inizializzata");

  pinMode(ledPin, OUTPUT);
  pinMode (alarmPin, OUTPUT);
  pinMode (pirPin, INPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
}
void loop()
{
  if(bluetooth.available()){
    message = "";
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
      } else if(message == "P"){
        digitalWrite(alarmPin, HIGH);
        bluetooth.write("P");
        if(digitalRead(pirPin) == HIGH) {
          digitalWrite(ledPin, HIGH);
          digitalWrite(relayPin, LOW);
          Serial.println("PIR detection");          
        } else {
          digitalWrite(ledPin, LOW);
          digitalWrite(relayPin, HIGH);
          Serial.println("PIR listening");
        }
        delay(100);
      } else if(message == "Q"){
        digitalWrite(ledPin, LOW);
        digitalWrite(alarmPin, LOW);
        digitalWrite(relayPin, HIGH);
        bluetooth.write("Q");
        Serial.println("PIR OFF");
        message = "";
      }
    }
  }
}
